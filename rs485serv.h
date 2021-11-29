#ifndef  __RS485_SERV_H__
#define __RS485_SERV_H__

#ifdef __cplusplus
extern "C"{
#endif /* End of #ifdef __cplusplus */

typedef  unsigned long PRS485_HANDLE;

typedef struct _T_RS485_PACKET
{
    int iDataLen;
    char *pcData;
} __attribute__((packed)) T_RS485_PACKET, *PT_RS485_PACKET;

PRS485_HANDLE RS485_CreateConnect();
int RS485_DestroyConnect(PRS485_HANDLE pRs485Handle);
int RS485_GetDataFromRs485Queue(PRS485_HANDLE pRs485Handle, PT_RS485_PACKET ptPkt);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */


#endif
