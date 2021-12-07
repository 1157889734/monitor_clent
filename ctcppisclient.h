#ifndef CTCPPISCLIENT_H
#define CTCPPISCLIENT_H

#ifdef __cplusplus
extern "C"{
#endif /* End of #ifdef __cplusplus */
#include "log.h"
#include <arpa/inet.h>
#include <pthread.h>
#include "types.h"
#include "state.h"


#define         TX_MSG_HEARTBEAT                  0x01			//接受心跳
#define         TX_MSG_ADDTEXT                    0x05		    //视频叠加字符报文
#define         TX_MSG_RECV_PIS                   0x04			//动车组受电弓视频监控系统与PIS系统的通信报文
#define         TX_MSG_HEARTBEAT_FEEDBACK         0x51		    //反馈心跳

#define MAX_SERVER_NUM 4

extern int g_iIsPBD;
typedef  unsigned long PIS_HANDLE;
typedef  unsigned long Clent_PIS_HANDLE;
#define MSG_START_FLAG 0xFF

enum _E_PIS_CONNECT_STATUS
{
    E_PIS_STATUS_UNCONNECT	= 0,
    E_PIS_STATUS_CONNECT = 1
};
typedef struct _T_PIS_PACKET
{
    PIS_HANDLE PHandle;
    unsigned char ucMsgCmd;
    int iMsgDataLen;
    char *pcMsgData;
} __attribute__((packed)) T_PIS_PACKET, *PT_PIS_PACKET;

typedef struct _T_PMSG_PACKET_LIST
{
    T_PIS_PACKET tPkt;
    struct _T_PMSG_PACKET_LIST *next;
} __attribute__((packed)) T_PMSG_PACKET_LIST;

typedef struct _T_PMSG_QUEUE
{
    T_PMSG_PACKET_LIST *ptFirst, *ptLast;
    INT32 iQueueType;
    INT32 iPktCount;
    pthread_mutex_t *pMutex;
} __attribute__((packed)) T_PMSG_QUEUE, *PT_PMSG_QUEUE;

typedef struct _T_PIS_CONN_INFO
{
    int iSockfd;
    int iConnectStatus;
    int iThreadRunFlag;
    int iServPort;
    char acIpAddr[20];

    pthread_t ThreadHandle;
    pthread_mutex_t	tPmsgMutex;

} T_PIS_CONN_INFO, *PT_PIS_CONN_INFO;



typedef struct _TimeInfo
{
    INT16		Year;					    // 年
    INT8		Month;					    // 月
    INT8		Day;					        // 日
    INT8		Hour;					    // 时
    INT8		Minute;					    // 分
    INT8		Second;					    // 秒
}TimeInfo;


//校时报文
typedef struct  _Msg_TimingInfo
{
    TimeInfo	dateTime;					    //时间
}Msg_TimingInfo;

// 最新标准PIS协议
typedef struct  _Msg_RecvPISInfoEx
{
    TimeInfo	dateTime;					    //时间
    INT16        Speed;						    // 速度
    INT8        TrainNumber[11];				    // 车次
    INT16        Mileage;					    // 区间里程数
    INT8		BeginStation[3];
    INT8		EndStation[3];
    INT8        IntervalInfo[24];               // 区间信息
}Msg_RecvPISInfoEx;


//动车组受电弓视频监控系统与PIS系统的通信报文
typedef struct  _Msg_RecvPISInfo
{
    TimeInfo	dateTime;					    //时间
    INT16        Speed;						    // 速度
    INT8        TrainNumber[7];				    // 车次
    INT16        Mileage;					    // 区间里程数
    INT8        IntervalInfo[30];               // 区间信息
}Msg_RecvPISInfo;

//易程特殊类型转发报文
typedef struct  _Msg_RecvPISYCInfo
{
    INT8	    CommandType;					    //命令类型
    INT8        DateFeedBack;						//数据
    INT16       Speed;						    // 速度
    INT8        Effective;							//数据有效性
    INT8        Mileage[4];					    // 区间里程数
    INT8        Time[3];						  //时间，按16进制值表示 如 0x23 0x58 0x59 表示 23时58分59秒
    INT8        TrainNumber1[4];				    // 车次字母信息
    INT8        TrainNumber2[3];				    // 车次数字信息	 0x00 0x02 0x11	  表示数字位为211
    INT8        BeginStation[3];                    //开始站点代码 01 01 01 代表111
    INT8        EndStation[3];						//开始站点代码 01 02 02 代表122
}Msg_RecvPISYCInfo;


// 视频字符叠加报文，主要为了获取车次信息
typedef struct _Video_ADDTextInfo
{
    TimeInfo	dateTime;					    //时间
    INT8        Speed[2];						// 速度
    INT8        TrainNumber[7];				    // 车次
    INT8		CarriageNumber;					// 车厢号
    INT8		PantoPos;						// 受电弓位置号 20151023
    INT8        Mileage[2];					    // 区间里程数
    INT8        IntervalInfo[30];               // 区间信息
}Video_ADDTextInfo;



typedef struct _NCIP_HEADER{
    INT8        HEARD;						// 报文头 ff
    INT8		FrameType;					// 报文类型
    INT8        DataLenth[2];				    // 报文长度
}TCP_HEADER;

typedef struct _NCIP_PIS_HEADER{
    INT8        HEARD[2];						// 报文头 ff
    INT8        DataLenth;				    // 报文长度
}TCP_PIS_HEADER;


void ParsePisYCInfo(Msg_RecvPISYCInfo  RecvPISInfo);
void ClearPisInfo();
void ParsePisInfo(Msg_RecvPISInfo  RecvPISInfo);
void ParsePisInfoEx(Msg_RecvPISInfoEx RecvPISInfo);
PIS_HANDLE PIS_CreateConnect(char *pcIpAddr, int iPort);
int PIS_DestroyConnect(PIS_HANDLE pMsgHandle);
int PIS_SendRawData(PIS_HANDLE pMsgHandle, char *pcData, int iDataLen);
void DestroyPisTcpSocket(int iSockfd);
int CreatePisTcpSocket(char *pcIpAddr, int iPort);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif // CTCPPISCLIENT_H
