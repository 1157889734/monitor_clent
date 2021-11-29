#ifndef __MODESET_H_INCLUDED__
#define __MODESET_H_INCLUDED__

#ifdef __cplusplus
extern "C"{
#endif

#include <xf86drmMode.h>

struct sp_dev;
struct sp_crtc;
struct sp_bo;

int initialize_screens(struct sp_dev *dev);
struct sp_plane *get_sp_plane(struct sp_dev *dev, struct sp_crtc *crtc);
void put_sp_plane(struct sp_plane *plane);
int set_sp_plane(struct sp_dev *dev, struct sp_plane *plane, struct sp_crtc *crtc, struct sp_bo *bo,
                 int x, int y, int nw, int nh);

#ifdef __cplusplus
}
#endif

#endif /* __MODESET_H_INCLUDED__ */
