#include "state.h"
#include "fileConfig.h"
#include <QDebug>
#include <QString>

#define VERSION "V2.0.0"

#define SYSCONFIGFILEPATH "/home/data/monitorCfg/C3SysConfig.ini"
#define DATACONFIGFILEPATH "/home/data/monitorCfg/C3DataConfig.ini"
#define CFGCONFIGFILEPATH "/home/data/monitorCfg/cfg"
#define STATIONCONFIGFILEPATH "/home/data/monitorCfg/Station.ini"
#define NETCONFIGFILEPATH "/mnt/sconf/netconf.ini"

static char g_acTrainType[32] = {0};    //列车车型
static char g_acTrainNumber[32] = {0};     //列车车次
static int g_iBlackScreenFlag = -1;      //监控轮询时间
static int g_iPollingTime = 0;      //监控轮询时间
static int g_iShadeAlarmEnableFlag = -1;    //遮挡报警使能标志
static int g_iPresetReturnTime = 0;    //预置点返回时间
static char g_acCurrentUserType[16] = {0};    //当前用户类型
static T_TRAIN_CONFIG g_tTrainConfigInfo;     //车型配置信息
static T_TRAIN_TYPE_LIST g_tTrainTypeList;     //车型列表
static T_PIS_INFO g_tPisConfigInfo;
static int g_iTrainTypeNum = 0;
static int iFirstFlag = 1;
static PMSG_HANDLE pisServerPmsgHandle = 0;    //pis服务器pmsg句柄
static PMSG_HANDLE nvrServerPmsgHandle[MAX_SERVER_NUM] = {0, 0, 0, 0};    //nvr服务器pmsg句柄

int STATE_GetSysVersion(char *pcVersion, int iLen)
{
	strncpy(pcVersion, VERSION, iLen);
	return 0;
}

int STATE_GetIpAddr(char *pcIpAddr, int iLen)
{
	char acIpStr[128] = {0};
	int iRet = 0;
	iRet = ReadParam(NETCONFIGFILEPATH, "EthName2=eth1", "IpAddr2", acIpStr);
	if (iRet < 0)
	{
		return -1;
	}

	strncpy(pcIpAddr, acIpStr, iLen);
	
	return 0;
}

int STATE_SetIpAddr(char *pcIpAddr)
{
	if (NULL == pcIpAddr)
	{
		return -1;
	}
	int iRet = ModifyParam(NETCONFIGFILEPATH, "EthName2=eth1", "IpAddr2", pcIpAddr);
	if (iRet < 0)
	{
		return -1;
	}

	return 0;
}

int STATE_GetNetMask(char *pcNetMask, int iLen)
{
	char acNetMaskStr[128] = {0};
	int iRet = 0;
	iRet = ReadParam(NETCONFIGFILEPATH, "EthName2=eth1", "NetMask2", acNetMaskStr);
	if (iRet < 0)
	{
		return -1;
	}

	strncpy(pcNetMask, acNetMaskStr, iLen);
	
	return 0;
}

int STATE_SetNetMask(char *pcNetMask)
{
	if (NULL == pcNetMask)
	{
		return -1;
	}
	int iRet = ModifyParam(NETCONFIGFILEPATH, "EthName2=eth1", "NetMask2", pcNetMask);
	if (iRet < 0)
	{
		return -1;
	}

	return 0;
}

int STATE_GetGateWay(char *pcGateWay, int iLen)
{
	char acGateWayStr[128] = {0};
	int iRet = 0;
	iRet = ReadParam(NETCONFIGFILEPATH, "EthName2=eth1", "GateWay2", acGateWayStr);
	if (iRet < 0)
	{
		return -1;
	}

	strncpy(pcGateWay, acGateWayStr, iLen);
	
	return 0;
}

int STATE_SetGateWay(char *pcGateWay)
{
	if (NULL == pcGateWay)
	{
		return -1;
	}
	int iRet = ModifyParam(NETCONFIGFILEPATH, "EthName2=eth1", "GateWay2", pcGateWay);
	if (iRet < 0)
	{
		return -1;
	}

	return 0;
}

