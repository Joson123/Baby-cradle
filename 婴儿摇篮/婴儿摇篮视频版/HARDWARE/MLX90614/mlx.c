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
    /*����Ϊ���缫��©���*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1);
}


/**
* @���� I2Cͨ��״̬�ı�����ʱ
* @˵�� ��
* @���� ��
* @����ֵ ��
*/
void I2C_Delay(void)
{
    delay_us(2);
}
/**
* @���� ����ͨѶ��ʼ�ź�
* @˵�� MLX90614��SCK=1ʱ����⵽SDA��1��0��ʾͨ�ſ�ʼ
* @���� ��
* @����ֵ ��
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
* @���� ����ͨѶֹͣ�ź�
* @˵�� MLX90614��SCK=1ʱ����⵽SDA��0��1��ʾͨ�Ž���
* @���� ��
* @����ֵ ��
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
* @���� ��RAM/EEPROM�ж�ȡһ���ֽ�����
* @˵�� ��MLX90614�е�ָ����ַ��ȡһ���ֽ�����,��λ��ǰ����λ�ں�
* @���� ack_nack:����Ӧ���ź�
* @����ֵ dat: ��ȡ������
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
    //��8��ʱ���½���
    ClrBit_SCK;
    delay_us(3 * N);
    if (!ack_nack)
        //�ڵ�9��ʱ�������أ���������Ӧ���ź�
        ClrBit_SDA;
    else
        //�ڵ�9��ʱ�������أ���������Ӧ���ź�
        SetBit_SDA;
    delay_us(3 * N);
    SetBit_SCK;
    delay_us(4 * N);
    ClrBit_SCK;
    delay_us(4 * N);
    return dat;
}
/**
* @���� ��EEPROMдһ���ֽ�����
* @˵�� ��д��һ���ֽں���MLX6014�Ƿ�����Ӧ���ź�
* @���� dat����Ҫ���͵��ֽ�
* @����ֵ s_ack��Ӧ���ź�״̬
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
        //�ı�SDA״̬
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
        //SCK������д������
        SetBit_SCK;
        delay_us(4 * N);
    }
    //��8���½��ؿ�ʼ��MLX90614��SDA��Ϊ�͵�ƽ����������Ƿ���ȷ����
    ClrBit_SCK;
    SetBit_SDA;
    delay_us(2 * N);
    //��9�������غ��������SDA״̬
    SetBit_SCK;
    //�ߵ�ƽ��ʾ��ȷ��������$MLX90614.C
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
* @���� ����PEC����У����,���ݽ��յ��ֽڼ���PEC��
* @˵�� ���㴫�����ݵ�PEC��
* @���� pec[]�����������
            n���������ݸ���
* @����ֵ pec[0]������õ���PECֵ
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
        //���� CRC��ֵ 0x000000000107
        crc[5] = 0;
        crc[4] = 0;
        crc[3] = 0;
        crc[2] = 0;
        crc[1] = 0x01;
        crc[0] = 0x07;
        //����Bitposition�����ֵΪ47
        Bitposition = 47;
        shift = 0;
        //�ڴ��͵��ֽ����ҳ���һ����1��
        i = 5; //������߱�־λ (�����ֽڱ�־)
        j = 0; //�ֽ�λ��־�������λ��ʼ
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
        }//while�����������ҳ�Bitposition��Ϊ��1�������λλ��
        shift = Bitposition - 8;
        //�õ�CRC��ֵ��Ҫ����/���Ƶ���ֵ��shift��
        //��CRC�������ơ�shift��λ
        while (shift)
        {
            for (i = 5; i < 0xFF; i--)
            {
                if ((crc[i - 1] & 0x80) && (i > 0)) //�˶��ֽڵ����λ����һλ�Ƿ�Ϊ"1"
                {
                    //�� - ��ǰ�ֽ� + 1
                    temp = 1;                //�� - ��ǰ�ֽ� + 0
                }                            //ʵ���ֽ�֮���ƶ���1��
                else
                {
                    temp = 0;
                }
                crc[i] <<= 1;
                crc[i] += temp;
            }
            shift--;
        }
        for (i = 0; i <= 5; i++) //pec��crc֮�����������
        {
            pec[i] ^= crc[i];
        }
    }
    while (Bitposition > 8);
    return pec[0]; //���ؼ������õ�crc��ֵ
}

/**
* @���� ��MLX90614��RAM������
* @˵�� ��Ҫ��ȡ�����������¶ȣ������¶�1�������¶�2
* �����ӵ�ַ����ͨ����EEPROM��SMBus��ַ0x0E��д���������趨��
* @���� saddr���ӻ���ַ��7λ��ַ���κ�MLX90614�����0x00��ַ������Ӧ
* cmd������¶ȵļĴ�����ַ
* @����ֵ Data����ȡ��������ֵ
*/
uint16_t I2C_ReadRAM(uint8_t saddr, uint8_t cmd)
{
    uint16_t Data;
    uint8_t DataL; //�������ݵ��ֽ�
    uint8_t DataH; //�������ݸ��ֽ�
    uint8_t PEC;
    uint8_t retry = 10; //ʧ���ظ�����
    uint8_t s_ack = 0;
    uint8_t Pecreg; //�����PECֵ
    uint8_t buf[6]; //�洢�ѽ������ݵĻ���
    ClrBit_SCK;
    while (retry--)
    {
        I2C_Start(); //������ʼλ
        s_ack = I2C_WriteByte((saddr << 1) | WR); //���ʹӻ���ַ��Wrλ
        if (s_ack == ACK_SUCCESS)
        {
            s_ack = 0;
            s_ack = I2C_WriteByte(RAM_ACCESS | cmd);
            //�������8λ��RAM��ʾ��RAM������cmd��ʾ����RAM�ĵ�ַ
            if (s_ack == ACK_SUCCESS)
            {
                s_ack = 0;
                I2C_Start(); //���·�����ʼλ
                s_ack = I2C_WriteByte((saddr << 1) + 1); //���ʹӻ���ַ��Rdλ
                if (s_ack == ACK_SUCCESS)
                {
                    s_ack = 0;
                    DataL = I2C_ReadByte(1); //�����ݵ��ֽ�
                    DataH = I2C_ReadByte(1); //�����ݸ��ֽ�
                    PEC = I2C_ReadByte(1); //������PEC�ֽ�
                    // DataL=RX_byte(0); //$MLX90614.C
                    // DataH=RX_byte(0); //
                    // PEC=RX_byte(1);
                    I2C_Stop(); //����ֹͣλ
                    buf[5] = (saddr << 1);
                    buf[4] = EEPROM_ACCESS | cmd;
                    buf[3] = (saddr << 1) | RD;
                    buf[2] = DataL;
                    buf[1] = DataH;
                    buf[0] = 0;
                    Pecreg = PEC_Cal(buf, 6); //���ü��� PEC �ĺ���
                    if (Pecreg == PEC)
                    {
                        break; //�˳�ѭ��
                    }
                }
                else goto stop_rr;
            }
            else goto stop_rr;
        }
        else goto stop_rr;
stop_rr:
        I2C_Stop(); //����ֹͣλ,оƬ����ʧ��
    }
    PEC = PEC + 1;
    Data = (DataH << 8) + DataL;
    return Data;
}

