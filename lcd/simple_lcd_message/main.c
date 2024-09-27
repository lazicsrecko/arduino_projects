#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"
#include "lcd.h"

int main(void) {
	lcd_init_4bit();
	_delay_ms(20);
	
	char message[] = "Long message so I can work with display and cursor shift";
	//write_message(message);
	// write_character(0x43); // C 0x43 ASCII hex code
	// write_character(0x4F); // O 0x4F ASCII hex code
	// write_character(0x4F); // O 0x4F ASCII hex code
	// write_character(0x4C); // L 0x4C ASCII hex code
	// write_character(0x20); // Space 0x20 ASCII hex codes
	// write_character(0x4C); // L 0x4C ASCII hex code
	// write_character(0x43); // C 0x43 ASCII hex code
	// write_character(0x44); // D 0x44 ASCII hex code 
	
	set_cursor(4, 0);
	write_message("COOL LCD");

	while(1) {
		
		// Display shifting should be used with interupts?
		if (CTL_PIN & (HIGH << LCD_RIGHT)) {
			shift_display_to_right();
		}

		if (CTL_PIN & (HIGH << LCD_LEFT)) {
			shift_display_to_left();
		}				
	}
	
	return SUCCESS;
}
