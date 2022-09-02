#ifndef __USART_H
#define __USART_H
#include "stdio.h"
#include "sys.h"

#define USART_REC_LEN 100    //定义最大接收字节数为100

extern u8 USART_RX_BUF[USART_REC_LEN];
extern u16 g_tail ;  // 定义一个全局队列最后一个元素
extern u16 g_head ; //定义一个全局队列顶元素
void usart1_init(u32 bound);
int fputc(int ch, FILE *f);
int fgetc(FILE *f);
void USART1_IRQHandler(void);
char USART1_Receive(void);
#endif


