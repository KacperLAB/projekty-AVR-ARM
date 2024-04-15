#ifndef F_CPU //Instrukcja preprocesora, która sprawdza czy zmienna o podanej nazwie istnieje.
#define F_CPU 1000000  //Jeśli nie istnieje : tworzenia zmienej preprocesora - ustawienie taktowania. 
#endif //Koniec bloku warunkowego preprocesora

#ifndef LCD_H //Sprawdzanie, czy plik nie został już wcześniej dołączony
#define LCD_H //Jeśli nie to:

#include <avr/io.h> //Dołączenie potrzebnych bibliotek
#include <util/delay.h>
#include <string.h>

void wybor(uint8_t a); //Deklaracja funkcji, pozwalajacej na konfiguracje wybranego portu

void inicjalizacjaLCD(); //Deklaracja funkcji inicjalizującej/konfigurującej wyświetlacz

void LCD_char_write(uint8_t b); //Deklaracja funkcji wyświetlającej pojedynczy znak

void LCDclear(); //Deklaracja funkcji czyszczącej cały wyświetlacz

void LCD_setxy(unsigned char x, unsigned char y); //Deklaracja funkcji ustawiającej kursor w wierszu 'x' na pozycji 'y'

void LCD_str_write(char *tekst, int8_t dlugosc); //Deklaracja funkcji wyświetlającej ciąg znaków pobieranych z tablicy

void LCDclear_y(unsigned char x,unsigned char y); //Deklaracja funkcji czyszczącej wyświetlacz od wiersza 'x' 
                                                  //i pozycji 'y' do końca danego wiersza*/

#endif //Koniec bloku warunkowego
