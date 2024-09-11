#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"

int main(void) {
	int loop_flag = 1;

	// Sets pin 12 (PB4) as output
	setPinMode(12, OUTPUT);

	while(loop_flag) {
		// Toggle LED
		
		digitalPinWrite(12, HIGH);
		_delay_ms(2500);

		digitalPinWrite(12, LOW);
		_delay_ms(500);
	}
	
	return SUCCESS;
}
