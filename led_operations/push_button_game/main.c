#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"
#include "push_button_game_utils.h"

int main(void) {
	int loop_flag = 1;

	// Setting used pins mode
	// DDRB (Data direction register B) data direction for pins 8 to 13
	// DDRD (Data direction register D) data direction for pins 0 to 7
	DDRB |= (OUTPUT << DDB5) | (OUTPUT << DDB4) | (OUTPUT << DDB3) | (OUTPUT << DDB2);
	DDRD |= (OUTPUT << DDD4) | (OUTPUT << DDD5) | (OUTPUT << DDD6) | (OUTPUT << DDD7);
	DDRD |= (INPUT << DDD2) | (INPUT << DDD3);

	char is_pressed = 0;
	int debounce_margin = 500;
	int button_pressed_level = 0;
	int button_released_level = 0;
	char green_led_count = 0;
	char yellow_led_count = 0;
	
	while(loop_flag) {
		// Checks if left hand side button is pressed
		// (PIND & (HIGH << PIND2) check value of pin2
		if (PIND & (HIGH << PORTD2)) {
			if (debounce_voltage(&debounce_margin, &button_pressed_level, &button_released_level, &is_pressed)) {
				green_led_count++;
				led_on(&PORTB, get_portb_led_pin_number(green_led_count));
			}
			_delay_ms(500);
		}

		// Checks if right hand side button is pressed
		if (PIND & (HIGH << PIND3)) {
			if (debounce_voltage(&debounce_margin, &button_pressed_level, &button_released_level, &is_pressed)) {
				yellow_led_count++;
				led_on(&PORTD, get_portd_led_pin_number(yellow_led_count));
			}
			_delay_ms(500);
		}
		check_winner(&green_led_count, &yellow_led_count);	
	}
	
	return SUCCESS;
}
