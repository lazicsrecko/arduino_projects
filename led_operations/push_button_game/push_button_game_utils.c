#include <avr/io.h>
#include <util/delay.h>

#include "push_button_game_utils.h"
#include "../../common_types.h"

void led_on(volatile unsigned char *port, char pin_number) {
	*port |= (HIGH << pin_number);
}

char get_portb_led_pin_number(char led_count) {
         switch (led_count) {
                 case 1:
                         return 2;
                 case 2:
                          return 3;
                  case 3:
                          return 4;
                  case 4:
                          return 5;
                  default:
                          return 0;
          }
}

char get_portd_led_pin_number(char led_count) {
         switch (led_count) {
                 case 1:
                         return 7;
                 case 2:
                         return 6;
                 case 3:
                         return 5;
                 case 4:
                         return 4;
                 default:
                         return 0;
	}	
}

char debounce_voltage(int *p_margin, int *p_pressed_level, int *p_released_level, char *p_is_pressed) {
         if (!(*p_is_pressed)) {
                 *p_pressed_level++;
                 if (*p_pressed_level > *p_margin) {
                         *p_pressed_level = 1;
                         return 1;
                 }
         } else {
                 *p_released_level++;
                 if (*p_released_level > *p_margin) {
                         *p_is_pressed = 0;
                         *p_released_level = 0;
                         return 0;
                 }
         }
}

void check_winner(char *p_green_led_count, char *p_yellow_led_count) {
         if (PINB & (HIGH << PINB5)) {
                 for (char i = 0; i < 8; i++) {
                         PORTB ^= (HIGH << PORTB2) ^ (HIGH << PORTB3) ^ (HIGH << PORTB4) ^ (HIGH << PORTB5);
                         _delay_ms(500);
                 }
                 reset_ports_and_counters(p_green_led_count, p_yellow_led_count);
         } 
         if (PIND & (HIGH << PIND4)) {
                 for (char i = 0; i < 8; i++) {
                         PORTD ^= (HIGH << PORTD4) ^ (HIGH << PORTD5) ^ (HIGH << PORTD6) ^ (HIGH << PORTD7);
                         _delay_ms(500);
                 }
                 reset_ports_and_counters(p_green_led_count, p_yellow_led_count);
         }
}
 
void reset_ports_and_counters(char *p_green_led_count, char *p_yellow_led_count) {
         PORTB &= ~(HIGH << PORTB2) & ~(HIGH << PORTB3) & ~(HIGH << PORTB4) & ~(HIGH << PORTB5);
         PORTD &= ~(HIGH << PORTD4) & ~(HIGH << PORTD5) & ~(HIGH << PORTD6) & ~(HIGH << PORTD7);
         *p_green_led_count = 0;
         *p_yellow_led_count = 0;
}
