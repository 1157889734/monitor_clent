#include "ctcppisclient.h"
#include "log.h"
#include "debug.h"
#include "stdlib.h"
#define RECV_BUF_LEN 1024

int g_iIsPBD = 0;

char g_strTrainNumber;
int g_iCarriageNums;

typedef struct _T_TIME
{
    INT16 i16Year;  //年
    INT8 i8Mon;     //月
    INT8 i8day;     //天
    INT8 i8Hour;    //时
    INT8 i8Min;    //分
    INT8 i8Sec;    //秒
} __attribute__((packed))T_TIME, *PT_TIME;

typedef struct _T_PIS_MSG_INFO
{
    T_TIME tTime;     //时间
    WORD  wSpeed;         //区间速度
    char  cTrainNum[7];  //车次号
    char  CarriageNumber;					// 车厢号
    char  PantoPos;						// 受电弓位置号 20151023
    WORD  wDistance;      //区间距离
    char  cIntervalInfo[30]; //区间信息
} __attribute__((packed))T_PIS_MSG_INFO, *PT_PIS_MSG_INFO;


void init(void)
{
    T_TRAIN_CONFIG tTrainConfigInfo;
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);

    for (int i = 0; i < tTrainConfigInfo.iNvrServerCount; i++)
    {
        for (int j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
         {
                g_iCarriageNums++;
         }
    }
    g_iIsPBD = 0;
}


