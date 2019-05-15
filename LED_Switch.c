/*
 * test_LED.c
 *
 * Created: 2019-05-13 오후 7:24:52
 *  Author: Administrator
 */ 
#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>
int init();
int main(void)
{
	DDRG = 0xff;  // portg를 출력으로 사용
	DDRF = 0xff; // portf를 출력으로 사용
	DDRE = 0x00; // porte를 입력으로 사용 
  
	init();
	unsigned char sw;
	
    while(1)
    {
		sw = PINE & 0xf0; // 스위치 마스크, 사용하고자 하는 핀만 1로 두고 사용하지 않는 핀은 0. 
                      // 회로적으로 풀업 저항되있어서 항상 1인 상태임. sw를 누르면 0이됨. 
                      // 따라서 항상 1인 핀 상태와 쓰고자 하는 핀을 &시키면 1&1 >> 1 이다. 
                      // 누를 때는 0이 되므로 제어하고자 하는 스위치는 0으로 제어문에 쓰면된다.
		switch (sw)
		{
		case 0x70:
		PORTF = 0x00;
		_delay_ms(100);
		PORTF = 0xff;
		_delay_ms(100);
		break;
		
		case 0xb0:
		PORTF = 0xff;
		_delay_ms(100);
		for (int i=0;i<8;i++)
		{
			PORTF = ((PORTF+0x00)<<1);
			_delay_ms(100);
		}
		break;
		
		case 0xd0:
		PORTF = 0xff;
		_delay_ms(100);
		for (int a=0;a<8;a++)
		{
			PORTF = PORTF >> 1;
			_delay_ms(100);
		}
		break;
		}	
	}
    
}

int init() // 초기화 함수
{
	PORTG = 0x00;
	_delay_ms(100);
	PORTG = 0xff;
	_delay_ms(100);
}

