/**
 * Utilities for drawing the tui with ncurses
 */

#include "tui_utils.h"

#include <ncurses.h>
#include <string.h>

int main() {
	Init();

	char* lines_of_text[3] = {"One", "Two", "Three"};

	int selected_line = 0;

	DrawFiles(lines_of_text, 3, selected_line, 5, 2);
	refresh();

	for (;;) {
		// Wait for user input
		char input = getch();

		if (input == 'q') {
			// End ncurses
			endwin();
			return 0;
			break;
		}
		switch (input) {
			case 'q':
				// End ncurses
				endwin();
				return 0;
				break;
			case 'j':
				if (selected_line < 2) {
					selected_line = (selected_line + 1);
					DrawFiles(lines_of_text, 3, selected_line, 5, 2);
					refresh();
				}
				break;
			case 'k':
				if (selected_line > 0) {
					selected_line = (selected_line - 1);
					DrawFiles(lines_of_text, 3, selected_line, 5, 2);
					refresh();
				}
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

void DrawFiles(char* files[], int n_files, int selected, int p_top, int p_bot) {
	int y_height;
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
