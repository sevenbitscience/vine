/**
 * Testing out drawing out a tui
 */

#include <ncurses.h>
#include <string.h>

int loop();

int main() {
	// Initialize ncurses
	initscr(); 
	
	// Set some setttings
	noecho();

	// Setup colors
	
	if (has_colors()) {
		start_color();

		init_pair(1, COLOR_RED, COLOR_BLUE);
		init_pair(2, COLOR_GREEN, COLOR_MAGENTA);
	}

	char* title = "Hello, ncurses!";

	// Print text to the window
	mvaddstr((LINES/2)-3, (COLS/2)-(strlen(title)/2), title); 

	// Refresh the screen to display the text
	refresh();

	loop();
	
	return 0;
}

int loop() {
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
				mvaddch(1,1, 'j');
				break;
			case 'k':
				attrset(COLOR_PAIR(2));
				mvaddch(1,1, 'k');
				break;
		}
	}
}
