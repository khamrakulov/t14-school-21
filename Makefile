CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

all: state_sort

state_sort: ./state_sort.o
	$(CC) $(CFLAGS) -o ../build/Quest_1 ./state_sort.o

state_sort.o: ./state_sort.c
	$(CC) $(CFLAGS) -c ./state_sort.c

state_search: ./state_search.o
	$(CC) $(CFLAGS) -o ../build/Quest_2 ./state_search.o

state_search.o: ./state_search.c
	$(CC) $(CFLAGS) -c ./state_search.c

clear_state: ./clear_state.o
	$(CC) $(CFLAGS) -o ../build/Quest_3 ./clear_state.o

clear_state.o: ./clear_state.c
	$(CC) $(CFLAGS) -c ./clear_state.c

clean:
	rm -f *.o ../build/*
