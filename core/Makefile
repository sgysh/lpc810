CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld

TARGET = firm.elf

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS  = -Wall -O0 -g -fomit-frame-pointer -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -nostdlib -ffreestanding
LDFLAGS = -nostartfiles -g

all : $(TARGET)

.PHONY : all clean install_ft232h

$(TARGET) : $(OBJS) ld.script Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -T ld.script -o $(TARGET) $(OBJS)

clean :
	rm -f $(TARGET)
	rm -f $(OBJS)

install_ft232h :
	sudo openocd -f /usr/local/share/openocd/scripts/interface/ftdi/ft232h-with-resistor.cfg \
	  -f /usr/local/share/openocd/scripts/target/lpc8xx.cfg \
	  -c init -c "reset halt" -c "adapter_khz 300" -c "flash write_image erase firm.elf" \
	  -c resume -c halt -c "verify_image firm.elf" -c exit

