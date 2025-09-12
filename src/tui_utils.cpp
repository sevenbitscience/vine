/**
 * Utilities for drawing the tui with ncurses
 */

#include "tui_utils.h"

namespace fs = std::filesystem;

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
void drawCenteredText(std::string string, int y) {
	int x_cor = (COLS/2)-((string.length())/2);
	mvaddstr(y, x_cor, string.c_str()); 
}

void drawFileList(std::vector<fs::directory_entry> files, unsigned int selected, int p_top, int p_bot) {
	int y_height;

	// Draw the name of the directory we are currently in
	drawCenteredText(files[0].path().parent_path(), p_top - 1);

	for (unsigned int i = 0; i < files.size(); i++) {
		// Figure out where the line needs to go
		y_height = i + p_top + 1;
		// If the line is too far down, give up and don't draw it.
		if (y_height > (LINES - p_bot))
			break;

		// Change color if we are drawing the selected item
		if (i == selected) 
			attrset(COLOR_PAIR(2));

		// Create a string for the filename
		std::string formatted_filename = files[i].path().filename();

		// Draw the filename
		drawCenteredText(formatted_filename, y_height);

		// If we changed the colors, switch back to the defaults
		if (i == selected)
			attrset(COLOR_PAIR(1));
	}
}

int FileMenu(std::vector<fs::directory_entry> items) {
	unsigned int selected_item = 0;
	int reload_required = 0;

	drawFileList(items, selected_item, 5, 2);
	refresh();

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
				if (selected_item < items.size()-1) {
					selected_item = (selected_item + 1);
					reload_required++;
				}
				break;
			case 'k':
				if (selected_item > 0) {
					selected_item = (selected_item - 1);
					reload_required++;
				}
				break;
			case '\n':
				return selected_item;
		}
		if (reload_required) {
			drawFileList(items, selected_item, 5, 2);
			refresh();
			reload_required = 0;
		}
	}
}
