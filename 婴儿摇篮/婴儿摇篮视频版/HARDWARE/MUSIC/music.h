#ifndef MUSIC_H_
#define MUSIC_H_
#include"stm32f10x.h"
#include"stm32f10x_gpio.h"
#include "sys.h"

void Music_1_Config(void);
void Music_2_Config(void);

void Music_1(void);//����1
void Music_2(void);//����2
void Music_3(void);//����3
void Music_4(void);//����4
void Music_5(void);//����5
void Music_6(void);//����6
void Music_7(void);//����7
void Music_8(void);//����8
void Music_9(void);//����9
void Music_10(void);//����10
void Music_11(void);//����11
void Music_12(void);//����12
void Music_13(void);//����13
void Music_14(void);//����14
void Music_15(void);//����15
void Music_16(void);//����16
void Music_17(void);//����17
void Music_18(void);//����18
void Music_19(void);//����19
void Music_20(void);//����20
void Music_21(void);//����21
void Music_22(void);//����22
void Music_23(void);//����23
void Music_24(void);//����24
void Music_25(void);//����25
void Music_25(void);//����26

void Music_change(void);
void Music_play(void);//Ӧ������
void Music_stop(void);//����ֹͣ

extern int music_priority;

#define  IN1   PFin(8)


#endif