int STATE_FindUsbDev()
{
	FILE *pFile = 0;
    char acBuf[256] = {0};

	pFile = fopen("/proc/partitions", "rb");
    if (NULL == pFile)
    {
        return 0;
    }

    while (fgets(acBuf, sizeof(acBuf), pFile))
    {
        if (strstr(acBuf, "sd") != NULL)
        {
			fclose(pFile);
        	return 1;
        }
    }

    fclose(pFile);
    return 0;
}

int STATE_RefreshTrainTypeInfo()
{
	iFirstFlag = 1;
	return 0;
}

int STATE_GetCurrentTrainType(char *pcTrainType, int iLen)
{
	char acparseStr[32] = {0};
	int iRet = 0;
	if (NULL == pcTrainType || iLen <= 0)
	{
		return -1;
	}
	if (0 == strlen(g_acTrainType))    //g_acTrainType为空，则通过配置文件获取
	{
		iRet = ReadParam(DATACONFIGFILEPATH, "[SelectTrainType]", "TrainType", acparseStr);
		if (iRet < 0)
		{
			return -1;
		}
		memset(g_acTrainType, 0, sizeof(g_acTrainType));
		strncpy(g_acTrainType, acparseStr, strlen(acparseStr));
	}

	strncpy(pcTrainType, g_acTrainType, iLen);
	return 0;
}

int STATE_SetCurrentTrainType(char *pcTrainType)
{
	if (NULL == pcTrainType)
	{
		return -1;
	}
	int iRet = ModifyParam(DATACONFIGFILEPATH, "[SelectTrainType]", "TrainType", pcTrainType);
	if (iRet < 0)
	{
		return -1;
	}
	memset(g_acTrainType, 0, sizeof(g_acTrainType));
	strncpy(g_acTrainType, pcTrainType, sizeof(g_acTrainType));
	return 0;
}

int STATE_GetPollingTime()
{
	char acParseStr[32] = {0};
	if (0 == g_iPollingTime)
	{
		int iRet = ReadParam(DATACONFIGFILEPATH, "[PantoMoniTime]", "MoniTime", acParseStr);
		if (iRet < 0)
		{
			return -1;
		}
		g_iPollingTime = atoi(acParseStr);
	}
	
	return g_iPollingTime;
}

int STATE_SetPollingTime(int iPollingTime)
{
	if (iPollingTime <= 0)
	{
		return -1;
	}
	char acPollingTime[16] = {0};
	snprintf(acPollingTime, sizeof(acPollingTime), "%d", iPollingTime);
	int iRet = ModifyParam(DATACONFIGFILEPATH, "[PantoMoniTime]", "MoniTime", acPollingTime);
	if (iRet < 0)
	{
		return -1;
	}
	g_iPollingTime = iPollingTime;
	return 0;
}

int STATE_GetPresetReturnTime()
{
	char acParseStr[32] = {0};
	if (0 == g_iPresetReturnTime)
	{
		int iRet = ReadParam(DATACONFIGFILEPATH, "[PantoBackTime]", "BackTime", acParseStr);
		if (iRet < 0)
		{
			return -1;
		}
		g_iPresetReturnTime= atoi(acParseStr);
	}
	
	return g_iPresetReturnTime;
}

int STATE_SetPresetReturnTime(int iPresetReturnTime)
{
	if (iPresetReturnTime <= 0)
	{
        return -1;
	}
	char acPresetReturnTime[16] = {0};
	snprintf(acPresetReturnTime, sizeof(acPresetReturnTime), "%d", iPresetReturnTime);
	int iRet = ModifyParam(DATACONFIGFILEPATH, "[PantoBackTime]", "BackTime", acPresetReturnTime);
	if (iRet < 0)
	{
        return -1;
	}
	g_iPresetReturnTime= iPresetReturnTime;
	return 0;
}

int STATE_GetTrainNumber(char *pcTrainNo, int iLen)
{
	char acparseStr[32] = {0};
	if (NULL == pcTrainNo || iLen <= 0)
	{
        return -1;
	}
	if (0 == strlen(g_acTrainNumber))    //g_acTrainNo为空，则通过配置文件获取
	{
		int iRet = ReadParam(DATACONFIGFILEPATH, "[TrainNumber]", "Value", acparseStr);
		if (iRet < 0)
		{
            return -1;
		}
		memset(g_acTrainNumber, 0, sizeof(g_acTrainNumber));
		strncpy(g_acTrainNumber, acparseStr, strlen(acparseStr));
	}
	strncpy(pcTrainNo, g_acTrainNumber, iLen);
    return 0;
}

