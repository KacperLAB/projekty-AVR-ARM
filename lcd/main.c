#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h" //dolaczenie biblioteki obslugujacej wyswietlacz lcd

int main(void)
{
	wybor(2); //wyswietlacz podlaczony do portu B
	inicjalizacjaLCD(); //inicjalizacja wyswietlacza LCD
	char tekst[]={'A','B','C','D','E','F','G','H','I','J','K'}; //testowy tekst
	char tekst2[]={'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A'};
	while (1)
	{
		LCD_str_write(tekst,strlen(tekst)); //wypisanie ciagu "ABCDEFGH"
		_delay_ms(1000);
		LCD_setxy(1,6); //ustawienie kursora w 2-giej linii na pozycji 6-tej
		_delay_ms(1000);
		LCD_char_write('A'); //wypisanie znaku "A"
		LCD_setxy(1,9); //ustawienie kursora w 2-giej linii na pozycji 6-tej
		_delay_ms(1000);
		LCD_char_write('B'); //wypisanie znaku "A"
		_delay_ms(1000);
		LCDclear_y(1,6); //wyczyszczenie linii wyswietlacza zaczynajac od 2-giej linii i 6-tej pozycji
		_delay_ms(1000);
		LCDclear(); //wyczyszczenie calego wyswietlacza
		_delay_ms(1000);
	}
}