int CreatePisTcpSocket(char *pcIpAddr, int iPort)
{
    int iSockfd = 0;
    int iRet = 0;
    struct sockaddr_in servaddr;
    struct timeval tv_out;

    iSockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (iSockfd < 0)
    {
        perror("socket error:");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(pcIpAddr);
    servaddr.sin_port = htons(iPort);

    iRet = connect(iSockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (iRet < 0)
    {
//        printf("sockfd %d connect addr %s  port %d error\n", iSockfd, servaddr.sin_addr.s_addr, servaddr.sin_port);
       // perror(":");
        close(iSockfd);
        return -1;
    }

    tv_out.tv_sec = 5;
    tv_out.tv_usec = 500;
    setsockopt(iSockfd, SOL_SOCKET, SO_RCVTIMEO, &tv_out, sizeof(tv_out));
    setsockopt(iSockfd, SOL_SOCKET, SO_SNDTIMEO, &tv_out, sizeof(tv_out));

    return iSockfd;

}
void DestroyPisTcpSocket(int iSockfd)
{
   close(iSockfd);
}

int PIS_SendRawData(PIS_HANDLE pMsgHandle, char *pcData, int iDataLen)
{
    PT_PIS_CONN_INFO ptPmsgConnInfo = (PT_PIS_CONN_INFO)pMsgHandle;
    int iRet = 0;

    if ((NULL == ptPmsgConnInfo) || (NULL == pcData) || (iDataLen <= 0))
    {
        return -1;
    }

    if (E_PIS_STATUS_CONNECT != ptPmsgConnInfo->iConnectStatus)
    {
        return -1;
    }
    pthread_mutex_lock(&ptPmsgConnInfo->tPmsgMutex);
    iRet = send(ptPmsgConnInfo->iSockfd, pcData, iDataLen, 0);
    pthread_mutex_unlock(&ptPmsgConnInfo->tPmsgMutex);

    return iRet;
}




int PIS_DestroyConnect(PIS_HANDLE pMsgHandle)
{
    PT_PIS_CONN_INFO ptPmsgConnInfo = (PT_PIS_CONN_INFO)pMsgHandle;

    if (NULL == ptPmsgConnInfo)
    {
        return -1;
    }
    ptPmsgConnInfo->iThreadRunFlag = 0;

    // join thread exit
    if (ptPmsgConnInfo->ThreadHandle)
    {
        pthread_join(ptPmsgConnInfo->ThreadHandle, NULL);
    }

    free(ptPmsgConnInfo);
    ptPmsgConnInfo = NULL;

    return 0;
}


void *PisProcessThread(void *arg)
{
    const int c_iBufLen =1024;
    unsigned char *pcRecvBuf = NULL;
    unsigned char *pcLeaveBuf = NULL;
    unsigned char *pcMsgBuf = NULL;
    int iBufLen = RECV_BUF_LEN;
    int iPreLeaveLen = 0, iLeaveLen = 0, iRecvLen = 0;

//    unsigned char pcRecvBuf[RECV_BUF_LEN];
    int iSocket = 0;
    int iOffset = 0;
    fd_set	tAllSet, tTmpSet;
    T_LOG_INFO tLogInfo;
    struct timeval tv;
    int iHearCount = 0;
//    int iRecvLen = 0;



    T_PIS_CONN_INFO *ptPmsgConnInfo = (T_PIS_CONN_INFO *)arg;
//    PIS_HANDLE pMsgHandle = (PIS_HANDLE)arg;

    if (NULL == ptPmsgConnInfo)
    {
        return NULL;
    }


    pcRecvBuf = (unsigned char *)malloc(iBufLen);
    if (NULL == pcRecvBuf)
    {
        return NULL;
    }
    memset(pcRecvBuf, 0, iBufLen);

    pcLeaveBuf = (unsigned char *)malloc(iBufLen);
    if (NULL == pcLeaveBuf)
    {
        free(pcRecvBuf);
        pcRecvBuf = NULL;
        return NULL;
    }
    memset(pcLeaveBuf, 0, iBufLen);


    while (ptPmsgConnInfo->iThreadRunFlag == 1)
    {
        if (iSocket <= 0)
        {
            iSocket = CreatePisTcpSocket(ptPmsgConnInfo->acIpAddr, (unsigned short)ptPmsgConnInfo->iServPort);
            if (iSocket > 0)
            {
                FD_ZERO(&tAllSet);
                FD_SET(iSocket, &tAllSet);
                ptPmsgConnInfo->iSockfd = iSocket;
                ptPmsgConnInfo->iConnectStatus = E_PIS_STATUS_CONNECT;
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "PIS %s connected", ptPmsgConnInfo->acIpAddr);
                LOG_WriteLog(&tLogInfo);
            }

        }

        if (iSocket <= 0)
        {
            sleep(2);
            ptPmsgConnInfo->iConnectStatus = E_PIS_STATUS_UNCONNECT;
            continue;
        }

        tv.tv_sec = 0;
        tv.tv_usec = 20000;

        tTmpSet = tAllSet;	//重新置位.
        if (select(iSocket + 1, &tTmpSet, NULL, NULL, &tv) > 0)
        {

            if (FD_ISSET(iSocket, &tTmpSet))
            {

                iHearCount = 0;
//                memset(pcRecvBuf, 0, RECV_BUF_LEN);

                memset(&pcRecvBuf[iPreLeaveLen], 0, iBufLen - iPreLeaveLen);
                iRecvLen = recv(iSocket, &pcRecvBuf[iPreLeaveLen], iBufLen - iPreLeaveLen - 1, 0);

//                iRecvLen = recv(iSocket, pcRecvBuf, c_iBufLen, 0);
                if (iRecvLen <= 0)
                {
                    perror("recv:");
                    //printf("nvr serv %s exit, recv error\n", ptPmsgConnInfo->acIpAddr);

                    DestroyPisTcpSocket(iSocket);
                    iSocket = -1;
                    ptPmsgConnInfo->iSockfd = -1;
                    ptPmsgConnInfo->iConnectStatus = E_PIS_STATUS_UNCONNECT;
                    memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                    tLogInfo.iLogType = 0;
                    snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "Pis %s disconnected", ptPmsgConnInfo->acIpAddr);
                    LOG_WriteLog(&tLogInfo);
                    continue;
                }
                if (iPreLeaveLen > 0)
                {
                    memcpy(pcRecvBuf, pcLeaveBuf, iPreLeaveLen);
                }

                iLeaveLen = iRecvLen + iPreLeaveLen;
                iOffset = 0;


                while (iRecvLen > 0)
                {
                    if (iLeaveLen < 5)
                    {
                        memcpy(pcLeaveBuf, &pcRecvBuf[iOffset], iLeaveLen);
                        iPreLeaveLen = iLeaveLen;
                        break;
                    }

                    // 验证消息头的正确性
                    if (MSG_START_FLAG != pcRecvBuf[iOffset])
                    {
                        break;
                    }
//                    if(CheckSum(pcRecvBuf,sizeof (pcRecvBuf)!=0))
//                    {
//                        break;
//                    }
                    if(g_iIsPBD == 0)
                    {
                        TCP_PIS_HEADER tcp_pis_header;
                        memcpy(&tcp_pis_header,pcRecvBuf,sizeof(TCP_PIS_HEADER));
                        //解析TCP报文
                        if(tcp_pis_header.DataLenth == 0x1A)
                        {
                            Msg_RecvPISYCInfo RecvPISYCInfo;
                            memcpy(&RecvPISYCInfo,pcRecvBuf+3,sizeof(Msg_RecvPISYCInfo));
                            //解析PIS报文
                            ParsePisYCInfo(RecvPISYCInfo);
                        }

                        if(tcp_pis_header.DataLenth == 0x37)
                        {
                            Msg_RecvPISInfoEx RecvPISInfo;
                            memcpy(&RecvPISInfo,pcRecvBuf+5,sizeof(RecvPISInfo));
                            ParsePisInfoEx(RecvPISInfo);
//                            ParsePisInfoEx( RecvPISInfo);
                        }

                    }
                    else if(g_iIsPBD == 1)
                    {
                        TCP_HEADER tcp_header;
                        memcpy(&tcp_header,pcRecvBuf,sizeof(TCP_HEADER));
                        //解析TCP报文
                        if(tcp_header.FrameType == TX_MSG_RECV_PIS)
                        {
                            Msg_RecvPISInfo RecvPISInfo;
                            memcpy(&RecvPISInfo,pcRecvBuf+4,sizeof(Msg_RecvPISInfo));
                            //解析PIS报文
                            ParsePisInfo(RecvPISInfo);
                        }
                        else if(tcp_header.FrameType == TX_MSG_HEARTBEAT)		// 心跳报文
                        {
                            char sendBuff[5];
                            sendBuff[0] = 0xff;
                            sendBuff[1] = TX_MSG_HEARTBEAT_FEEDBACK;
                            sendBuff[2] = 0x00;
                            sendBuff[3] = 0x00;
                            sendBuff[4] = 0xAE;

                           int ret= PIS_SendRawData((PIS_HANDLE)ptPmsgConnInfo,sendBuff,sizeof (sendBuff));
                           if (ret <= 0)
                           {
                               DestroyPisTcpSocket(iSocket);
                               iSocket = -1;
                               ptPmsgConnInfo->iSockfd = -1;
                               ptPmsgConnInfo->iConnectStatus = E_PIS_STATUS_UNCONNECT;
                               memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                               tLogInfo.iLogType = 0;
                               snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "server %s disconnected", ptPmsgConnInfo->acIpAddr);
                               LOG_WriteLog(&tLogInfo);
                               iHearCount = 0;
                           }
                        }

                    }
                    else if(g_iIsPBD == 2)
                    {
                        Clent_PIS_HANDLE m_Clinet_Pis_Phandle=0;
                        TCP_HEADER tcp_header;
                        memcpy(&tcp_header,pcRecvBuf,sizeof(TCP_HEADER));
                        //解析TCP报文
                        if(tcp_header.FrameType == TX_MSG_RECV_PIS)
                        {
                            Msg_RecvPISInfoEx RecvPISInfoEx;
                            memcpy(&RecvPISInfoEx,pcRecvBuf + sizeof(TCP_HEADER), sizeof(Msg_RecvPISInfoEx));
                            //解析PIS报文
                            ParsePisInfoEx(RecvPISInfoEx);
                        }
                        else if(tcp_header.FrameType == TX_MSG_HEARTBEAT)		// 心跳报文
                        {
                            char sendBuff[5];
                            sendBuff[0] = 0xff;
                            sendBuff[1] = TX_MSG_HEARTBEAT_FEEDBACK;
                            sendBuff[2] = 0x00;
                            sendBuff[3] = 0x00;
                            sendBuff[4] = 0xAE;

                           m_Clinet_Pis_Phandle = STATE_GetPisPmsgHandle();
                           int ret = PMSG_SendPmsgData(m_Clinet_Pis_Phandle, TX_MSG_HEARTBEAT_FEEDBACK, sendBuff, sizeof(sendBuff));
                            if (ret <= 0)
                            {
                                DestroyPisTcpSocket(iSocket);
                                iSocket = -1;
                                ptPmsgConnInfo->iSockfd = -1;
                                ptPmsgConnInfo->iConnectStatus = E_PIS_STATUS_UNCONNECT;
                                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                                tLogInfo.iLogType = 0;
                                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "server %s disconnected", ptPmsgConnInfo->acIpAddr);
                                LOG_WriteLog(&tLogInfo);
                                iHearCount = 0;
                            }

                        }


                    }
                    memset(&pcRecvBuf[iPreLeaveLen], 0, iBufLen - iPreLeaveLen);
                    usleep(500*1000);

                }


            }


        }

        iHearCount ++;
        if (iHearCount > 1000)
        {
            DestroyPisTcpSocket(iSocket);
            iSocket = -1;
            ptPmsgConnInfo->iSockfd = -1;
            ptPmsgConnInfo->iConnectStatus = E_SERV_STATUS_UNCONNECT;
            memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
            tLogInfo.iLogType = 0;
            snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "server %s disconnected", ptPmsgConnInfo->acIpAddr);
            LOG_WriteLog(&tLogInfo);
            iHearCount = 0;

        }


    }

    if (iSocket > 0)
    {
        DestroyPisTcpSocket(iSocket);
        ptPmsgConnInfo->iSockfd = -1;
    }
    if (pcRecvBuf)
    {
        free(pcRecvBuf);
        pcRecvBuf = NULL;
    }

    if (pcLeaveBuf)
    {
        free(pcLeaveBuf);
        pcLeaveBuf = NULL;
    }

    return NULL;

}

