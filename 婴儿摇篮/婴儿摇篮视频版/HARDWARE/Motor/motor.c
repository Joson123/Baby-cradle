#include "motor.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "timer.h"
#include "GUI.h"

//初始化PF1,PF0输出
void Motor_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_Pin_0 | GPIO_Pin_2);
}
//电机1停止
void Motor_1_STOP(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_0);
    GPIO_ResetBits(GPIOF, GPIO_Pin_2);
}

//电机1正转
void Motor_1_Run(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_2);
    GPIO_ResetBits(GPIOF, GPIO_Pin_2);
}

