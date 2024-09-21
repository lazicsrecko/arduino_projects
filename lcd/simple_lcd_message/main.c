#include <avr/io.h>
#include <util/delay.h>

#include "../../common_types.h"
#include "lcd.h"

int main(void) {
	lcd_init_4bit();
	_delay_ms(20);

	write_message_4bit("COOL LCD");
	// write_character_4bit(0x43); // C 0x43 ASCII hex code
	// write_character_4bit(0x4F); // O 0x4F ASCII hex code
	// write_character_4bit(0x4F); // O 0x4F ASCII hex code
	// write_character_4bit(0x4C); // L 0x4C ASCII hex code
	// write_character_4bit(0x20); // Space 0x20 ASCII hex codes
	// write_character_4bit(0x4C); // L 0x4C ASCII hex code
	// write_character_4bit(0x43); // C 0x43 ASCII hex code
	// write_character_4bit(0x44); // D 0x44 ASCII hex code
	
	while(1) {
	}
	
	return SUCCESS;
}
