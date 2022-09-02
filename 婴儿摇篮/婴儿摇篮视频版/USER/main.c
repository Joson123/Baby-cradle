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


//ʹ���ڲ�ram��������30K�ڴ��emWin��ͼ�����������е㿨
int main(void)
{
	
	 
  

    /*���������������λ��������γ�������Ҫ��*/
    SystemInit();
    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    //��ʱ������ʼ��
    delay_init();
    //ʹ��CRCʱ�ӣ�����STemWin����ʹ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);
    //���ڳ�ʼ��Ϊ9600
    usart1_init(9600);
    /******************�����Ʋ��ֳ�ʼ��*********************/
    //��ʱ��3��ʼ��,1msһ���ж�
    TIM3_Int_Init(7199, 9);
    //����3��ʼ��
    usart3_init(9600);
    //������������ݳ�ʼ��
    userInit();
    //Э���ʼ���ӿ�
    gizwitsInit();
    LED_Init();
    //������ʼ��
    keyInit();
    //watchdog reset time :10s
    watchdogInit(10);
    /******************emWin�����ʼ��**********************/
    //LCD��ʼ��  ,0����
    LCD_Init();//TFTLCD_Init();
    //��������ʼ��
    TP_Init();
    //10ms�ж�
    TIM6_Int_Init(999, 719);
    //��ʼ���ڲ��ڴ��
    my_mem_init(SRAMIN);
    //�����洢�豸�����ƴ��ڵ�����ЧӦ
    WM_SetCreateFlags(WM_CF_MEMDEV);
    GUI_Init();
    //��ʾ���
    GUI_CURSOR_Show();
    //����Ƥ��
    BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    //����ʱ�䴰��
    CreateWindowTime();
    //�����Ի��򴰿�
    CreateWindow();
    /********************����ģ���ʼ��***********************/
    //�����ʼ��
    Motor_Config();
    //��ʱ��4��ʼ��,5msһ���ж�
    TIM4_Int_Init(49, 7199); //10Khz�ļ���Ƶ�ʣ�������50Ϊ5ms
    //�����ʼ��
    MLX_Init();
    //AD�ɼ���ʼ�� mq-7
    MQ7_init();
    //MP3��������ʼ��
    Music_1_Config();
    Music_2_Config();
    //DHT11��ʼ��
    DHT11_Init();
    //��������ʼ��
    heater_Init();
    //��ʪ����ʼ��
    humidifier_Init();
    //��������ʼ��
    purifier_Init();
			usart2_init(38400);		//��ʼ������2��γ�� 
//		if(SkyTra_Cfg_Rate(5)!=0)	//���ö�λ��Ϣ�����ٶ�Ϊ5Hz,˳���ж�GPSģ���Ƿ���λ. 
//	{
//   	LCD_ShowString(30,120,200,16,16,"SkyTraF8-BD Setting...");
//		do
//		{
//			usart2_init(9600);			//��ʼ������3������Ϊ9600
//	  	SkyTra_Cfg_Prt(3);			//��������ģ��Ĳ�����Ϊ38400
//			usart2_init(38400);			//��ʼ������3������Ϊ38400
//      key=SkyTra_Cfg_Tp(100000);	//������Ϊ100ms
//		}while(SkyTra_Cfg_Rate(5)!=0&&key!=0);//����SkyTraF8-BD�ĸ�������Ϊ5Hz
//	  LCD_ShowString(30,120,200,16,16,"SkyTraF8-BD Set Done!!");
//		delay_ms(500);
//		LCD_Fill(30,120,30+200,120+16,WHITE);//�����ʾ 
//	}
    delay_ms(200);
    printf("����ģ���ʼ������\n");
    LED0 = 0;
    while (1)
    {
			
	
        watchdogFeed();
        userHandle();
        //�ı䲥������
        Music_change();
        //���ֲ���
        Music_play();
        gizwitsHandle((dataPoint_t *)&currentDataPoint);
        //���������ʱ��������Ļ�޷�����
        GUI_Delay(20);
    }
}
