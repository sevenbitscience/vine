/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include <string.h>
#include <iostream>

#include "file_parsing.h"
#include "tui_utils.h"

namespace fs = std::filesystem;

void loop(fs::directory_entry &path, unsigned int &paging);

void help();

int main(int argc, char *argv[]) {
	fs::directory_entry path = fs::directory_entry(fs::path("./"));
	unsigned int paging_size = 15;

	// Get command line args
	for (int arg = 1; arg < argc; arg++) {
		int moreFollows = arg + 1 < argc;
		if (!strcmp(argv[arg], "-d") && moreFollows)
			path = fs::directory_entry(fs::path(argv[arg+1]));
		else if (!strcmp(argv[arg], "-p") && moreFollows) {
			paging_size = atoi(argv[arg+1]);
			if (paging_size < 1) return -1;
		} else if (!strcmp(argv[arg], "--help") || !strcmp(argv[arg], "-h")) {
			help();
			exit(0);
		} else {
			std::cout << "Unrecognized argument: " << argv[arg] << '\n';
			help();
			exit(1);
		}
	}

	loop(path, paging_size);

	exit(0);
}

void help() {
	std::cout << 
		"-dir <directory>\tSet the directory to look in\n"
		"-p <page_size>\t\tSet how many items to show per page\n"
		"-h, --help\t\tShow this help\n";
}

void loop(fs::directory_entry &path, unsigned int &paging) {
	std::vector<fs::directory_entry> directory;
	int selection_index;
	fs::directory_entry selection;

	std::string title = "Vine";

	// Start ncurses
	Init();

	while (1) {
		// Create the array of classes
		directory = GetFiles(path);

		// Show user the selection menu to pick a file
		selection_index = FileMenu(directory, title, paging);

		// If the user wants to quit
		if (selection_index == -1) {
			endwin();
			return;
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

			return;
		}
	}
}
