#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h> 
#include <sys/time.h>   
#include <fcntl.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <termios.h>
#include "rs485serv.h"
#include "debug.h"
#include "types.h"

#define UART_DEV_NAME  "/dev/ttyS7"
#define RECV_BUF_SIZE  1400

typedef struct _T_RS485_PACKET_LIST
{
    T_RS485_PACKET tPkt;
    struct _T_RS485_PACKET_LIST *next;
} __attribute__((packed)) T_RS485_PACKET_LIST;

typedef struct _T_RS485_QUEUE
{
    T_RS485_PACKET_LIST *ptFirst, *ptLast;
    INT32 iQueueType;
    INT32 iPktCount;
    pthread_mutex_t *pMutex;
} __attribute__((packed)) T_RS485_QUEUE, *PT_RS485_QUEUE;

typedef struct _T_RS485_CONN_INFO
{
    int iDevfd;
    int iThreadRunFlag;
    pthread_t ThreadHandle;
    pthread_mutex_t tRs485QueueMutex;

    PT_RS485_QUEUE ptRs485Queue;
} __attribute__((packed))T_RS485_CONN_INFO, *PT_RS485_CONN_INFO;

typedef struct _T_TIME
{
    INT16 i16Year;  //年
    INT8 i8Mon;     //月
    INT8 i8day;     //天
    INT8 i8Hour;    //时
    INT8 i8Min;    //分
    INT8 i8Sec;    //秒
} __attribute__((packed))T_TIME, *PT_TIME;

typedef struct _T_RS485_PISMSG_INFO
{ 
    T_TIME tTime;     //时间
    WORD  wSpeed;         //区间速度
    char  cTrainNum[11];  //车次号
    WORD  wDistance;      //区间距离
    char  cIntervalInfo[30]; //区间信息
} __attribute__((packed))T_RS485_PISMSG_INFO, *PT_RS485_PISMSG_INFO;


int speed_arr[] ={B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B600,B300};
int name_arr[] = {115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 600,300};

PT_RS485_QUEUE CreateRs485Queue(pthread_mutex_t *pMutex, int iQueueType)
{
    PT_RS485_QUEUE ptRs485Queue = NULL;

    ptRs485Queue = (PT_RS485_QUEUE)malloc(sizeof(T_RS485_QUEUE));
    if (NULL == ptRs485Queue)
    {
        return NULL;
    }
    memset(ptRs485Queue, 0, sizeof(T_RS485_QUEUE));
    ptRs485Queue->pMutex = pMutex;
    ptRs485Queue->iQueueType = iQueueType;
    ptRs485Queue->ptLast = NULL;
    ptRs485Queue->ptFirst = NULL;
    ptRs485Queue->iPktCount= 0;

    return ptRs485Queue;
}

int DestroyRs485Queue(PT_RS485_QUEUE ptRs485Queue)
{
    T_RS485_PACKET_LIST *ptPktList = NULL, *ptTmp;

    if (NULL == ptRs485Queue)
    {
        return -1;
    }

    if (ptRs485Queue->pMutex)
    {
        pthread_mutex_lock(ptRs485Queue->pMutex);
    }

    ptPktList = ptRs485Queue->ptFirst;
    while (ptPktList)
    {
        ptTmp = ptPktList;
        ptPktList = ptPktList->next;
//        DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
        free(ptTmp);
//        DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
    }

    ptRs485Queue->ptLast = NULL;
    ptRs485Queue->ptFirst = NULL;
    ptRs485Queue->iPktCount= 0;

    if (ptRs485Queue->pMutex)
    {
        pthread_mutex_unlock(ptRs485Queue->pMutex);
    }

//    DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
    free(ptRs485Queue);
//    DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
    ptRs485Queue = NULL;
//    DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);

    return 0;
}

int PutNodeToRs485Queue(PT_RS485_QUEUE ptRs485Queue, PT_RS485_PACKET ptPkt)
{
    T_RS485_PACKET_LIST *ptPktList = NULL;


    if ((NULL == ptRs485Queue) || (NULL == ptPkt))
    {
        return -1;
    }
    ptPktList = (T_RS485_PACKET_LIST *)malloc(sizeof(T_RS485_PACKET_LIST));
    if (NULL == ptPktList)
    {
        return -1;
    }

    memset(ptPktList, 0, sizeof(T_RS485_PACKET_LIST));
    ptPktList->tPkt = *ptPkt;

    if (ptRs485Queue->pMutex)
    {
        pthread_mutex_lock(ptRs485Queue->pMutex);
    }

    if (NULL == ptRs485Queue->ptLast)
    {
        ptRs485Queue->ptFirst = ptPktList;
    }
    else
    {
        ptRs485Queue->ptLast->next = ptPktList;
    }
    ptRs485Queue->ptLast = ptPktList;
    ptRs485Queue->iPktCount++;

    if (ptRs485Queue->pMutex)
    {
        pthread_mutex_unlock(ptRs485Queue->pMutex);
    }

    return 0;
}

