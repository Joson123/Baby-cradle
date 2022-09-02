#include "sys.h"
#include "usart.h"
//初始化IO 串口1
//bound:波特率]
void usart1_init(u32 bound)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //使能USART1，GPIOA时钟
    USART_DeInit(USART1);  //复位串口1
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
    //USART1_RX   PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10
    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure); //根据指定的参数初始化VIC寄存器
    //USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART1, ENABLE);                    //使能串口
}
/*******************************************************************************
** 函数名称: fputc
** 功能描述:
** 参数说明: ch: [输入/出]
**           f: [输入/出]
** 返回说明: None
********************************************************************************/

/*******************************************************************************
** 函数名称: fgetc
** 功能描述:
** 参数说明: f: [输入/出]
** 返回说明: None
********************************************************************************/
/*******************************************************************************
** 函数名称: USART1_IRQHandler
** 功能描述:
** 参数说明: None
** 返回说明: None
********************************************************************************/
u8 USART_RX_BUF[USART_REC_LEN];
u16 g_tail = 0;  // 定义一个全局队列最后一个元素
u16 g_head = 0; //定义一个全局队列顶元素
void USART1_IRQHandler(void)
{
    u8 ch;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        ch =  USART_ReceiveData(USART1);
        USART_RX_BUF[g_tail++] = ch;
    }
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);          /* Clear the USART Receive interrupt */
}
/*
    循环队列每次读取接收到的三个字节，如果如果接收到的首字节为0xaa并且尾字节为0xbb，则读取中间那个字节，如果type == 1，则返回值为1，1为吐奶异常，如果type == 2，2为捂被子
则返回值为2，如果type == 3，则返回值为3，3为睡姿异常，若type为其他值，则返回零，无任何异常如果接收到数据小于三个字节，则往后循环队列往后面一个元素，返回值为0，无任何异常。
*/
char USART1_Receive(void)
{
    char type;
    if ((USART_REC_LEN + g_tail - g_head) % USART_REC_LEN >= 3)
    {
        if (USART_RX_BUF[g_head] == 0xaa && USART_RX_BUF[(g_head + 2) % USART_REC_LEN] == 0xbb)
        {
            type = USART_RX_BUF[(g_head + 1) % USART_REC_LEN];
            g_head  = (g_head + 3) % USART_REC_LEN;
            if (type == 0x00)
            {
                return type;
            }
            else if (type == 0x01)
            {
                return type;
            }
            else if (type == 0x02)
            {
                return type;
            }
            else if (type == 0x03)
            {
                return type;
            }
            else
            {
                return 4;
            }
        }
        else
        {
            g_head = (g_head + 1) % USART_REC_LEN;
            return 4;
        }
    }
    return 4;
}


