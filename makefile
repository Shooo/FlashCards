TORM = deck.o flash_cards flash_cards.o
CC = g++
CCFLAGS = -g -O3 -Wall -Wpointer-arith -Wcast-qual -Wwrite-strings

flash_cards:	flash_cards.o
	${CC} ${CCFLAGS} -o flash_cards flash_cards.o deck.o

flash_cards.o:		flash_cards.cpp flash_cards.h deck.o
		${CC} ${CCFLAGS} -c flash_cards.cpp

deck.o:		deck.cc deck.h deck_exception.h
		${CC} ${CCFLAGS} -c deck.cc

clean:
	rm -f ${TORM}
