#ifndef _PUSH_BUTTON_UTILS_
#define _PUSH_BUTTON_UTILS_

void led_on(volatile unsigned char *port, char pin_number);
char get_portb_led_pin_number(char led_count);
char get_portd_led_pin_number(char led_count);
char debounce_voltage(int *p_margin, int *p_pressed_level, int *p_released_level, char *p_p_is_pressed);
void check_winner(char *p_green_led_count, char *p_yellow_led_count);
void reset_ports_and_counters(char *p_green_led_count, char *p_yellow_led_count);

#endif
