#include "music.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "timer.h"
#include "gizwits_product.h"
#include "led.h"
#include "GUI.h"
#include "WM.h"
#include "WindowDLG.h"
#include "common.h"

WM_HWIN hItem1;
int music_priority = 0;
dataPoint_t control_music;
bool music_warn_fever = 0;
bool equipment_warn;
void Music_1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_SetBits(GPIOF, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

void Music_2_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_Pin_8);
}


//音乐确认
void Music_stop(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐1 关闭睡醒检测
void Music_1(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐2 开始测量体温，请贴近额头或者手心
void Music_2(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐3 体温测量完成，建议多次测量
void Music_3(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐4 婴儿车开始摇摆
void Music_4(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐5 婴儿车停止摇摆
void Music_5(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐6 婴儿睡姿不正常，请及时处理
void Music_6(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐7 婴儿脸被蒙住了，请及时处理
void Music_7(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐8 开始暖奶
void Music_8(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐9 结束暖奶
void Music_9(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐10 一氧化碳超标，请及时将婴儿车移动到安全位置
void Music_10(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐11 《世上只有妈妈好》
void Music_11(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐12 《数鸭子》
void Music_12(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐13 《抓泥鳅》
void Music_13(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐14 《上学歌》
void Music_14(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐15 《小兔子乖乖》
void Music_15(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_SetBits(GPIOF, GPIO_Pin_7);
}
//音乐16 《摇篮曲》
void Music_16(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐17 《Magic Waltz》
void Music_17(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐18 婴儿尿床了，请及时处理
void Music_18(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐19 注意婴儿不在床上
void Music_19(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐20 净化器开启
void Music_20(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐21 净化器关闭
void Music_21(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐22 加湿器开启
void Music_22(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐23 加湿器关闭
void Music_23(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐24    婴儿醒来了
void Music_24(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐25    关闭音乐
void Music_25(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐26 婴儿可能发烧了，请注意
void Music_26(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐27    开启,捂被子检测
void Music_27(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_SetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐28    关闭捂被子检测
void Music_28(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐29    开启防偷模式
void Music_29(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_SetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐30    关闭防偷模式
void Music_30(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
//音乐31    开启睡醒检测
void Music_31(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_3);
    GPIO_ResetBits(GPIOF, GPIO_Pin_4);
    GPIO_ResetBits(GPIOF, GPIO_Pin_5);
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
    GPIO_ResetBits(GPIOF, GPIO_Pin_7);
}
void Music_play(void)
{
    Music_stop();
    switch (music_priority)
    {
    //case 0: Music_stop();break;
    case 1:
        Music_10();//10、一氧化碳超标，请及时将婴儿车移动到安全位置
        music_priority = 2;
        break;
    case 2:
        if (IN1 == 0)
        {
            Music_10();
            music_priority = 100;
        }
        break;
    case 3:
        Music_19();//19 ，注意婴儿不在床上
        music_priority = 4;
        break;
    case 4:
        if (IN1 == 0)
        {
            Music_19();
            music_priority = 100;
        }
        break;
    case 5:
        Music_6();//6、婴儿睡姿不正常，请及时处理
        music_priority = 6;
        break;
    case 6:
        if (IN1 == 0)
        {
            Music_6();
            music_priority = 100;
        }
        break;
    case 7:
        Music_7();//7、婴儿脸被蒙住了，请及时处理
        music_priority = 8;
        break;
    case 8:
        if (IN1 == 0)
        {
            Music_7();
            music_priority = 100;
        }
        break;
    case 11:
        Music_18();//18、婴儿尿床了，请及时处理
        music_priority = 12;
        break;
    case 12:
        if (IN1 == 0)
        {
            Music_18();
            music_priority = 100;
        }
        break;
    case 13:
        if (IN1 == 0)
        {
            Music_2();   //2、开始测量体温，请贴近额头或者口腔
            music_priority = 100;
        }
        break;
    case 14:
        if (IN1 == 0)
        {
            Music_3();           //3、体温测量完成，建议多次测量
            music_priority = 100;
        }
        break;
    case 15:
        if (IN1 == 0)
        {
            Music_4();           //4、婴儿车开始摇摆
            music_priority = 100;
        }
        break;
    case 16:
        if (IN1 == 0)
        {
            Music_5();          //5、婴儿车停止摇摆
            music_priority = 100;
        }
        break;
    case 17:
        if (IN1 == 0)
        {
            Music_8();       //8、开始暖奶
            music_priority = 100;
        }
        break;
    case 18:
        if (IN1 == 0)
        {
            Music_9();          //9、结束暖奶
            music_priority = 100;
        }
        break;
    case 19:
        if (IN1 == 0)
        {
            Music_20();      //20、净化器开启
            music_priority = 100;
        }
        break;
    case 20:
        if (IN1 == 0)
        {
            Music_21();         //21、净化器关闭
            music_priority = 100;
        }
        break;
    case 21:
        if (IN1 == 0)
        {
            Music_22();      //22、加湿器开启
            music_priority = 100;
        }
        break;
    case 22:
        if (IN1 == 0)
        {
            Music_23();         //23、加湿器关闭
            music_priority = 100;
        }
        break;
    case 23:
        if (IN1 == 0)
        {
            Music_24();         //24、婴儿醒来了
            music_priority = 100;
        }
        break;
    case 32:
        if (IN1 == 0)
        {
            Music_27();         //27、开启,捂被子检测
            music_priority = 100;
        }
        break;
    case 33:
        if (IN1 == 0)
        {
            Music_28();         //28、关闭捂被子检测
            music_priority = 100;
        }
        break;
    case 34:
        if (IN1 == 0)
        {
            Music_29();         //29、开启防偷模式
            music_priority = 100;
        }
        break;
    case 35:
        if (IN1 == 0)
        {
            Music_30();         //30、关闭防偷模式
            music_priority = 100;
        }
        break;
    case 36:
        if (IN1 == 0)
        {
            Music_31();         //31、开启睡醒检测
            music_priority = 100;
        }
        break;
    case 37:
        Music_1();         //1、关闭睡醒检测
        music_priority = 100;
        break;
    case 24:
        Music_11();
        music_priority = 100;
        break;
    case 25:
        Music_12();
        music_priority = 100;
        break;
    case 26:
        Music_13();
        music_priority = 100;
        break;
    case 27:
        Music_14();
        music_priority = 100;
        break;
    case 28:
        Music_15();
        music_priority = 100;
        break;
    case 29:
        Music_16();
        music_priority = 100;
        break;
    case 30:
        Music_25();
        music_priority = 100;
        break;
    case 31:
        Music_26();         //23、婴儿发烧了
        music_priority = 100;
        break;
    default:
        ;
        break;
    }
}

void Music_change(void)
{
    //18、婴儿尿床了，请及时处理
    if (g_warn_rain_water == 1)
    {
        if (IN1 == 0)
        {
            control_music.valuerain_water = g_warn_rain_water;
            g_warn_rain_water = 0;
            music_priority = 11;
        }
    }
    else if (g_warn_rain_water != control_music.valuerain_water)
    {
        control_music.valuerain_water = g_warn_rain_water;
        music_priority = 100;
    }
    // 婴儿睡醒
    if (g_warn_up_test == 0)
    {
        if (IN1 == 0)
        {
            control_music.valuewake_up_testing = g_warn_up_test;
            music_priority = 29;
            g_warn_up_test = 1;
            currentDataPoint.valueplay_the_music = 6;
            app_control_mcu.valueplay_the_music = 6;
        }
    }
    else if (g_warn_up_test != control_music.valuewake_up_testing)
    {
        control_music.valuewake_up_testing = g_warn_up_test;
        music_priority = 100;
    }
    //婴儿发烧了
    if (music_warn_fever != g_warn_fever)
    {
        music_warn_fever = g_warn_fever;
        if (music_warn_fever == 1)
        {
            music_priority = 31;
        }
    }
    //10、一氧化碳超标，请及时将婴儿车移动到安全位置
    if (g_warn_mq_7 == 1)
    {
        if (music_priority > 23)
        {
            music_priority = 1;
        }
        if (IN1 == 0)
        {
            control_music.valuemq_7 = g_warn_mq_7;
            g_warn_mq_7 = 0;
            music_priority = 1;
        }
    }
    else if (g_warn_mq_7 != control_music.valuemq_7)
    {
        control_music.valuemq_7 = g_warn_mq_7;
        music_priority = 100;
    }
    //7、婴儿脸被蒙住了，请及时处理
    if (g_warn_quilt == 1)
    {
        if (music_priority > 23)
        {
            music_priority = 7;
        }
        if (IN1 == 0)
        {
            control_music.valuecover_the_quilt = g_warn_quilt;
            music_priority = 7;
            g_warn_quilt = 0;
        }
    }
    else if (g_warn_quilt != control_music.valuecover_the_quilt)
    {
        control_music.valuecover_the_quilt = g_warn_quilt;
        music_priority = 0;
    }
    //19 ，注意婴儿不在床上
    if (g_warn_valueweight_on_of == 1)
    {
        if (IN1 == 0)
        {
            control_music.valueon_the_bed = g_warn_valueweight_on_of;
            music_priority = 3;
            g_warn_valueweight_on_of = 0;
        }
    }
    else if (g_warn_valueweight_on_of != control_music.valueon_the_bed)
    {
        control_music.valueon_the_bed = g_warn_valueweight_on_of;
        music_priority = 100;
    }
    //2、体温
    if (app_control_mcu.valuetemp_check != control_music.valuetemp_check)
    {
        control_music.valuetemp_check = app_control_mcu.valuetemp_check;
        if (app_control_mcu.valuetemp_check == 1)
        {
            music_priority = 13;
        }
        else
        {
            music_priority = 14;
        }
    }
    //4、摇摆
    else if (app_control_mcu.valueswing_state != control_music.valueswing_state)
    {
        control_music.valueswing_state = app_control_mcu.valueswing_state;
        if (app_control_mcu.valueswing_state == 1)
        {
            music_priority = 15;
        }
        else
        {
            music_priority = 16;
        }
    }
    //8、暖奶
    else if (app_control_mcu.valueWarm_milk != control_music.valueWarm_milk)
    {
        control_music.valueWarm_milk = app_control_mcu.valueWarm_milk;
        if (app_control_mcu.valueWarm_milk == 1)
        {
            music_priority = 17;
        }
        else
        {
            music_priority = 18;
        }
    }
    //20、净化器
    else if (app_control_mcu.valuepurifier != control_music.valuepurifier)
    {
        control_music.valuepurifier = app_control_mcu.valuepurifier;
        if (app_control_mcu.valuepurifier == 1)
        {
            music_priority = 19;
        }
        else
        {
            music_priority = 20;
        }
    }
    //   加湿器
    else if (app_control_mcu.valuehumidification != control_music.valuehumidification)
    {
        control_music.valuehumidification = app_control_mcu.valuehumidification;
        if (app_control_mcu.valuehumidification == 1)
        {
            music_priority = 21;
        }
        else
        {
            music_priority = 22;
        }
    }
    //捂被子检测
    else if (app_control_mcu.valuecover_the_quilt_switch != control_music.valuecover_the_quilt_switch)
    {
        control_music.valuecover_the_quilt_switch = app_control_mcu.valuecover_the_quilt_switch;
        if (app_control_mcu.valuecover_the_quilt_switch == 1)
        {
            music_priority = 32;
        }
        else
        {
            music_priority = 33;
        }
    }
    //防偷模式
    else if (app_control_mcu.valueweight_on_of != control_music.valueweight_on_of)
    {
        control_music.valueweight_on_of = app_control_mcu.valueweight_on_of;
        if (app_control_mcu.valueweight_on_of == 1)
        {
            music_priority = 34;
        }
        else
        {
            music_priority = 35;
        }
    }
    //睡醒检测
    else if (app_control_mcu.valuewake_up_testing_switch != control_music.valuewake_up_testing_switch)
    {
        control_music.valuewake_up_testing_switch = app_control_mcu.valuewake_up_testing_switch;
        if (app_control_mcu.valuewake_up_testing_switch == 1)
        {
            music_priority = 36;
        }
        else
        {
            music_priority = 37;
        }
    }
    //音乐
    switch (app_control_mcu.valueplay_the_music)
    {
    case 0:
        if (app_control_mcu.valueplay_the_music != control_music.valueplay_the_music)
        {
            control_music.valueplay_the_music = app_control_mcu.valueplay_the_music;
            music_priority = 30;
        }
        break;
    case 1:
        if (app_control_mcu.valueplay_the_music != control_music.valueplay_the_music)
        {
            control_music.valueplay_the_music = app_control_mcu.valueplay_the_music;
            music_priority = 24;
        }
        break;
    case 2:
        if (app_control_mcu.valueplay_the_music != control_music.valueplay_the_music)
        {
            control_music.valueplay_the_music = app_control_mcu.valueplay_the_music;
            music_priority = 25;
        }
        break;
    case 3:
        if (app_control_mcu.valueplay_the_music != control_music.valueplay_the_music)
        {
            control_music.valueplay_the_music = app_control_mcu.valueplay_the_music;
            music_priority = 26;
        }
        break;
    case 4:
        if (app_control_mcu.valueplay_the_music != control_music.valueplay_the_music)
        {
            control_music.valueplay_the_music = app_control_mcu.valueplay_the_music;
            music_priority = 27;
        }
        break;
    case 5:
        if (app_control_mcu.valueplay_the_music != control_music.valueplay_the_music)
        {
            control_music.valueplay_the_music = app_control_mcu.valueplay_the_music;
            music_priority = 28;
        }
        break;
    case 6:
        if (app_control_mcu.valueplay_the_music != control_music.valueplay_the_music)
        {
            control_music.valueplay_the_music = app_control_mcu.valueplay_the_music;
            music_priority = 29;
        }
        break;
    }
}