int GetNodeFromRs485Queue(PT_RS485_QUEUE ptRs485Queue, PT_RS485_PACKET ptPkt)
{
    T_RS485_PACKET_LIST *ptTmp = NULL;

    if ((NULL == ptRs485Queue) || (NULL == ptPkt))
    {
        return 0;
    }

    if (ptRs485Queue->pMutex)
    {
        pthread_mutex_lock(ptRs485Queue->pMutex);
    }

    if (NULL == ptRs485Queue->ptFirst)
    {
        if (ptRs485Queue->pMutex)
        {
            pthread_mutex_unlock(ptRs485Queue->pMutex);
        }

        return 0;
    }

    ptTmp = ptRs485Queue->ptFirst;
    ptRs485Queue->ptFirst = ptRs485Queue->ptFirst->next;
    if (NULL == ptRs485Queue->ptFirst)
    {
        ptRs485Queue->ptLast= NULL;
    }
    ptRs485Queue->iPktCount--;
    *ptPkt = ptTmp->tPkt;
    free(ptTmp);

    if (ptRs485Queue->pMutex)
    {
        pthread_mutex_unlock(ptRs485Queue->pMutex);
    }

    return 1;
}

static int setSpeed(int fd, int speed)      
{
	unsigned int i;
	int status;

	struct termios Opt;
	if(tcgetattr(fd, &Opt)!=0)
	{
		perror("SetupSerial error");
		return -1;
	}
	for(i = 0; i < sizeof(speed_arr)/sizeof(int); i++)
	{
		if (speed==name_arr[i])
		{
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&Opt, speed_arr[i]);
			cfsetospeed(&Opt, speed_arr[i]);
			status=tcsetattr(fd, TCSANOW,&Opt);
			if(0!=status)
			{
				perror("tcsetattr fd error!");
			}
			tcflush(fd, TCIOFLUSH);
		}
	}
	return 0;
}

static int setParity(int fd, int databits, int parity, int stopbits)
{
	struct termios options;

	if (tcgetattr(fd, &options) != 0)
	{
		perror("Setup Serial error!");
		return -1;
	}
    
	options.c_cflag &= ~CSIZE;
	switch (databits)
	{
	case 5:
		options.c_cflag |= CS5;
		break;
	case 6:
		options.c_cflag |= CS6;
		break;
	case 7:
		options.c_cflag |= CS7;
		break;
	case 8:
		options.c_cflag |= CS8;
		break;
	default:
		fprintf(stderr, "Unsupported data size!\n");
		return -1;
	}

	switch (parity)
	{
	case (0):	//无校验
		options.c_cflag &= ~PARENB;
		options.c_iflag &= ~INPCK;
		break;
	case 1:		//奇校验
		options.c_cflag |= PARENB;
		options.c_cflag |= PARODD;
		options.c_iflag |= INPCK;
		break;
	case 2:		//偶校验
		options.c_cflag |= PARENB;
		options.c_cflag &= ~PARODD;
		options.c_iflag |= INPCK;
		break;
	default:
		fprintf(stderr, "Unsupported parity!\n");
		return -1;
	}
	switch (stopbits)
	{
	case 1:
		options.c_cflag &= ~CSTOPB;
		break;
	case 2:
		options.c_cflag |= CSTOPB;
		break;
	default:
		fprintf(stderr, "Unsupported stop bits!\n");
		return -1;
	}
	options.c_lflag &= ~(ECHO | ICANON | ECHOE | ISIG);
	options.c_oflag &= ~OPOST;
    
    //options.c_iflag &= ~(IXON|IXOFF|IXANY);
    
	tcflush(fd, TCIOFLUSH);
	if (tcsetattr(fd, TCSANOW, &options) != 0)
	{
		perror("Setup Serial in set_parity  error!");
		return -1;
	}

	return 1;
}

BYTE GetPisMsgDataEcc(BYTE *pcData, INT32 iLen)
{
    int i = 0;
    BYTE ucEcc = 0;
    
    if ((NULL == pcData) || (0 == iLen))	
    {
        return 0;	
    }
    
    for (i = 0; i < iLen; i++)
    {
        ucEcc ^= pcData[i];
    }
    
    return ucEcc;
}


