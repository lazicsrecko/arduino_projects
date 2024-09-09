#include <avr/io.h>
#include <util/delay.h>

#include "../common_types.h"

int OUTPUT = 0x1;
int HIGH = 0x1;
int LOW = 0x0;

int main(void) {
	int loop_flag = 1;

	// Sets pin 13 (PB5) as output
	//DDRB |= (1 << DDB5);
	setPinMode(12, OUTPUT);

	while(loop_flag) {
		// Toggle LED
		//PORTB ^= (1 << PORTB5);
		
		//PORTB ^= (1 << PORTB4);
		digitalPinWrite(12, HIGH);
		_delay_ms(2500);

		digitalPinWrite(12, LOW);
		_delay_ms(500);
	}
	
	return SUCCESS;
}