PIS_HANDLE PIS_CreateConnect(char *pcIpAddr, int iPort)
{
    init();

    PT_PIS_CONN_INFO ptPmsgConnInfo = NULL;
    pthread_mutexattr_t	mutexattr;
    int iRet = 0;

    ptPmsgConnInfo = (PT_PIS_CONN_INFO)malloc(sizeof(PT_PIS_CONN_INFO));
    if (NULL == ptPmsgConnInfo)
    {
        return 0;
    }
    memset(ptPmsgConnInfo, 0, sizeof(PT_PIS_CONN_INFO));
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_TIMED_NP);
    pthread_mutex_init(&ptPmsgConnInfo->tPmsgMutex, &mutexattr);
    pthread_mutexattr_destroy(&mutexattr);

    strncpy(ptPmsgConnInfo->acIpAddr, pcIpAddr, sizeof(ptPmsgConnInfo->acIpAddr));
    ptPmsgConnInfo->iServPort = iPort;

    ptPmsgConnInfo->iThreadRunFlag = 1;
    iRet = pthread_create(&ptPmsgConnInfo->ThreadHandle, NULL, PisProcessThread, (void *)ptPmsgConnInfo);
    if (iRet < 0)
    {
        free(ptPmsgConnInfo);
        ptPmsgConnInfo = NULL;
        return 0;
    }

    return (PIS_HANDLE)ptPmsgConnInfo;
}

