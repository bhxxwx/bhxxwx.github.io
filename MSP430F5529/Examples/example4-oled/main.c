#include <msp430.h> 
#include <Arduino.h>
#include <IIC.h>
/**
 * main.c
 */
static w = 20;
static j = 1;
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    _EINT();                    // ʹ�����ж�
    interrupt_d (1,5,1);        // Px.y�����ſ����½����ж�;  p-->0 pull dowm;p-->1 pull up
    interrupt_u (2,2,0);        // Px.y�����ſ����������ж�;  p-->0 pull dowm;p-->1 pull up
    IIC_ioinit();               // IICЭ���ʼ��
    LCD_Init();                 // oled��ʼ��
    while(1)
    {
        print (10,1,w);         // oled��ʾ
        print (10,3,520);       //print (int x,int y,long i); ��ʼ����Ϊ��x,y������ʾ����Ϊi;  y--> 1~7;
        print (10,5,984236571);
        print (10,7,1314);
        pwm_12(1000,w);         //P1.2�������pwm
    }

}
#pragma vector = PORT1_VECTOR
__interrupt void port1(void)    //P1.X�����жϺ���
{
    switch (j)
            {
            case 1:w++;break;
            default:w--;break;
            }
    P1IFG &=~BIT5;              //���жϱ�־λ
}
#pragma vector = PORT2_VECTOR   //P2.X�����жϺ���
__interrupt void port2(void)
{
    j = ~j;                     //jȡ��
    P2IFG &=~BIT2;              //���жϱ�־λ
}