float standard[3] = {36.2, 36.4, 37.3};
float actual[3] = {31.9, 32.1, 34.0};

/*
*�������ܣ����������㷨�����ڼ������ֵ�ͱ�׼ֵ֮���ƫ��
*������N:Ĭ������ actual��ʵ�ʲ��ֵ standard����׼��ֵ value����β��ֵ
*����ֵ��У׼���ֵ
*��ע��Ҫô��������adֵ��Ҫô����ֵΪadת���ɵ���ʵģ��ֵ
*/
float Lagrange(const int n, const float actual[], const float standard[], const float value)
{
    /*����������*/
    float result;
    /*��ʱ����*/
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
    /*����ת�����ֵ*/
    return result;
}

//�Ƚϴ�С
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
    //ȡ n��У׼������ ����ƽ��ֵ
    char n = 30;
    for (i = 0; i < n; i++)
    {
        i2c_RAM = I2C_ReadRAM(SA, RAM_ACCESS | RAM_TOBJ1);
        temp[i] = i2c_RAM * 0.02 - 273.15 ;
        //  �¶Ȳ��� 3������d
        temp[i] = Lagrange(3, actual, standard, temp[i]);
    }
    qsort(temp, n, sizeof(float), inc);
    //��С��ֵƫ��
    for (i = 14; i < n - 12; i++)
    {
        sum += temp[i];
    }
    //����(n-4)��ƽ��ֵ
    sum =  sum / (n - 12 - 14);
    return sum;
}