void ParsePisYCInfo(Msg_RecvPISYCInfo  RecvPISInfo)
{
    char acTmp[32] = {0}, acTmp1[32] = {0}, acTmp2[32] = {0}, acStr[256] = {0};
    char tranNum[16]={0};
    time_t uiTime = 0;
    struct tm *tvTimeValue;
    T_TIME_INFO tTimeInfo;
    time_t localTime = 0,pisTime = 0;
    struct tm tmVal;
    T_LOG_INFO tLogInfo;

    short iYear = 0;

    time(&uiTime);
    tvTimeValue = localtime(&uiTime);


    PT_PIS_MSG_INFO ptPisInfo= NULL;
    if(ptPisInfo == NULL)
         ptPisInfo = (PT_PIS_MSG_INFO)malloc(sizeof(T_PIS_MSG_INFO));


    ptPisInfo->tTime.i16Year = 1900+tvTimeValue->tm_year;
    ptPisInfo->tTime.i8Mon = tvTimeValue->tm_mon+1;
    ptPisInfo->tTime.i8day = tvTimeValue->tm_mday;
    ptPisInfo->tTime.i8Hour =  RecvPISInfo.Time[0];
    ptPisInfo->tTime.i8Min =  RecvPISInfo.Time[1];
    ptPisInfo->tTime.i8Sec =  RecvPISInfo.Time[2];


    memset(&tTimeInfo, 0, sizeof(tTimeInfo));
    tTimeInfo.year =  ptPisInfo->tTime.i16Year;
    tTimeInfo.mon = ptPisInfo->tTime.i8Mon;
    tTimeInfo.day = ptPisInfo->tTime.i8day;
    tTimeInfo.hour = ptPisInfo->tTime.i8Hour;
    tTimeInfo.min = ptPisInfo->tTime.i8Min;
    tTimeInfo.sec = ptPisInfo->tTime.i8Sec;


    iYear = ptPisInfo->tTime.i16Year;
    printf("********iYear=%d---tTimeInfo.hour=%d---tTimeInfo.min=%d--tTimeInfo.sec=%d\n",iYear,tTimeInfo.hour,tTimeInfo.min,tTimeInfo.sec);

    localTime = time(NULL);
    tmVal.tm_year = iYear - 1900;
    tmVal.tm_mon = tTimeInfo.mon - 1;
    tmVal.tm_mday = tTimeInfo.day;
    tmVal.tm_hour = tTimeInfo.hour;
    tmVal.tm_min = tTimeInfo.min;
    tmVal.tm_sec = tTimeInfo.sec;
    pisTime = mktime(&tmVal);

    if (abs(localTime - pisTime) > 3)
    {
        snprintf(acStr, sizeof(acStr), "date %02d%02d%02d%02d%4d.%02d", ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Sec,iYear, ptPisInfo->tTime.i8Min);
        system(acStr);
        system("hwclock -w");

        /*系统校时记录日志*/
        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
        tLogInfo.iLogType = 0;
        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "set local time %4d-%02d-%02d %02d:%02d:%02d", iYear, ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Min, ptPisInfo->tTime.i8Sec);
        LOG_WriteLog(&tLogInfo);

    }



    ptPisInfo->wSpeed = RecvPISInfo.Speed;

    BYTE testInfo[2]={0};
    memcpy(testInfo,&RecvPISInfo.Speed,2);

    strncpy(ptPisInfo->cTrainNum,RecvPISInfo.TrainNumber1,sizeof(RecvPISInfo.TrainNumber1));
    strncpy(ptPisInfo->cTrainNum+4,RecvPISInfo.TrainNumber2,sizeof(RecvPISInfo.TrainNumber2));


    int uiTmp = RecvPISInfo.Mileage[0] << 24 | RecvPISInfo.Mileage[1] << 16 | RecvPISInfo.Mileage[2] << 8 | RecvPISInfo.Mileage[3];
    short sDistance = (uiTmp/1000) & 0xffff;            //里程    ？？？？？

    ptPisInfo->wDistance = sDistance;

    snprintf(acTmp, sizeof(acTmp), "%03d", (int)RecvPISInfo.BeginStation[0]);
    STATE_GetStationName(acTmp1, sizeof(acTmp1), acTmp);
    memset(acTmp, 0, sizeof(acTmp));
    snprintf(acTmp, sizeof(acTmp), "%03d", (int)RecvPISInfo.EndStation[0]);
    STATE_GetStationName(acTmp2, sizeof(acTmp2), acTmp);

    snprintf(ptPisInfo->cIntervalInfo, sizeof(ptPisInfo->cIntervalInfo), "%s-%s", acTmp1, acTmp2);

    int iRet = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    PIS_HANDLE P_Handle = 0;

    for (int i=0;i<tTrainConfigInfo.iNvrServerCount;i++)
    {
        for (int j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            P_Handle = STATE_GetNvrServerPmsgHandle(i);
            ptPisInfo->CarriageNumber =tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;
            ptPisInfo->PantoPos = (8 +j);

            iRet = PMSG_SendPmsgData(P_Handle, CLI_SERV_MSG_TYPE_CHECK_TIME, (char *)&tTimeInfo, sizeof(T_TIME_INFO));    //发送校时命令
            if (iRet < 0)
            {
                DebugPrint(DEBUG_UI_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d\n",iRet);
            }
            else
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "notify server %d Time Check OK, %4d-%02d-%02d %02d:%02d:%02d!", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO,
                    iYear, ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Min,  ptPisInfo->tTime.i8Sec);
                LOG_WriteLog(&tLogInfo);
            }


            iRet = PMSG_SendPmsgData(P_Handle, TX_MSG_ADDTEXT, (char *)ptPisInfo, sizeof (T_PIS_MSG_INFO));
            if (iRet < 0)
            {

                DebugPrint(DEBUG_PMSG_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d---i=%d\n",iRet,i);

            }
        }
    }

}



