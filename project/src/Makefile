# makfile configuration

COMMON_OBJECTS  =

CPU             = msp430g2553

CFLAGS          = -mmcu=${CPU} -Os -I../h 

LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include





#switch the compiler (for the internal make rules)

CC              = msp430-elf-gcc

AS              = msp430-elf-as



all: wdt.elf buzzer.elf led.elf wakedemo.elf



#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wdt-c.o buzzer.o led.o wakedemo.o ../../wakedemo/wdt_handler.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

#buzzer.elf: buzzer.o ../lib/libTimer.a
#	${CC} ${CFLAGS} -o $@ $^

led.elf: led.o greenBeat-c.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

wdt.elf: wdt-c.o 


load: wakedemo.elf wdt.elf
	msp430loader.sh  $^

load2: wakedemo.elf 
	msp430loader.sh  $^

clean: $^

	rm -f *.o *.elf

led.o: led.h

wdt-c.o: buzzer.h

buzzer.o : buzzer.h

greenBeat-c.o: led.h

greenBeat-s.o: led.h