int STATE_SetTrainNumber(char *pcTrainNo)
{
	if (NULL == pcTrainNo)
	{
		return -1;
	}
	int iRet = ModifyParam(DATACONFIGFILEPATH, "[TrainNumber]", "Value", pcTrainNo);
	if (iRet < 0)
	{
		return -1;
	}
	memset(g_acTrainNumber, 0, sizeof(g_acTrainNumber));
	strncpy(g_acTrainNumber, pcTrainNo, sizeof(g_acTrainNumber));
	return 0;
}



int STATE_GetTrainTypeNum()
{
	char acParseStr[32] = {0};
	if (1 == iFirstFlag)
	{
		int iRet = ReadParam(SYSCONFIGFILEPATH, "[TrainType]", "TrainNum", acParseStr);
		if (iRet < 0)
		{
			return -1;
		}
		g_iTrainTypeNum = atoi(acParseStr);
	}
	
	return g_iTrainTypeNum;
}

int STATE_SetTrainTypeNum(int iTrainTypeNum)
{
	char acTrainTypeNum[16] = {0};
	int iRet = 0;
	
	if (iTrainTypeNum <= 0)
	{
		return -1;
	}
	
	snprintf(acTrainTypeNum, sizeof(acTrainTypeNum), "%d", iTrainTypeNum);
	iRet = ModifyParam(SYSCONFIGFILEPATH, "[TrainType]", "TrainNum", acTrainTypeNum);
	if (iRet < 0)
	{
		return -1;
	}
	g_iTrainTypeNum = iTrainTypeNum;
	
	return 0;
}

int STATE_GetTrainTypeList(T_TRAIN_TYPE_LIST *pstTrainTypeList)
{
	char acParseStr[32] = {0};
	char acTypeStr[32] = {0};

	int iRet = 0, i = 0;

	if (1 == iFirstFlag)
	{
		iRet = STATE_GetTrainTypeNum();
		if (iRet < 0)
		{
			return -1;
		}
		g_tTrainTypeList.iTypeNum = iRet;
		pstTrainTypeList->iTypeNum = g_tTrainTypeList.iTypeNum;

		for(i = 0; i < pstTrainTypeList->iTypeNum; i++)
		{
			memset(g_tTrainTypeList.acTrainTypeName[i], 0, sizeof(g_tTrainTypeList.acTrainTypeName[i]));
			memset(acTypeStr, 0, sizeof(acTypeStr));
			memset(acParseStr, 0, sizeof(acParseStr));
			snprintf(acTypeStr, sizeof(acTypeStr), "TrainType%d", i+1);
			iRet = ReadParam(SYSCONFIGFILEPATH, "[TrainType]", acTypeStr, acParseStr);
			if (iRet < 0)
			{
				break;
			}
			strncpy(g_tTrainTypeList.acTrainTypeName[i], acParseStr, strlen(acParseStr));
		}

		iFirstFlag = 0;
	}
	memcpy(pstTrainTypeList, &g_tTrainTypeList, sizeof(T_TRAIN_TYPE_LIST));

	return iRet;
}

int STATE_SetTrainTypeList(T_TRAIN_TYPE_LIST stTrainTypeList)
{
	char acTypeStr[32] = {0};
	int iRet = 0, i = 0;

	for(i = 0; i < stTrainTypeList.iTypeNum; i++)
	{
		memset(acTypeStr, 0, sizeof(acTypeStr));
		snprintf(acTypeStr, sizeof(acTypeStr), "TrainType%d", i+1);
		iRet = ModifyParam(SYSCONFIGFILEPATH, "[TrainType]", acTypeStr, stTrainTypeList.acTrainTypeName[i]);
		if (iRet < 0)
		{
			return -1;
		}
	}

	iRet = STATE_SetTrainTypeNum(stTrainTypeList.iTypeNum);
	if (iRet < 0)
	{
		return -1;
	}
	
	memcpy(&g_tTrainTypeList, &stTrainTypeList, sizeof(T_TRAIN_TYPE_LIST));

	return 0;
}


