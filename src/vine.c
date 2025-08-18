/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include "file_parsing.c"
#include "tui_utils.c"

#include <stdio.h>

#define TITLE "vine"

int main(int argc, char *argv[]) {

	char* path = "./";
	// Get the search directory
	if (argc > 1 && isDirectory(argv[1])) {
		path = strdup(argv[1]);
	}

	int n_files;
	char** directory = NULL;
	int selection_index;
	char* selection = NULL;

	// Start ncurses
	Init();

	while (1) {
		n_files = getFileCount(path);

		// Create the array of classes
		if (directory != NULL) {
			free(directory);

		}
		directory = GetFiles(path);
		if (directory == NULL) {
			endwin();
			perror("Fatal errror, could not open selected directory");
			return -1;
		}

		drawCenteredText(TITLE, 3);
		DrawFiles(directory, n_files, 0, 5, 2);
		refresh();

		// Show user the selection menu to pick a file
		selection_index = SelectMenu(directory, n_files);

		// If the user wants to quit
		if (selection_index == -1) {
			free(directory);
			if (selection != NULL) {
				free(selection);
			}
			endwin();
			return 0;
		}

		if (selection != NULL) {
			free(selection);
		}
		selection = concatPath(path, directory[selection_index]);

		if (isDirectory(selection)) {
			// The selected item is a directory, so we should
			// append it to the path, and let the user look in there
			path = (char*)malloc(sizeof(char) * strlen(selection));
			path = strdup(selection);
			clear();
			//drawCenteredText(selection, 10);
			refresh();
		} else {
			// The selected item is some file, so lets open it up for the user
			char* callEditor = (char*)malloc(sizeof(char)* (12 + strlen(selection)));
			sprintf(callEditor, "$EDITOR \"%s\"", selection);
			
			endwin();
			system(callEditor);

			free(callEditor);
			free(selection);
			return 0;
		}
	}
	return 0;
}

