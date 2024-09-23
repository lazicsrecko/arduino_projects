#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"
#include "lcd.h"

int main(void) {
	lcd_init_4bit();
	_delay_ms(20);
	
	char message[] = "Long message so I can work with display and cursor shift";
	write_message_4bit(message);
	// write_character_4bit(0x43); // C 0x43 ASCII hex code
	// write_character_4bit(0x4F); // O 0x4F ASCII hex code
	// write_character_4bit(0x4F); // O 0x4F ASCII hex code
	// write_character_4bit(0x4C); // L 0x4C ASCII hex code
	// write_character_4bit(0x20); // Space 0x20 ASCII hex codes
	// write_character_4bit(0x4C); // L 0x4C ASCII hex code
	// write_character_4bit(0x43); // C 0x43 ASCII hex code
	// write_character_4bit(0x44); // D 0x44 ASCII hex code

	while(1) {
		if (CTL_PIN & (HIGH << LCD_RIGHT)) {
			shift_display_to_right();
		}

		if (CTL_PIN & (HIGH << LCD_LEFT)) {
			shift_display_to_left();
		}
	}
	
	return SUCCESS;
}
