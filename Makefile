CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: state_sort

state_sort: src/state_sort.o
	$(CC) $(CFLAGS) -o ./build/Quest_1 src/state_sort.o

state_sort.o: src/state_sort.c
	$(CC) $(CFLAGS) -c src/state_sort.c

state_search: src/state_search.o
	$(CC) $(CFLAGS) -o ./build/Quest_2 src/state_search.o

state_search.o: src/state_search.c
	$(CC) $(CFLAGS) -c src/state_search.c

clean:
	rm -f *.o build/*