int STATE_GetLastTrainType(char *pcTrainType, int iLen)
{
	char acparseStr[32] = {0};
	char acStr[32] = {0};
	int iTrainTypeNum = 0, iRet = 0;
	if (NULL == pcTrainType || iLen <= 0)
	{
		return -1;
	}
	
	iTrainTypeNum = STATE_GetTrainTypeNum();
	snprintf(acStr, sizeof(acStr), "TrainType%d", iTrainTypeNum);
	iRet = ReadParam(SYSCONFIGFILEPATH, "[TrainType]", acStr, acparseStr);
	if (iRet < 0)
	{
		return -1;
	}
	strncpy(pcTrainType, acparseStr, iLen);
	return 0;
}

int STATE_addTrainType(char *pcTrainType)
{
	int iTrainTypeNum = 0, iRet = 0;
	char acStr[32] = {0};
	char acParseStr[32] = {0};
	char acTypeStr[32] = {0};
	if (NULL == pcTrainType)
	{
		return -1;
	}

	iTrainTypeNum = STATE_GetTrainTypeNum();
	snprintf(acStr, sizeof(acStr), "TrainType%d", iTrainTypeNum);
	iRet = ModifyParam(SYSCONFIGFILEPATH, "[TrainType]", acStr, pcTrainType);
	if (iRet < 0)
	{
		return -1;
	}

	g_tTrainTypeList.iTypeNum = iTrainTypeNum + 1;
	for(int i = 0; i < g_tTrainTypeList.iTypeNum; i++)
	{
		memset(g_tTrainTypeList.acTrainTypeName[i], 0, sizeof(g_tTrainTypeList.acTrainTypeName[i]));
		memset(acTypeStr, 0, sizeof(acTypeStr));
		memset(acParseStr, 0, sizeof(acParseStr));
		snprintf(acTypeStr, sizeof(acTypeStr), "TrainType%d", i+1);
		iRet = ReadParam(SYSCONFIGFILEPATH, "[TrainType]", acTypeStr, acParseStr);
		if (iRet < 0)
		{
			break;
		}
		strncpy(g_tTrainTypeList.acTrainTypeName[i], acParseStr, strlen(acParseStr));
	}
	
	return 0;
}

int STATE_delTrainType(int iTrainTypeNo)
{
	int iTrainTypeNum = 0, iRet = 0, i = 0;
	char acStr[64] = {0};
	char acParseStr[32] = {0};
	char acTypeStr[64] = {0};

	
	iTrainTypeNum = STATE_GetTrainTypeNum();
	if (iTrainTypeNo < 1 || iTrainTypeNo > iTrainTypeNum)
	{
		return -1;
	}
	
	/*删除车型配置文件*/
	snprintf(acStr, sizeof(acStr), "TrainType%d", iTrainTypeNo);
	ReadParam(SYSCONFIGFILEPATH, "[TrainType]", acStr, acParseStr);
	if (strlen(acParseStr) != 0)
	{	
		snprintf(acTypeStr, sizeof(acTypeStr), "%s/%s.ini", CFGCONFIGFILEPATH, acParseStr);
		if (0 == access(acTypeStr, F_OK))
		{
			memset(acParseStr, 0, sizeof(acParseStr));
			snprintf(acParseStr, sizeof(acParseStr), "rm %s", acTypeStr);
			system(acParseStr);
		}
	}

	/*修改C3SysConfig配置文件中车型配置内容*/
	for (i = iTrainTypeNo; i <= iTrainTypeNum - 1; i++)
	{
		memset(acStr, 0, sizeof(acStr));
		memset(acParseStr, 0, sizeof(acParseStr));
		snprintf(acStr, sizeof(acStr), "TrainType%d", i+1);
		iRet = ReadParam(SYSCONFIGFILEPATH, "[TrainType]", acStr, acParseStr);
		if (iRet < 0 || 0 == strlen(acParseStr))
		{
			continue;
		}
		memset(acStr, 0, sizeof(acStr));
		snprintf(acStr, sizeof(acStr), "TrainType%d", i);
		iRet = ModifyParam(SYSCONFIGFILEPATH, "[TrainType]", acStr, acParseStr);
		if (iRet < 0)
		{
			continue;
		}
	}

	/*删除C3SysConfig配置文件中车型配置最后一行*/
	memset(acStr, 0, sizeof(acStr));
	snprintf(acStr, sizeof(acStr), "TrainType%d", iTrainTypeNum);
	DeleteParam(SYSCONFIGFILEPATH, acStr);
	
	/*更新车型列表全局结构体*/
	g_tTrainTypeList.iTypeNum = iTrainTypeNum - 1;
	for(i = 0; i < g_tTrainTypeList.iTypeNum; i++)
	{
		memset(g_tTrainTypeList.acTrainTypeName[i], 0, sizeof(g_tTrainTypeList.acTrainTypeName[i]));
		memset(acTypeStr, 0, sizeof(acTypeStr));
		memset(acParseStr, 0, sizeof(acParseStr));
		snprintf(acTypeStr, sizeof(acTypeStr), "TrainType%d", i+1);
		iRet = ReadParam(SYSCONFIGFILEPATH, "[TrainType]", acTypeStr, acParseStr);
		if (iRet < 0)
		{
			break;
		}
		strncpy(g_tTrainTypeList.acTrainTypeName[i], acParseStr, strlen(acParseStr));
	}

	return 0;
}


