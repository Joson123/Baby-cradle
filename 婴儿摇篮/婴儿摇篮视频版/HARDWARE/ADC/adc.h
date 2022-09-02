#ifndef __ADC_H
#define __ADC_H
#include "sys.h"


void MQ7_init(void);
float Get_Adc_Average(u8 ch, u8 times);
float MQ7_GetPPM(void);
int Get_Adc(u8 ch);
float Water(void);
float pressure_Get(void);
#endif


