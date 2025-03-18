vine:
	mkdir -p ./build
	gcc ./src/vine.c -lncurses -o ./build/vine

tui:
	mkdir -p ./build
	gcc ./src/tui_utils.c -lncurses -o ./build/tui

.PHONY: clean
clean:
	rm -r ./build
