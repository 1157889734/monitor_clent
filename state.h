#ifndef STATE_H
#define STATE_H
#include "pmsgcli.h"

#ifdef __cplusplus
extern "C"{
#endif /* End of #ifdef __cplusplus */

#define MAX_SERVER_NUM 4    //最大服务器个数
#define MAX_CAMERA_OFSERVER 2    //每个服务器连接的最大摄像机数
#define MAX_TRAINTYPE_NUM  16   //最大车型数
#define MAX_TRAINTYPESTR_LEN  32   //车型字符串最大长度
#define MAX_TRAINNOSTR_LEN  8  //车次字符串最大长度

typedef struct _T_NVRSERVER_INFO      /*单个NVR服务器信息*/
{
	int iCarriageNO;      //NVR服务器车厢号
	int iPvmsCameraNum;   //受电弓摄像机数量
	int iPvmsCarriageNO;  //受电弓车厢号
} T_NVRSERVER_INFO, *PT_NVRSERVER_INFO;

typedef struct _T_TRAIN_CONFIG      /*车型配置信息*/
{
	int iFormationType;   //编组类型 1为8编组，2为16编组
	int iNvrServerCount;  //NVR服务器数量
	T_NVRSERVER_INFO tNvrServerInfo[MAX_SERVER_NUM];    //NVR服务器信息
} T_TRAIN_CONFIG, *PT_TRAIN_CONFIG;

typedef struct _T_TRAIN_TYPE_LIST   /*设备类型列表*/
{
 	int iTypeNum;    //类型总数
 	char acTrainTypeName[MAX_TRAINTYPE_NUM][MAX_TRAINTYPESTR_LEN];
} T_TRAIN_TYPE_LIST, *PT_TRAIN_TYPE_LIST;

typedef struct _T_PIS_INFO   /*PIS系统信息*/
{
	char acIpAddr[128];
	int iPort;
} T_PIS_INFO, *PT_PIS_INFO;

int STATE_GetIpAddr(char *pcIpAddr, int iLen);

int STATE_SetIpAddr(char *pcIpAddr);

int STATE_GetNetMask(char *pcNetMask, int iLen);

int STATE_SetNetMask(char *pcNetMask);

int STATE_GetGateWay(char *pcGateWay, int iLen);

int STATE_SetGateWay(char *pcGateWay);

int STATE_GetSysVersion(char *pcVersion, int iLen);

int STATE_FindUsbDev();

int STATE_RefreshTrainTypeInfo();

int STATE_GetCurrentTrainType(char *pcTrainType, int iLen);

int STATE_SetCurrentTrainType(char *pcTrainType);

int STATE_GetPollingTime();

int STATE_SetPollingTime(int iPollingTime);

int STATE_GetPresetReturnTime();

int STATE_SetPresetReturnTime(int iPresetReturnTime);

int STATE_GetTrainNumber(char *pcTrainNo, int iLen);

int STATE_SetTrainNumber(char *pcTrainNo);

int STATE_GetTrainTypeNum();

int STATE_SetTrainTypeNum(int iTrainTypeNum);

int STATE_GetTrainTypeList(T_TRAIN_TYPE_LIST *pstTrainTypeList);

int STATE_SetTrainTypeList(T_TRAIN_TYPE_LIST stTrainTypeList);

int STATE_GetLastTrainType(char *pcTrainType, int iLen);

int STATE_addTrainType(char *pcTrainType);

int STATE_delTrainType(int iTrainTypeNo);

int STATE_ReadTrainConfigFile();

int STATE_GetCurrentTrainConfigInfo(T_TRAIN_CONFIG *pstTrainConfigInfo);

PMSG_HANDLE STATE_GetNvrServerPmsgHandle(int iServerIdex);

int STATE_SetNvrServerPmsgHandle(int iServerIdex, PMSG_HANDLE pmsgHandle);

int STATE_ReadPisConfig();

int STATE_GetPisConfigInfo(T_PIS_INFO *ptPisConfigInfo);

int STATE_SetPisConfigInfo(T_PIS_INFO tPisConfigInfo);

PMSG_HANDLE STATE_GetPisPmsgHandle();

int STATE_SetPisPmsgHandle(PMSG_HANDLE pmsgHandle);

int STATE_GetTrainConfigInfo(char *pcTrainType, T_TRAIN_CONFIG *pstTrainConfigInfo);

int STATE_SetTrainConfigInfo(char *pcTrainType, T_TRAIN_CONFIG stTrainConfigInfo); 

int STATE_GetCurrentUserType(char *pcUserType, int iLen);

int STATE_SetCurrentUserType(const char *pcUserType);

int STATE_GetBlackScreenFlag();

int STATE_SetBlackScreenFlag(int iBlackScreenFlag);

int STATE_GetShadeAlarmEnableFlag();

int STATE_SetShadeAlarmEnableFlag(int iShadeAlarmEnableFlag);

int STATE_GetStationName(char *pcStationName, int iLen, char *pcStationCode);

int STATE_ParseUsbLicense(char *pcPath);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif

