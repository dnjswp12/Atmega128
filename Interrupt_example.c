/*
 * INT.c
 *
 * Created: 2019-05-15 오후 6:11:47
 *  Author: Administrator
 */ 
typedef unsigned char INT8;
typedef unsigned int  INT16;


#define F_CPU 8000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned char sw;
ISR(INT4_vect) // INT4번을 쓰겠다. >>PE4
{
	sw = PINE&0x90;
	if (sw ==0x80) // 1110 0000
		{
			PORTF = 0xdf;
			_delay_ms(100);
		}
}

int main(void)
{
	
	DDRE = 0x00; //sw 
	DDRF = 0xff; // LED
	
	EICRB |= 0x02; // 외부 인터럽트 센스 컨트롤, 상승, 하강 어느 엣지에서 감지 할지 결정
	EIMSK |= 0x10; // 개별인터럽트 허용여부 INT4를 쓸거니까 0x10; defualt>>0임
	EIFR |= 0x00; // 개별 인터럽트 상태
	SREG |=0x80; // 전체 INT ENABLE
    while(1)
    {
		sw = PINE&0x90; 
		if (sw == 0x10) 
		{
			for (int i=0;i<10;i++)
			{
				PORTF = 0x00;
				_delay_ms(100);
				PORTF = 0xff;
				_delay_ms(100);
			}
			
		}
		else
		{
			PORTF = 0xff;
			_delay_ms(100);
		}
        //TODO:: Please write your application code 
    }
}
