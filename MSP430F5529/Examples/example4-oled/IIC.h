/*
 * IIC.h
 *
 *  Created on: 2018年7月12日
 *      Author: Wang Xiang
 *
 *  MSP430F5529类Arduino库文件
 *  IIC协议与OLED通讯协议，OLED显示程序封装在<Arduino.h>中
 *
 *      P6.3 --> SCL
 *      P6.4 --> SDA
 */

#ifndef IIC_H_
#define IIC_H_

#include    <msp430f5529.h>
#include    <msp430.h>
//IIC通信接口引脚输出宏定义
#define   SCL_HIGH    P6OUT|=BIT3               //定义引脚6.3为高电平时的输出
#define   SCL_LOW     P6OUT&=~BIT3              //定义引脚6.3为低电平时的输出
#define   SDA_HIGH    P6OUT|=BIT4               //定义引脚6.4为高电平时的输出
#define   SDA_LOW     P6OUT&=~BIT4              //定义引脚6.4为低电平时的输出
#define XLevelL           0x00                  //低位地址
#define XLevelH           0x10                  //高位地址
#define XLevel            ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column        128                   //最大屏幕像素宽度
#define Max_Row           64                    //最大屏幕像素宽度
#define Brightness        0xCF                  //IIC起始地址
#define X_WIDTH           128                   //屏幕像素宽度
#define Y_WIDTH           64                    //屏幕像素高度
void IIC_delayus(unsigned int i);
void IIC_ioinit(void);                          //初始化IIC
void IIC_start(void);                           //开始IIC通信
void IIC_stop(void);                            //结束IIC通信
void IIC_writebyte(unsigned char IIC_byte);     //写字节
void IIC_writecmd(unsigned char IIC_command);       //写命令
void IIC_writedata(unsigned char IIC_data);         //写数据
void LCD_Set_Pos(unsigned char x, unsigned char y); //设置显示位置
void LCD_CLS(void);                                 //清屏
void LCD_Init(void);                                //OLED屏初始化
void LCD_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);//显示字符
void LCD_ShowString(unsigned char x,unsigned char y,unsigned char *chr,unsigned char Char_Size);//显示字符串
void LCD_ShowNum(unsigned char x,unsigned char y,unsigned long num,unsigned char len,unsigned char size2);//显示数字
unsigned long oled_pow(unsigned char m,unsigned char n);//字符求幂函数




#endif /* IIC_H_ */
