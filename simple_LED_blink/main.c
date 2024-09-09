#include <avr/io.h>
#include <util/delay.h>

#define SUCCESS 0

int main(void) {
	int loop_flag = 1;
	// Sets pin 13 (PB5) as output
	DDRB |= (1 << DDB5);

	while(loop_flag) {
		// Toggle LED
		PORTB ^= (1 << PORTB5);
		_delay_ms(1000);
	}
	
	return SUCCESS;
}