void ParsePisInfo(Msg_RecvPISInfo  RecvPISInfo)
{
    char acTmp[32] = {0}, acTmp1[32] = {0}, acTmp2[32] = {0}, acStr[256] = {0};
    T_TIME_INFO tTimeInfo;
    time_t localTime = 0,pisTime = 0;
    struct tm tmVal;
    T_LOG_INFO tLogInfo;

    int iYear = 0;

    PT_PIS_MSG_INFO ptPisInfo= NULL;
    if(ptPisInfo == NULL)
         ptPisInfo = (PT_PIS_MSG_INFO)malloc(sizeof(T_PIS_MSG_INFO));

    ptPisInfo->tTime.i16Year = RecvPISInfo.dateTime.Year;
    ptPisInfo->tTime.i8Mon =  RecvPISInfo.dateTime.Month;
    ptPisInfo->tTime.i8day =  RecvPISInfo.dateTime.Day;
    ptPisInfo->tTime.i8Hour =  RecvPISInfo.dateTime.Hour;
    ptPisInfo->tTime.i8Min =  RecvPISInfo.dateTime.Minute;
    ptPisInfo->tTime.i8Sec =  RecvPISInfo.dateTime.Second;



    memset(&tTimeInfo, 0, sizeof(tTimeInfo));
    tTimeInfo.year =  ptPisInfo->tTime.i16Year;
    tTimeInfo.mon = ptPisInfo->tTime.i8Mon;
    tTimeInfo.day = ptPisInfo->tTime.i8day;
    tTimeInfo.hour = ptPisInfo->tTime.i8Hour;
    tTimeInfo.min = ptPisInfo->tTime.i8Min;
    tTimeInfo.sec = ptPisInfo->tTime.i8Sec;


    iYear = htons(ptPisInfo->tTime.i16Year);

    localTime = time(NULL);
    tmVal.tm_year = iYear - 1900;
    tmVal.tm_mon = tTimeInfo.mon - 1;
    tmVal.tm_mday = tTimeInfo.day;
    tmVal.tm_hour = tTimeInfo.hour;
    tmVal.tm_min = tTimeInfo.min;
    tmVal.tm_sec = tTimeInfo.sec;
    pisTime = mktime(&tmVal);

    if (abs(localTime - pisTime) > 3)
    {
        snprintf(acStr, sizeof(acStr), "date %02d%02d%02d%02d%4d.%02d", ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Sec,iYear, ptPisInfo->tTime.i8Min);
        system(acStr);
        system("hwclock -w");

        /*系统校时记录日志*/
        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
        tLogInfo.iLogType = 0;
        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "set local time %4d-%02d-%02d %02d:%02d:%02d", iYear, ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Min, ptPisInfo->tTime.i8Sec);
        LOG_WriteLog(&tLogInfo);

    }


    ptPisInfo->wSpeed = RecvPISInfo.Speed;

    ptPisInfo->wDistance = (RecvPISInfo.Mileage)/1000;
    strncpy(ptPisInfo->cTrainNum,(char *)RecvPISInfo.TrainNumber,sizeof (ptPisInfo->cTrainNum));

    snprintf(acTmp, sizeof(acTmp), "%03d", (int)RecvPISInfo.IntervalInfo[2]);
    STATE_GetStationName(acTmp1, sizeof(acTmp1), acTmp);
    memset(acTmp, 0, sizeof(acTmp));
    snprintf(acTmp, sizeof(acTmp), "%03d", (int)RecvPISInfo.IntervalInfo[5]);
    STATE_GetStationName(acTmp2, sizeof(acTmp2), acTmp);

    snprintf(ptPisInfo->cIntervalInfo, sizeof(ptPisInfo->cIntervalInfo), "%s-%s", acTmp1, acTmp2);

    int iRet = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    PIS_HANDLE P_Handle = 0;

    for (int i=0;i<tTrainConfigInfo.iNvrServerCount;i++)
    {
        for (int j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            P_Handle = STATE_GetNvrServerPmsgHandle(i);
            ptPisInfo->CarriageNumber =tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;
            ptPisInfo->PantoPos = (8 +j);

            iRet = PMSG_SendPmsgData(P_Handle, CLI_SERV_MSG_TYPE_CHECK_TIME, (char *)&tTimeInfo, sizeof(T_TIME_INFO));    //发送校时命令
            if (iRet < 0)
            {
                DebugPrint(DEBUG_UI_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d\n",iRet);
            }
            else
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "notify server %d Time Check OK, %4d-%02d-%02d %02d:%02d:%02d!", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO,
                    iYear, ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Min,  ptPisInfo->tTime.i8Sec);
                LOG_WriteLog(&tLogInfo);
            }

            iRet = PMSG_SendPmsgData(P_Handle, TX_MSG_ADDTEXT, (char *)ptPisInfo, sizeof (T_PIS_MSG_INFO));
            if (iRet < 0)
            {
                DebugPrint(DEBUG_PMSG_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d---i=%d\n",iRet,i);
            }
        }
    }

}

void ParsePisInfoEx(Msg_RecvPISInfoEx RecvPISInfo)
{
    char acTmp[32] = {0}, acTmp1[32] = {0}, acTmp2[32] = {0}, acStr[256] = {0};
    T_TIME_INFO tTimeInfo;
    time_t localTime = 0,pisTime = 0;
    struct tm tmVal;
    T_LOG_INFO tLogInfo;
    int iYear = 0;


    PT_PIS_MSG_INFO ptPisInfo= NULL;
    if(ptPisInfo == NULL)
         ptPisInfo = (PT_PIS_MSG_INFO)malloc(sizeof(T_PIS_MSG_INFO));

    ptPisInfo->tTime.i16Year = (RecvPISInfo.dateTime.Year);
    ptPisInfo->tTime.i8Mon =  RecvPISInfo.dateTime.Month;
    ptPisInfo->tTime.i8day =  RecvPISInfo.dateTime.Day;
    ptPisInfo->tTime.i8Hour =  RecvPISInfo.dateTime.Hour;
    ptPisInfo->tTime.i8Min =  RecvPISInfo.dateTime.Minute;
    ptPisInfo->tTime.i8Sec =  RecvPISInfo.dateTime.Second;



    memset(&tTimeInfo, 0, sizeof(tTimeInfo));
    tTimeInfo.year =  ptPisInfo->tTime.i16Year;
    tTimeInfo.mon = ptPisInfo->tTime.i8Mon;
    tTimeInfo.day = ptPisInfo->tTime.i8day;
    tTimeInfo.hour = ptPisInfo->tTime.i8Hour;
    tTimeInfo.min = ptPisInfo->tTime.i8Min;
    tTimeInfo.sec = ptPisInfo->tTime.i8Sec;


    iYear = htons(ptPisInfo->tTime.i16Year);

    localTime = time(NULL);
    tmVal.tm_year = iYear - 1900;
    tmVal.tm_mon = tTimeInfo.mon - 1;
    tmVal.tm_mday = tTimeInfo.day;
    tmVal.tm_hour = tTimeInfo.hour;
    tmVal.tm_min = tTimeInfo.min;
    tmVal.tm_sec = tTimeInfo.sec;
    pisTime = mktime(&tmVal);

    if (abs(localTime - pisTime) > 3)
    {
        snprintf(acStr, sizeof(acStr), "date %02d%02d%02d%02d%4d.%02d", ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Sec,iYear, ptPisInfo->tTime.i8Min);
        system(acStr);
        system("hwclock -w");

        printf("**********date=%s\n",acStr);
        /*系统校时记录日志*/
        memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
        tLogInfo.iLogType = 0;
        snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "set local time %4d-%02d-%02d %02d:%02d:%02d", iYear, ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Min, ptPisInfo->tTime.i8Sec);
        LOG_WriteLog(&tLogInfo);

    }


    ptPisInfo->wSpeed =RecvPISInfo.Speed;


    ptPisInfo->wDistance = (RecvPISInfo.Mileage)/1000;
    strncpy(ptPisInfo->cTrainNum,(char *)RecvPISInfo.TrainNumber,sizeof (ptPisInfo->cTrainNum));


    snprintf(acTmp, sizeof(acTmp), "%03d", (int)RecvPISInfo.BeginStation[0]);
    STATE_GetStationName(acTmp1, sizeof(acTmp1), acTmp);
    memset(acTmp, 0, sizeof(acTmp));
    snprintf(acTmp, sizeof(acTmp), "%03d", (int)RecvPISInfo.EndStation[0]);
    STATE_GetStationName(acTmp2, sizeof(acTmp2), acTmp);

    snprintf(ptPisInfo->cIntervalInfo, sizeof(ptPisInfo->cIntervalInfo), "%s-%s", acTmp1, acTmp2);

    int iRet = 0;
    T_TRAIN_CONFIG tTrainConfigInfo;
    memset(&tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
    STATE_GetCurrentTrainConfigInfo(&tTrainConfigInfo);
    PIS_HANDLE P_Handle = 0;

    for (int i=0;i<tTrainConfigInfo.iNvrServerCount;i++)
    {
        for (int j = 0; j < tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum; j++)
        {
            P_Handle = STATE_GetNvrServerPmsgHandle(i);
            ptPisInfo->CarriageNumber =tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO;
            ptPisInfo->PantoPos = (8 +j);

            iRet = PMSG_SendPmsgData(P_Handle, CLI_SERV_MSG_TYPE_CHECK_TIME, (char *)&tTimeInfo, sizeof(T_TIME_INFO));    //发送校时命令
            if (iRet < 0)
            {
                DebugPrint(DEBUG_UI_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d\n",iRet);
            }
            else
            {
                memset(&tLogInfo, 0, sizeof(T_LOG_INFO));
                tLogInfo.iLogType = 0;
                snprintf(tLogInfo.acLogDesc, sizeof(tLogInfo.acLogDesc), "notify server %d Time Check OK, %4d-%02d-%02d %02d:%02d:%02d!", 100+tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO,
                    iYear, ptPisInfo->tTime.i8Mon, ptPisInfo->tTime.i8day, ptPisInfo->tTime.i8Hour, ptPisInfo->tTime.i8Min,  ptPisInfo->tTime.i8Sec);
                LOG_WriteLog(&tLogInfo);
            }

            iRet = PMSG_SendPmsgData(P_Handle, TX_MSG_ADDTEXT, (char *)ptPisInfo, sizeof (T_PIS_MSG_INFO));
            if (iRet < 0)
            {
                DebugPrint(DEBUG_PMSG_ERROR_PRINT, "PMSG_SendPmsgData CLI_SERV_MSG_TYPE_CHECK_TIME error!iRet=%d---i=%d\n",iRet,i);
            }
        }
    }

}




