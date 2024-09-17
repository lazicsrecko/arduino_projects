#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"

int main(void) {
	int loop_flag = 1;
	int repeat_count = 0;	
	// Sets pin 12 to be output pin
	DDRB |= (OUTPUT << DDB4);
	
	// Sets TCCR1B without prescaling (Timer/Counter Control Register 1 B)  
	// TCCR1B |= (HIGH << CS10);

	// Sets TCCR1B with prescaling of 256
	// CS12 is bit at position 2 
	TCCR1B |= (HIGH << CS12); 
	while(loop_flag) {
		// Arduino Uno R3 board has oscillator which works at 16MHz which is set to be used by microcontroller(internal microcontroller oscilator works at 8MHz, if microcontroller was used direct on breadboard we would use internal oscilator)
		// This means that 16 000 000 cycles happens in 1 sec
		// TCNT0 uses 8-bit register and can count only from 0 to 255 so it is better to utilize TCNT1
		// TCNT1 uses 16-bit registers so it can count from 0  up to 65535
		// If we devide 16 000 000 by 65535 we get around 244,14435 operations per seconds (in this case led will turn on and off for 244 times in 1 second)
		// So for easy math we can devide 16 000 000 by 10 000 we get 1600 operations per second and when 1600 operetions happens (which is stored in variable) we know that 1 second passed
		// Following code is some kind of prescaling using code 
		
		/*if (TCNT1 >  10000) {
			repeat_count++;
			TCNT1 = 0;
			if (repeat_count > 1600) {
				PORTB ^= (HIGH << PORTB4);
				repeat_count = 0; 
			}
		}*/

		// To know which presacling to use divide cpu_clock_speed by max_value_of_TCNT1 (16 000 000 / 65535 = 244,14435) <- this is lowest prescale that we can use TCNT1 has prescale of 8, 64 ,256 and 1024 so we use 256
		// To get when exactly 1 second passed we divide cpu_clock_speed by prescale that is used (16 000 000 / 256 = 62 500) <- this is the value that we need to check when TCNT1 is at  
		if (TCNT1 > 62500) {
			TCNT1 = 0;
			PORTB ^= (HIGH << PORTB4);
		}
	}
	
	return SUCCESS;
}
