#include "lcd.h"

void wybor(uint8_t a)
{
	if(a==1) //wybrany port A
	{
		#define LCD_DDR DDRA
		#define LCD_PORT PORTA
		#define EN PA0
		#define RS PA1
	}
	if(a==2) //wybrany port B
	{
		#define LCD_DDR DDRB
		#define LCD_PORT PORTB
		#define EN PB0
		#define RS PB1
	}
	if(a==3) //wybrany port C
	{
		#define LCD_DDR DDRC
		#define LCD_PORT PORTC
		#define EN PC0
		#define RS PC1
	}
	if(a==4) //wybrany port D
	{
		#define LCD_DDR DDRD
		#define LCD_PORT PORTD
		#define EN PD0
		#define RS PD1
	}
	LCD_PORT=0xF0;
}

void inicjalizacjaLCD()
{	
	LCD_DDR=(0xF0)|(1<<RS)|(1<<EN); //ustawienie kierunku wyjsciowego dla wszystkich linii
	LCD_PORT=0; //ustawienie poczatkowego stanu niskiego
	LCD_PORT&=~(1<<RS); //RS na 0 - wysylanie komend
	LCD_char_write(0b00101000); //function set aktywne - znaki 5x7 , 2 wiersze, interfejs 4-bitowy
	LCD_PORT |=1<<RS;
	LCD_PORT &=~(1<<RS);
	LCD_char_write(0b00000110); //entry mode set aktwne - przesuwanie kursora, przesuw w prawo
	LCD_PORT |=1<<RS;
	LCD_PORT &=~(1<<RS);
	LCD_char_write(0b00001110); //dysplay on/off aktywne - wyswietlacz wlaczony, kursor widoczny, kursor miga
	LCD_PORT |=1<<RS; //tryb wysylania danych
	LCDclear(); //wyczyszczenie wyswietlacza po poprzednim uruchomieniu
}

void LCD_char_write(uint8_t b)
{
	LCD_PORT |=1<<EN; //wlaczenie linii ENABLE (zapis do rejestrow)
	LCD_PORT=(b & 0xF0) | (LCD_PORT & 0x0F); //wyslanie 4 starszych bitow
	LCD_PORT &=~(1<<EN); //wylaczenie ENABLE
	asm volatile("nop"); //odczekanie cyklu
	LCD_PORT |=1<<EN; //wlaczenie EN
	LCD_PORT=((b & 0x0F)<<4) | (LCD_PORT & 0x0F); //wyslanie 4 mlodszych bitow
	LCD_PORT &=~(1<<EN); //wylaczenie EN
	_delay_us(50); //czekanie na wyslanie danych
}

void LCDclear()
{
	LCD_PORT &=~(1<<RS); //linia RS na 0 aby wysylac komendy (tabela kod�w))
	LCD_char_write(0x01); //wyslanie polecenia wyczyszczenia
	LCD_PORT |= 1<<RS; //linia RS na 1 aby ponownie wysylac dane
	_delay_ms(50);
}

void LCD_setxy(unsigned char x, unsigned char y)
{
	LCD_PORT &=~(1<<RS); //wysylanie komend
	LCD_char_write((x*0x40+y)|0x80);  //przesuniecie kursora, gdzie 0x40 to poczatek 2-go wiersza,
	//x oznacza numer wiersza, y pozycje w wierszu, jesli x=0 i y=0 to 0*0x40+0=0 ,
	//wtedy zostanie wywolana komenda 0x80, czyli wybranie adresu "domyslnego" - 1-szy wiersz, 1-szy znak
	LCD_PORT |=1<<RS; //wysylanie danych
	_delay_ms(5);
}

void LCD_str_write(char *tekst, int8_t dlugosc)
{
	int8_t i=0;
	LCD_setxy(0,0); //ustawia kursor na 1-szy znak 1-szej linii
	while(i<dlugosc) //przejscie po wszystkich znakach
	{
		if(i==16) //jesli ostatni znak linii, przejdz do nowej linii
		LCD_setxy(1,0); //ustaw kursor na 1-szy znak 2-giej linii
		LCD_char_write(tekst[i]); //wypisz i-ty znak tekstu
		i++;
	}
}

void LCDclear_y(unsigned char x,unsigned char y)
{
	for(int i=y;i<16;i++) //rozpocznij od wybranego wczesniej znaku (y)
	{
		LCD_setxy(x,i); //ustawianie kursora na kolejnych pozycjach w wierszu
		LCD_char_write(' '); //kasowanie obecnego znaku - zastepowanie znakiem 'spacjii'
		_delay_ms(50);
	}
}
