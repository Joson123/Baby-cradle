#include "delay.h"
#include "usart3.h"
#include "gizwits_protocol.h"

//PB10 usart3_TXD
//PB11 usart3_RXD
void usart3_init(u32 bound)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                          //GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);                         //串口3时钟使能
    //USART3_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                     //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                //复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //初始化PB10
    //USART3_RX   PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                          //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //初始化PB11
    USART_InitStructure.USART_BaudRate = bound;                                    //波特率一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                //收发模式
    USART_Init(USART3, &USART_InitStructure);       //初始化串口3
    USART_Cmd(USART3, ENABLE);                      //使能串口
    //使能接收中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //开启中断
    //设置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0 ; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
}

/**
* @brief USART3 串口中断服务函数 * 接收功能，用于接收与 WiFi 模组间的串口协议数据
*@param none
* @return none
*/

void USART3_IRQHandler(void)
{
    u8 res;
    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) //接收到数据
    {
        res = USART_ReceiveData(USART3);
        gizPutData(&res, 1);
    }
    USART_ClearITPendingBit(USART3, USART_IT_RXNE);
}