void *Rs485ProcessThread(void *arg)
{
	unsigned char *pcRecvBuf = NULL;
	char acPisData[64] = {0};
	int iPos = 0;
    int iBufLen = RECV_BUF_SIZE;
    int iMaxLen = 0;
    int iReadLen = 0;
	fd_set readfd,tmpfd;
	struct timeval tv;
    T_RS485_PACKET tPkt;
	T_RS485_CONN_INFO *pRs485ConnInfo = (T_RS485_CONN_INFO *)arg;

	if (NULL == pRs485ConnInfo)
    {
        return NULL;	
    }

    pcRecvBuf = (unsigned char *)malloc(iBufLen);
    if (NULL == pcRecvBuf)
    {
        return NULL;        	
    }
    memset(pcRecvBuf, 0, iBufLen);

	FD_ZERO(&readfd);
	FD_SET(pRs485ConnInfo->iDevfd, &readfd);
	
    while(1 == pRs485ConnInfo->iThreadRunFlag)
	{	
		tv.tv_sec = 0;
    	tv.tv_usec = 50000;
    
		tmpfd = readfd; 
		if (select(pRs485ConnInfo->iDevfd + 1, &tmpfd, NULL, NULL, &tv) > 0)
		{
			if (FD_ISSET(pRs485ConnInfo->iDevfd, &tmpfd))
			{
				iMaxLen = iBufLen - iPos;
                iReadLen = read(pRs485ConnInfo->iDevfd, pcRecvBuf+iPos, iMaxLen);
                iPos += iReadLen;
                if (iPos == iBufLen)
                {
                     iPos = 0;
                }
			}			
		}
		else
		{
            if (iPos > 0)	
            {
//                DebugPrint(DEBUG_RS485_DATA_PRINT, "uart data len %d", iPos);
                if (iPos > 3)
                {
//                    DebugPrint(DEBUG_RS485_DATA_PRINT, "%x %x %x", pcRecvBuf[0], pcRecvBuf[1], pcRecvBuf[2]);
                }
                if ((0xFF == pcRecvBuf[0]) && (0xFF == pcRecvBuf[1]) && (0x1A == pcRecvBuf[2]) && (iPos >= 29))
                {
                    short sSpeed = 0;
                    short sYear = 0;
                    char  cMon = 0;
                    char  cDay = 0;
                    char  cHour = 0;
                    char  cMin = 0;
                    char  cSec  =0;
                    char  cPisHour = 0;
                    char  cPisMin = 0;
                    char  cPisSec = 0;
                    char acTrainNO [11];
                    char acTrainAsc[5];
                    char cEcc = 0;
                    int iTrainAscCount = 0, i = 0;
                    unsigned int uiTrainNum=0;
                    unsigned int uiTmp = 0;
                    short sDistance = 0;
                    T_RS485_PISMSG_INFO *ptPisInfo = NULL;
                    struct tm *tvTimeValue;
                    time_t uiTime = 0;
                        
                    for (i = 0; i < 2; i++)
                    {
//                        DebugPrint(DEBUG_RS485_DATA_PRINT,  "%x %x %x %x %x %x %x %x %x %x %x %x %x %x ", pcRecvBuf[i*14], pcRecvBuf[i*14 + 1], pcRecvBuf[i*14 + 2],
//                                       pcRecvBuf[i*14 + 3], pcRecvBuf[i*14 + 4], pcRecvBuf[i*14 + 5], pcRecvBuf[i*14 + 6],
//                                       pcRecvBuf[i*14 + 7], pcRecvBuf[i*14 + 8], pcRecvBuf[i*14 + 9], pcRecvBuf[i*14 + 10],
//                                       pcRecvBuf[i*14 + 11], pcRecvBuf[i*14 + 12], pcRecvBuf[i*14 + 13]);
                    }
                    // check ecc
                    for (i = 2; i < 28; i++)
                    {
                        cEcc += pcRecvBuf[i];	
                    }
                    if (cEcc != pcRecvBuf[28])
                    {
                        iPos = 0;
//                        DebugPrint(DEBUG_RS485_DATA_PRINT, "ecc data %x, ecc %x", pcRecvBuf[28], cEcc);
                        continue;
                    }
                    
                    //DebugPrint(DEBUG_LEVEL_3, "recv pisdata");
                    sSpeed = (pcRecvBuf[5] << 8 & 0xFF00) + pcRecvBuf[6];                //速度
                    //DebugPrint(DEBUG_LEVEL_3, "speed %x , %x, %x", sSpeed, pcRecvBuf[5], pcRecvBuf[6]);
                        
                    cPisHour = (pcRecvBuf[12]/16)*10 + pcRecvBuf[12]%16;     //16   10    17  11    32  20   16进制字符串到10进制转换
                    cPisMin  = (pcRecvBuf[13]/16)*10 + pcRecvBuf[13]%16;
                    cPisSec  = (pcRecvBuf[14]/16)*10 + pcRecvBuf[14]%16;
                    
                    time(&uiTime);
                    tvTimeValue = localtime(&uiTime);
                    sYear = 1900+tvTimeValue->tm_year;
                    cMon  = tvTimeValue->tm_mon+1;
                    cDay = tvTimeValue->tm_mday;
                    cHour = tvTimeValue->tm_hour;
                    cMin  = tvTimeValue->tm_min;
                    cSec  = tvTimeValue->tm_sec;
                    
                    if ((cHour != cPisHour) && (cMin != cPisMin))
                    {
                        if (!((cPisHour == 0 && cPisMin <= 10) || (cPisHour == 23 && cPisMin >= 50)))
                        {
                            cHour = cPisHour;
                            cMin = cPisMin;
                            cSec = cPisSec;
                        }
                    }

                    uiTmp = pcRecvBuf[8] << 24 | pcRecvBuf[9] << 16 | pcRecvBuf[10] << 8 | pcRecvBuf[11]; 
                    sDistance = (uiTmp/1000) & 0xffff;            //里程    ？？？？？

                    memset(acTrainAsc, 0, sizeof(acTrainAsc));
                    memset(acTrainNO, 0, sizeof(acTrainNO));
                    memcpy(acTrainAsc, &pcRecvBuf[15], 4);   //车次
                    for (i = 0; i < 5; i++)
                    {
                        // ignore space
                        if (acTrainAsc[i] == 0x20)                 
                        {
                            iTrainAscCount++;
                        }
                    }

                    if (pcRecvBuf[19]==0xff)
                    {
                        if (pcRecvBuf[20]==0xff)
                        {
                            uiTrainNum = pcRecvBuf[21]%16;
                            uiTrainNum = (pcRecvBuf[21]/16>10?uiTrainNum:(pcRecvBuf[21]/16*10+uiTrainNum));
                        }
                        else
                        {
                            uiTrainNum = (pcRecvBuf[20]%16)*100+(pcRecvBuf[21]/16)*10+pcRecvBuf[21]%16;
                            uiTrainNum = (pcRecvBuf[20]/16>10?uiTrainNum:(pcRecvBuf[20]/16*1000+uiTrainNum));
                        }
                    }
                    else
                    {
                        uiTrainNum = (pcRecvBuf[19]%16)*10000+(pcRecvBuf[20]/16)*1000+(pcRecvBuf[20]%16)*100+(pcRecvBuf[21]/16)*10+pcRecvBuf[21]%16;//整数取余
                        uiTrainNum = (pcRecvBuf[19]/16>10?uiTrainNum:(pcRecvBuf[19]/16*100000+uiTrainNum));
                    }
                    
                    snprintf(acTrainNO, sizeof(acTrainNO), "%s%d", &acTrainAsc[iTrainAscCount], uiTrainNum);
                    
                    memset(acPisData, 0, sizeof(acPisData));
                    acPisData[0] = 0xFF;
                    acPisData[1] = 0x04;
                    acPisData[2] = 0;
                    acPisData[3] = 52;
                    
                    ptPisInfo = (T_RS485_PISMSG_INFO *)&acPisData[4];
                    ptPisInfo->tTime.i16Year = htons(sYear);
			        ptPisInfo->tTime.i8Mon = cMon;
			        ptPisInfo->tTime.i8day = cDay;
			        ptPisInfo->tTime.i8Hour = cHour;
			        ptPisInfo->tTime.i8Min = cMin;
			        ptPisInfo->tTime.i8Sec = cSec;
                    ptPisInfo->wSpeed = htons(sSpeed);
                    memcpy(ptPisInfo->cTrainNum, acTrainNO, sizeof(ptPisInfo->cTrainNum));
                    ptPisInfo->wDistance = htons(sDistance);
                    memcpy(ptPisInfo->cIntervalInfo, &pcRecvBuf[22], 3);
                    memcpy(&ptPisInfo->cIntervalInfo[3], &pcRecvBuf[25], 3);
//                    DebugPrint(DEBUG_RS485_DATA_PRINT, "year %d, mon %d, day %d, hour %d, min %d, sec %d, speed %x, distance %x, trainno %s",
//                                sYear, cMon, cDay, cHour, cMin, cSec, sSpeed, sDistance, acTrainNO);
                    cEcc = GetPisMsgDataEcc((BYTE *)acPisData, sizeof(T_RS485_PISMSG_INFO) + 4);
                    acPisData[sizeof(T_RS485_PISMSG_INFO) + 4] = cEcc;
                    
                    tPkt.iDataLen = sizeof(T_RS485_PISMSG_INFO) + 5;
                    tPkt.pcData = (char *)malloc(tPkt.iDataLen+16);
                    if (NULL == tPkt.pcData)
                    {
                        break;
                    }
                    memcpy(&(tPkt.pcData[0]), acPisData, tPkt.iDataLen);
                    PutNodeToRs485Queue(pRs485ConnInfo->ptRs485Queue, &tPkt);
                }
                
                iPos = 0;
            }
        }
	}

//	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	free(pcRecvBuf);
//	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	pcRecvBuf = NULL;
//	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	return NULL;
}

