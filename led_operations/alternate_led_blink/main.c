#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"

int main(void) {
	int loop_flag = 1;

	// Set pin 12 and 8 mode to output
	// We do that by shifting bit in register DDRB defined in io.h or by address which found in Atmega328p microporcessor datasheet 0x04(it is the same thing)
	// (HIGH << DDB4) shifts bit on position 4
	// (HIGH << DDB0) by datasheet bit for pin is at position 0
	// HIGH macro is defined in common_types.h 
	
	DDRB |= (HIGH << DDB4);
	DDRB |= (HIGH << DDB0);

	while(loop_flag) {
		// Toggle LED
		// PORTB or address 0x05 is used to write values into I/O pin 
				
		PORTB |= (HIGH << PORTB4);
		if (PORTB & (HIGH << PORTB4)) {
			PORTB &= ~(HIGH << PORTB0);
		}
		_delay_ms(2500);

		PORTB &= ~(HIGH << PORTB4);
		if (!(PORTB & (HIGH << PORTB4))) {
			PORTB |= (HIGH << PORTB0);
			
		}
		_delay_ms(500);
	}
	
	return SUCCESS;
}
