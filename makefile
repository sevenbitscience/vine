CFLAGS = -Wall -g

all: tui_utils.o file_parsing.o vine.o
	gcc $(CFLAGS) -lncurses -o vine ./vine.o ./tui_utils.o ./file_parsing.o 

tui_utils.o: ./src/tui_utils.h ./src/tui_utils.cpp 
	g++ $(CFLAGS) -c ./src/tui_utils.cpp

file_parsing.o: ./src/file_parsing.h ./src/file_parsing.cpp 
	g++ $(CFLAGS) -c ./src/file_parsing.cpp

vine.o: ./src/vine.cpp tui_utils.o file_parsing.o 
	g++ $(CFLAGS) -c ./src/vine.cpp

clean:
	rm -f *.o vine