PRS485_HANDLE RS485_CreateConnect()
{
	int fd = 0, iRet = 0;
    pthread_mutexattr_t	mutexattr;
	
	PT_RS485_CONN_INFO pRs485ConnInfo = NULL;
	pRs485ConnInfo = (PT_RS485_CONN_INFO)malloc(sizeof(T_RS485_CONN_INFO));
    if (NULL == pRs485ConnInfo)
    {		
        return 0;	
    }
    
	if ((fd = open(UART_DEV_NAME, O_RDWR)) == -1)
    {
//        DebugPrint(DEBUG_UI_ERROR_PRINT, "open %s failed\n", UART_DEV_NAME);
        free(pRs485ConnInfo);
        pRs485ConnInfo = NULL;
        return 0;	
    }
	
	setSpeed(fd, 115200);
    setParity(fd, 8, 0, 1);

    memset(pRs485ConnInfo, 0, sizeof(T_RS485_CONN_INFO));
	pRs485ConnInfo->iDevfd = fd;

    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_settype(&mutexattr,PTHREAD_MUTEX_TIMED_NP);
    pthread_mutex_init(&pRs485ConnInfo->tRs485QueueMutex, &mutexattr);
    pthread_mutexattr_destroy(&mutexattr);

    pRs485ConnInfo->ptRs485Queue = CreateRs485Queue(&pRs485ConnInfo->tRs485QueueMutex, 0);

	pRs485ConnInfo->iThreadRunFlag = 1;
	iRet = pthread_create(&pRs485ConnInfo->ThreadHandle, NULL, Rs485ProcessThread, (void *)pRs485ConnInfo);
    if (iRet < 0)
    {
//    	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
        free(pRs485ConnInfo);
//    	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
        pRs485ConnInfo = NULL;
//    	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
        return 0;	
    }

    return (PRS485_HANDLE)pRs485ConnInfo;
}

