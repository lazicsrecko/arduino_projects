#include <util/delay.h>
#include "lcd.h"
#include "../../common_types.h"

void lcd_init_4bit(void) {
	// Wait for more than 40ms by Initialization manual
	_delay_ms(500);

	// Sets pins on arduino board to output
	DATA_DDR |= (HIGH << LCD_D7) | (HIGH << LCD_D6) | (HIGH << LCD_D5) | (HIGH << LCD_D4);
	CTL_DDR |= (HIGH << LCD_EN) |(HIGH << LCD_R_W) | (HIGH << LCD_RS);
	CTL_BUS &= ~(HIGH << LCD_EN);	

	// Initialization proccess
	send_command_4bit(0x33);
	send_command_4bit(0x32);
	send_command_4bit(LCD_CMD_4BIT_5x7);
	_delay_ms(500);
	
	send_command_4bit(LCD_CMD_CURSOR_BLINK);
	_delay_ms(500);

	send_command_4bit(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(500);
}

void send_command_4bit(unsigned char command) {
	is_lcd_busy();
	
	CTL_BUS &= ~(HIGH << LCD_RS) &~(HIGH << LCD_R_W); // prepares lcd for command mode
	// sends only upper nibble
	send_nibble(command >> 4); 
	flash_data();
	
	// sends lower nibble
	send_nibble(command & 0x0F);
	flash_data();
	clear_data_bus();
}

void write_character_4bit(unsigned char character) {
	is_lcd_busy();

	CTL_BUS &= ~(HIGH << LCD_R_W); // sets to write mode 
	CTL_BUS |= (HIGH << LCD_RS); // sets to data mode 
	
	// sends upper nibble
	send_nibble(character >> 4);
	flash_data();

	// sends lower nibble
	send_nibble(character & 0x0F);
	flash_data();
	clear_data_bus();
}

void write_message_4bit(char *message) {
	char i = 0;

	while (message[i] != '\0')
	{
		write_character_4bit(message[i]);
		i++;
	}	
}

void clear_lcd(void) {
	send_command_4bit(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(2);
}

void clear_data_bus(void) {
	DATA_BUS &= ~(HIGH << LCD_D7) & ~(HIGH << LCD_D6) & ~(HIGH << LCD_D5) & ~(HIGH << LCD_D4);
}

void is_lcd_busy(void) {
	DATA_DDR = 0x0; // sets all port d pin to input mode so we can read flag stored in bit 7
	
	// When RS pin is 0 and R/w pin is 1, busy flag is set to DB7, it must be 0 for accpeting next set of instructions
	CTL_BUS |= (HIGH << LCD_R_W);
	CTL_BUS &= ~(HIGH << LCD_RS);

	while ((DATA_BUS == 0x80)) { // 0x80 is 0b10000000
		flash_data();
	}
	
	DATA_DDR = 0xFF; // sets all port d pin to output mode
}

void flash_data(void) {
	// Turns lights on and off so LCD could retrive data
	 
	CTL_BUS |= (HIGH << LCD_EN);
	_delay_ms(50);
	CTL_BUS &= ~(HIGH << LCD_EN);
}

void send_nibble(unsigned char nibble) {
	if (nibble & 0x01) {
		DATA_BUS |= (HIGH << LCD_D4);
	} else {
		DATA_BUS &= ~(HIGH << LCD_D4);
	}

	if (nibble & 0x02) {
		DATA_BUS |= (HIGH << LCD_D5);
	} else {
		DATA_BUS &= ~(HIGH << LCD_D5);
	}

	if (nibble & 0x04) {
		DATA_BUS |= (HIGH << LCD_D6);
	} else {
		DATA_BUS &= ~(HIGH << LCD_D6);
	}

	if (nibble & 0x08) {
		DATA_BUS |= (HIGH << LCD_D7);
	} else {
		DATA_BUS &= ~(HIGH << LCD_D7);
	}
}