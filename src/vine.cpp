/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include "file_parsing.h"
#include "tui_utils.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
	fs::directory_entry path;

	// Get directory from path if it exists
	if (argc > 1) {
		path = fs::directory_entry(fs::path(argv[1]));
		// Make sure that argv[1] is valid input
		if (!path.exists() || !path.is_directory())
			path = fs::directory_entry(fs::path("./"));
	} else {
		path = fs::directory_entry(fs::path("./"));
	}

	std::vector<fs::directory_entry> directory;
	int selection_index;
	fs::directory_entry selection;

	std::string title = "Vine";
	unsigned int paging_size = 15;

	// Start ncurses
	Init();

	while (1) {
		// Create the array of classes
		directory = GetFiles(path);

		// Show user the selection menu to pick a file
		selection_index = FileMenu(directory, title, paging_size);

		// If the user wants to quit
		if (selection_index == -1) {
			endwin();
			return 0;
		}

		selection = directory[selection_index];

		if (selection.is_directory()) {
			// The selected item is a directory, so we should
			// append it to the path, and let the user look in there
			path = selection;
			clear();
			refresh();
		} else {
			// The selected item is some file, so lets open it up for the user
			std::string callEditor = "$EDITOR \"";
			callEditor.append(selection.path());
			callEditor.append("\"\n");
			
			endwin();
			std::system(callEditor.c_str());

			return 0;
		}
	}
	return 0;
}

