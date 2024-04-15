#include <targets\AT91SAM7.h>
#include "pcf8833u8_lcd.h"

#define LCD_BACKLIGHT PIOB_SODR_P20 //podswietlenie 
#define AUDIO_OUT PIOB_SODR_P19 //buzzer
#define SW_1 PIOB_SODR_P24 //przycisk SW_1
#define SW_2 PIOB_SODR_P25 //przycisk SW_2
#define j_left PIOA_SODR_P7 //joystick lewo
#define j_down PIOA_SODR_P8 //joystick dol
#define j_up PIOA_SODR_P9 //joystick gora
#define j_right PIOA_SODR_P14 //joystick right
#define j_push PIOA_SODR_P15 //joystick wcisniety

int poziom;
int kursor;
int limit;
int kursor_temp;

void glowne(int *poziom)
{
  *poziom=0;
}


void menu(int *poziom)
{
    
    switch(*poziom)
    {
    case 0:
        LCDPutStr("Kacper Papinski",10,10,SMALL,BLACK,YELLOW);
        LCDPutStr("Menu 1",40,20,SMALL,BLACK,YELLOW);
        LCDPutStr("Menu 2",60,20,SMALL,BLACK,YELLOW);
        LCDPutStr("Menu 3",80,20,SMALL,BLACK,YELLOW);
        LCDPutStr("LSW",110,10,SMALL,BLACK,YELLOW);
        
        break;
    case 1:
        LCDPutStr("Menu 1",10,10,SMALL,BLACK,YELLOW);
        LCDPutStr("Program 1",40,20,SMALL,BLACK,YELLOW);
        LCDPutStr("Program 2",60,20,SMALL,BLACK,YELLOW);
        LCDPutStr("LSW",110,10,SMALL,BLACK,YELLOW);
        break;
    case 2:
        LCDPutStr("Menu 2",10,10,SMALL,BLACK,YELLOW);
        LCDPutStr("Program 1",40,20,SMALL,BLACK,YELLOW);
        LCDPutStr("Program 2",60,20,SMALL,BLACK,YELLOW);
        LCDPutStr("LSW",110,10,SMALL,BLACK,YELLOW);
        break;
    case 3:
        LCDPutStr("Menu 3",10,10,SMALL,BLACK,YELLOW);
        LCDPutStr("Program 1",40,20,SMALL,BLACK,YELLOW);
        LCDPutStr("Menu 1",60,20,SMALL,BLACK,YELLOW);
        LCDPutStr("LSW",110,10,SMALL,BLACK,YELLOW);
        break;

    default:
        break;
    }
}

