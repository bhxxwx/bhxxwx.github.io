#include <msp430.h> 
#include <Arduino.h>
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	pwm (1000,900,2,0);         //pwm (int T,int Ton ,int x,int y);  T-->����;  Ton-->����ռ�ձȣ��ߵ�ƽ��ռʱ��;  �������ΪPx.y --> P1.1~1.5 ; P1.7 ; p2.0
	return 0;
}
