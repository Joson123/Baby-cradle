#ifndef MLX2_H
#define MLX2_H
#include "stm32f10x.h"

//-- IO Operate --
#define SetBit_SDA              PCout(1) = 1
#define ClrBit_SDA              PCout(1) = 0
#define SetBit_SCK              PCout(0) = 1
#define ClrBit_SCK              PCout(0) = 0
#define STA_SDA                 PCin(1)

#define SA              0x00    //Slave address ����MLX90614ʱ��ַΪ0x00,���ʱ��ַĬ��Ϊ0x5a

//-- MLX90614 Command Mode --
#define RAM_ACCESS      0x00    //�� RAM ���в���
#define EEPROM_ACCESS   0x20    //�� EEPROM ���в���
#define MODE            0x60    //��������ģʽ
#define EXITMODE        0x61    //�˳�����ģʽ
#define READFLAG        0xf0    //����־
#define SLEEP           0xff    //����˯��ģʽ
#define RD              0x01    //������
#define WR              0x00    //д����

//-- MLX90614 RAM Address --
#define AMBITEMPADDR    0x03    //��Χ�¶�
#define ENVITEMPADDR    0x06    //�����¶� -40 ~ 125 ��
#define RAM_TOBJ1       0x07    //Ŀ��1�����¶�-70.01 ~ 382.19 ��
#define RAM_TOBJ2       0x08    //Ŀ��2�����¶�-70.01 ~ 382.19 ��

//-- MLX90614 EEPROM Address --
#define TOBJMAXADDR     0x00    //�����¶������趨
#define TOBJMINADDR     0x01    //�����¶������趨
#define PWMCTRLADDR     0x02    //PWM�趨
#define TARANGEADDR     0x03    //�����¶��趨
#define KEADDR          0x04    //Ƶ������ϵ��
#define CONFIGADDR      0x05    //���üĴ���
#define SMBUSADDR       0x0e    //������ַ�趨
#define RES1ADDR        0x0f    //����
#define RES2ADDR        0x19    //����
#define ID1ADDR         0x1c    //ID��ַ1
#define ID2ADDR         0x1d    //ID��ַ2
#define ID3ADDR         0x1e    //ID��ַ3
#define ID4ADDR         0x1f    //ID��ַ4

//-- Special Define --
#define ACK_SUCCESS     0x01    //�ɹ����յ�Ӧ���ź�
#define ACK_FAIL        0x00    //û���յ�Ӧ���ź�
#define N               5

uint16_t I2C_ReadRAM(uint8_t saddr, uint8_t cmd);

void MLX_Init(void);
float ReadTemp(void);
float Lagrange(const int n, const float actual[], const float standard[], const float value);

#endif

