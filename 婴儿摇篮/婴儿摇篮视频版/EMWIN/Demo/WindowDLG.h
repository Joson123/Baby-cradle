#ifndef _WINDOWDLG_H
#define _WINDOWDLG_H
#include "sys.h"
#include "GUI.h"
#include "DIALOG.h"
#include "stdbool.h"
#include "gizwits_product.h"
/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define ID_WINDOW_0        (GUI_ID_USER + 0x00)
#define ID_WINDOW_1        (GUI_ID_USER + 0x02)
#define ID_WINDOW_2        (GUI_ID_USER + 0x03)
#define ID_WINDOW_3        (GUI_ID_USER + 0x99)

#define ID_BUTTON_0       (GUI_ID_USER + 0x04)//��������
#define ID_BUTTON_1       (GUI_ID_USER + 0x05)//�豸����
#define ID_BUTTON_2       (GUI_ID_USER + 0x06)//���¿���
#define ID_BUTTON_3        (GUI_ID_USER + 0x07)
#define ID_EDIT_4        (GUI_ID_USER + 0x08)//�汻��
#define ID_BUTTON_5        (GUI_ID_USER + 0x09)//������
#define ID_BUTTON_6        (GUI_ID_USER + 0x010)//�豸����
#define ID_BUTTON_7        (GUI_ID_USER + 0x011)//�Ƿ�ҡ��
#define ID_BUTTON_8        (GUI_ID_USER + 0x012)//ů����
#define ID_BUTTON_9        (GUI_ID_USER + 0x013)//��ʪ��
#define ID_BUTTON_10        (GUI_ID_USER + 0x014)//�����ӿ�������
#define ID_BUTTON_11        (GUI_ID_USER + 0x015)
#define ID_BUTTON_12        (GUI_ID_USER + 0x016)//������
#define ID_BUTTON_13        (GUI_ID_USER + 0x017)//��������
#define ID_BUTTON_14        (GUI_ID_USER + 0x018)//˯�Ѽ��
#define ID_BUTTON_15        (GUI_ID_USER + 0x019)//��һҳ


#define ID_TEXT_0        (GUI_ID_USER + 0x20)//���¿���
#define ID_TEXT_1        (GUI_ID_USER + 0x21)//Ӥ������
#define ID_TEXT_2        (GUI_ID_USER + 0x22)
#define ID_TEXT_3        (GUI_ID_USER + 0x23)
#define ID_TEXT_4        (GUI_ID_USER + 0x24)
#define ID_TEXT_5        (GUI_ID_USER + 0x25)
#define ID_TEXT_6        (GUI_ID_USER + 0x26)
#define ID_TEXT_7        (GUI_ID_USER + 0x27)
#define ID_TEXT_8        (GUI_ID_USER + 0x28)
#define ID_TEXT_9        (GUI_ID_USER + 0x29)
#define ID_TEXT_10        (GUI_ID_USER + 0x30)//�����¶�
#define ID_TEXT_11        (GUI_ID_USER + 0x31)//����ʪ��
#define ID_TEXT_12        (GUI_ID_USER + 0x32)//COŨ��
#define ID_TEXT_13        (GUI_ID_USER + 0x33)//���̼��
#define ID_TEXT_14        (GUI_ID_USER + 0x34)//��ʪ��
#define ID_TEXT_15        (GUI_ID_USER + 0x35)//�汻��
#define ID_TEXT_16        (GUI_ID_USER + 0x36)//��

#define ID_BUTTON_16        (GUI_ID_USER + 0x038)//˯�Ѽ��
#define ID_BUTTON_17        (GUI_ID_USER + 0x039)//�汻�Ӽ��
#define ID_BUTTON_18        (GUI_ID_USER + 0x040)
#define ID_BUTTON_19        (GUI_ID_USER + 0x041)//��͵ģʽ
#define ID_EDIT_20        (GUI_ID_USER + 0x042)//˯��
#define ID_EDIT_21        (GUI_ID_USER + 0x043)//�ڳ���
#define ID_TEXT_17        (GUI_ID_USER + 0x44)//�汻�Ӽ��
#define ID_TEXT_18        (GUI_ID_USER + 0x45)//�汻��
#define ID_TEXT_19        (GUI_ID_USER + 0x46)//��͵ģʽ
#define ID_TEXT_20        (GUI_ID_USER + 0x47)//�ڳ���
#define ID_TEXT_21        (GUI_ID_USER + 0x48)//˯�Ѽ��
#define ID_TEXT_22        (GUI_ID_USER + 0x49)//˯��
#define ID_EDIT_23        (GUI_ID_USER + 0x050)//��

#define ID_DROPDOWN_0       (GUI_ID_USER + 0x37)//����

extern char valuemlx90614[7];
extern char valuedht11_tempe[7];
extern char valuedht11_humidity[7];
extern char valuemq_7[7];
extern char valuerain_water[7];
extern WM_HWIN g_time_win; //ʱ�䴰�ھ��
extern WM_HWIN g_main_win; //1���ھ��
extern WM_HWIN g_environment_win; //2���ھ��
extern WM_HWIN g_equipment_win; //3���ھ��
extern WM_HWIN g_baby_detection_win;//4��һҳ

extern GUI_CONST_STORAGE GUI_BITMAP bmbaby;
extern GUI_CONST_STORAGE GUI_BITMAP bmwifi;
extern GUI_CONST_STORAGE GUI_BITMAP bmoff;
extern GUI_CONST_STORAGE GUI_BITMAP bmon;
extern GUI_CONST_STORAGE GUI_BITMAP bmbabytemperature;
extern GUI_CONST_STORAGE GUI_BITMAP bmtitle;
extern GUI_CONST_STORAGE GUI_BITMAP bmbed;
extern GUI_CONST_STORAGE GUI_BITMAP bmtitle1;
extern GUI_CONST_STORAGE GUI_BITMAP bmenv;
extern GUI_CONST_STORAGE GUI_BITMAP bmsmoke;
extern GUI_CONST_STORAGE GUI_BITMAP bmenvironmenttemperature;
extern GUI_CONST_STORAGE GUI_BITMAP bmbabyweight;
extern GUI_CONST_STORAGE GUI_BITMAP bmenvironmenthumidity;
extern GUI_CONST_STORAGE GUI_BITMAP bmmilkheater;
extern GUI_CONST_STORAGE GUI_BITMAP bmnowifi;
extern GUI_CONST_STORAGE GUI_BITMAP bmswing;
extern GUI_CONST_STORAGE GUI_BITMAP bmhumidifier;
extern GUI_CONST_STORAGE GUI_BITMAP bmmusic2;
extern GUI_CONST_STORAGE GUI_BITMAP bmsafetymode;
extern GUI_CONST_STORAGE GUI_BITMAP bmwakeup;
extern GUI_CONST_STORAGE GUI_BITMAP bmcleanup;

extern GUI_CONST_STORAGE GUI_BITMAP bmbabdsscd;
extern GUI_CONST_STORAGE GUI_BITMAP bmbabyssd;
extern GUI_CONST_STORAGE GUI_BITMAP bmLockoff;
extern GUI_CONST_STORAGE GUI_BITMAP bmLockon;

extern GUI_CONST_STORAGE GUI_FONT GUI_Fontsong16;
extern GUI_CONST_STORAGE GUI_FONT GUI_Fontsong22;
extern const char Font_Close[];

extern int g_year;
extern int g_month;
extern int g_day;
extern int g_hour;
extern int g_minute;
extern u8 wifi_flag;
void CreateWindow(void);
void CreateWindowTime(void);
void MainTask1(void);
// USER START (Optionally insert additional defines)
// USER END
#endif
