#include "sys.h"
#include "usart.h"
//��ʼ��IO ����1
//bound:������]
void usart1_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE); //ʹ��USART1��GPIOAʱ��
    USART_DeInit(USART1);  //��λ����1
    //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
    //USART1_RX   PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10
    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3 ; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;      //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
    //USART ��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
}
/*******************************************************************************
** ��������: fputc
** ��������:
** ����˵��: ch: [����/��]
**           f: [����/��]
** ����˵��: None
********************************************************************************/

/*******************************************************************************
** ��������: fgetc
** ��������:
** ����˵��: f: [����/��]
** ����˵��: None
********************************************************************************/
/*******************************************************************************
** ��������: USART1_IRQHandler
** ��������:
** ����˵��: None
** ����˵��: None
********************************************************************************/
u8 USART_RX_BUF[USART_REC_LEN];
u16 g_tail = 0;  // ����һ��ȫ�ֶ������һ��Ԫ��
u16 g_head = 0; //����һ��ȫ�ֶ��ж�Ԫ��
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
    ѭ������ÿ�ζ�ȡ���յ��������ֽڣ����������յ������ֽ�Ϊ0xaa����β�ֽ�Ϊ0xbb�����ȡ�м��Ǹ��ֽڣ����type == 1���򷵻�ֵΪ1��1Ϊ�����쳣�����type == 2��2Ϊ�汻��
�򷵻�ֵΪ2�����type == 3���򷵻�ֵΪ3��3Ϊ˯���쳣����typeΪ����ֵ���򷵻��㣬���κ��쳣������յ�����С�������ֽڣ�������ѭ������������һ��Ԫ�أ�����ֵΪ0�����κ��쳣��
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


