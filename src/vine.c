/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include "file_parsing.c"
#include "tui_utils.c"

#include <stdio.h>

#define TITLE "vine"

int main() {
	// Start ncurses
	Init();

	// Initial search directory
	char* path = "/home/joey";

	while (1) {
		int n_files;
		n_files = getFileCount(path);

		// Create the array of classes
		char** directory = GetFiles(path);

		drawCenteredText(TITLE, 3);
		DrawFiles(directory, n_files, 0, 5, 2);
		refresh();

		// Show user the selection menu to pick a file
		int selection_index = SelectMenu(directory, n_files);

		// If the user wants to quit
		if (selection_index == -1) {
			free(directory);
			endwin();
			return 0;
		}

		char* selection = strdup(path);
		strcat(selection, "/");
		strcat(selection, directory[selection_index]);

		if (isDirectory(selection)) {
			// The selected item is a directory, so we should
			// append it to the path, and let the user look in there

			path = strdup(selection);
			free(selection);
			refresh();
		} else {
			// The selected item is some file, so lets open it up for the user

			char* callEditor = strdup("$EDITOR ");
			strcat(callEditor, selection);
			endwin();
			system(callEditor);

			free(callEditor);
			free(directory);
			free(selection);
			return 0;
		}
	}
	return 0;
}
