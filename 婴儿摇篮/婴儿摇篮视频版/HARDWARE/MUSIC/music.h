#ifndef MUSIC_H_
#define MUSIC_H_
#include"stm32f10x.h"
#include"stm32f10x_gpio.h"
#include "sys.h"

void Music_1_Config(void);
void Music_2_Config(void);

void Music_1(void);//“Ù¿÷1
void Music_2(void);//“Ù¿÷2
void Music_3(void);//“Ù¿÷3
void Music_4(void);//“Ù¿÷4
void Music_5(void);//“Ù¿÷5
void Music_6(void);//“Ù¿÷6
void Music_7(void);//“Ù¿÷7
void Music_8(void);//“Ù¿÷8
void Music_9(void);//“Ù¿÷9
void Music_10(void);//“Ù¿÷10
void Music_11(void);//“Ù¿÷11
void Music_12(void);//“Ù¿÷12
void Music_13(void);//“Ù¿÷13
void Music_14(void);//“Ù¿÷14
void Music_15(void);//“Ù¿÷15
void Music_16(void);//“Ù¿÷16
void Music_17(void);//“Ù¿÷17
void Music_18(void);//“Ù¿÷18
void Music_19(void);//“Ù¿÷19
void Music_20(void);//“Ù¿÷20
void Music_21(void);//“Ù¿÷21
void Music_22(void);//“Ù¿÷22
void Music_23(void);//“Ù¿÷23
void Music_24(void);//“Ù¿÷24
void Music_25(void);//“Ù¿÷25
void Music_25(void);//“Ù¿÷26

void Music_change(void);
void Music_play(void);//”¶”√“Ù¿÷
void Music_stop(void);//“Ù¿÷Õ£÷π

extern int music_priority;

#define  IN1   PFin(8)


#endif
