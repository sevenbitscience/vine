/**
 * Utilities for drawing the tui with ncurses
 */

#include "tui_utils.h"
#include <string>

namespace fs = std::filesystem;

std::string PAGE_HINT = "...";

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

void drawCenteredText(std::string &text, int y) {
	int x_cor = (COLS/2)-((text.length())/2);
	mvaddstr(y, x_cor, text.c_str()); 
}

void drawFileList(std::vector<fs::directory_entry> &files, unsigned int &selected, int p_top, unsigned int &l_start, unsigned int &l_end) {
	int y_height;

	// Draw the name of the directory we are currently in
	std::string path = files[0].path().parent_path();
	int directory_position = p_top - 1;
	drawCenteredText(path, directory_position);

	for (unsigned int i = l_start; i < l_end; i++) {
		// Figure out where the line needs to go
		y_height = i + p_top + 1 - l_start;

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

	if (l_start != 0)
		drawCenteredText(PAGE_HINT, p_top);

	if (l_end != files.size()) {
		int tail_position = (l_end - l_start) + p_top + 1;
		drawCenteredText(PAGE_HINT, tail_position);
	}
}

int FileMenu(std::vector<fs::directory_entry> &items, unsigned int &paging) {
	unsigned int selected_item = 0;
	int reload_required = 0;
	unsigned int page = 0;
	unsigned int start = 0;
	unsigned int end = ((page+1)*paging > items.size()) ? items.size() : (page+1)*paging;

	drawFileList(items, selected_item, 5, start, end);
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
					selected_item++;
					if (selected_item % paging == 0) page++;
					reload_required++;
				}
				break;
			case 'k':
				if (selected_item > 0) {
					selected_item--;
					if (selected_item % paging == paging-1) page--;
					reload_required++;
				}
				break;
			case '\n':
				return selected_item;
		}
		if (reload_required) {
			start = page*paging;
			end = ((page+1)*paging > items.size()) ? items.size() : (page+1)*paging;
			
			clear();
			drawFileList(items, selected_item, 5, start, end);

			refresh();
			reload_required = 0;
		}
	}
}
