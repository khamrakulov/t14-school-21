CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: state_sort

state_sort: src/state_sort.o
	$(CC) $(CFLAGS) -o ./build/Quest_1 src/state_sort.o

state_sort.o: src/state_sort.c
	$(CC) $(CFLAGS) -c src/state_sort.c

clean:
	rm -f *.o build/Quest_1