int STATE_ReadTrainConfigFile()
{
	char acparseStr[32] = {0};
	char acTrainType[32] = {0};
	char acTmp[32] = {0}, acTrainConfigFile[64] = {0};
	int iRet = 0, i = 0;
	memset(&g_tTrainConfigInfo, 0, sizeof(T_TRAIN_CONFIG));
	STATE_GetCurrentTrainType(acTrainType, sizeof(acTrainType));   //获取车型
	snprintf(acTrainConfigFile, sizeof(acTrainConfigFile), "%s/%s.ini", CFGCONFIGFILEPATH, acTrainType);

	iRet = ReadParam(acTrainConfigFile, "[PVSM_TRAIN]", "FormationType", acparseStr);
	if (iRet < 0)
	{
		return -1;
	}
	g_tTrainConfigInfo.iFormationType = atoi(acparseStr);
	memset(acparseStr, 0, sizeof(acparseStr));
	iRet = ReadParam(acTrainConfigFile, "[PVSM_TRAIN]", "NVRCount", acparseStr);
	if (iRet < 0)
	{
		return -1;
	}
	g_tTrainConfigInfo.iNvrServerCount = atoi(acparseStr);
	if (g_tTrainConfigInfo.iNvrServerCount > MAX_SERVER_NUM)
	{
		return -1;
	}

	for (i = 0; i < g_tTrainConfigInfo.iNvrServerCount; i++)
	{
		memset(acTmp,0, sizeof(acTmp));
		snprintf(acTmp, sizeof(acTmp), "[PVMS_NVR%d]", i+1);
		memset(acparseStr, 0, sizeof(acparseStr));
		iRet = ReadParam(acTrainConfigFile, acTmp, "NVRCarriageNO", acparseStr);
		if (iRet < 0)
		{
			return -1;
		}
		g_tTrainConfigInfo.tNvrServerInfo[i].iCarriageNO = atoi(acparseStr);
		
		memset(acparseStr, 0, sizeof(acparseStr));
		iRet = ReadParam(acTrainConfigFile, acTmp, "PvmsCarriageNO", acparseStr);
		if (iRet < 0)
		{
			return -1;
		}
		g_tTrainConfigInfo.tNvrServerInfo[i].iPvmsCarriageNO = atoi(acparseStr);

		memset(acparseStr, 0, sizeof(acparseStr));
		iRet = ReadParam(acTrainConfigFile, acTmp, "PvmsCameraNum", acparseStr);
		if (iRet < 0)
		{
			return -1;
		}
		g_tTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum = atoi(acparseStr);		
	}
	return 0;
}

int STATE_GetCurrentTrainConfigInfo(T_TRAIN_CONFIG *pstTrainConfigInfo)  
{
	memcpy(pstTrainConfigInfo, &g_tTrainConfigInfo, sizeof(T_TRAIN_CONFIG));
	return 0;
}

int STATE_SetCurrentTrainConfigInfo(T_TRAIN_CONFIG stTrainConfigInfo)  
{
	memcpy(&g_tTrainConfigInfo, &stTrainConfigInfo, sizeof(T_TRAIN_CONFIG));
	return 0;
}

