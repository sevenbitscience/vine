/**
 * Utilities for drawing the tui with ncurses
 */

#include "tui_utils.h"

#include <ncurses.h>
#include <string.h>

void Init() {
	// Initiallize ncuses
	initscr();

	noecho();
	curs_set(0);

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

void DrawFiles(char* files[], int n_files, int selected, int p_top, int p_bot) {
	int y_height;
	int x_cor;

	for (int i = 0; i < n_files; i++) {
		y_height = i + p_top;
		if (y_height > (LINES - p_bot)) {
			break;
		}
		if (i == selected) {
			attrset(COLOR_PAIR(2));
		} else {
			attrset(COLOR_PAIR(1));
		}
		drawCenteredText(files[i], y_height);
	}
}

int SelectMenu(char* items[], int size) {
	int selected_item = 0;

	for (;;) {
		// Wait for user input
		char input = getch();

		switch (input) {
			case 'q':
				// End ncurses
				endwin();
				return -1;
				break;
			case 'j':
				if (selected_item < size) {
					selected_item = (selected_item + 1);
				}
				break;
			case 'k':
				if (selected_item > 0) {
					selected_item = (selected_item - 1);
				}
				break;
			case '\n':
				return selected_item;
		}
		DrawFiles(items, size, selected_item, 5, 2);
		refresh();
	}
}
