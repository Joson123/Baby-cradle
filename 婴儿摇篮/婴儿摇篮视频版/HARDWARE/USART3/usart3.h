#ifndef __USART3_H
#define __USART3_H
#include "sys.h"

extern u8   USART3_RX_BUF[600];     //接收缓冲,最大600字节
extern u8   USART3_TX_BUF[600];     //发送缓冲,最大600字节
extern vu16 USART3_RX_STA;          //接收数据状态

void usart3_init(u32 bound);        //串口2初始化

void USART3_IRQHandler(void);
#endif













