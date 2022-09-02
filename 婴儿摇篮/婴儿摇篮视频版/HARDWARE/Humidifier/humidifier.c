#include "humidifier.h"
void humidifier_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_Pin_1);
}
//打开加湿器

void humidifier_on(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_1);
}
//关闭加湿器

void humidifier_off(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_1);
}


