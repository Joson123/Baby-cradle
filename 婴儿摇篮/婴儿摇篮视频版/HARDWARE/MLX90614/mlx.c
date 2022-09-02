#include "mlx.h"
#include "sys.h"
#include "delay.h"
#include "stdlib.h"
#include "stdio.h"
//mlx90614
void MLX_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    /*配置为集电极开漏输出*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1);
}


/**
* @功能 I2C通信状态改变后的延时
* @说明 无
* @参数 无
* @返回值 无
*/
void I2C_Delay(void)
{
    delay_us(2);
}
/**
* @功能 产生通讯开始信号
* @说明 MLX90614在SCK=1时，检测到SDA由1到0表示通信开始
* @参数 无
* @返回值 无
*/
void I2C_Start(void)
{
    SetBit_SDA;
    SetBit_SCK;
    I2C_Delay();
    ClrBit_SDA;
    I2C_Delay();
    ClrBit_SCK;
    I2C_Delay();
}
/**
* @功能 产生通讯停止信号
* @说明 MLX90614在SCK=1时，检测到SDA由0到1表示通信结束
* @参数 无
* @返回值 无
*/
void I2C_Stop(void)
{
    ClrBit_SDA;
    ClrBit_SCK;
    I2C_Delay();
    SetBit_SCK;
    I2C_Delay();
    SetBit_SDA;
    I2C_Delay();
}

/**
* @功能 从RAM/EEPROM中读取一个字节数据
* @说明 从MLX90614中的指定地址读取一个字节数据,高位在前，低位在后
* @参数 ack_nack:主机应答信号
* @返回值 dat: 读取的数据
*/
uint8_t I2C_ReadByte(uint8_t ack_nack)
{
    uint8_t i = 0;
    uint8_t dat = 0;
    ClrBit_SCK;
    delay_us(5);
    for (i = 0; i < 8; i++)
    {
        dat = dat << 1;
        ClrBit_SCK;
        delay_us(5 * N);
        SetBit_SCK;
        delay_us(5 * N);
        if (STA_SDA)
        {
            dat = dat | 0x01;
        }
    }
    //第8个时钟下降沿
    ClrBit_SCK;
    delay_us(3 * N);
    if (!ack_nack)
        //在第9个时钟上升沿，主机发送应答信号
        ClrBit_SDA;
    else
        //在第9个时钟上升沿，主机发送应答信号
        SetBit_SDA;
    delay_us(3 * N);
    SetBit_SCK;
    delay_us(4 * N);
    ClrBit_SCK;
    delay_us(4 * N);
    return dat;
}
/**
* @功能 向EEPROM写一个字节数据
* @说明 在写完一个字节后检测MLX6014是否发送了应答信号
* @参数 dat：需要发送的字节
* @返回值 s_ack：应答信号状态
*/
uint8_t I2C_WriteByte(uint8_t dat)
{
    uint8_t i = 0;
    uint8_t s_ack = 0;
    ClrBit_SCK;
    ClrBit_SDA;
    I2C_Delay();
    for (i = 0; i < 8; i++)
    {
        ClrBit_SCK;
        delay_us(3 * N);
        //改变SDA状态
        if (dat & 0x80)
        {
            SetBit_SDA;
        }
        else
        {
            ClrBit_SDA;
        }
        dat = dat << 1;
        delay_us(4 * N);
        //SCK上升沿写入数据
        SetBit_SCK;
        delay_us(4 * N);
    }
    //第8个下降沿开始，MLX90614将SDA置为低电平供主机检测是否正确接收
    ClrBit_SCK;
    SetBit_SDA;
    delay_us(2 * N);
    //第9个上升沿后，主机检测SDA状态
    SetBit_SCK;
    //高电平表示正确接收数据$MLX90614.C
    if (STA_SDA)
    {
        s_ack = ACK_FAIL;
    }
    else
    {
        s_ack = ACK_SUCCESS;
    }
    delay_us(2 * N);
    ClrBit_SCK;
    delay_us(4 * N);
    return s_ack;
}

/**
* @功能 计算PEC包裹校验码,根据接收的字节计算PEC码
* @说明 计算传入数据的PEC码
* @参数 pec[]：传入的数据
            n：传入数据个数
* @返回值 pec[0]：计算得到的PEC值
*/
uint8_t PEC_Cal(uint8_t pec[], uint16_t n)
{
    unsigned char crc[6];
    unsigned char Bitposition = 47;
    unsigned char shift;
    unsigned char i;
    unsigned char j;
    unsigned char temp;
    do
    {
        //载入 CRC数值 0x000000000107
        crc[5] = 0;
        crc[4] = 0;
        crc[3] = 0;
        crc[2] = 0;
        crc[1] = 0x01;
        crc[0] = 0x07;
        //设置Bitposition的最大值为47
        Bitposition = 47;
        shift = 0;
        //在传送的字节中找出第一个“1”
        i = 5; //设置最高标志位 (包裹字节标志)
        j = 0; //字节位标志，从最低位开始
        while ((pec[i] & (0x80 >> j)) == 0 && (i > 0))
        {
            Bitposition--;
            if (j < 7)
            {
                j++;
            }
            else
            {
                j = 0x00;
                i--;
            }
        }//while语句结束，并找出Bitposition中为“1”的最高位位置
        shift = Bitposition - 8;
        //得到CRC数值将要左移/右移的数值“shift”
        //对CRC数据左移“shift”位
        while (shift)
        {
            for (i = 5; i < 0xFF; i--)
            {
                if ((crc[i - 1] & 0x80) && (i > 0)) //核对字节的最高位的下一位是否为"1"
                {
                    //是 - 当前字节 + 1
                    temp = 1;                //否 - 当前字节 + 0
                }                            //实现字节之间移动“1”
                else
                {
                    temp = 0;
                }
                crc[i] <<= 1;
                crc[i] += temp;
            }
            shift--;
        }
        for (i = 0; i <= 5; i++) //pec和crc之间进行异或计算
        {
            pec[i] ^= crc[i];
        }
    }
    while (Bitposition > 8);
    return pec[0]; //返回计算所得的crc数值
}

