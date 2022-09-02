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

#define ID_BUTTON_0       (GUI_ID_USER + 0x04)//环境参数
#define ID_BUTTON_1       (GUI_ID_USER + 0x05)//设备控制
#define ID_BUTTON_2       (GUI_ID_USER + 0x06)//体温开关
#define ID_BUTTON_3        (GUI_ID_USER + 0x07)
#define ID_EDIT_4        (GUI_ID_USER + 0x08)//捂被子
#define ID_BUTTON_5        (GUI_ID_USER + 0x09)//主界面
#define ID_BUTTON_6        (GUI_ID_USER + 0x010)//设备控制
#define ID_BUTTON_7        (GUI_ID_USER + 0x011)//是否摇把
#define ID_BUTTON_8        (GUI_ID_USER + 0x012)//暖奶器
#define ID_BUTTON_9        (GUI_ID_USER + 0x013)//加湿器
#define ID_BUTTON_10        (GUI_ID_USER + 0x014)//负离子空气净化
#define ID_BUTTON_11        (GUI_ID_USER + 0x015)
#define ID_BUTTON_12        (GUI_ID_USER + 0x016)//主界面
#define ID_BUTTON_13        (GUI_ID_USER + 0x017)//环境参数
#define ID_BUTTON_14        (GUI_ID_USER + 0x018)//睡醒检测
#define ID_BUTTON_15        (GUI_ID_USER + 0x019)//下一页


#define ID_TEXT_0        (GUI_ID_USER + 0x20)//体温开关
#define ID_TEXT_1        (GUI_ID_USER + 0x21)//婴儿体温
#define ID_TEXT_2        (GUI_ID_USER + 0x22)
#define ID_TEXT_3        (GUI_ID_USER + 0x23)
#define ID_TEXT_4        (GUI_ID_USER + 0x24)
#define ID_TEXT_5        (GUI_ID_USER + 0x25)
#define ID_TEXT_6        (GUI_ID_USER + 0x26)
#define ID_TEXT_7        (GUI_ID_USER + 0x27)
#define ID_TEXT_8        (GUI_ID_USER + 0x28)
#define ID_TEXT_9        (GUI_ID_USER + 0x29)
#define ID_TEXT_10        (GUI_ID_USER + 0x30)//环境温度
#define ID_TEXT_11        (GUI_ID_USER + 0x31)//环境湿度
#define ID_TEXT_12        (GUI_ID_USER + 0x32)//CO浓度
#define ID_TEXT_13        (GUI_ID_USER + 0x33)//吐奶检测
#define ID_TEXT_14        (GUI_ID_USER + 0x34)//尿床湿度
#define ID_TEXT_15        (GUI_ID_USER + 0x35)//捂被子
#define ID_TEXT_16        (GUI_ID_USER + 0x36)//℃

#define ID_BUTTON_16        (GUI_ID_USER + 0x038)//睡醒检测
#define ID_BUTTON_17        (GUI_ID_USER + 0x039)//捂被子检测
#define ID_BUTTON_18        (GUI_ID_USER + 0x040)
#define ID_BUTTON_19        (GUI_ID_USER + 0x041)//防偷模式
#define ID_EDIT_20        (GUI_ID_USER + 0x042)//睡醒
#define ID_EDIT_21        (GUI_ID_USER + 0x043)//在车上
#define ID_TEXT_17        (GUI_ID_USER + 0x44)//捂被子检测
#define ID_TEXT_18        (GUI_ID_USER + 0x45)//捂被子
#define ID_TEXT_19        (GUI_ID_USER + 0x46)//防偷模式
#define ID_TEXT_20        (GUI_ID_USER + 0x47)//在车上
#define ID_TEXT_21        (GUI_ID_USER + 0x48)//睡醒检测
#define ID_TEXT_22        (GUI_ID_USER + 0x49)//睡醒
#define ID_EDIT_23        (GUI_ID_USER + 0x050)//尿床

#define ID_DROPDOWN_0       (GUI_ID_USER + 0x37)//音乐

extern char valuemlx90614[7];
extern char valuedht11_tempe[7];
extern char valuedht11_humidity[7];
extern char valuemq_7[7];
extern char valuerain_water[7];
extern WM_HWIN g_time_win; //时间窗口句柄
extern WM_HWIN g_main_win; //1窗口句柄
extern WM_HWIN g_environment_win; //2窗口句柄
extern WM_HWIN g_equipment_win; //3窗口句柄
extern WM_HWIN g_baby_detection_win;//4下一页

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
