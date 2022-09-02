#include "adc.h"
#include "sys.h"
#include "delay.h"
#include "stm32f10x_adc.h"
#include "math.h"
#include "usart2.h"
//g_CAL_PPMΪУ׼�����е�PPMֵ
char g_CAL_PPM = 10;
//g_mq7_RL��ֵ�ɵ�����
float g_mq7_RL = 35.7;
//����һ��ȫ�ֱ�����R0���裬R0Ϊ�����ڽྻ�����еĵ���ֵ
const float g_mq7_R0 = 6.20f;
//ͨ��7  -> PA7 ��δ�����
//ͨ��13 -> PC3 MQ-7
//ͨ��6 -> PA6 ��Ĥѹ��������
void MQ7_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    ADC_InitTypeDef ADC_InitTStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
    //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    //����ת��������ÿ��ת����Ҫʹ��ADC_SoftwareStartConvCmd
    ADC_InitTStruct.ADC_ContinuousConvMode = DISABLE;
    //ADC�����Ҷ���
    ADC_InitTStruct.ADC_DataAlign = ADC_DataAlign_Right;
    //ѡ��SWSATART��Ϊ�����¼�
    ADC_InitTStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    //����ģʽ
    ADC_InitTStruct.ADC_Mode = ADC_Mode_Independent;
    //˳����й���ת����ADCͨ������Ŀ
    ADC_InitTStruct.ADC_NbrOfChannel = 1;
    //����Ϊ��ͨ��ģʽ��ɨ��ģʽֻ�����һ��ͨ��ת����Ϻ�Ż����EOC��JEOC�ж�
    ADC_InitTStruct.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC2, &ADC_InitTStruct);
    ADC_Cmd(ADC2, ENABLE);
    //ʹ�ܸ�λУ׼ ADC_CR2 RSTCAL
    ADC_ResetCalibration(ADC2);
    //�ȴ���λУ׼��������λ��������ò���Ӳ�����
    while (ADC_GetResetCalibrationStatus(ADC2));
    //����ADУ׼��CAL�� A/DУ׼,��λ��������ÿ�ʼУ׼������У׼����ʱ��Ӳ�����
    ADC_StartCalibration(ADC2);
    //�ȴ�У׼����
    while (ADC_GetCalibrationStatus(ADC2));
}
#if 0
//������У׼����
void MQ7_PPM_Calibration(float RS)
{
    g_mq7_R0 = RS / pow(g_CAL_PPM / 98.322, 1 / -1.458f);
}
#endif
//ȡ���temp_val��ƽ��ֵ�����һ�ȡ��������ƽ��ֵ
int Get_Adc(u8 ch)
{
    //����ָ��ADC�Ĺ�����ͨ����ת�����У�����ʱ��
    ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5);
    //��ʼת������ͨ��,���������,ת����ʼ��Ӳ�����������λ��
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
    //ADC_FLAG_EOC = 0 ת��δ���
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
//��δ����� RH
float Water(void)
{
    float data = 0;
    float val = 0;
    float voltage = 5.0;
    val = Get_Adc_Average(ADC_Channel_7, 3);
    val = val * (voltage / 4096);
    //����100���%RH
    data = (voltage - val) * 100.0 / 5.0;
    return data;
}
//MQ7
float MQ7_GetPPM(void)
{
    float ppm;
    float RS;
    float voltage = 5.0;
    //Vrl����ADC��13��ͨ����ȡ���ƽ��ֵ�ڽ���ADת��
    float Vrl = voltage * Get_Adc_Average(ADC_Channel_13, 5) / 4096.0f;
    Vrl = ((float)((int)((Vrl + 0.005) * 100))) / 100;
    //���ݹ�ʽRS/g_mq7_RL=(Vc-Vrl)/Vrl�õ�RS
    RS  = (voltage - Vrl) / Vrl * g_mq7_RL;
    //MQ7_PPM_Calibration(RS);
    //���ݹ�ʽ�������õ�ppm
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
