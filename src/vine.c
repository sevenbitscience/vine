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
		char* directory[n_files];
		GetFiles(directory, path);

		drawCenteredText(TITLE, 3);
		DrawFiles(directory, n_files, 0, 5, 2);
		refresh();

		// Show user the selection menu to pick a file
		int selection_index = SelectMenu(directory, n_files);

		// If the user wants to quit
		if (selection_index == -1) {
			//free(directory);
			endwin();
			return 0;
		}

		if (isDirectory(directory[selection_index])) {
			// The selected item is a directory, so we should
			// append it to the path, and let the user look in there

			char* next_dir;
			next_dir = malloc(2 + sizeof(path) + sizeof(directory[selection_index]));
			strcpy(next_dir, path);
			strcat(next_dir, directory[selection_index]);
			strcat(next_dir, "/");
			path = next_dir;
		} else {
			// The selected item is some file, so lets open it up for the user

			char* callEditor;
			// Allocate space for the string with the name of the program, a space,
			// the path to the file, and the file name.
			callEditor = malloc(sizeof(EDITOR) + sizeof(path) + 
					sizeof(directory[selection_index] + 2));
			strcpy(callEditor, EDITOR);
			strcat(callEditor, " ");
			strcat(callEditor, path);
			strcat(callEditor, directory[selection_index]);
			endwin();
			system(callEditor);

			free(callEditor);
			//free(directory);
			return 0;
		}
	}
	return 0;
}
