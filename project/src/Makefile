# makfile configuration

COMMON_OBJECTS  =

CPU             = msp430g2553

CFLAGS          = -mmcu=${CPU} -Os -I../h 

LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include





#switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc

AS              = msp430-elf-as



all: buzzer.elf led.elf wakedemo.elf



#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wakedemo.o ../../wakedemo/wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

#buzzer.elf: greenBeat-c.o buzzer.o main.o ../lib/libTimer.a
#	${CC} ${CFLAGS} -o $@ $^

led.elf: greenBeat-c.o buzzer.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

led2.elf: greenBeat-s.o buzzer.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load:  wakedemo.elf
	msp430loader.sh  $^

load2: buzzer.elf led2.elf
	msp430loader.sh  $^

clean: $^

	rm -f *.o *.elf

greenBeat-c.o: led.h

greenBeat-s.o: led.h