PMSG_HANDLE STATE_GetNvrServerPmsgHandle(int iServerIdex)
{
	if (iServerIdex > MAX_SERVER_NUM || iServerIdex < 0)
	{
		return 0;
	}

	return nvrServerPmsgHandle[iServerIdex];
}

int STATE_SetNvrServerPmsgHandle(int iServerIdex, PMSG_HANDLE pmsgHandle)
{
	if (pmsgHandle <= 0 || iServerIdex > MAX_SERVER_NUM || iServerIdex < 0)
	{
		return -1;
	}

	nvrServerPmsgHandle[iServerIdex] = pmsgHandle;
	return 0;
}

int STATE_ReadPisConfig()
{
	char acparseStr[128] = {0};
	int iRet = 0;

	iRet = ReadParam(SYSCONFIGFILEPATH, "[PISServer]", "IPAddr", acparseStr);
	if (iRet < 0)
	{
		return -1;
	}
	strncpy(g_tPisConfigInfo.acIpAddr, acparseStr, strlen(acparseStr));

	iRet = ReadParam(SYSCONFIGFILEPATH, "[PISServer]", "Port", acparseStr);
	if (iRet < 0)
	{
		return -1;
	}
	g_tPisConfigInfo.iPort = atoi(acparseStr);

	return 0;
}

int STATE_GetPisConfigInfo(T_PIS_INFO *ptPisConfigInfo)
{
	memcpy(ptPisConfigInfo, &g_tPisConfigInfo, sizeof(T_PIS_INFO));
	return 0;
}

int STATE_SetPisConfigInfo(T_PIS_INFO tPisConfigInfo)  
{
	char acPort[16] = {0};
	int iRet = 0;
	iRet = ModifyParam(SYSCONFIGFILEPATH, "[PISServer]", "IPAddr", tPisConfigInfo.acIpAddr);
	if (iRet < 0)
	{
		return -1;
	}

	snprintf(acPort, sizeof(acPort), "%d", tPisConfigInfo.iPort);
	iRet = ModifyParam(SYSCONFIGFILEPATH, "[PISServer]", "Port", acPort);
	if (iRet < 0)
	{
		return -1;
	}
	
	memcpy(&g_tPisConfigInfo, &tPisConfigInfo, sizeof(T_PIS_INFO));
	return 0;
}

PMSG_HANDLE STATE_GetPisPmsgHandle()
{
	return pisServerPmsgHandle;
}

int STATE_SetPisPmsgHandle(PMSG_HANDLE pmsgHandle)
{
	if (pmsgHandle <= 0)
	{
		return -1;
	}
	pisServerPmsgHandle = pmsgHandle;
	return 0;
}

int STATE_GetTrainConfigInfo(char *pcTrainType, T_TRAIN_CONFIG *pstTrainConfigInfo)  
{
	int iRet = 0, i = 0;
	char acTrainTypeConFile[128] = {0};
	char acparseStr[32] = {0}, acTmp[32] = {0};
	
	if (NULL == pcTrainType)
	{
		return -1;
	}

	snprintf(acTrainTypeConFile, sizeof(acTrainTypeConFile), "%s/%s.ini", CFGCONFIGFILEPATH, pcTrainType);
	iRet = ReadParam(acTrainTypeConFile, "[PVSM_TRAIN]", "FormationType", acparseStr);
	if (iRet < 0)
	{
		return -1;
	}
	pstTrainConfigInfo->iFormationType = atoi(acparseStr);
	memset(acparseStr, 0, sizeof(acparseStr));
	iRet = ReadParam(acTrainTypeConFile, "[PVSM_TRAIN]", "NVRCount", acparseStr);
	if (iRet < 0)
	{
		return -1;
	}
	pstTrainConfigInfo->iNvrServerCount = atoi(acparseStr);

	for (i = 0; i < pstTrainConfigInfo->iNvrServerCount; i++)
	{
		memset(acTmp,0, sizeof(acTmp));
		snprintf(acTmp, sizeof(acTmp), "[PVMS_NVR%d]", i+1);
		memset(acparseStr, 0, sizeof(acparseStr));
		iRet = ReadParam(acTrainTypeConFile, acTmp, "NVRCarriageNO", acparseStr);
		if (iRet < 0)
		{
			return -1;
		}
		pstTrainConfigInfo->tNvrServerInfo[i].iCarriageNO = atoi(acparseStr);
		
		memset(acparseStr, 0, sizeof(acparseStr));
		iRet = ReadParam(acTrainTypeConFile, acTmp, "PvmsCarriageNO", acparseStr);
		if (iRet < 0)
		{
			return -1;
		}
		pstTrainConfigInfo->tNvrServerInfo[i].iPvmsCarriageNO = atoi(acparseStr);

		memset(acparseStr, 0, sizeof(acparseStr));
		iRet = ReadParam(acTrainTypeConFile, acTmp, "PvmsCameraNum", acparseStr);
		if (iRet < 0)
		{
			return -1;
		}
		pstTrainConfigInfo->tNvrServerInfo[i].iPvmsCameraNum = atoi(acparseStr);		
	}
	return 0;
}

