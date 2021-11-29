#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <errno.h>
#include        <unistd.h>
#include        <sys/types.h>
#include        <sys/stat.h>
#include        <fcntl.h>
#include        <pthread.h>

#include "log.h"


static int g_iLogCount = 0;
static int g_iSyncFlag = 0;
static pthread_mutex_t	g_tLogMutex;

int CopyFile(char *pcDstFile, char *pcSrcFile)
{
    FILE *fpr = NULL;
    FILE *fpw = NULL;
    int iLen = 0;
    int iFileLen = 0;
    int iSize = 0;
    char acBuf[4096];
    
    if (NULL == pcDstFile || NULL == pcSrcFile)
    {
        return -1;	
    }
    fpr = fopen(pcSrcFile, "rb");
    if (fpr == NULL)
    {
        perror("open read file:");
        return -1;
    }

    fpw = fopen(pcDstFile, "wb");
    if (fpw == NULL)
    {
        printf("[%s]open write file %s\n", __FUNCTION__, pcDstFile);
        perror("open write file error:");
        
        return -1;
    }

    while (1)
    {
        iLen = fread(acBuf, 1, sizeof(acBuf), fpr);
        if (iLen <= 0)
        {
            printf("read file over\n");
            break;
        }
        iSize = fwrite(acBuf, 1, iLen, fpw);
        if (iSize != iLen)
        {
            perror("wirte file error:");
            fclose(fpr);
            fclose(fpw);
            return -1;
        }
        iFileLen += iLen;
    }
    fflush(fpw);
    fsync(fileno(fpw));
    fclose(fpr);
    fclose(fpw);
    
    return iFileLen;
}

int LOG_Init(void)
{
    FILE *fp = NULL;
    char acBuf[256];
    pthread_mutexattr_t mutexattr;
    
    fp = fopen(LOG_FILE_NAME, "rb");
    if (NULL == fp)
    {
        fp = fopen(LOG_FILE_NAME, "ab");

    }

    if (NULL == fp)
    {
        printf("open file %s error\n", LOG_FILE_NAME);
        perror(":");
        return -1;
    }
	
    while (fgets(acBuf, sizeof(acBuf), fp))
    {
        g_iLogCount ++;	
    }
    fclose(fp);

    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_TIMED_NP);
    pthread_mutex_init(&g_tLogMutex, &mutexattr);
    pthread_mutexattr_destroy(&mutexattr);
        
    return 0;
}

void LOG_UnInit(void)
{
    pthread_mutex_destroy(&g_tLogMutex);
}

int LOG_WriteLog(PT_LOG_INFO ptLog)
{
    FILE *pFile, *pNewFile;
    //char acLogType[24];
    char acLogTime[24];
    char acBuf[256];
    char acTmpName[64];
    int iFd;
    int iLogCount = 0;
    
    if (NULL == ptLog)
    {
        printf("[%s] param error\n", __FUNCTION__);
        return -1;
    }
    
    struct	tm	ptr;
    time_t tTime = time(NULL);

    if (localtime_r(&tTime, &ptr) == NULL)
    {
        return(-1);
    }

    snprintf(acLogTime, sizeof(acLogTime), "%02d%02d%4d %02d:%02d:%02d", 
             ptr.tm_mday, ptr.tm_mon+1, (ptr.tm_year+1900), 
             ptr.tm_hour, ptr.tm_min, ptr.tm_sec);
    
    pthread_mutex_lock(&g_tLogMutex);
    /* <daymonyear hour:min:second> log description */
    if (g_iLogCount < MAX_LOG_NUMBER + 1000)
    {
        pFile = fopen(LOG_FILE_NAME, "ab");
        if (NULL == pFile)
        {
            printf("[%s] open file %s error\n", __FUNCTION__, LOG_FILE_NAME);
            perror(":");
            pthread_mutex_unlock(&g_tLogMutex);
            return -1;
        }
       // fseek(pFile, 0, SEEK_END);
        if (LOG_TYPE_EVENT == ptLog->iLogType)
        {
            snprintf(acBuf, sizeof(acBuf), "e%s %s\r\n", 
                         acLogTime, ptLog->acLogDesc);
        }
        else
        {
            snprintf(acBuf, sizeof(acBuf), "s%s %s\r\n", 
                         acLogTime, ptLog->acLogDesc);
        }
        //printf("[%s] %s\n", __FUNCTION__, acBuf);
        fputs(acBuf, pFile);
        fflush(pFile);
        fclose(pFile);
        g_iLogCount ++;
        
        if (0 == (g_iLogCount % 20))
        {
            //snprintf(acTmpName, sizeof(acTmpName), "%s~", LOG_FILE_NAME);
            //CopyFile(acTmpName, LOG_FILE_NAME);
        }
    }
    else
    {
        // delete the oldest 100 logs
        pFile = fopen(LOG_FILE_NAME, "rb");
        if (NULL == pFile)
        {
            printf("[%s] open file %s error\n", __FUNCTION__, LOG_FILE_NAME);
            perror(":");
            pthread_mutex_unlock(&g_tLogMutex);
            return -1;
        }
        snprintf(acTmpName, sizeof(acTmpName), "%s~", LOG_FILE_NAME);
        pNewFile = fopen(acTmpName, "wb");
        if (NULL == pNewFile)
        {
            printf("[%s] open file %s error\n", __FUNCTION__, acTmpName);
            perror(":");
            fclose(pFile);
            pthread_mutex_unlock(&g_tLogMutex);
            return -1;
        }
        while (fgets(acBuf, sizeof(acBuf), pFile))
        {
            iLogCount ++;
            if (1000 == iLogCount)
            {
                break;	
            }
        }
        g_iLogCount -= 1000;
        while (fgets(acBuf, sizeof(acBuf), pFile))
        {
            fputs(acBuf, pNewFile);	
        }
        printf("[%s] Log over max count, and delete 1000\n", __FUNCTION__);

        if (LOG_TYPE_EVENT == ptLog->iLogType)
        {
            snprintf(acBuf, sizeof(acBuf), "e%s %s\r\n", 
                         acLogTime, ptLog->acLogDesc);
        }
        else
        {
            snprintf(acBuf, sizeof(acBuf), "s%s %s\r\n", 
                         acLogTime, ptLog->acLogDesc);
        }
		
        //printf("[%s] %s\n", __FUNCTION__, acBuf);
        fputs(acBuf, pNewFile);
        
        iFd = fileno(pNewFile);	
        fsync(iFd);
        fclose(pNewFile);
        fclose(pFile);
        //rename(acTmpName, LOG_FILE_NAME);
        CopyFile(LOG_FILE_NAME, acTmpName);
        g_iLogCount ++;
    }
    g_iSyncFlag ++;

    pthread_mutex_unlock(&g_tLogMutex);
	
    return 0;
}

int LOG_FsyncFile(void)
{
    int iFd = 0;
    
    if (g_iSyncFlag)
    { 
        pthread_mutex_lock(&g_tLogMutex);
        iFd = open(LOG_FILE_NAME, O_RDWR);
        if (iFd < 0)
        {
            return -1;
        }
        fsync(iFd);
        close(iFd);
        g_iSyncFlag = 0;
        pthread_mutex_unlock(&g_tLogMutex);
    }
    return 0;
}

