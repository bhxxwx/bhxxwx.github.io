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
    _EINT();                    // 使能总中断
    interrupt_d (1,5,1);        // Px.y号引脚开启下降沿中断;  p-->0 pull dowm;p-->1 pull up
    interrupt_u (2,2,0);        // Px.y号引脚开启上升沿中断;  p-->0 pull dowm;p-->1 pull up
    IIC_ioinit();               // IIC协议初始化
    LCD_Init();                 // oled初始化
    while(1)
    {
        print (10,1,w);         // oled显示
        print (10,3,520);       //print (int x,int y,long i); 初始坐标为（x,y），显示数据为i;  y--> 1~7;
        print (10,5,984236571);
        print (10,7,1314);
        pwm_12(1000,w);         //P1.2引脚输出pwm
    }

}
#pragma vector = PORT1_VECTOR
__interrupt void port1(void)    //P1.X引脚中断函数
{
    switch (j)
            {
            case 1:w++;break;
            default:w--;break;
            }
    P1IFG &=~BIT5;              //清中断标志位
}
#pragma vector = PORT2_VECTOR   //P2.X引脚中断函数
__interrupt void port2(void)
{
    j = ~j;                     //j取反
    P2IFG &=~BIT2;              //清中断标志位
}
