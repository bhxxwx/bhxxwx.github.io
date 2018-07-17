#include <msp430.h> 
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	            // stop watchdog timer
	        P1DIR &= BIT1;                  //设置P1.1为输入
	        P1REN |= BIT1;                  //使能上\下拉电阻
	        P1OUT |= BIT1;                  //引脚拉高
	        P4DIR |= BIT7;                  //设置P4.7为输出
	        P4OUT |= BIT7;                  //输出为低电平
	        while (1)
	        {
	            if (P1IN & BIT1)            //检测P1.1是否为高电平
	            {
	                __delay_cycles(500);    //延时500us，按键消抖
	                if (P1IN & BIT1)        //再次检测
	                {
	                    P4OUT = (1<<7);     //P4.7输出高电平
	                }
	            }
	            else
	            {
	                P4OUT = (0<<7);         //P4.7输出低电平
	            }
	        }
	return 0;
}
