CC=gcc
CFLAGS=-g -O0 -Wall

SRC=./src
SRCS=$(SRC)/Mush.c $(SRC)/Mush.h

OBJS=$(SRC)/Mush.o

## Where you want mush to install to.
PATH=/bin


mush: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

Mush.o: Mush.c
	$(CC) $(CFLAGS) -c -o $@ $^


install::
	cp -v mush $(PATH)/mush


clean::
	rm -f $(SRC)/*.o mush

iClean::
	rm -f $(PATH)/mush
