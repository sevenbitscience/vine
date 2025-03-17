/**
 * Utilities for drawing the tui with ncurses
 */

#include "tui_utils.h"

#include <ncurses.h>
#include <string.h>

int main() {
	Init();

	refresh();

	for (;;) {
		// Wait for user input
		char input = getch();

		switch (input) {
			case 'q':
				// End ncurses
				endwin();
				return 0;
				break;
			case 'j':
				attrset(COLOR_PAIR(1));
				drawCenteredText("AAAAAHHH", 10);
				break;
			case 'k':
				attrset(COLOR_PAIR(2));
				drawCenteredText("WOOOOO!!!", 10);
				break;
		}
	}

	endwin();
	return 0;
}

void Init() {
	// Initiallize ncuses
	initscr();

	noecho();

	// Setup colors, if the terminal supports them
	if (has_colors()) {
		start_color();

		init_pair(1, COLOR_WHITE, COLOR_BLACK);
		init_pair(2, COLOR_BLACK, COLOR_WHITE);
	}
}

void drawCenteredText(char* string, int y) {
	int x_cor = (COLS/2)-(strlen(string)/2);
	mvaddstr(y, x_cor, string); 
}

