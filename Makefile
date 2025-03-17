vine:
	mkdir -p ./build
	gcc ./src/vine.c -o ./build/vine

tui:
	mkdir -p ./build
	gcc ./src/tui_utils.c -lncurses -o ./build/tui

drawtest:
	mkdir -p ./build
	gcc src/drawtest.c -lncurses -o draw

.PHONY: clean
clean:
	rm -r ./build
