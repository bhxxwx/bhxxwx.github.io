/*
 * IIC.h
 *
 *  Created on: 2018��7��12��
 *      Author: Wang Xiang
 *
 *  MSP430F5529��Arduino���ļ�
 *  IICЭ����OLEDͨѶЭ�飬OLED��ʾ�����װ��<Arduino.h>��
 *
 *      P6.3 --> SCL
 *      P6.4 --> SDA
 */

#ifndef IIC_H_
#define IIC_H_

#include    <msp430f5529.h>
#include    <msp430.h>
//IICͨ�Žӿ���������궨��
#define   SCL_HIGH    P6OUT|=BIT3               //��������6.3Ϊ�ߵ�ƽʱ�����
#define   SCL_LOW     P6OUT&=~BIT3              //��������6.3Ϊ�͵�ƽʱ�����
#define   SDA_HIGH    P6OUT|=BIT4               //��������6.4Ϊ�ߵ�ƽʱ�����
#define   SDA_LOW     P6OUT&=~BIT4              //��������6.4Ϊ�͵�ƽʱ�����
#define XLevelL           0x00                  //��λ��ַ
#define XLevelH           0x10                  //��λ��ַ
#define XLevel            ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column        128                   //�����Ļ���ؿ��
#define Max_Row           64                    //�����Ļ���ؿ��
#define Brightness        0xCF                  //IIC��ʼ��ַ
#define X_WIDTH           128                   //��Ļ���ؿ��
#define Y_WIDTH           64                    //��Ļ���ظ߶�
void IIC_delayus(unsigned int i);
void IIC_ioinit(void);                          //��ʼ��IIC
void IIC_start(void);                           //��ʼIICͨ��
void IIC_stop(void);                            //����IICͨ��
void IIC_writebyte(unsigned char IIC_byte);     //д�ֽ�
void IIC_writecmd(unsigned char IIC_command);       //д����
void IIC_writedata(unsigned char IIC_data);         //д����
void LCD_Set_Pos(unsigned char x, unsigned char y); //������ʾλ��
void LCD_CLS(void);                                 //����
void LCD_Init(void);                                //OLED����ʼ��
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);//��ʾ�ַ�
void LCD_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size);//��ʾ�ַ���
void LCD_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size2);//��ʾ����
unsigned long oled_pow(unsigned char m,unsigned char n);//�ַ����ݺ���




#endif /* IIC_H_ */
