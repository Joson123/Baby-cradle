#ifndef __USART3_H
#define __USART3_H
#include "sys.h"

extern u8   USART3_RX_BUF[600];     //���ջ���,���600�ֽ�
extern u8   USART3_TX_BUF[600];     //���ͻ���,���600�ֽ�
extern vu16 USART3_RX_STA;          //��������״̬

void usart3_init(u32 bound);        //����2��ʼ��

void USART3_IRQHandler(void);
#endif













