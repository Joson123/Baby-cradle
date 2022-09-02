/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "gizwits_protocol.h"
#include "common.h"
#include "led.h"
#include "usart.h"
#include "GUI.h"
#include "WM.h"
#include "WindowDLG.h"
#include "mlx.h"
#include "adc.h"
#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "dht11.h"
#include "stm32f10x_exti.h"
#include "heater.h"
#include "humidifier.h"
#include "purifier.h"
#include "DIALOG.h"
#include "music.h"
#include "sys.h"
#include "gps.h"
#include "usart2.h"
static uint32_t timerMsCount;
static uint32_t timerMsCount;
//wifi标志位，连接成功标志位为1，连接失败标志位为0
u8 wifi_flag = 0;
/** Current datapoint */
dataPoint_t currentDataPoint;
dataPoint_t app_control_mcu;
nmea_msg gpsx; 											//GPS信息
u8 USART1_TX_BUF[USART2_MAX_RECV_LEN]; 					//串口1,发送缓存区

WM_HWIN hItem;
WM_MESSAGE Message;
//手机控制mcu的开关
//尿床警告
bool g_warn_rain_water = 0;
//一氧化碳警告
bool g_warn_mq_7 = 0;
//体重警告
bool g_warn_valueweight_on_of;
//发烧
bool g_warn_fever;
//捂被子
bool g_warn_quilt;
//睡醒
bool g_warn_up_test = 1;
float humi;
float temp;
bool wake_up_testing_state;
//gps
 	float tp;
 	float *tpla;	//纬度
 	float *tpln;	//经度

