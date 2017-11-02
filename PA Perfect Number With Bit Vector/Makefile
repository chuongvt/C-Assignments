CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = parfait.o sieve.o bv.o

.PHONY:	all
all: parfait

parfait:	$(OBJECTS)
	$(CC) $(CFLAGS)	$(OBJECTS) -o parfait -lm

parfait.o:	parfait.c
	$(CC) $(CFLAGS) -c -g parfait.c

sieve.o:	sieve.c
	$(CC) $(CFLAGS) -c sieve.c

bv.o:	bv.c
	$(CC) $(CFLAGS) -c bv.c

.PHONY:	clean
clean:
	rm -f $(OBJECTS) parfait
