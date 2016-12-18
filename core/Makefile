CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld

TARGET = firm.elf

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CFLAGS  = -Wall -O0 -g -fomit-frame-pointer -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft
LDFLAGS = -nostartfiles -g

all : $(TARGET)

.PHONY : all clean

$(TARGET) : $(OBJS) ld.script Makefile
	$(CC) $(CFLAGS) $(LDFLAGS) -T ld.script -o $(TARGET) $(OBJS)

clean :
	rm -f $(TARGET)
	rm -f $(OBJS)

