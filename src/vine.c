/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include "file_parsing.c"
#include "tui_utils.c"

#include <stdio.h>

#define TITLE "vine"
#define EDITOR "vim"

int main() {
	// Start ncurses
	Init();

	// Initial search directory
	char* path = "./";

	//int n_files = getCourseCount(path);
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

		if (isDirectory(directory[selection_index])) {
			// The selected item is a directory, so we should
			// append it to the path, and let the user look in there
			char* next_dir = strdup(path);
			strcat(next_dir, directory[selection_index]);
			path = next_dir;
		} else {
			// The selected item is some file, so lets open it up for the user

			char* callEditor = strdup(EDITOR);
			strcat(callEditor, " ");
			strcat(callEditor, directory[selection_index]);
			endwin();
			system(callEditor);

			free(callEditor);
			free(directory);
			return 0;
		}
	}
	return 0;
}