void next(int *poziom, int *kursor, int *x_temp1, int *x_start)
{
    switch(*poziom)
    {
    case 3:
        switch(*kursor)
        {
        case 0:
            //cout<<"wykonujesz program 1_3"<<endl;
            break;
        case 1:
            *poziom=1;
            *kursor=0;
            *x_temp1=*x_start;
            break;
        default:
            break;
        }
        break;

    case 2:
        switch(*kursor)
        {
        case 0:
            //cout<<"wykonujesz program 1_2"<<endl;
            break;
        case 1:
            //cout<<"wykonujesz program 2_2"<<endl;
            break;
        default:
            break;
        }
        break;

    case 1:
        switch(*kursor)
        {
        case 0:
            //cout<<"wykonujesz program 1_1"<<endl;
            break;
        case 1:
            //cout<<"wykonujesz program 2_1"<<endl;
            break;
        default:
            break;
        }
        break;

    case 0:
        switch(*kursor)
        {
        case 0:
            *poziom=1;
            *kursor=0;
            *x_temp1=*x_start;
            break;
        case 1:
            *poziom=2;
            *kursor=0;
            *x_temp1=*x_start;
            break;
        case 2:
            *poziom=3;
            *kursor=0;
            *x_temp1=*x_start;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void rysuj_kursor(int kur)
{
  switch(kur)
  {
    case 0:
     LCDPutStr("<",40,80,SMALL,BLACK,YELLOW);
     break;
    case 1:
     LCDPutStr("<",60,80,SMALL,BLACK,YELLOW);
     break;
    case 2:
     LCDPutStr("<",80,80,SMALL,BLACK,YELLOW);
     break;
    default:
    break; 
  }
}

int main (){

int x_start=40, y_start=80;
int x_temp1=x_start, y_temp1=y_start;

PMC_PCER=PMC_PCER_PIOB; //wlaczenie we/wy PIOB
PMC_PCER=PMC_PCER_PIOA; //wlaczenie we/wy PIOA
PIOB_OER=LCD_BACKLIGHT | AUDIO_OUT; //OUTPUT ENABLE
PIOB_PER=LCD_BACKLIGHT | AUDIO_OUT; //PIO ENABLE 

InitLCD(); // Inicjalizacja ekranu LCD
SetContrast(30); // Ustawienie kontrastu wyswietlacza
LCDClearScreen(); // Wyczyszczenie ekranu




while(1)  {
   
   if(poziom==0)
    limit=2;
  else
   limit=1;

  //tlo();
  drawBoard();
  menu(&poziom);
  rysuj_kursor(kursor);
  

  if ((PIOB_PDSR & SW_1)==0) //Jesli wcisniety przycisk SW_1
  {
  if(poziom>0)
  //poziom--;
  {
    
  kursor=kursor_temp;
  
  glowne(&poziom);

   /* switch(poziom)
    {
      case 1: poziom=0; break;
      case 2: poziom=0; break;
      case 3: poziom=0; break;
      default: break;
    }*/
  
  }
  

  Delaya(10000000); //opoznienie
  LCDClearScreen(); // Wyczyszczenie ekranu
  
  }
  
  if ((PIOB_PDSR & SW_2)==0) //Jesli wcisniety przycisk SW_2
  {
  kursor_temp=kursor;
  next(&poziom,&kursor,&x_temp1,&x_start);

  Delaya(10000000); //opoznienie
  LCDClearScreen(); // Wyczyszczenie ekranu
  }

  if ((PIOA_PDSR & j_left)==0) //Jesli joystick skierowany w lewo
  {
  //LCDClearScreen(); // Wyczyszczenie ekranu
  //Delaya(1000000); //opoznienie
  //LCDPutStr("LEFT ", 60, 55, LARGE, RED, WHITE); //wyswietlenie tekstu
  }


  
  if ((PIOA_PDSR & j_down)==0) //Jesli joystick skierowany w dol
  {

  if(kursor<limit)
  {
    kursor++;
    LCDClearScreen_xy(x_temp1,x_temp1+10,y_temp1,y_temp1+10);
    x_temp1+=20;
    
  }

  
  //LCDClearScreen(); // Wyczyszczenie ekranu
  Delaya(1000000); //opoznienie
  
  }
 
  if ((PIOA_PDSR & j_up)==0) //Jesli joystick skierowany w gore
  {
  if(kursor>0)
  {
    kursor--;
    LCDClearScreen_xy(x_temp1,x_temp1+10,y_temp1,y_temp1+10);
    x_temp1-=20;
  
  }
   
  

  //LCDClearScreen(); // Wyczyszczenie ekranu
  //Delaya(1000000); //opoznienie
 
  }
  
  if ((PIOA_PDSR & j_right)==0) //Jesli joystick skierowany w prawo
  {
  //LCDClearScreen(); // Wyczyszczenie ekranu
  //Delaya(1000000); //opoznienie
  //LCDPutStr("RIGHT", 60, 55, LARGE, RED, WHITE); //wyswietlenie tekstu
  }
  
  if ((PIOA_PDSR & j_push)==0) //Jesli joystick wcisniety
  {
  //LCDClearScreen(); // Wyczyszczenie ekranu
  //Delaya(1000000); //opoznienie
  //LCDPutStr("PUSH ", 60, 60, LARGE, RED, WHITE); //wyswietlenie tekstu
  }

 } 
  return 0;
}
