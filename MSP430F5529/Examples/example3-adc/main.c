#include <msp430.h> 
#include <Arduino.h>
#include <IIC.h>
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	            // stop watchdog timer
	adc_60();                               // 设置ADC ，默认引脚为P6.0 ，单通道单次/循环采样可选
	                                        //ADC需要配合ADC中断使用，在main函数下方声明 - #pragma vector=ADC12_VECTOR - __interrupt void ADC18 (void)
	return 0;
}
#pragma vector=ADC12_VECTOR
__interrupt void ADC18 (void)
{
    if (ADC12MEM0 < 0x7FF)
    {

      P1OUT &= ~0x01;                       //P1.0低电平
      print (10,1,(int)ADC12MEM0);          //oled显示
    }
    else
      P1OUT |= 0x01;                        //P1.0高电平
}

