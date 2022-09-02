#include "delay.h"
#include "sys.h"
//#include "ILI93xx.h"
#include "usart.h"
#include "touch.h"
#include "timer.h"
#include "malloc.h"
#include "GUI.h"
#include "string.h"
#include "WindowDLG.h"
#include "gizwits_product.h"
#include "led.h"
#include "key.h"
#include "watchdog.h"
#include "usart3.h"
#include "usart2.h"
#include "usart.h"
#include "adc.h"
#include "mlx.h"
#include "dht11.h"
#include "motor.h"
#include "lcd.h"
#include "purifier.h"
#include "heater.h"
#include "humidifier.h"
#include "music.h"
#include "gps.h"


//使用内部ram，分配了30K内存给emWin，图标滚动界面会有点卡
int main(void)
{
	
	 
  

    /*程序里面有软件复位，所以这段程序是需要的*/
    SystemInit();
    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //延时函数初始化
    delay_init();
    //使能CRC时钟，否则STemWin不能使用
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
    //串口初始化为9600
    usart1_init(9600);
    /******************机智云部分初始化*********************/
    //定时器3初始化,1ms一次中断
    TIM3_Int_Init(7199, 9);
    //串口3初始化
    usart3_init(9600);
    //机智云相关数据初始化
    userInit();
    //协议初始化接口
    gizwitsInit();
    LED_Init();
    //按键初始化
    keyInit();
    //watchdog reset time :10s
    watchdogInit(10);
    /******************emWin界面初始化**********************/
    //LCD初始化  ,0竖屏
    LCD_Init();//TFTLCD_Init();
    //触摸屏初始化
    TP_Init();
    //10ms中断
    TIM6_Int_Init(999, 719);
    //初始化内部内存池
    my_mem_init(SRAMIN);
    //开启存储设备，抑制窗口的闪变效应
    WM_SetCreateFlags(WM_CF_MEMDEV);
    GUI_Init();
    //显示鼠标
    GUI_CURSOR_Show();
    //更换皮肤
    BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //创建时间窗口
    CreateWindowTime();
    //创建对话框窗口
    CreateWindow();
    /********************外设模块初始化***********************/
    //电机初始化
    Motor_Config();
    //定时器4初始化,5ms一次中断
    TIM4_Int_Init(49, 7199); //10Khz的计数频率，计数到50为5ms
    //红外初始化
    MLX_Init();
    //AD采集初始化 mq-7
    MQ7_init();
    //MP3播放器初始化
    Music_1_Config();
    Music_2_Config();
    //DHT11初始化
    DHT11_Init();
    //加热器初始化
    heater_Init();
    //加湿器初始化
    humidifier_Init();
    //净化器初始化
    purifier_Init();
			usart2_init(38400);		//初始化串口2经纬度 
//		if(SkyTra_Cfg_Rate(5)!=0)	//设置定位信息更新速度为5Hz,顺便判断GPS模块是否在位. 
//	{
//   	LCD_ShowString(30,120,200,16,16,"SkyTraF8-BD Setting...");
//		do
//		{
//			usart2_init(9600);			//初始化串口3波特率为9600
//	  	SkyTra_Cfg_Prt(3);			//重新设置模块的波特率为38400
//			usart2_init(38400);			//初始化串口3波特率为38400
//      key=SkyTra_Cfg_Tp(100000);	//脉冲宽度为100ms
//		}while(SkyTra_Cfg_Rate(5)!=0&&key!=0);//配置SkyTraF8-BD的更新速率为5Hz
//	  LCD_ShowString(30,120,200,16,16,"SkyTraF8-BD Set Done!!");
//		delay_ms(500);
//		LCD_Fill(30,120,30+200,120+16,WHITE);//清除显示 
//	}
    delay_ms(200);
    printf("外设模块初始化结束\n");
    LED0 = 0;
    while (1)
    {
			
	
        watchdogFeed();
        userHandle();
        //改变播放音乐
        Music_change();
        //音乐播放
        Music_play();
        gizwitsHandle((dataPoint_t *)&currentDataPoint);
        //必须加上延时，否则屏幕无法更新
        GUI_Delay(20);
    }
}
