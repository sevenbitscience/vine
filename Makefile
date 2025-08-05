vine:
	mkdir -p ./build
	gcc ./src/vine.c -lncurses -Wall -o ./build/vine

tui:
	mkdir -p ./build
	gcc ./src/tui_utils.c -lncurses -Wall -o ./build/tui

.PHONY: clean
clean:
	rm -r ./build
