/*
* Cylon.c
*
* Created: 03/09/2013
*  Author: phenoptix
*                 ------
*      Reset 1 --|o     |-- 20 +5v
*            2 --|ATtiny|-- 19
*            3 --|2313A |-- 18
*            4 --|      |-- 17 PB5 *PWM
*			 5 --|      |-- 16 PB4 *PWM
*SWITCH INT0 6 --|      |-- 15 PB3 *PWM
*            7 --|      |-- 14 PB2 *PWM
*			 8 --|      |-- 13
*            9 --|      |-- 12
*           10 --|      |-- 11
*                 ------ (Diagram idea from NickNorton.net)
* PWM Code grabbed from   darus67 20 October 2007 on the Adafruit forums
other stuff from http://www.instructables.com/id/Creating-a-charlieplexed-LED-grid-to-run-on-ATTiny/#step1
great PWM Stuff from http://startingelectronics.com/tutorials/AVR-8-microcontrollers/ATtiny2313-tutorial/P11-PWM/
*/

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


#define OUT_A PORTB2
#define OUT_B PORTB3
#define OUT_C PORTB4
#define OUT_D PORTB5

int b;


int main(void)
{
	basic_larson();
}
//DDRB Config for each LED. Here we need to assign the two "active" pins to switch on each LED.
//Setting the others to inputs which gives them a high impedance state.
//This line states that the information will be a constant, the value will be a character, stored in a list called PINS_ACT that is 12 values long (0-11)
const char PINS_ACT[12] = {
	( 1<<OUT_A | 1<<OUT_D ),//LED0
	( 1<<OUT_A | 1<<OUT_C ),//LED1
	( 1<<OUT_A | 1<<OUT_B ),//LED2
	( 1<<OUT_B | 1<<OUT_A ),//LED3

	( 1<<OUT_B | 1<<OUT_D ),//LED4
	( 1<<OUT_B | 1<<OUT_C ),//LED5
	( 1<<OUT_C | 1<<OUT_B ),//LED6
	( 1<<OUT_C | 1<<OUT_A ),//LED7

	( 1<<OUT_C | 1<<OUT_D ),//LED8
	( 1<<OUT_D | 1<<OUT_C ),//LED9
	( 1<<OUT_D | 1<<OUT_B ),//LED10
	( 1<<OUT_D | 1<<OUT_A )//LED11
};


//PORTB Config for each LED. We've already set the active pins now we set which is high.
const char LED_HIGH[12] = {
	(1<<OUT_D),//LED0
	(1<<OUT_C),//LED1
	(1<<OUT_B),//LED2
	(1<<OUT_A),//LED2

	(1<<OUT_D),//LED4
	(1<<OUT_C),//LED5
	(1<<OUT_B),//LED6
	(1<<OUT_A),//LED7

	(1<<OUT_D),//LED8
	(1<<OUT_C),//LED9
	(1<<OUT_B),//LED10
	(1<<OUT_A)//LED11
};

void LED_ON(char LED) { //LED must be from 0 to 11
	DDRB = PINS_ACT[LED];
	PORTB = LED_HIGH[LED];
	DDRB |= (1 << PORTB);
	TCCR0A = (1 << COM0A1) | (1 << WGM00);  // phase correct PWM mode
	OCR0A  = 0xA0;                          // initial PWM pulse width
}

basic_larson()
{
int i;
	while(1){     // loop forever
		// scan from right to left, with the trailing LED fading out.
		for(b=0; b <= 11; b++){  // Instead of incrementing, b gets shifted left.
			// When the 1 bit shifts off the left side
			// b == 0 and the loop terminates

			LED_ON(b);  // turn on the LED
			for(i = 30000; i > 0; i--); // short delay

//			fade(LED_ON(b-1)); // call fade to fade out the LED to the right of
			// the currently lit one
		}

		// scan from left to right, with the trailing LED fading out
		for(b=11; b >= 0; b--){ // We're shifting b right instead of left this time

			LED_ON(b);  // turn on the LED
			for(i = 30000; i > 0; i--); // short delay

//			fade(LED_ON(b+1)); // fade the LED to the left of the lit one
		}

	} // end while

} // end main