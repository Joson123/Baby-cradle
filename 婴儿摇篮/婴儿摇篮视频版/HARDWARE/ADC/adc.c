#include "adc.h"
#include "sys.h"
#include "delay.h"
#include "stm32f10x_adc.h"
#include "math.h"
#include "usart2.h"
//g_CAL_PPM为校准环境中的PPM值
char g_CAL_PPM = 10;
//g_mq7_RL阻值可调电阻
float g_mq7_RL = 35.7;
//定义一个全局变量的R0电阻，R0为器件在洁净空气中的电阻值
const float g_mq7_R0 = 6.20f;
//通道7  -> PA7 雨滴传感器
//通道13 -> PC3 MQ-7
//通道6 -> PA6 薄膜压力传感器
void MQ7_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    ADC_InitTypeDef ADC_InitTStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    //连续转换，否则每次转换都要使能ADC_SoftwareStartConvCmd
    ADC_InitTStruct.ADC_ContinuousConvMode = DISABLE;
    //ADC数据右对齐
    ADC_InitTStruct.ADC_DataAlign = ADC_DataAlign_Right;
    //选择SWSATART作为触发事件
    ADC_InitTStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    //单次模式
    ADC_InitTStruct.ADC_Mode = ADC_Mode_Independent;
    //顺序进行规则转换的ADC通道的数目
    ADC_InitTStruct.ADC_NbrOfChannel = 1;
    //设置为单通道模式，扫描模式只在最后一个通道转换完毕后才会产生EOC或JEOC中断
    ADC_InitTStruct.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC2, &ADC_InitTStruct);
    ADC_Cmd(ADC2, ENABLE);
    //使能复位校准 ADC_CR2 RSTCAL
    ADC_ResetCalibration(ADC2);
    //等待复位校准结束，该位由软件设置并由硬件清除
    while (ADC_GetResetCalibrationStatus(ADC2));
    //开启AD校准，CAL： A/D校准,该位由软件设置开始校准，并在校准结束时由硬件清除
    ADC_StartCalibration(ADC2);
    //等待校准结束
    while (ADC_GetCalibrationStatus(ADC2));
}
#if 0
//传感器校准函数
void MQ7_PPM_Calibration(float RS)
{
    g_mq7_R0 = RS / pow(g_CAL_PPM / 98.322, 1 / -1.458f);
}
#endif
//取五次temp_val的平均值，并且获取传感器的平均值
int Get_Adc(u8 ch)
{
    //设置指定ADC的规则组通道，转换序列，采样时间
    ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5);
    //开始转换规则通道,由软件设置,转换开始后硬件马上清除此位。
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    //ADC_FLAG_EOC = 0 转换未完成
    while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC));
    return  ADC_GetConversionValue(ADC2);
}

float Get_Adc_Average(u8 ch, u8 times)
{
    float temp_val = 0;
    u8 t;
    for (t = 0; t < times; t++)
    {
        temp_val += Get_Adc(ch);
    }
    temp_val /= times;
    return temp_val;
}
//雨滴传感器 RH
float Water(void)
{
    float data = 0;
    float val = 0;
    float voltage = 5.0;
    val = Get_Adc_Average(ADC_Channel_7, 3);
    val = val * (voltage / 4096);
    //乘以100变成%RH
    data = (voltage - val) * 100.0 / 5.0;
    return data;
}
//MQ7
float MQ7_GetPPM(void)
{
    float ppm;
    float RS;
    float voltage = 5.0;
    //Vrl等于ADC在13号通道口取五次平均值在进行AD转化
    float Vrl = voltage * Get_Adc_Average(ADC_Channel_13, 5) / 4096.0f;
    Vrl = ((float)((int)((Vrl + 0.005) * 100))) / 100;
    //根据公式RS/g_mq7_RL=(Vc-Vrl)/Vrl得到RS
    RS  = (voltage - Vrl) / Vrl * g_mq7_RL;
    //MQ7_PPM_Calibration(RS);
    //根据公式计算最后得到ppm
    ppm = 98.322f * pow(RS / g_mq7_R0, -1.458f);
    // printf("%.1f\r\n", ppm);
    return ppm;
}
float pressure_Get(void)
{
    float _data = 0.0;
    float val;
    val = Get_Adc_Average(ADC_Channel_6, 5);
    _data = (float)val * (5.0f / 4096) * 1000;
    return _data;
}
