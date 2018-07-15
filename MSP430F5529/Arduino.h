/*
 * Arduino.h
 *
 *  Created on: 2018年7月15日
 *      Author: Wang Xiang 、Zhangru Hao
 *
 *  MSP430F5529类Arduino库文件
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#define  OUTPUT   1
#define  INPUT    0
#define  HIGH     1
#define  LOW      0

void pinMode(int p ,int m);                 // 基本I/O操作
void digitalWrite(int i,int x);
void digitalRead(int P, int M);

void print (int x,int y,long i);            // 初始坐标为（x,y），显示数据为i;  y--> 1,3,5,7;OLED display
void pwm_12 (int x,int y);                  // x-->将定时器A0捕捉/比较0寄存器中的周期设置为 X us;   y-->设置占空比，高电平所占时间;
void interrupt_d (int x,int y,int p);       // Px.y号引脚开启下降沿中断;  p-->0 pull dowm;p-->1 pull up
void interrupt_u (int x,int y,int p);       // Px.y号引脚开启上升沿中断;  p-->0 pull dowm;p-->1 pull up
void pwm (int T,int Ton ,int x,int y);      // T-->周期;  Ton-->设置占空比，高电平所占时间;  输出引脚为Px.y  ;P1.1~1.5 ; P1.7 ; p2.0
void adc_60 (int x,int y);                  // 设置ADC ，默认引脚为P6.0 ，初始显示坐标为(X,Y) ，单通道单次/循环采样可选


#endif /* ARDUINO_H_ */
