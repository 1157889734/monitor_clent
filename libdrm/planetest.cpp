#include "planetest.h"
#include "mutex.h"

static int s_drm_init_count = 0;
static volatile PDRM_INFO s_drm_info = NULL;


PDRM_INFO DRM_Init(int x, int y, int w, int h)
{
    int ret;
    int crtc = 1, planeIndex = 3, card = 0;
    RGA_HANDLE rgaHandle;
    PDRM_INFO drm_info = NULL;
    struct sp_dev *dev;
    struct sp_crtc *test_crtc;
    struct sp_plane *plane = NULL;
    if(s_drm_info != NULL)
    {
        s_drm_init_count++;
        return s_drm_info;
    }
    dev = create_sp_dev(card);
    if (!dev) {
        printf("Failed to create sp_dev\n");
        goto err;
    }

    if (crtc >= dev->num_crtcs) {
        printf("Invalid crtc %d (num=%d)\n", crtc, dev->num_crtcs);
        goto err;
    }

    ret = initialize_screens(dev);
    if (ret) {
        printf("Failed to initialize screens\n");
        goto err;
    }

    test_crtc = &dev->crtcs[crtc];
    plane = &dev->planes[planeIndex];
    if (!plane) {
        printf("no unused planes available\n");
        goto err;
    }
    if (is_supported_format(plane, DRM_FORMAT_NV12))
        printf("  is_supported_format DRM_FORMAT_NV12 \n");
    else
        printf("  is_supported_format error \n");

    plane->format = DRM_FORMAT_NV12;
    memset(plane->bo, 0, sizeof(plane->bo));

    ret = drmModeObjectSetProperty(dev->fd, plane->plane->plane_id, DRM_MODE_OBJECT_PLANE, plane->zpos_pid, 7);

    w = CODEC_ALIGN(w, 16);
    h = CODEC_ALIGN(h, 16);
    plane->bo[0] = create_sp_bo(dev, w, h, 16, plane->format, 0);
    if (!plane->bo[0]) {
        printf("failed to create plane bo\n");
        goto err;
    }
    set_sp_plane(dev, plane, test_crtc, plane->bo[0], x, y, w, h);

    if(plane->bo[0]->format == DRM_FORMAT_NV12)
    {
        memset(plane->bo[0]->map_addr, 0x10, plane->bo[0]->pitch*plane->bo[0]->height);
        memset(plane->bo[0]->map_addr+plane->bo[0]->pitch*plane->bo[0]->height, 0x80,
                plane->bo[0]->size-plane->bo[0]->pitch*plane->bo[0]->height);
    }

    drm_info = new DRM_INFO();
    drm_info->x = x;
    drm_info->y = y;
    drm_info->w = w;
    drm_info->h = h;
    drm_info->dev = dev;
    drm_info->use_crtc = test_crtc;
    drm_info->plane = plane;

    rgaHandle = rga_create(w, h);
    if(!rgaHandle)
    {
        printf("rga_create error \n");
    }
    drm_info->iShow = 1;
    drm_info->rgaHandle = rgaHandle;

    s_drm_info = drm_info;
    printf("DRM_Init ok \n");
    return drm_info;
err:
    return NULL;
}
int DRM_UnInit(PDRM_INFO drm_info)
{
    int i;
    struct sp_bo *bo;
    s_drm_init_count--;
    if(s_drm_init_count <= 0)
    {
        for(i = 0; i < SP_PLANE_BO_NUM_MAX; i++)
        {
            bo = s_drm_info->plane->bo[i];
            if(bo)
            {
                free_sp_bo(bo);
            }
        }
        destroy_sp_dev(s_drm_info->dev);

        if(s_drm_info->rgaHandle)
        {
            rga_destroy(s_drm_info->rgaHandle);
            s_drm_info->rgaHandle = NULL;
        }

        delete s_drm_info;
        s_drm_info = NULL;
    }
    return 0;
}
int DRM_Display(MppFrame frame)
{
    int err, i;
    struct sp_bo *bo;
    int width, height, h_stride, v_stride;
    MppBuffer buffer    = NULL;
    unsigned char* base = NULL;
    if(s_drm_info == NULL)
    {
        return -1;
    }

    s_drm_info->locker.Lock();
    RGA_HANDLE rgaHandle = s_drm_info->rgaHandle;
    MppFrame  dstFrame  = NULL;
    err = rga_blit(rgaHandle, frame, &dstFrame);
    if(err < 0)
    {
        s_drm_info->locker.Unlock();
        return -1;
    }
    err = mpp_frame_get_errinfo(dstFrame) | mpp_frame_get_discard(dstFrame);
    if (err)
    {
        printf("get err info %d discard %d, go back.\n",
               mpp_frame_get_errinfo(dstFrame),
               mpp_frame_get_discard(dstFrame));
        s_drm_info->locker.Unlock();
        return -1;
    }

    h_stride = mpp_frame_get_hor_stride(dstFrame);
    v_stride = mpp_frame_get_ver_stride(dstFrame);
    width  =   mpp_frame_get_width(dstFrame);
    height =   mpp_frame_get_height(dstFrame);
    buffer = mpp_frame_get_buffer(dstFrame);
    bo = s_drm_info->plane->bo[0];
//    printf("w:%d, h:%d,h_stride:%d,v_stride:%d, bo->pitch:%d, bo->height:%d \n", width, height, h_stride, v_stride,
//           bo->pitch, bo->height);
    if(h_stride > bo->pitch || height > bo->height)
    {
        printf("h_stride > bo->pitch || height > bo->height \n");
        s_drm_info->locker.Unlock();
        return -1;
    }
    base = (RK_U8 *)mpp_buffer_get_ptr(buffer);
    uint8_t *luma;
    uint8_t *chroma;
    for (i = 0; i < height; i++)
    {
        luma = (uint8_t *)bo->map_addr + i * bo->pitch;
        memcpy(luma, base + i*h_stride, width);
    }
    for (i = 0; i < height / 2; i++)
    {
        chroma = (uint8_t *)bo->map_addr + (i + height) * bo->pitch;
        memcpy(chroma, base + (i+height)*h_stride, width);
    }
    s_drm_info->locker.Unlock();
    return 0;
}

