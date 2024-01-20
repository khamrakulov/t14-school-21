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

clear_state: src/clear_state.o
	$(CC) $(CFLAGS) -o ./build/Quest_3 src/clear_state.o

clear_state.o: src/clear_state.c
	$(CC) $(CFLAGS) -c src/clear_state.c

clean:
	rm -f *.o build/*