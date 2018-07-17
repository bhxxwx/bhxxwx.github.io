#include <msp430.h> 
#include <Arduino.h>
#include <IIC.h>
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	            // stop watchdog timer
	adc_60();                               // ����ADC ��Ĭ������ΪP6.0 ����ͨ������/ѭ��������ѡ
	                                        //ADC��Ҫ���ADC�ж�ʹ�ã���main�����·����� - #pragma vector=ADC12_VECTOR - __interrupt void ADC18 (void)
	return 0;
}
#pragma vector=ADC12_VECTOR
__interrupt void ADC18 (void)
{
    if (ADC12MEM0 < 0x7FF)
    {

      P1OUT &= ~0x01;                       //P1.0�͵�ƽ
      print (10,1,(int)ADC12MEM0);          //oled��ʾ
    }
    else
      P1OUT |= 0x01;                        //P1.0�ߵ�ƽ
}

