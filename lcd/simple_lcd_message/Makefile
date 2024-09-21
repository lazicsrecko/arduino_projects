# MCU variable holds name for microcontroller unit that is installed on circut board
# F_CPU variable holds value for CPU speed mesuared in MHz (16 000 000 cycles per seconds) UL=unsigned long
# BAUD_RATE speed of transfering data form host PC to microcontroller unit (upload speed) 
# PORT connection to circut board. Depends on system, in linux can be obtained by reading kernel messages using dmesg command
# TARGET program name
# CFLAGS flags used by avr-gcc compiler 
#

MCU=atmega328p 
F_CPU=16000000UL 
BAUD_RATE=115200
PROGRAMMER=arduino
PORT=/dev/ttyACM0

TARGET=main
SOURCES=../../common_types.c lcd.c $(TARGET).c

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os

all: $(TARGET).hex

%.elf: $(SOURCES)
	avr-gcc $(CFLAGS) -o $@ $^
%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

flash: $(TARGET).hex
	avrdude -V -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD_RATE) -D -Uflash:w:$(TARGET).hex:i
clean:
	rm -f *.elf *.hex 
