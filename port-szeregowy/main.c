/*
 * GccApplication1.c
 *
 * Created: 10.11.2022 16:32:46
 * Author : Student_PL
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#define F_CPU 8000000UL // ustawienie czêstotliwoœci zegara – proponowane 8MHz
#define BAUDRATE 9600 //okreœlenie prêdkoœci przesy³ania
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1) //wyznaczenie zawartoœci rejestru UBRR ze wzoru

void USART_Init(void)
{
	/* ustawienie baud */
	UBRRH = (BAUD_PRESCALLER>>8);
	UBRRL = (BAUD_PRESCALLER);
	//konfiguracja… (baud rate = 9600, ramka: 8 bitów danych, brak kontroli parzystoœci, 1 bit stopu)
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UCSRB = (1<<TXEN) | (1<<RXEN);
}

void USART_putchar(unsigned char data)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = data;
}void USART_putstring(char* tekst){		for(int i=0;i<strlen(tekst);i++)		{			USART_putchar(tekst[i]);		}}223322unsigned char UART_RxChar()
{
	USART_putstring("Nacisnij przycisk [1] ");
	while ((UCSRA & (1<<RXC))==0); /* Wait till data is received */
	if(UDR == 0x31)
		USART_putstring("Poprawny przycisk ");
	else
		USART_putstring("Niepoprawny przycisk ");
	_delay_ms(5000);
}unsigned char diody()
{
	while ((UCSRA & (1<<RXC))==0); /* Wait till data is received */
	if(UDR == 0x31)
	PORTA ^= 1<<1;
	if(UDR == 0x32)
	PORTA ^= 1<<2;
	if(UDR == 0x33)
	PORTA ^= 1<<3;
	if(UDR == 0x34)
	PORTA ^= 1<<4;
	if(UDR == 0x35)
	PORTA ^= 1<<5;
	if(UDR == 0x36)
	PORTA ^= 1<<6;
	if(UDR == 0x37)
	PORTA ^= 1<<7;
	if(UDR == 0x38)
	PORTA ^= 1<<8;
	if(UDR == 0x39)
	PORTA ^= 1<<9;
	if(UDR == 0x63)
	PORTA = 0x00;
	if(UDR == 0x73)
	PORTA = 0xFF;
	else
	USART_putstring("Blad - zly przycisk");
}

int main(void)
{
	USART_Init();
    /* Replace with your application code */
	DDRA=0xFF;
    while (1) 
    {		
			//_delay_ms(5000);
			//USART_putstring("Kacper Papinski ");
			//UART_RxChar();
			diody();
			
    }
}