int STATE_SetTrainConfigInfo(char *pcTrainType, T_TRAIN_CONFIG stTrainConfigInfo)  
{
	int iRet = 0, i = 0;
	char acTrainTypeConFile[128] = {0};
	char acTmp[32] = {0}, acStr[32] = {0};
	
	if (NULL == pcTrainType)
	{
		return -1;
	}

	snprintf(acTrainTypeConFile, sizeof(acTrainTypeConFile), "%s/%s.ini", CFGCONFIGFILEPATH, pcTrainType);
	snprintf(acStr, sizeof(acStr), "%d", stTrainConfigInfo.iFormationType);
	iRet = ModifyParam(acTrainTypeConFile, "[PVSM_TRAIN]", "FormationType", acStr);
	if (iRet < 0)
	{
		return -1;
	}

	memset(acStr, 0, sizeof(acStr));
	snprintf(acStr, sizeof(acStr), "%d", stTrainConfigInfo.iNvrServerCount);
	iRet = ModifyParam(acTrainTypeConFile, "[PVSM_TRAIN]", "NVRCount", acStr);
	if (iRet < 0)
	{
		return -1;
	}

	for (i = 0; i < stTrainConfigInfo.iNvrServerCount; i++)
	{
		memset(acTmp,0, sizeof(acTmp));
		snprintf(acTmp, sizeof(acTmp), "[PVMS_NVR%d]", i+1);
		memset(acStr, 0, sizeof(acStr));
		snprintf(acStr, sizeof(acStr), "%d", stTrainConfigInfo.tNvrServerInfo[i].iCarriageNO);
		iRet = ModifyParam(acTrainTypeConFile, acTmp, "NVRCarriageNO", acStr);
		if (iRet < 0)
		{
			return -1;
		}

		memset(acStr, 0, sizeof(acStr));
		snprintf(acStr, sizeof(acStr), "%d", stTrainConfigInfo.tNvrServerInfo[i].iPvmsCarriageNO);
		iRet = ModifyParam(acTrainTypeConFile, acTmp, "PvmsCarriageNO", acStr);
		if (iRet < 0)
		{
			return -1;
		}

		memset(acStr, 0, sizeof(acStr));
		snprintf(acStr, sizeof(acStr), "%d", stTrainConfigInfo.tNvrServerInfo[i].iPvmsCameraNum);
		iRet = ModifyParam(acTrainTypeConFile, acTmp, "PvmsCameraNum", acStr);
		if (iRet < 0)
		{
			return -1;
		}
	}
	return 0;
}


int STATE_GetCurrentUserType(char *pcUserType, int iLen)
{
	if (NULL == pcUserType || iLen <= 0)
	{
		return -1;
	}
	strncpy(pcUserType, g_acCurrentUserType, iLen);
	return 0;
}

int STATE_SetCurrentUserType(const char *pcUserType)
{
	if (NULL == pcUserType)
	{
		return -1;
	}
	strncpy(g_acCurrentUserType, pcUserType, sizeof(g_acCurrentUserType));
	return 0;
}

int STATE_GetBlackScreenFlag()
{
	int iFlag = 0, iRet = 0;
	char acParseStr[32] = {0};
	if (-1 == g_iBlackScreenFlag)
	{
		iRet = ReadParam(SYSCONFIGFILEPATH, "[BlackScreen]", "bCloseBlackScreen", acParseStr);
		if (iRet < 0)
		{
			return -1;
		}
		iFlag = atoi(acParseStr);
		g_iBlackScreenFlag = !iFlag;
	}
	
	return g_iBlackScreenFlag;
}

