#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

unsigned char TB7SEG[] = {
	0b00111111, 0b00000110, 0b01011011, 0b01001111,
	0b01100110, 0b01101101, 0b01111101, 0b00000111,
	0b01111111, 0b01101111, 0b01110111, 0b01111100,
	0b00111001, 0b01011110, 0b01111001, 0b01110001,
        0b01010010};

unsigned char accumulator=0;
unsigned char quotient;
unsigned char divisor=0;
unsigned char DECODE = 0;
	
int main()
 { 
   
   DDRD = 0xff;
   DDRB = 0xff;
    
    PORTB = 0xff;
    
   ADMUX = 0x20;
   ADCSRA = 0b10101101;
   ADCSRB = 0b00000110;
    
    TCNT1 = 65528;
   TCCR1A = 0x00;
   TCCR1B = 0x05;
   TIMSK1 = 0x01;
    sei();
        
   while (1);
   
   return 0;
 }
 
 ISR(TIMER1_OVF_vect)
 {
    TCNT1 = 65528;
 }
 
 ISR(ADC_vect)
 {
    PORTD = ~PORTD;
    if(ADCH>9)
    {
       accumulator += ADCH;
       divisor++;
    }
    else
    {
       accumulator = 0;
       divisor = 0;
    }
    
    if(divisor == 10)
    {
       quotient = accumulator/divisor;
       if(quotient>9 && quotient<16)		DECODE = 1;
      else if(quotient>18 && quotient<26)	DECODE = 2;
      else if(quotient>29 && quotient<37)	DECODE = 3;
      else if(quotient>46 && quotient<53)	DECODE = 4;
      else if(quotient>74 && quotient<81)	DECODE = 5;
      else if(quotient>99 && quotient<107)	DECODE = 6;
      else if(quotient>133 && quotient<141)	DECODE = 7;
      else if(quotient>169 && quotient<177)	DECODE = 8;
      else if(quotient>192 && quotient<199)	DECODE = 9;
      else if(quotient>212 && quotient<220)	DECODE = 10;
      else if(quotient>228 && quotient<236)	DECODE = 0;
      else if(quotient>236 && quotient<244)	DECODE = 11;
      else DECODE = 16;    
	 
      if(DECODE != 16)
	 PORTB = ~TB7SEG[DECODE];
    }
 }
