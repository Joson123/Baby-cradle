#include "purifier.h"

void purifier_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_Pin_13);
}
//打开净化器
void purifier_on(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_13);
}
//关闭净化器
void purifier_off(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_13);
}



