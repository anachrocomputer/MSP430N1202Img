# Makefile for MSP430 Nokia 1202 display

CC=msp430-gcc
LD=msp430-gcc

MCU=msp430g2231

COMMON=-mmcu=$(MCU)

CFLAGS=$(COMMON) -Wall -Os -c
LDFLAGS=$(COMMON) -Wl,-Map=n1202img.map,--relax

all: n1202img.elf
.PHONY: all

n1202img.o: n1202img.c
	$(CC) $(CFLAGS) -o $@ $^

n1202img.elf: n1202img.o
	$(LD) $(LDFLAGS) -o $@ $^

prog: n1202img.elf
	mspdebug rf2500 'prog n1202img.elf'
.PHONY: prog

clean:
	-rm -f n1202img.o n1202img.elf n1202img.map
.PHONY: clean

