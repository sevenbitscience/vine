CC = g++
CFLAGS = -Wall -g
LNFLAGS = -lncurses

all: tui_utils.o file_parsing.o vine.o
	$(CC) $(CFLAGS) $(LNFLAGS) -o vine ./vine.o ./tui_utils.o ./file_parsing.o 

tui_utils.o: ./includes/tui_utils.h ./src/tui_utils.cpp ./includes/constants.h
	$(CC) $(CFLAGS) -c ./src/tui_utils.cpp

file_parsing.o: ./includes/file_parsing.h ./src/file_parsing.cpp ./includes/constants.h
	$(CC) $(CFLAGS) -c ./src/file_parsing.cpp

vine.o: ./src/vine.cpp ./includes/constants.h
	$(CC) $(CFLAGS) -c ./src/vine.cpp

clean:
	rm -f *.o vine
