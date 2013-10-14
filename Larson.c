/*
* Cylon.c
*
* Created: 14/10/2013
*  Author: phenoptix
*                 ------
*      Reset 1 --|o     |-- 20 +5v
*            2 --|ATtiny|-- 19
*            3 --|2313A |-- 18
*            4 --|      |-- 17 
*			 5 --|      |-- 16 PB4 *PWM
*SWITCH INT0 6 --|      |-- 15 PB3 *PWM
*            7 --|      |-- 14 PB2 *PWM
*			 8 --|      |-- 13
* PD5 *PWM   9 --|      |-- 12
*           10 --|      |-- 11
*                 ------ (Diagram idea from NickNorton.net)
* PWM Code grabbed from   darus67 20 October 2007 on the Adafruit forums
other stuff from http://www.instructables.com/id/Creating-a-charlieplexed-LED-grid-to-run-on-ATTiny/#step1
great PWM Stuff from http://startingelectronics.com/tutorials/AVR-8-microcontrollers/ATtiny2313-tutorial/P11-PWM/
really helpful Blog from a chap called Suhas http://iamsuhasm.wordpress.com/tutsproj/avr-gcc-tutorial/ */

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


#define OUT_A PORTB2
#define OUT_B PORTB3
#define OUT_C PORTB4
#define OUT_D PORTD5
#define PWM_A OCR0A,//LED0
#define PWM_B OCR1A,//LED1
#define PWM_C OCR1B,//LED2
#define PWM_D OCR0B,//LED3

int b;
int i;


int main(void)
{
	basic_larson();
}
//DDRx Config for each LED. Here we need to assign the two "active" pins to switch on each LED.
//Setting the others to inputs which gives them a high impedance state.
//This line states that the information will be a constant, the value will be a character, stored in a list called PINS_ACT that is 12 values long (0-11)

//PORTx Config for each LED. We've already set the active pins now we set which is high.
//We've explicitly stated the High and Low states of the PORTx register as if the LED is accessed non-sequentially the Pin may not be in the correct state.


void LED_ON(char LED) { //LED must be from 0 to 11 Switches selected CharliePlexed LED
	if(LED==0){
	DDRB = (1<<OUT_A);
	DDRD = (1<<OUT_D);
	PORTD = (1<<OUT_D);
	PORTB = (0<<OUT_A);
	}else if(LED==1){
	DDRB = (1<<OUT_A|1<<OUT_C);
	DDRD = (0<<OUT_D);
	PORTB = (1<<OUT_C);
	PORTD = (0<<OUT_D);
	}
	else if(LED==2){
	DDRB = (1<<OUT_A|1<<OUT_B);
	DDRD = (0<<OUT_D);
	PORTB = (1<<OUT_B);
	PORTD = (0<<OUT_D);
	}
	else if(LED==3){
		DDRB = (1<<OUT_B|1<<OUT_A);
		DDRD = (0<<OUT_D);
		PORTB = (1<<OUT_A);
		PORTD = (0<<OUT_D);
	}
	else if(LED==4){
		DDRB = (1<<OUT_B);
		DDRD = (1<<OUT_D);
		PORTD = (1<<OUT_D);
		PORTB = (0<<OUT_B);
	}
	else if(LED==5){
		DDRB = (1<<OUT_B|1<<OUT_C);
		DDRD = (0<<OUT_D);
		PORTB = (1<<OUT_C);
		PORTD = (0<<OUT_D);
	}
	else if(LED==6){
		DDRB = (1<<OUT_C|1<<OUT_B);
		DDRD = (0<<OUT_D);
		PORTB = (1<<OUT_B);
		PORTD = (0<<OUT_D);
	}
	else if(LED==7){
		DDRB = (1<<OUT_C|1<<OUT_A);
		DDRD = (0<<OUT_D);
		PORTB = (1<<OUT_A);
		PORTD = (0<<OUT_D);
	}
	else if(LED==8){
		DDRB = (1<<OUT_C);
		DDRD = (1<<OUT_D);
		PORTD = (1<<OUT_D);
		PORTB = (0<<OUT_D);
	}
	else if(LED==9){
		DDRD = (1<<OUT_D);
		DDRB = (1<<OUT_C);
		PORTD = (0<<OUT_D);
		PORTB = (1<<OUT_C);
	}
	else if(LED==10){
		DDRD = (1<<OUT_D);
		DDRB = (1<<OUT_B);
		PORTD = (0<<OUT_D);
		PORTB = (1<<OUT_B);
	}
	else if(LED==11){
		DDRD = (1<<OUT_D);
		DDRB = (1<<OUT_A);
		PORTD = (0<<OUT_D);
		PORTB = (1<<OUT_A);
	}
}
//void LED_PWM(int LED) { //LED must be from 0 to 11 Switches selected PWM CharliePlexed LED
	//	DDRB = PINS_ACT[LED];
	//	PORTB = LED_HIGH[LED];
//	if(LED==0){
//		TCCR0A = (1 << COM0A1) | (1 << WGM00);  // phase correct PWM mode
//		TCCR0B = (1 << CS01);   // clock source = CLK/8, start PWM
//		OCR0A = 0x10;
//		DDRB = PINS_ACT[LED];
//		PORTB = LED_HIGH[LED];
//	}
//	if(LED==1){
//		OCR1A = 0x10;
//		TCCR1A = (1 << COM0A1) | (1 << WGM00);  // phase correct PWM mode
//		TCCR1B = (1 << CS01);   // clock source = CLK/8, start PWM
//		DDRB = PINS_ACT[LED];
//		PORTB = LED_HIGH[LED];
//	}
//	if(LED==2){
//		OCR1B = 0x10;
//		DDRB = PINS_ACT[LED];
//		PORTB = LED_HIGH[LED];
//	}
//	if(LED==3){
//		OCR0B = 0x10;
//		DDRB = PINS_ACT[LED];
//		PORTD = LED_HIGH[LED];
//	}                  // initial PWM pulse width pin PB2
//	TCCR0B = (1 << CS01);   // clock source = CLK/8, start PWM
//}

basic_larson() // This is a bit of a bodge together until we work out the hardware PWM
{
	while(1){     // loop forever
		// scan from right to left, with the trailing LED fading out.
		for(b=0; b <= 11; b++){  // Instead of incrementing, b gets shifted left.
			// When the 1 bit shifts off the left side
			// b == 0 and the loop terminates
			for(i=0;i<10;i++){
			LED_ON(b+1);  // turn on the LED before the center of the eye
			_delay_ms(1); // delay 
			LED_ON(b);  // turn on the LED
			_delay_ms(10); // delay
			LED_ON(b-1);  // turn on the LED
		    _delay_ms(2); // delay
			}

//			LED_PWM(b-1); // call fade to fade out the LED to the right of
			// the currently lit one
//			_delay_ms(1000); // delay
		}

		// scan from left to right, with the trailing LED fading out
		for(b=11; b >= 0; b--){ // We're shifting b right instead of left this time

		for(i=0;i<10;i++){
			LED_ON(b-1);  // turn on the LED
			_delay_ms(1); // delay
			LED_ON(b);  // turn on the LED
			_delay_ms(10); // delay
			LED_ON(b+1);  // turn on the LED
			_delay_ms(2); // delay
			}
//			LED_PWM(b+1); // fade the LED to the left of the lit one
//			_delay_ms(1000); // delay
		}

	} // end while

} // end main