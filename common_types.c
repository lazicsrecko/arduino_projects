#include <avr/io.h>

// Custom version of pinMode function used in Arduino IDE
void setPinMode(int pinNumber, int mode) {
	if (pinNumber > 7 && pinNumber < 14) {
		int registerStartPosition = 8;
		int bitsToShift = pinNumber - registerStartPosition;
		DDRB |= (mode << bitsToShift);
	}
	
	if (pinNumber > 0 && pinNumber < 8) {
		DDRD |= (mode << pinNumber);
	} 
}

// Custom version of digitalWrite function used in Arduino IDE
void digitalPinWrite(int pinNumber, int voltage) {
	if (pinNumber >= 0 && pinNumber < 8) {
		PORTD = (voltage << pinNumber);
	}

	if (pinNumber > 7 && pinNumber < 14) {
		int registerStartPosition = 8;
		int bitsToShift = pinNumber - registerStartPosition;
		PORTB = (voltage << bitsToShift);
	}
}
