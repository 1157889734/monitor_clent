#ifndef _DEBUGOUT_H
#define _DEBUGOUT_H


#define DEBUG_LEVEL_1      1 << 0
#define DEBUG_LEVEL_2      1 << 1
#define DEBUG_LEVEL_3      1 << 2
#define DEBUG_LEVEL_4      1 << 3
#define DEBUG_LEVEL_5      1 << 4
#define DEBUG_LEVEL_6      1 << 5
#define DEBUG_LEVEL_7      1 << 6
#define DEBUG_LEVEL_8      1 << 7
#define DEBUG_LEVEL_9      1 << 8
#define DEBUG_LEVEL_10      1 << 9
#define DEBUG_LEVEL_11      1 << 10
#define DEBUG_LEVEL_12      1 << 11
#define DEBUG_LEVEL_13      1 << 12
#define DEBUG_LEVEL_14      1 << 13
#define DEBUG_LEVEL_15      1 << 14
#define DEBUG_LEVEL_16      1 << 15
#define DEBUG_LEVEL_17      1 << 16
#define DEBUG_LEVEL_18      1 << 17
#define DEBUG_LEVEL_19      1 << 18
#define DEBUG_LEVEL_20      1 << 19
#define DEBUG_LEVEL_21      1 << 20
#define DEBUG_LEVEL_22      1 << 21
#define DEBUG_LEVEL_23      1 << 22
#define DEBUG_LEVEL_24      1 << 23
#define DEBUG_LEVEL_25      1 << 24
#define DEBUG_LEVEL_26      1 << 25
#define DEBUG_LEVEL_27      1 << 26
#define DEBUG_LEVEL_28      1 << 27
#define DEBUG_LEVEL_29      1 << 28
#define DEBUG_LEVEL_30      1 << 29
#define DEBUG_LEVEL_31      1 << 30
#define DEBUG_LEVEL_32      1 << 31

// ������ӡ�ʹ����ӡ��û����������ʱ��Ӵ��ڴ�ӡ����
#define DEBUG_NORMAL_PRINT  DEBUG_LEVEL_1
#define DEBUG_ERROR_PRINT   DEBUG_LEVEL_2

#define DEBUG_CMPLAYER_ERROR_PRINT DEBUG_LEVEL_3
#define DEBUG_CMPLAYER_NORMAL_PRINT DEBUG_LEVEL_4
#define DEBUG_VDEC_PRINT	DEBUG_LEVEL_5
//#define DEBUG_CMPLAYER_AVDEC_PRINT DEBUG_LEVEL_5
#define DEBUG_CMPLAYER_RTSP_PRINT DEBUG_LEVEL_6
#define DEBUG_PMSG_ERROR_PRINT DEBUG_LEVEL_7
#define DEBUG_PMSG_NORMAL_PRINT DEBUG_LEVEL_8
#define DEBUG_PMSG_DATA_PRINT DEBUG_LEVEL_9
#define DEBUG_RS485_DATA_PRINT DEBUG_LEVEL_10
#define DEBUG_UI_ERROR_PRINT DEBUG_LEVEL_11
#define DEBUG_UI_OPTION_PRINT DEBUG_LEVEL_12
#define DEBUG_UI_MESSAGE_PRINT DEBUG_LEVEL_13
#define DEBUG_UI_NOMAL_PRINT DEBUG_LEVEL_14
#define DEBUG_RTSP_LEVEL DEBUG_LEVEL_15


#ifdef  __cplusplus
extern "C"
{
#endif
/*************************************************
  ��������:     DebugInit
  ��������:     ��ӡ��ʹ��
  �������:     sDebugPort ��ӡ�˿�
  �������:     ��
  ����ֵ:       0-�ɹ�������ʧ��
  ���ߣ�        dingjq
  ����:         2016-06-21 
*************************************************/
int DebugInit(short sDebugPort);

/*************************************************
  ��������:     DebugUninit
  ��������:     ��ӡ����ʹ��
  �������:     ��
  �������:     ��
  ����ֵ:       ��
  ���ߣ�        dingjq
  ����:         2016-06-21 
*************************************************/
void DebugUninit(void);

/*************************************************
  ��������:     DebugCmdProcess
  ��������:     ��ӡ�����
  �������:     ��
  �������:     ��
  ����ֵ:       0-�ɹ�������ʧ��
  ���ߣ�        dingjq
  ����:         2016-06-21 
*************************************************/
int DebugCmdProcess(void);

/*************************************************
  ��������:     DebugPrint
  ��������:     ��ӡ����
  �������:     uiDebugLevel-��ӡ����
  �������:     ��
  ����ֵ:       ��
  ���ߣ�        dingjq
  ����:         2016-06-21 
*************************************************/
void DebugPrint(unsigned int uiDebugLevel,  const char *format, ...);
#ifdef  __cplusplus
}
#endif

#endif