int RS485_DestroyConnect(PRS485_HANDLE pRs485Handle)  
{
	PT_RS485_CONN_INFO ptRs485ConnInfo = (PT_RS485_CONN_INFO)pRs485Handle; 
    
    if (NULL == ptRs485ConnInfo)
    {	
        return -1;	
    }
    ptRs485ConnInfo->iThreadRunFlag = 0;
    
    // join thread exit
    if (ptRs485ConnInfo->ThreadHandle)
    {
        pthread_join(ptRs485ConnInfo->ThreadHandle, NULL);
    }

    close(ptRs485ConnInfo->iDevfd);

    DestroyPmsgQueue(ptRs485ConnInfo->ptRs485Queue);
    pthread_mutex_destroy(&ptRs485ConnInfo->tRs485QueueMutex);
    
//	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
    free(ptRs485ConnInfo);
//	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
    ptRs485ConnInfo = NULL;
//	DebugPrint(DEBUG_ERROR_PRINT, "%s %s:%d\n",__FILE__,__FUNCTION__,__LINE__);
    
    return 0;
}

int RS485_GetDataFromRs485Queue(PRS485_HANDLE pRs485Handle, PT_RS485_PACKET ptPkt)
{
    int iRet = 0;
    PT_RS485_CONN_INFO ptRs485ConnInfo = (PT_RS485_CONN_INFO)pRs485Handle;

    if (NULL == ptRs485ConnInfo)
    {
        return -1;
    }

    iRet = GetNodeFromRs485Queue(ptRs485ConnInfo->ptRs485Queue, ptPkt);
    if (0 == iRet)
    {
        return -1;
    }

    return 0;
}