int STATE_SetBlackScreenFlag(int iBlackScreenFlag)
{	
	int iRet = 0;
	char acStr[16] = {0};
	if (iBlackScreenFlag != 0 && iBlackScreenFlag != 1)
	{
		return -1;
	}
	snprintf(acStr, sizeof(acStr), "%d", !iBlackScreenFlag);
	iRet = ModifyParam(SYSCONFIGFILEPATH, "[BlackScreen]", "bCloseBlackScreen", acStr);
	if (iRet < 0)
	{
		return -1;
	}
	g_iBlackScreenFlag = iBlackScreenFlag;
	return 0;
}

int STATE_GetShadeAlarmEnableFlag()
{
	int iFlag = 0, iRet = 0;
	char acParseStr[32] = {0};
	if (-1 == g_iShadeAlarmEnableFlag)
	{
		iRet = ReadParam(SYSCONFIGFILEPATH, "[PantoSHADEALARM]", "Enable", acParseStr);
		if (iRet < 0)
		{
			return -1;
		}
		iFlag = atoi(acParseStr);
		g_iShadeAlarmEnableFlag = iFlag;
	}
	
	return g_iShadeAlarmEnableFlag;
}

int STATE_SetShadeAlarmEnableFlag(int iShadeAlarmEnableFlag)
{
	int iRet = 0;
	char acStr[16] = {0};
	if (iShadeAlarmEnableFlag != 0 && iShadeAlarmEnableFlag != 1)
	{
		return -1;
	}
	snprintf(acStr, sizeof(acStr), "%d", iShadeAlarmEnableFlag);
	iRet = ModifyParam(SYSCONFIGFILEPATH, "[PantoSHADEALARM]", "Enable", acStr);
	if (iRet < 0)
	{
		return -1;
	}
	g_iShadeAlarmEnableFlag = iShadeAlarmEnableFlag;
	return 0;
}


int STATE_GetStationName(char *pcStationName, int iLen, char *pcStationCode)
{
	char acTmp[32] = {0};
	int iRet = 0;
	iRet = ReadParam(STATIONCONFIGFILEPATH, "[StationCode]", pcStationCode, acTmp);
	if (iRet < 0)
	{
		return -1;
	}

	strncpy(pcStationName, acTmp, iLen);
	
	return 0;
}

static char *GetStrFromContent(char *pcBuf, char *pcBegin, char *pcEnd)
{
	char *pcPos = NULL;
	char *pcTemp = NULL;

	pcPos = pcBuf;
	pcTemp =strtok(pcPos, pcBegin);
	if (pcTemp)
	{
		pcTemp = strtok(NULL,pcEnd);
	}

	return pcTemp;
}

int STATE_ParseUsbLicense(char *pcPath)
{
	char acFileName[256];
	char acBuf [256];
	char* pcTmp;
	int iSucc = 0;
	FILE *pFile = NULL;

	if (NULL == pcPath )
	{
		return -1;	
	}
	
	memset(acFileName,0,sizeof(acFileName));
	memset(acBuf,0,sizeof(acFileName));
	sprintf(acFileName,"%s/C3License.txt",pcPath);
	pFile = fopen(acFileName, "rb");
	if (NULL == pFile)
	{
		return -1;
	}
	
	while (fgets(acBuf, sizeof(acBuf), pFile))
	{
		if (memcmp(acBuf, "Username", strlen("Username")) == 0)
		{
			pcTmp = GetStrFromContent(acBuf, (char *)"[", (char *)"]");
			if (pcTmp)
			{
				if(0 == strncmp("admin", pcTmp, sizeof("admin")))
				{
					iSucc++;
				}
			}
		}
		else if (memcmp(acBuf, "Password", strlen("Password")) == 0)
		{
			pcTmp = GetStrFromContent(acBuf, (char *)"[", (char *)"]");
			if (pcTmp)
			{
				if(0 == strncmp("12345", pcTmp, sizeof("12345")))
				{
					iSucc++;
				}
			}
		}
	}
	
	fclose(pFile);
	
	if (2 != iSucc)
	{
		return -1;
	}
	
	return 0;
}


