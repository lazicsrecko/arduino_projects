/* All information found in Hitachi HD4478 LCD datasheet */

#ifndef _LCD_H_
#define _LCD_H_

#include <avr/io.h>

// Display controls

#define LCD_CMD_CLEAR_DISPLAY 0x01 // Also could be set to 0b00000001
#define LCD_CMD_RETURN_HOME 0x02 // Also cuold be set to 0b00000010
#define LCD_CMD_DISPLAY_OFF 0x80 // Also could be set to 0b10000000
#define LCD_CMD_CURSOR_BLINK 0x0F // Also could be set to 0b00001111
#define LCD_CMD_SHIFT_TO_LEFT 0x18
#define LCD_CMD_SHIFT_TO_RIGHT 0x1C
#define LCD_CMD_CURSOR_FIRST_LINE 0x80
#define LCD_CMD_CURSOR_SECOND_LINE 0xC0
#define LCD_CMD_LEFT_TO_RIGHT_TEXT 0x05
#define LCD_CMD_RIGHT_TO_LEFT_TEXT 0x07
#define LCD_CMD_DEFAULT_TEXT 0x06

// LCD Data transfer mode
#define LCD_CMD_4BIT_5x11 0x2c 
#define LCD_CMD_4BIT_5x7 0x28 // Also could be set to 0b00101000
#define LCD_CMD_8BIT_5x7 0x38 // Also could be set to 0b00111000

// LCD Data and Conrtol Ports
#define DATA_BUS PORTB 
#define CTL_BUS PORTD
#define DATA_DDR DDRB
#define CTL_DDR DDRD
#define CTL_PIN PIND

// LCD Data pins
#define LCD_D4 0
#define LCD_D5 1
#define LCD_D6 4
#define LCD_D7 5

// LCD Control pins
#define LCD_EN 7
#define LCD_R_W 4
#define LCD_RS 2
#define LCD_LEFT 6
#define LCD_RIGHT 3

void lcd_init_4bit(void);
void send_command(unsigned char command);
void write_character(unsigned char character);
void write_message(unsigned char *message);
void clear_lcd(void);
void flash_data(void);
void clear_data_bus(void);
void is_lcd_busy(void);
void send_nibble(unsigned char nibble);
void shift_display_to_left(void);
void shift_display_to_right(void);
void set_cursor(char column, char row);
void scroll_text(unsigned char direction);

#endif
