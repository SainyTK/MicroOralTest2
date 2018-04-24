#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

unsigned char TB7SEG[] = {
	0b00111111, 0b00000110, 0b01011011, 0b01001111,
	0b01100110, 0b01101101, 0b01111101, 0b00000111,
	0b01111111, 0b01101111, 0b01110111, 0b01111100,
	0b00111001, 0b01011110, 0b01111001, 0b01110001,
        0b01010010};

int main()
 { 
   unsigned char DECODE = 0;
    
   DDRD = 0xff;
   DDRB = 0xff;
    
   ADMUX = 0x20;
    
    PORTB = 0xff;
        
   while (1)
   {
      ADCSRA = 0xC7; //ob11000111;
      while(!(ADCSRA&(1<<ADIF)));
	 
      if(ADCH>9 && ADCH<16)		DECODE = 1;
      else if(ADCH>18 && ADCH<26)	DECODE = 2;
      else if(ADCH>29 && ADCH<37)	DECODE = 3;
      else if(ADCH>46 && ADCH<53)	DECODE = 4;
      else if(ADCH>74 && ADCH<81)	DECODE = 5;
      else if(ADCH>99 && ADCH<107)	DECODE = 6;
      else if(ADCH>133 && ADCH<141)	DECODE = 7;
      else if(ADCH>169 && ADCH<177)	DECODE = 8;
      else if(ADCH>192 && ADCH<199)	DECODE = 9;
      else if(ADCH>212 && ADCH<220)	DECODE = 10;
      else if(ADCH>228 && ADCH<236)	DECODE = 0;
      else if(ADCH>236 && ADCH<244)	DECODE = 11;
      else DECODE = 16;    
	 
      if(DECODE != 16)
	 PORTB = ~TB7SEG[DECODE];
   }
   return 0;
 }
