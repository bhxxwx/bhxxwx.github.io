#include <msp430.h> 
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	            // stop watchdog timer
	        P1DIR &= BIT1;                  //����P1.1Ϊ����
	        P1REN |= BIT1;                  //ʹ����\��������
	        P1OUT |= BIT1;                  //��������
	        P4DIR |= BIT7;                  //����P4.7Ϊ���
	        P4OUT |= BIT7;                  //���Ϊ�͵�ƽ
	        while (1)
	        {
	            if (P1IN & BIT1)            //���P1.1�Ƿ�Ϊ�ߵ�ƽ
	            {
	                __delay_cycles(500);    //��ʱ500us����������
	                if (P1IN & BIT1)        //�ٴμ��
	                {
	                    P4OUT = (1<<7);     //P4.7����ߵ�ƽ
	                }
	            }
	            else
	            {
	                P4OUT = (0<<7);         //P4.7����͵�ƽ
	            }
	        }
	return 0;
}
