#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"

int main(void) {
	int loop_flag = 1;

	// set digital pin 12 to output mode
	// set digital pin 2 to input mode, it should be by default in input mode
	DDRB |= (OUTPUT << DDB4);
	DDRD |= (INPUT << DDD2);

	while(loop_flag) {
		if (PIND & (HIGH << PIND2)) {
			PORTB |= (HIGH << PORTB4);
		}
		
		PORTB &= ~(HIGH << PORTB4);
	}
	
	return SUCCESS;
}