/**
* @功能 读MLX90614的RAM中内容
* @说明 主要读取三个，环境温度，物体温度1，物体温度2
* 器件从地址可以通过向EEPROM的SMBus地址0x0E中写入来进行设定。
* @参数 saddr：从机地址，7位地址，任何MLX90614都会对0x00地址作出反应
* cmd：存放温度的寄存器地址
* @返回值 Data：读取出来的数值
*/
uint16_t I2C_ReadRAM(uint8_t saddr, uint8_t cmd)
{
    uint16_t Data;
    uint8_t DataL; //接收数据低字节
    uint8_t DataH; //接收数据高字节
    uint8_t PEC;
    uint8_t retry = 10; //失败重复次数
    uint8_t s_ack = 0;
    uint8_t Pecreg; //计算的PEC值
    uint8_t buf[6]; //存储已接收数据的缓存
    ClrBit_SCK;
    while (retry--)
    {
        I2C_Start(); //发送起始位
        s_ack = I2C_WriteByte((saddr << 1) | WR); //发送从机地址和Wr位
        if (s_ack == ACK_SUCCESS)
        {
            s_ack = 0;
            s_ack = I2C_WriteByte(RAM_ACCESS | cmd);
            //发送命令，8位，RAM表示对RAM操作，cmd表示操作RAM的地址
            if (s_ack == ACK_SUCCESS)
            {
                s_ack = 0;
                I2C_Start(); //重新发送起始位
                s_ack = I2C_WriteByte((saddr << 1) + 1); //发送从机地址和Rd位
                if (s_ack == ACK_SUCCESS)
                {
                    s_ack = 0;
                    DataL = I2C_ReadByte(1); //读数据低字节
                    DataH = I2C_ReadByte(1); //读数据高字节
                    PEC = I2C_ReadByte(1); //读数据PEC字节
                    // DataL=RX_byte(0); //$MLX90614.C
                    // DataH=RX_byte(0); //
                    // PEC=RX_byte(1);
                    I2C_Stop(); //发送停止位
                    buf[5] = (saddr << 1);
                    buf[4] = EEPROM_ACCESS | cmd;
                    buf[3] = (saddr << 1) | RD;
                    buf[2] = DataL;
                    buf[1] = DataH;
                    buf[0] = 0;
                    Pecreg = PEC_Cal(buf, 6); //调用计算 PEC 的函数
                    if (Pecreg == PEC)
                    {
                        break; //退出循环
                    }
                }
                else goto stop_rr;
            }
            else goto stop_rr;
        }
        else goto stop_rr;
stop_rr:
        I2C_Stop(); //发送停止位,芯片接收失败
    }
    PEC = PEC + 1;
    Data = (DataH << 8) + DataL;
    return Data;
}

float standard[3] = {36.2, 36.4, 37.3};
float actual[3] = {31.9, 32.1, 34.0};

/*
*函数介绍：拉格朗日算法，用于计算测量值和标准值之间的偏差
*参数：N:默认三组 actual：实际测的值 standard：标准的值 value：这次测的值
*返回值：校准后的值
*备注：要么参数都是ad值，要么所有值为ad转换成的真实模拟值
*/
float Lagrange(const int n, const float actual[], const float standard[], const float value)
{
    /*用来保存结果*/
    float result;
    /*临时保存*/
    float temp;
    float temp1 = 0.0;
    char i;
    char j;
    for (i = 0; i < n; i++)
    {
        temp = standard[i];
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                temp = temp * 1.0 * (value - actual[j]) / (actual[i] - actual[j]);
            }
        }
        temp1 += temp;
    }
    result = temp1;
    /*返回转换后的值*/
    return result;
}

//比较大小
int inc(const void *a, const void *b)
{
    return *(float *)a > *(float *)b ? 1 : -1;
}

float ReadTemp(void)
{
    float temp[40];
    float sum = 0;
    int i = 0;
    int i2c_RAM;
    //取 n组校准后数据 计算平均值
    char n = 30;
    for (i = 0; i < n; i++)
    {
        i2c_RAM = I2C_ReadRAM(SA, RAM_ACCESS | RAM_TOBJ1);
        temp[i] = i2c_RAM * 0.02 - 273.15 ;
        //  温度补偿 3组数据d
        temp[i] = Lagrange(3, actual, standard, temp[i]);
    }
    qsort(temp, n, sizeof(float), inc);
    //减小极值偏差
    for (i = 14; i < n - 12; i++)
    {
        sum += temp[i];
    }
    //计算(n-4)组平均值
    sum =  sum / (n - 12 - 14);
    return sum;
}


