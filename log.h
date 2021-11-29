#ifndef  _LOG_H_
#define  _LOG_H_

#ifdef __cplusplus
extern "C"{
#endif /* End of #ifdef __cplusplus */

#define LOG_FILE_NAME "/home/data/sys.log"

#define	MAX_LOG_NUMBER	5000

#define MAX_LOG_DESC_LEN 256

typedef enum _E_LOG_TYPE
{
    LOG_TYPE_SYS    = 0,
    LOG_TYPE_EVENT  = 1,
    LOG_TYPE_OTHER  = 2
}E_LOG_TYPE;

typedef struct _T_LOG_INFO
{
    int iLogType;  /* 0: system log, 1: event log, 2: other log */
    char acLogDesc[MAX_LOG_DESC_LEN];
}T_LOG_INFO, *PT_LOG_INFO;

int LOG_Init(void);
void LOG_UnInit(void);
int LOG_WriteLog(PT_LOG_INFO ptLog);
int LOG_FsyncFile(void);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif
