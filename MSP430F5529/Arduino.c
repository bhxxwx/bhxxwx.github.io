/*
 * Arduino.c
 *
 *  Created on: 2018��7��15��
 *      Author: Wang Xiang ��Zhangru Hao
 *
 *  MSP430F5529��Arduino���ļ�
 */
#include <msp430.h>
#include <IIC.h>
#include <Arduino.h>

void pwm_12 (int x,int y)
{
        int T,Ton;
        T = x;                          //����
        Ton = y;                        //�ߵ�ƽʱ��
        P1DIR |= BIT2;                  //����1.2Ϊ���
        P1SEL |= BIT2;                  //1.2���PWM
        TA0CCR0 = T;                    //����ʱ��A0��׽/�Ƚ�0�Ĵ����е���������Ϊ X us��
        TA0CCTL1 = OUTMOD_7;
        TA0CCR1 = Ton;                  //����ռ�ձȣ��ߵ�ƽ��ռʱ��
        TA0CTL = TASSEL_2 + MC_1;
}

void print (int x,int y,long i)         //OLED display
{
    long k,te,j,p,m;
    char l[11]={0};
    char temp[11]={0};
    for (j=0;;j++)
    {
        te = i%10;
        p = i/10;
        l[j] = (te+49);
        i = p;
        if (p == 0)
            break;
    }
    for (k = 0,m = j;k<=j;k++)
    {
        temp[m] = l[k];
        m--;
    }
    LCD_ShowString(x,y,temp,12);
}


void interrupt_d (int x,int y,int p)    //��Ҫ����ж�ʹ�ã���main�����·����� - #pragma vector = PORT -X- _VECTOR - __interrupt void port1(void)
{
    switch (x)
    {
    case 1:{
            P1DIR &=~(1<<y);            //����P1.yΪ����
            P1OUT = (p<<y);             //p=0->����
            P1REN |= (1<<y);            //��Ϊ����ʱ������ϴ˼Ĵ�������
            P1IE  |= (1<<y);            //��P1.y���ж�
            P1IES &=~(1<<y);            //������ʽΪ�½���
            P1IFG &=~(1<<5);            //���жϱ�־λ
            }break;
    case 2:{
            P2DIR &=~(1<<y);            //����P2.yΪ����
            P2OUT = (p<<y);             //p=0->����
            P2REN |= (1<<y);            //��Ϊ����ʱ������ϴ˼Ĵ�������
            P2IE  |= (1<<y);            //��P2.y���ж�
            P2IES &=~(1<<y);            //������ʽΪ�½���
            P2IFG &=~(1<<5);            //���жϱ�־λ
            }break;

    }
}


void interrupt_u (int x,int y,int p)
{
    switch (x)
    {
    case 1:{
            P1DIR &=~(1<<y);            //����P1.yΪ����
            P1OUT = (p<<y);             //p=0->����
            P1REN |= (1<<y);            //��Ϊ����ʱ������ϴ˼Ĵ�������
            P1IE  |= (1<<y);            //��P1.y���ж�
            P1IES &=~(0<<y);            //������ʽΪ�½���
            P1IFG &=~(1<<5);            //���жϱ�־λ
            }break;
    case 2:{
            P2DIR &=~(1<<y);            //����P2.yΪ����
            P2OUT = (p<<y);             //p=0->����
            P2REN |= (1<<y);            //��Ϊ����ʱ������ϴ˼Ĵ�������
            P2IE  |= (1<<y);            //��P2.y���ж�
            P2IES &=~(0<<y);            //������ʽΪ�½���
            P2IFG &=~(1<<5);            //���жϱ�־λ
            }break;

    }
}

void pwm (int T,int Ton,int x,int y)    //P1.2~1.5; P2.0; P2.1; P2.4; P2.5; P3.5; P3.6; P7.4~7.6
{
    switch (x)
    {
    case 1:{
        P1DIR |= (1<<y);                //�������� P1.y Ϊ���ģʽ
        P1SEL |= (1<<y);                //�������� P1.y ��Ϊ PWM ���.
        //TA0CCR0 = T;                    //���ö�ʱ�� A0 ����Ϊ T us.
        pwm1_y(T,Ton,y);
        }break;
    case 2:{
        P2DIR |= (1<<y);
        P2SEL |= (1<<y);
        //TA0CCR1 = T;
        pwm2_y(T,Ton,y);
        }break;
    case 3:{
        P3DIR |= (1<<y);
        P3SEL |= (1<<y);
        //TA0CCR1 = T;
        pwm3_y(T,Ton,y);
        }break;
    case 7:{
        P7DIR |= (1<<y);
        P7SEL |= (1<<y);
        //TA0CCR1 = T;
        pwm7_y(T,Ton,y);
        }break;
    }

}

void adc_60 (int x,int y)                      // ADC��Ҫ���ADC�ж�ʹ�ã���main�����·����� - #pragma vector=ADC12_VECTOR - __interrupt void ADC18 (void)
{
    IIC_ioinit();
    LCD_Init();
    P1DIR = BIT0;
    ADC12CTL0 = ADC12SHT0_2 + ADC12ON;         // ���ò������ֵ�ʱ��Ϊ8����ADCʱ�ӣ�Set sampling time, turn on ADC12
    ADC12CTL1 = ADC12SHP;                      // �ɲ�����ʱ������������ʱ�䣬Use sampling timer
    ADC12IE = ADC12IE0;                        // ֻʹ��ADC12MEM0�жϣ���ת�������ݴ���MEM0ʱ�жϿɴ�����Enable interrupt
    ADC12CTL0 |= ADC12ENC;                     // ʹ��ת��
    P6SEL |= 0x01;
    //for (;;)                                 // �Ƿ����� for ѭ����ʹ����ͨ��ѭ������������ע����ͨ�����β���
    //{
            ADC12CTL0 |= ADC12SC;              // Sampling open
            _BIS_SR( GIE);                     // ADC12_ISR  exit

    //}
}


void PxDIR(int i,int m,int y)
{
    switch(i)
    {
        case 1: P1DIR = (m<<y);break;
        case 2: P2DIR = (m<<y);break;
        case 3: P3DIR = (m<<y);break;
        case 4: P4DIR = (m<<y);break;
        case 5: P5DIR = (m<<y);break;
        case 6: P6DIR = (m<<y);break;
        case 7: P7DIR = (m<<y);break;
        case 8: P8DIR = (m<<y);break;
    }
}

int PxOUT(int i,int m,int y)
{
    switch(i)
    {
        case 1: P1OUT = (m<<y);break;
        case 2: P2OUT = (m<<y);break;
        case 3: P3OUT = (m<<y);break;
        case 4: P4OUT = (m<<y);break;
        case 5: P5OUT = (m<<y);break;
        case 6: P6OUT = (m<<y);break;
        case 7: P7OUT = (m<<y);break;
        case 8: P8OUT = (m<<y);break;

    }
}

int PxIN(int i,int m,int y)
{
    switch(i)
    {
        case 1: P1IN = (m<<y);break;
        case 2: P2IN = (m<<y);break;
        case 3: P3IN = (m<<y);break;
        case 4: P4IN = (m<<y);break;
        case 5: P5IN = (m<<y);break;
        case 6: P6IN = (m<<y);break;
        case 7: P7IN = (m<<y);break;
        case 8: P8IN = (m<<y);break;
    }
}

void pinMode(int p ,int m)
{
    int x,y;
    x = p / 10;
    y = p % 10;
    PxDIR(x,m,y);
}

void digitalWrite(int P, int M)
{
    int x,y;
    x = P / 10;
    y = P % 10;
    PxOUT(x,M,y);
}

void digitalRead(int P, int M)
{
    int x,y;
    x = P / 10;
    y = P % 10;
    PxIN(x,M,y);
}
void pwm1_y(int T,int Ton,int y)
{
    switch (y)
    {
         case 2:{
             TA0CCR0 = T;
             TA0CCTL1 = OUTMOD_7;
             TA0CCR1 = Ton;
             TA0CTL = TASSEL_2 + MC_1;
             }break;
         case 3:{
             TA0CCR0 = T;
             TA0CCTL2 = OUTMOD_7;
             TA0CCR2 = Ton;
             TA0CTL = TASSEL_2 + MC_1;
             }break;
         case 4:{                               //P1.4 1.5Ϊһ·�����ɴ����������PWM
             TA0CCR0 = T;
             TA0CCTL3 = OUTMOD_2;
             TA0CCR3 = Ton;
             TA0CTL = TASSEL_2 + MC_3;
             }break;
         case 5:{
              TA0CCR0 = T;
              TA0CCTL4 = OUTMOD_6;
              TA0CCR4 = Ton;
              TA0CTL = TASSEL_2 + MC_3;
              }break;
        }
}
void pwm2_y(int T,int Ton,int y)
{
    switch (y)
    {
         case 0:{
              TA1CCR0 = T;
              TA1CCTL1 = OUTMOD_7;
              TA1CCR1 = Ton;
              TA1CTL = TASSEL_2 + MC_1;
              }break;
         case 1:{
              TA1CCR0 = T;
              TA1CCTL2 = OUTMOD_7;
              TA1CCR2 = Ton;
              TA1CTL = TASSEL_2 + MC_1;
              }break;
         case 4:{
              TA2CCR0 = T;
              TA2CCTL1 = OUTMOD_7;
              TA2CCR1 = Ton;
              TA2CTL = TASSEL_2 + MC_1;
              }break;
         case 5:{
              TA2CCR2 = T;
              TA2CCTL2 = OUTMOD_7;
              TA2CCR2 = Ton;
              TA2CTL = TASSEL_2 + MC_1;
              }break;
        }
}
void pwm3_y(int T,int Ton,int y)
{
    switch (y)
    {
         case 5:{                               //P3.5 3.6Ϊһ·�����ɴ����������PWM
              TB0CCR0 = T;
              TB0CCTL5 = OUTMOD_2;
              TB0CCR5 = Ton;
              TB0CTL = TASSEL_2 + MC_3;
              }break;
         case 6:{
              TB0CCR0 = T;
              TB0CCTL6 = OUTMOD_6;
              TB0CCR6 = Ton;
              TB0CTL = TASSEL_2 + MC_3;
              }break;

    }
}
void pwm7_y(int T,int Ton,int y)
{
    switch (y)
    {
        case 4:{
              TB0CCR0 = T;
              TB0CCTL2 = OUTMOD_7;
              TB0CCR2 = Ton;
              TB0CTL = TASSEL_2 + MC_1;
              }break;
        case 5:{
              TB0CCR0 = T;
              TB0CCTL3 = OUTMOD_7;
              TB0CCR3 = Ton;
              TB0CTL = TASSEL_2 + MC_1;
              }break;
         case 6:{
              TB0CCR0 = T;
              TB0CCTL4 = OUTMOD_7;
              TB0CCR4 = Ton;
              TB0CTL = TASSEL_2 + MC_1;
              }break;
    }
}