/**@} */
/**@name Gizwits User Interface
* @{
*/
dataPoint_t currentDataPoint;

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
 switch (info->event[i])
        {
        case EVENT_temp_check:
            currentDataPoint.valuetemp_check = dataPointPtr->valuetemp_check;
            //            GIZWITS_LOG("Evt: EVENT_temp_check %d \r\n", currentDataPoint.valuetemp_check);
            //体温检测开关
            hItem = WM_GetDialogItem(g_main_win, ID_BUTTON_2);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valuetemp_check ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valuetemp_check = !app_control_mcu.valuetemp_check;
            break;
        case EVENT_swing_state:
            currentDataPoint.valueswing_state = dataPointPtr->valueswing_state;
            //            GIZWITS_LOG("Evt: EVENT_swing_state %d \r\n", currentDataPoint.valueswing_state);
            //是否摇摆开关
            hItem = WM_GetDialogItem(g_equipment_win, ID_BUTTON_7);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valueswing_state ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valueswing_state = !app_control_mcu.valueswing_state;
            break;
        case EVENT_Warm_milk:
            currentDataPoint.valueWarm_milk = dataPointPtr->valueWarm_milk;
            //            GIZWITS_LOG("Evt: EVENT_Warm_milk %d \r\n", currentDataPoint.valueWarm_milk);
            //暖奶器开关
            hItem = WM_GetDialogItem(g_equipment_win, ID_BUTTON_8);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valueWarm_milk ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valueWarm_milk = !app_control_mcu.valueWarm_milk;
            break;
        case EVENT_humidification:
            currentDataPoint.valuehumidification = dataPointPtr->valuehumidification;
            //            GIZWITS_LOG("Evt: EVENT_humidification %d \r\n", currentDataPoint.valuehumidification);
            //加湿器开关
            hItem = WM_GetDialogItem(g_equipment_win, ID_BUTTON_9);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valuehumidification ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valuehumidification = !app_control_mcu.valuehumidification;
            break;
        case EVENT_weight_on_of:
            currentDataPoint.valueweight_on_of = dataPointPtr->valueweight_on_of;
            //            GIZWITS_LOG("Evt: EVENT_weight_on_of %d \r\n", currentDataPoint.valueweight_on_of);
            //体重检测开关
            hItem = WM_GetDialogItem(g_baby_detection_win, ID_BUTTON_19);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valueweight_on_of ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valueweight_on_of = !app_control_mcu.valueweight_on_of;
            app_control_mcu.valueon_the_bed = currentDataPoint.valueweight_on_of;
            currentDataPoint.valueon_the_bed = currentDataPoint.valueweight_on_of;
            break;
        case EVENT_purifier:
            currentDataPoint.valuepurifier = dataPointPtr->valuepurifier;
            //            GIZWITS_LOG("Evt: EVENT_purifier %d \r\n", currentDataPoint.valuepurifier);
            //净化器开关
            hItem = WM_GetDialogItem(g_equipment_win, ID_BUTTON_10);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valuepurifier ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valuepurifier = !app_control_mcu.valuepurifier;
            break;
        case EVENT_wake_up_testing_switch:
            currentDataPoint.valuewake_up_testing_switch = dataPointPtr->valuewake_up_testing_switch;
            //            GIZWITS_LOG("Evt: EVENT_wake_up_testing_switch %d \n", currentDataPoint.valuewake_up_testing_switch);
            //睡醒检测开关
            hItem = WM_GetDialogItem(g_baby_detection_win, ID_BUTTON_16);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valuewake_up_testing_switch ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valuewake_up_testing_switch = !app_control_mcu.valuewake_up_testing_switch;
            app_control_mcu.valuewake_up_testing = currentDataPoint.valuewake_up_testing_switch;
            currentDataPoint.valuewake_up_testing = currentDataPoint.valuewake_up_testing_switch;
            break;
        case EVENT_cover_the_quilt_switch:
            currentDataPoint.valuecover_the_quilt_switch = dataPointPtr->valuecover_the_quilt_switch;
            //            GIZWITS_LOG("Evt: EVENT_cover_the_quilt_switch %d \n", currentDataPoint.valuecover_the_quilt_switch);
            //捂被子检测开关
            hItem = WM_GetDialogItem(g_baby_detection_win, ID_BUTTON_17);  //获得按钮句柄!!!
            BUTTON_SetBitmapEx(hItem, 0, app_control_mcu.valuecover_the_quilt_switch ? &bmoff : &bmon, 0, 0);
            app_control_mcu.valuecover_the_quilt_switch = !app_control_mcu.valuecover_the_quilt_switch;
            app_control_mcu.valuecover_the_quilt = currentDataPoint.valuecover_the_quilt_switch;
            currentDataPoint.valuecover_the_quilt = currentDataPoint.valuecover_the_quilt_switch;
            break;
        case EVENT_play_the_music:
            currentDataPoint.valueplay_the_music = dataPointPtr->valueplay_the_music;
            //            GIZWITS_LOG("Evt: EVENT_play_the_music %d\r\n", currentDataPoint.valueplay_the_music);
            //音乐选择开关
            switch (currentDataPoint.valueplay_the_music)
            {
            case play_the_music_VALUE0:
                hItem = WM_GetDialogItem(g_equipment_win, ID_DROPDOWN_0);
                DROPDOWN_SetSel(hItem, play_the_music_VALUE0);
                app_control_mcu.valueplay_the_music = play_the_music_VALUE0;
                break;
            case play_the_music_VALUE1:
                hItem = WM_GetDialogItem(g_equipment_win, ID_DROPDOWN_0);
                DROPDOWN_SetSel(hItem, play_the_music_VALUE1);
                app_control_mcu.valueplay_the_music = play_the_music_VALUE1;
                break;
            case play_the_music_VALUE2:
                hItem = WM_GetDialogItem(g_equipment_win, ID_DROPDOWN_0);
                DROPDOWN_SetSel(hItem, play_the_music_VALUE2);
                app_control_mcu.valueplay_the_music = play_the_music_VALUE2;
                break;
            case play_the_music_VALUE3:
                hItem = WM_GetDialogItem(g_equipment_win, ID_DROPDOWN_0);
                DROPDOWN_SetSel(hItem, play_the_music_VALUE3);
                app_control_mcu.valueplay_the_music = play_the_music_VALUE3;
                break;
            case play_the_music_VALUE4:
                hItem = WM_GetDialogItem(g_equipment_win, ID_DROPDOWN_0);
                DROPDOWN_SetSel(hItem, play_the_music_VALUE4);
                app_control_mcu.valueplay_the_music = play_the_music_VALUE4;
                break;
            case play_the_music_VALUE5:
                hItem = WM_GetDialogItem(g_equipment_win, ID_DROPDOWN_0);
                DROPDOWN_SetSel(hItem, play_the_music_VALUE5);
                app_control_mcu.valueplay_the_music = play_the_music_VALUE5;
                break;
            case play_the_music_VALUE6:
                hItem = WM_GetDialogItem(g_equipment_win, ID_DROPDOWN_0);
                DROPDOWN_SetSel(hItem, play_the_music_VALUE6);
                app_control_mcu.valueplay_the_music = play_the_music_VALUE6;
                break;
            default:
                break;
            }

      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{
 /*
    currentDataPoint.valuerain_water = ;//Add Sensor Data Collection
    currentDataPoint.valuecover_the_quilt = ;//Add Sensor Data Collection
    currentDataPoint.valueon_the_bed = ;//Add Sensor Data Collection
    currentDataPoint.valuewake_up_testing = ;//Add Sensor Data Collection
    currentDataPoint.valuedht11_tempe = ;//Add Sensor Data Collection
    currentDataPoint.valuedht11_humidity = ;//Add Sensor Data Collection
    currentDataPoint.valuemq_7 = ;//Add Sensor Data Collection
    currentDataPoint.valuemlx90614 = ;//Add Sensor Data Collection
    currentDataPoint.valuelongitude = ;//Add Sensor Data Collection
    currentDataPoint.valuelatitude = ;//Add Sensor Data Collection

    */
static uint32_t TemLastTimer = 0;
    float data = 0.0;
    float water;
		u16 i,rxlen;
    char ovjudge_type1;
    char ovjudge_type2;
    char ovjudge_type3;
    char ovjudge_type5;
    char ovjudge_type4;
    char ovjudge_type6;
    if (g_hour == gizwitsProtocol.TimeNTP.hour && g_minute == gizwitsProtocol.TimeNTP.minute && g_year)
    {
        wifi_flag = 1;
    }
    else
    {
        wifi_flag = 0;
    }
    if ((gizGetTimerCount() - TemLastTimer) > REPORT_TIME_MAX)
    {
        /*更新时间信息*/
        myGettime();
        /*更新婴儿体温*/
        if (app_control_mcu.valuetemp_check == 1)
        {
            printf("婴儿体温开关打开    ");
            data = ReadTemp();
            if (data > 0.0f)
            {
                sprintf(valuemlx90614, "%4.1f", data);
                currentDataPoint.valuemlx90614 = data;
                printf("婴儿体温:%4.1f ℃\r\n", data);
            }
            if (data > 37.5)
            {
                g_warn_fever = 1;
                printf("婴儿发烧了\r\n");
            }
            else
            {
                g_warn_fever = 0;
                printf(" 婴儿体温正常\r\n");
            }
        }
        else
        {
            printf("婴儿体温开关关闭\r\n");
            sprintf(valuemlx90614, "%4.1f", 0.0);
            currentDataPoint.valuemlx90614 = 0;
        }
        /*暖奶器*/
        if (app_control_mcu.valueWarm_milk == 1)
        {
            printf("暖奶器开关打开\r\n");
            heater_on();
        }
        else
        {
            printf("暖奶器开关关闭\r\n");
            heater_off();
        }
        /*加湿器*/
        if (app_control_mcu.valuehumidification == 1)
        {
            printf("加湿器开关打开\r\n");
            humidifier_on();
        }
        else
        {
            printf("加湿器开关关闭\r\n");
            humidifier_off();
        }
        /*体重检测(安全模式)包括防偷模式 */
        if (app_control_mcu.valueweight_on_of == 1)
        {
            printf("防偷模式开关打开    ");
            /*更新体重传感器数值*/
            data = pressure_Get();
            if (data <= 1000.0)
            {
                printf("婴儿不在车上\r\n");
                app_control_mcu.valueon_the_bed = 2;
                g_warn_valueweight_on_of = 1;
                currentDataPoint.valueon_the_bed = 2;
            }
            else
            {
                printf("婴儿在车上\r\n");
                app_control_mcu.valueon_the_bed = 1;
                g_warn_valueweight_on_of = 0;
                currentDataPoint.valueon_the_bed = 1;
            }
        }
        else
        {
            printf("防偷模式开关关闭\r\n");
            data = 0;
            g_warn_valueweight_on_of = 0;
            /*体重传感器数值置为零*/
        }
        /*净化器*/
        if (app_control_mcu.valuepurifier == 1)
        {
            printf("净化器开关打开\r\n");
            purifier_on();
        }
        else
        {
            printf("净化器开关关闭\r\n");
            purifier_off();
        }
        ovjudge_type1 = USART1_Receive();
        ovjudge_type2 = USART1_Receive();
        ovjudge_type3 = USART1_Receive();
        ovjudge_type4 = USART1_Receive();
        ovjudge_type5 = USART1_Receive();
        ovjudge_type6 = USART1_Receive();
        /*睡醒检测*/
        if (app_control_mcu.valuewake_up_testing_switch == 1)
        {
            if (ovjudge_type1 == 0x00 || ovjudge_type2 == 0x00 || ovjudge_type3 == 0x00 || ovjudge_type4 == 0x00 || ovjudge_type5 == 0x00 || ovjudge_type6 == 0x00)
            {
                app_control_mcu.valuewake_up_testing = 1;
                currentDataPoint.valuewake_up_testing = 1;
            }
            else if (ovjudge_type1 == 0x01 || ovjudge_type2 == 0x01 || ovjudge_type3 == 0x01 || ovjudge_type4 == 0x01 || ovjudge_type5 == 0x01 || ovjudge_type6 == 0x01)
            {
                app_control_mcu.valuewake_up_testing = 2;
                currentDataPoint.valuewake_up_testing = 2;
            }
        }
        /*捂被子检测*/
        if (app_control_mcu.valuecover_the_quilt_switch == 1)
        {
            if (ovjudge_type1 == 0x02 || ovjudge_type2 == 0x02 || ovjudge_type3 == 0x02 || ovjudge_type4 == 0x02 || ovjudge_type5 == 0x02 || ovjudge_type6 == 0x02)
            {
                app_control_mcu.valuecover_the_quilt = 1;
                currentDataPoint.valuecover_the_quilt = 1;
            }
            else if (ovjudge_type1 == 0x03 || ovjudge_type2 == 0x03 || ovjudge_type3 == 0x03 || ovjudge_type4 == 0x03 || ovjudge_type5 == 0x03 || ovjudge_type6 == 0x01)
            {
                app_control_mcu.valuecover_the_quilt = 2;
                currentDataPoint.valuecover_the_quilt = 2;
            }
        }
        /*如果两个开关都没打开*/
        if (app_control_mcu.valuecover_the_quilt_switch == 0 && app_control_mcu.valuewake_up_testing_switch == 0)
        {
            memset(USART_RX_BUF, 0, USART_REC_LEN);
            g_head = 0;
            g_tail = 0;
        }
        /*更新烟雾浓度 0-100*/
        data = MQ7_GetPPM();
        //        if (data > 0.0f && data < 1000.0f)
        //        {
        sprintf(valuemq_7, "%4.1f", data);
        currentDataPoint.valuemq_7 = data + 0.05;
        printf("CO浓度:%4.1f ppm    ", data);
        //      }
        if (data > 2.0)
        {
            printf("CO浓度超高\r\n");
            g_warn_mq_7 = 1;
        }
        else
        {
            printf("CO浓度正常\r\n");
            g_warn_mq_7 = 0;
        }
        /*更新环境温度，湿度 0-100*/
        DHT11_Read_Data(&temp, &humi);
        //printf("环境湿度10 %%PH\r\n");
        //printf("环境温度21 ℃\r\n");
        //if (humi > 0.0f && humi < 100.0f)
        //{
        sprintf(valuedht11_humidity, "%4.1f", humi);
        currentDataPoint.valuedht11_humidity = humi;
        //}
        //if (temp > 0.0f &&  temp < 50.0f)
        //{
        sprintf(valuedht11_tempe, "%4.1f", temp);
        currentDataPoint.valuedht11_tempe = temp;  //更新数据到云端
        //}
        /*更新雨滴传感器浓度 0-100 RH 1以上报警*/
        water = Water();
        if (water > 0.0 && water < 100.0)
        {
            printf("尿床湿度 %.1f %%RH    ", water);
            sprintf(valuerain_water, "%4.1f", water);
        }
        if (water >= 10.0)
        {
            printf("婴儿尿床了\r\n");
            g_warn_rain_water = 1;
            currentDataPoint.valuerain_water = 2;
            app_control_mcu.valuerain_water = 2;
        }
        else
        {
            printf("婴儿未尿床\r\n");
            g_warn_rain_water = 0;
            currentDataPoint.valuerain_water = 1;
            app_control_mcu.valuerain_water = 1;
        }
        if (currentDataPoint.valuewake_up_testing_switch)
        {
            printf("睡醒检测开启\r\n");
            if (currentDataPoint.valuewake_up_testing == 1)
            {
                printf("婴儿未睡醒\r\n");
                g_warn_up_test = 1;
                if (wake_up_testing_state == 1)
                {
                    app_control_mcu.valueswing_state = 0;
                    wake_up_testing_state = 0;
                    hItem = WM_GetDialogItem(g_equipment_win, ID_BUTTON_7);  //获得按钮句柄!!!
                    BUTTON_SetBitmapEx(hItem, 0, &bmoff , 0, 0);
                }
            }
            else if (currentDataPoint.valuewake_up_testing == 2)
            {
                printf("婴儿睡醒\r\n");
                g_warn_up_test = 0;
                app_control_mcu.valueswing_state = 1;
                hItem = WM_GetDialogItem(g_equipment_win, ID_BUTTON_7);  //获得按钮句柄!!!
                BUTTON_SetBitmapEx(hItem, 0, &bmon, 0, 0);
                wake_up_testing_state = 1;
            }
        }
        else
        {
            printf("睡醒检测关闭\r\n");
            if (wake_up_testing_state == 1)
            {
                app_control_mcu.valueswing_state = 0;
                wake_up_testing_state = 0;
                hItem = WM_GetDialogItem(g_equipment_win, ID_BUTTON_7);  //获得按钮句柄!!!
                BUTTON_SetBitmapEx(hItem, 0,  &bmoff, 0, 0);
                currentDataPoint.valueplay_the_music = 0;
                app_control_mcu.valueplay_the_music = 0;
            }
        }
        if (currentDataPoint.valuecover_the_quilt_switch)
        {
            printf("捂被子检测开启\r\n");
        }
        else
        {
            printf("捂被子检测关闭\r\n");
        }
        if (currentDataPoint.valuecover_the_quilt == 2)
        {
            printf("婴儿捂被子\r\n");
            g_warn_quilt = 1;
        }
        else if (currentDataPoint.valuecover_the_quilt == 1)
        {
            printf("婴儿未捂被子\r\n");
            g_warn_quilt = 0;
        }
        switch (app_control_mcu.valueplay_the_music)
        {
        case 0:
            printf("音乐关闭\r\n");
            break;
        case 1:
            printf("播放音乐：世上只有妈妈好\r\n");
            break;
        case 2:
            printf("播放音乐：数鸭子\r\n");
            break;
        case 3:
            printf("播放音乐：抓泥鳅\r\n");
            break;
        case 4:
            printf("播放音乐：上学歌\r\n");
            break;
        case 5:
            printf("播放音乐：小兔子乖乖\r\n");
            break;
        case 6:
            printf("播放音乐：摇篮曲\r\n");
            break;
        }
						//经纬度
		if(USART2_RX_STA&0X8000)		//接收到一次数据了
		{
			
			tpla=(float*)malloc(6 *sizeof(tpla));
			tpln=(float*)malloc(6 *sizeof(tpln));
			rxlen=USART2_RX_STA&0X7FFF;	//得到数据长度
		
			for(i=0;i<rxlen;i++){USART1_TX_BUF[i]=USART2_RX_BUF[i];}  
 			USART2_RX_STA=0;		   	//启动下一次接收
			USART1_TX_BUF[i]='\0';			//自动添加结束符
			GPS_Analysis(&gpsx,(u8*)USART1_TX_BUF);
			tp=gpsx.latitude; 
			*tpla=tp/100000;
			tp=gpsx.longitude;
			*tpln=tp/100000;
			GPS_transformation(*tpla,*tpln,tpla,tpln);
			tp=*tpln;
			currentDataPoint.valuelongitude=tp*10;	
			app_control_mcu.valuelongitude=tp*10;printf("%f\r\n",app_control_mcu.valuelongitude);
			tp=*tpla;
			currentDataPoint.valuelatitude=tp*10;
			app_control_mcu.valuelatitude=tp*10;
			free(tpla);free(tpln);
 		}
        WM_InvalidateWindow(g_time_win);         //时间窗口无效化
        GUI_Delay(10);
        WM_InvalidateWindow(g_main_win);         //更新窗口1和2的显示
        GUI_Delay(10);
        WM_InvalidateWindow(g_environment_win);
        GUI_Delay(10);
        WM_InvalidateWindow(g_equipment_win);
        GUI_Delay(10);
        WM_InvalidateWindow(g_baby_detection_win);
        TemLastTimer = gizGetTimerCount();
    }
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valuetemp_check = ;
      currentDataPoint.valueswing_state = ;
      currentDataPoint.valueWarm_milk = ;
      currentDataPoint.valuehumidification = ;
      currentDataPoint.valueweight_on_of = ;
      currentDataPoint.valuepurifier = ;
      currentDataPoint.valuewake_up_testing_switch = ;
      currentDataPoint.valuecover_the_quilt_switch = ;
      currentDataPoint.valueplay_the_music = ;
      currentDataPoint.valuerain_water = ;
      currentDataPoint.valuecover_the_quilt = ;
      currentDataPoint.valueon_the_bed = ;
      currentDataPoint.valuewake_up_testing = ;
      currentDataPoint.valuedht11_tempe = ;
      currentDataPoint.valuedht11_humidity = ;
      currentDataPoint.valuemq_7 = ;
      currentDataPoint.valuemlx90614 = ;
      currentDataPoint.valuelongitude = ;
      currentDataPoint.valuelatitude = ;
    */

}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
  __set_FAULTMASK(1);
    NVIC_SystemReset();
}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function ，For Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief uartWrite

* Serial write operation, send data to the WiFi module

* @param buf      : Data address
* @param len       : Data length
*
* @return : Not 0,Serial send success;
*           -1，Input Param Illegal
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }
    
    #ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);
    }
    GIZWITS_LOG("\n");
    #endif

    for(i=0; i<len; i++)
    {
				USART_SendData(USART3, buf[i]);//STM32 test demo
        while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
        //USART_SendData(UART, buf[i]);//STM32 test demo
        //Serial port to achieve the function, the buf[i] sent to the module
        if(i >=2 && buf[i] == 0xFF)
        {
						USART_SendData(USART3, 0x55);//STM32 test demo
            while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
          //Serial port to achieve the function, the 0x55 sent to the module
          //USART_SendData(UART, 0x55);//STM32 test demo
        }
    }

    
    return len;
}


