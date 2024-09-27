#include <util/delay.h>
#include "lcd.h"
#include "../../common_types.h"

/* Command and data functions are written in 4-bit mode, the difference is that we send two nibbles one after another and it is a little bit slower than 8-bit mode because of that
 * 8-bit mode can send all 8 bits at once  */

void lcd_init_4bit(void) {
	// Wait for more than 40ms by Initialization manual
	_delay_ms(500);

	// Sets pins on arduino board to output
	DATA_DDR |= (HIGH << LCD_D7) | (HIGH << LCD_D6) | (HIGH << LCD_D5) | (HIGH << LCD_D4);
	CTL_DDR |= (HIGH << LCD_EN) |(HIGH << LCD_R_W) | (HIGH << LCD_RS);
	CTL_BUS &= ~(HIGH << LCD_EN);	

	// Initialization proccess
	// By default LCD is in 8-bit mode so when sending commands 0x33(0b00110011) this is interpreted by LCD like like two separate 8-bit commands (0b00110000 and 0b00110000)
	// Because we are still in 8-bit mode next command is interpreted same so 0x32(0b00110010) will be send as two different 8-bit 0b00110000 and 0b0010000
	// 1) sets to default mode (8-bit mode)
	// 2) sets to 4-bit mode
	// 3) sets to 4-bit mode with 2 lines
	send_command(0x33); 
	send_command(0x32);
	send_command(LCD_CMD_4BIT_5x7);
	_delay_ms(500);
	
	send_command(LCD_CMD_CURSOR_BLINK);
	_delay_ms(500);

	send_command(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(500);

	// Sets CTL_DDR pins(3 and 6) to input mode so button can be used to control dispalay shift
	CTL_DDR &= ~(HIGH << LCD_LEFT) & ~(HIGH << LCD_RIGHT);
}

void send_command(unsigned char command) {
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

void write_character(unsigned char character) {
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

void write_message(unsigned char *message) {
	char i = 0;

	while (message[i] != '\0')
	{
		write_character(message[i]);
		i++;
	}	
}

void clear_lcd(void) {
	send_command(LCD_CMD_CLEAR_DISPLAY);
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

void shift_display_to_left(void) {
	send_command(LCD_CMD_SHIFT_TO_LEFT);
}

void shift_display_to_right(void) {
	send_command(LCD_CMD_SHIFT_TO_RIGHT);
}

void set_cursor(char column, char row) {
	if (row == 0) {
		send_command(LCD_CMD_CURSOR_FIRST_LINE | column);
	}

	if (row == 1) {
		send_command(LCD_CMD_CURSOR_SECOND_LINE | column);
	}
}

void scroll_text(unsigned char direction) {
	send_command(direction);
}
