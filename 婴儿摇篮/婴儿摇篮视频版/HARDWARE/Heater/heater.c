#include "heater.h"
void heater_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_Pin_12 | GPIO_Pin_14);
}
//打开加热器
void heater_on(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_12);
    GPIO_SetBits(GPIOF, GPIO_Pin_14);
}
//关闭加热器
void heater_off(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_12);
    GPIO_ResetBits(GPIOF, GPIO_Pin_14);
}



