/*
 * Arduino.h
 *
 *  Created on: 2018��7��15��
 *      Author: Wang Xiang ��Zhangru Hao
 *
 *  MSP430F5529��Arduino���ļ�
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#define  OUTPUT   1
#define  INPUT    0
#define  HIGH     1
#define  LOW      0

void pinMode(int p ,int m);                 // ����I/O����
void digitalWrite(int i,int x);
void digitalRead(int P, int M);

void print (int x,int y,long i);            // ��ʼ����Ϊ��x,y������ʾ����Ϊi;  y--> 1,3,5,7;OLED display
void pwm_12 (int x,int y);                  // x-->����ʱ��A0��׽/�Ƚ�0�Ĵ����е���������Ϊ X us;   y-->����ռ�ձȣ��ߵ�ƽ��ռʱ��;
void interrupt_d (int x,int y,int p);       // Px.y�����ſ����½����ж�;  p-->0 pull dowm;p-->1 pull up
void interrupt_u (int x,int y,int p);       // Px.y�����ſ����������ж�;  p-->0 pull dowm;p-->1 pull up
void pwm (int T,int Ton ,int x,int y);      // T-->����;  Ton-->����ռ�ձȣ��ߵ�ƽ��ռʱ��;  �������ΪPx.y  ;P1.1~1.5 ; P1.7 ; p2.0
void adc_60 (int x,int y);                  // ����ADC ��Ĭ������ΪP6.0 ����ʼ��ʾ����Ϊ(X,Y) ����ͨ������/ѭ��������ѡ


#endif /* ARDUINO_H_ */
