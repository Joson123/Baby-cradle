#ifndef MLX2_H
#define MLX2_H
#include "stm32f10x.h"

//-- IO Operate --
#define SetBit_SDA              PCout(1) = 1
#define ClrBit_SDA              PCout(1) = 0
#define SetBit_SCK              PCout(0) = 1
#define ClrBit_SCK              PCout(0) = 0
#define STA_SDA                 PCin(1)

#define SA              0x00    //Slave address 单个MLX90614时地址为0x00,多个时地址默认为0x5a

//-- MLX90614 Command Mode --
#define RAM_ACCESS      0x00    //对 RAM 进行操作
#define EEPROM_ACCESS   0x20    //对 EEPROM 进行操作
#define MODE            0x60    //进入命令模式
#define EXITMODE        0x61    //退出命令模式
#define READFLAG        0xf0    //读标志
#define SLEEP           0xff    //进入睡眠模式
#define RD              0x01    //读操作
#define WR              0x00    //写操作

//-- MLX90614 RAM Address --
#define AMBITEMPADDR    0x03    //周围温度
#define ENVITEMPADDR    0x06    //环境温度 -40 ~ 125 度
#define RAM_TOBJ1       0x07    //目标1红外温度-70.01 ~ 382.19 度
#define RAM_TOBJ2       0x08    //目标2红外温度-70.01 ~ 382.19 度

//-- MLX90614 EEPROM Address --
#define TOBJMAXADDR     0x00    //测量温度上限设定
#define TOBJMINADDR     0x01    //测量温度下限设定
#define PWMCTRLADDR     0x02    //PWM设定
#define TARANGEADDR     0x03    //环境温度设定
#define KEADDR          0x04    //频率修正系数
#define CONFIGADDR      0x05    //配置寄存器
#define SMBUSADDR       0x0e    //器件地址设定
#define RES1ADDR        0x0f    //保留
#define RES2ADDR        0x19    //保留
#define ID1ADDR         0x1c    //ID地址1
#define ID2ADDR         0x1d    //ID地址2
#define ID3ADDR         0x1e    //ID地址3
#define ID4ADDR         0x1f    //ID地址4

//-- Special Define --
#define ACK_SUCCESS     0x01    //成功接收到应答信号
#define ACK_FAIL        0x00    //没有收到应答信号
#define N               5

uint16_t I2C_ReadRAM(uint8_t saddr, uint8_t cmd);

void MLX_Init(void);
float ReadTemp(void);
float Lagrange(const int n, const float actual[], const float standard[], const float value);

#endif

