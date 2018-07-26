/*
 * Arduino.c
 *
 *  Created on: 2018年7月15日
 *      Author: Wang Xiang 、Zhangru Hao
 *
 *  MSP430F5529类Arduino库文件
 */
#include <msp430.h>
#include <IIC.h>
#include <Arduino.h>

void pwm_12 (int x,int y)
{
        int T,Ton;
        T = x;                          //周期
        Ton = y;                        //高电平时间
        P1DIR |= BIT2;                  //设置1.2为输出
        P1SEL |= BIT2;                  //1.2输出PWM
        TA0CCR0 = T;                    //将定时器A0捕捉/比较0寄存器中的周期设置为 X us。
        TA0CCTL1 = OUTMOD_7;
        TA0CCR1 = Ton;                  //设置占空比，高电平所占时间
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


void interrupt_d (int x,int y,int p)    //需要配合中断使用，在main函数下方声明 - #pragma vector = PORT -X- _VECTOR - __interrupt void port1(void)
{
    switch (x)
    {
    case 1:{
            P1DIR &=~(1<<y);            //设置P1.y为输入
            P1OUT = (p<<y);             //p=0->下拉
            P1REN |= (1<<y);            //设为输入时必须加上此寄存器配置
            P1IE  |= (1<<y);            //打开P1.y口中断
            P1IES &=~(1<<y);            //触发方式为下降沿
            P1IFG &=~(1<<5);            //清中断标志位
            }break;
    case 2:{
            P2DIR &=~(1<<y);            //设置P2.y为输入
            P2OUT = (p<<y);             //p=0->下拉
            P2REN |= (1<<y);            //设为输入时必须加上此寄存器配置
            P2IE  |= (1<<y);            //打开P2.y口中断
            P2IES &=~(1<<y);            //触发方式为下降沿
            P2IFG &=~(1<<5);            //清中断标志位
            }break;

    }
}


void interrupt_u (int x,int y,int p)
{
    switch (x)
    {
    case 1:{
            P1DIR &=~(1<<y);            //设置P1.y为输入
            P1OUT = (p<<y);             //p=0->下拉
            P1REN |= (1<<y);            //设为输入时必须加上此寄存器配置
            P1IE  |= (1<<y);            //打开P1.y口中断
            P1IES &=~(0<<y);            //触发方式为下降沿
            P1IFG &=~(1<<5);            //清中断标志位
            }break;
    case 2:{
            P2DIR &=~(1<<y);            //设置P2.y为输入
            P2OUT = (p<<y);             //p=0->下拉
            P2REN |= (1<<y);            //设为输入时必须加上此寄存器配置
            P2IE  |= (1<<y);            //打开P2.y口中断
            P2IES &=~(0<<y);            //触发方式为下降沿
            P2IFG &=~(1<<5);            //清中断标志位
            }break;

    }
}

void pwm (int T,int Ton,int x,int y)    //P1.2~1.5; P2.0; P2.1; P2.4; P2.5; P3.5; P3.6; P7.4~7.6
{
    switch (x)
    {
    case 1:{
        P1DIR |= (1<<y);                //设置引脚 P1.y 为输出模式
        P1SEL |= (1<<y);                //设置引脚 P1.y 作为 PWM 输出.
        //TA0CCR0 = T;                    //设置定时器 A0 周期为 T us.
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

void adc_60 (int x,int y)                      // ADC需要配合ADC中断使用，在main函数下方声明 - #pragma vector=ADC12_VECTOR - __interrupt void ADC18 (void)
{
    IIC_ioinit();
    LCD_Init();
    P1DIR = BIT0;
    ADC12CTL0 = ADC12SHT0_2 + ADC12ON;         // 设置采样保持的时间为8倍的ADC时钟，Set sampling time, turn on ADC12
    ADC12CTL1 = ADC12SHP;                      // 由采样定时器决定采样的时间，Use sampling timer
    ADC12IE = ADC12IE0;                        // 只使能ADC12MEM0中断，即转换的数据存入MEM0时中断可触发，Enable interrupt
    ADC12CTL0 |= ADC12ENC;                     // 使能转换
    P6SEL |= 0x01;
    //for (;;)                                 // 是否是能 for 循环，使能则单通道循环采样，将其注释则单通道单次采样
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
         case 4:{                               //P1.4 1.5为一路互补可带死区输出的PWM
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
         case 5:{                               //P3.5 3.6为一路互补可带死区输出的PWM
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
