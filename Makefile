vine:
	mkdir -p ./build
	gcc ./src/vine.c -lncurses -Wall -g -o ./build/vine

.PHONY: clean
clean:
	rm -r ./build
