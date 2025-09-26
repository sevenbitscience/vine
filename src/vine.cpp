/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include <string.h>
#include <iostream>

#include "../includes/constants.h"
#include "../includes/file_parsing.h"
#include "../includes/tui_utils.h"

namespace fs = std::filesystem;

int loop(fs::directory_entry &path, unsigned int &paging);

void help();

int main(int argc, char *argv[]) {
	fs::directory_entry path = fs::directory_entry(
			fs::path(vconstants::DEFAULT_DIRECTORY));
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
			exit(vconstants::SUCCESS);
		} else {
			std::cout << "Unrecognized argument: " << argv[arg] << '\n';
			help();
			exit(vconstants::ILLEGAL_ARGUMENT);
		}
	}

	loop(path, paging_size);

	exit(0);
}

void help() {
	std::cout << vconstants::HELP_TEXT;
}

int loop(fs::directory_entry &path, unsigned int &paging) {
	int status = vconstants::SUCCESS;

	std::vector<fs::directory_entry> directory;
	int selection_index;
	fs::directory_entry selection;

	// Start ncurses
	Init();

	while (1) {
		// Create the array of classes
		status = GetFiles(directory, path);

		if (status) return status;

		// Show user the selection menu to pick a file
		status = FileMenu(directory, selection_index, paging);

		// If the user wants to quit
		if (status == vconstants::USER_QUIT) {
			endwin();
			return status;
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
			std::string callEditor = vconstants::RUN_EDITOR;
			callEditor.append(selection.path());
			callEditor.append(vconstants::RUN_ED_TAIL);
			
			endwin();
			std::system(callEditor.c_str());

			return status;
		}
	}
	return vconstants::SUCCESS;
}