int DRM_SetRect(int x, int y, int w, int h)
{
    int iRet = -1;
    PDRM_INFO pdrm_info = s_drm_info;
    if(pdrm_info == NULL)
    {
        return -1;
    }
    pdrm_info->locker.Lock();
    s_drm_info = NULL;
    w = CODEC_ALIGN(w, 16);
    h = CODEC_ALIGN(h, 16);
    if(x != pdrm_info->x || y != pdrm_info->y ||
            w != pdrm_info->w || h != pdrm_info->h)
    {
        pdrm_info->x = x;
        pdrm_info->y = y;
        pdrm_info->w = w;
        pdrm_info->h = h;
//        printf("x:%d, %d, %d, %d \n", x, y, w, h);

        iRet = rga_set_cur_frame(pdrm_info->rgaHandle, w, h);
        if(iRet < 0)
        {
            printf("%s--rga_set_cur_frame err \n", __FUNCTION__);
        }

        struct sp_dev *dev = pdrm_info->dev;
        struct sp_crtc *test_crtc = pdrm_info->use_crtc;
        struct sp_plane *plane = pdrm_info->plane;
        struct sp_bo *bo = plane->bo[0];
        if(bo)
        {
            free_sp_bo(bo);
            bo = create_sp_bo(dev, w, h, 16, plane->format, 0);
            if (!bo) {
                printf("failed to create plane bo\n");
                goto err;
            }
//            printf("bo->pith:%d \n", bo->pitch);
            set_sp_plane(dev, plane, test_crtc, bo, x, y, w, h);
            if(bo->format == DRM_FORMAT_NV12)
            {
                memset(bo->map_addr, 0x10, bo->pitch * bo->height);
                memset(bo->map_addr + bo->pitch * bo->height, 0x80,
                        bo->size - bo->pitch * bo->height);
            }
            plane->bo[0] = bo;
        }
    }
    s_drm_info = pdrm_info;
    pdrm_info->locker.Unlock();
    return 0;
err:
    s_drm_info = pdrm_info;
    pdrm_info->locker.Unlock();
    return -1;
}

int DRM_Show(int iShow)
{
    PDRM_INFO pdrm_info = s_drm_info;
    if(pdrm_info == NULL)
    {
        return -1;
    }
    if(pdrm_info->iShow == iShow)
    {
        return -1;
    }
    pdrm_info->locker.Lock();
    s_drm_info = NULL;
    struct sp_dev *dev = pdrm_info->dev;
    struct sp_crtc *test_crtc = pdrm_info->use_crtc;
    struct sp_plane *plane = pdrm_info->plane;
    struct sp_bo *bo = plane->bo[0];

    pdrm_info->iShow = iShow;
    if(1 == iShow)
    {
        set_sp_plane(dev, plane, test_crtc, bo, pdrm_info->x, pdrm_info->y, pdrm_info->w, pdrm_info->h);
    }
    else
    {
        set_sp_plane(dev, plane, test_crtc, bo, -1280, 0, pdrm_info->w, pdrm_info->h);
    }
    s_drm_info = pdrm_info;
    pdrm_info->locker.Unlock();

    return 0;
}

int DRM_FillBcakColor(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
    PDRM_INFO pdrm_info = s_drm_info;
    if(pdrm_info == NULL)
    {
        return -1;
    }
    pdrm_info->locker.Lock();
    s_drm_info = NULL;
    struct sp_plane *plane = pdrm_info->plane;
    struct sp_bo *bo = plane->bo[0];
    fill_bo(bo, a, r, g, b);
    s_drm_info = pdrm_info;
    pdrm_info->locker.Unlock();
}
