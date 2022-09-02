#ifndef __MOTOR_H_
#define __MOTOR_H_
#include"stm32f10x.h"
#include"stm32f10x_gpio.h"
#include "sys.h"
#define END    PFout(3)

void Motor_Config(void);

void Motor_1_STOP(void);

void Motor_1_Run(void);

extern int g_motor_i;

#endif
