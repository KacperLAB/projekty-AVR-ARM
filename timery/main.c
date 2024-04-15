#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void timer10_ms()
{
	while(!(TIFR & (1<<OCF0)))
	{
		
	}
	TIFR |= 1<<OCF0;
}
void czas1s()
{
	for(int i=0;i<100;i++) //100 * 10ms = 1s
		timer10_ms();
}

/*int main(void) //zad1
{
	DDRA=0xFF;
	PORTA=0x00;
	
	TCCR0 |= (1<<CS02); // 1/256               
	TCCR0 |= (1<<WGM01); // tryb CTC
	OCR0=40;            // 1/4ms * 40 = 10ms              
	
    while (1) 
    {
		czas1s();
		PORTA^=1<<0;
    }
} */
 /*int main(void) //zad2
{
	DDRA=0xFF;
	PORTA=0x00;
	TCCR0 |= (1<<CS01 | 1<<CS02); //normal, sygnal zewn. , zbocze opad
	PORTB |= (1<<0); //przycisk S1 kl. 
	
	while (1)
	{
		while(!(TIFR & (1<<TOV0))) //gdy flaga nie ustawiona
		{
			_delay_ms(200);
			PORTA=TCNT0; //zliczenie kolejnych impulsow
		}
		TCCR0 &=~((1<<CS01) | (1<<CS02)); //zatrzymanie timera
	}
} */
int temp=0;
ISR (TIMER0_OVF_vect)
{	
	temp++;
	if(temp==10)
	{
		PORTA^=1<<0; //zmien stan diody
		temp=0;
	}
	TCNT0=40;
}
 
int main(void) //zad3
{
	sei(); //wlaczenie systemu przerwan
	TIMSK |= 1<<TOIE0; //obsluga przerw od TOV0
	
	DDRA=0xFF;
	PORTA=0x00;
	
	TCCR0 |= (1<<CS02); // 1/256
	TCCR0 |= (1<<WGM01); // tryb CTC
	TCNT0=40;
	
	while (1)
	{
		
	}
}




