CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = sorting.o minsort.o bubblesort.o insertionsort.o quicksort.o mergesort.o
.PHONY: all
all: sorting

sorting:        $(OBJECTS)
	$(CC) $(CFLAGS) -o sorting $(OBJECTS)

sorting.o:	sorting.c
	$(CC) $(CFLAGS) -DMASK=0x00ffffff -c -g sorting.c

minsort.o:        minsort.c
	$(CC) $(CFLAGS) -c minsort.c

bubblesort.o:   bubblesort.c
	$(CC) $(CFLAGS) -c bubblesort.c

insertionsort.o:	insertionsort.c
	$(CC) $(CFLAGS) -c insertionsort.c

quicksort.o:	quicksort.c
	$(CC) $(CFLAGS) -c quicksort.c

mergesort.o:	mergesort.c
	$(CC) $(CFLAGS) -c mergesort.c

.PHONY: clean
clean:
	rm -f $(OBJECTS) sorting
