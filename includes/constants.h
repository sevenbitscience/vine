#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace vconstants {
	// Hard strings
	const std::string TITLE = "Vine";
	const std::string PAGE_HINT = "...";
	const std::string DEFAULT_DIRECTORY = "./"; 
	const std::string RUN_EDITOR = "$EDITOR \"";
	const std::string RUN_ED_TAIL = "\"\n";

	const std::string HELP_TEXT = "-dir <directory>\tSet the directory to look in\n"
		"-p <page_size>\t\tSet how many items to show per page\n"
		"-h, --help\t\tShow this help\n";

	// return states
	const int SUCCESS = 0;
	const int PATH_DOES_NOT_EXIST = 1;
	const int PATH_IS_NOT_DIRECTORY = 2;
	const int ILLEGAL_ARGUMENT = 3;

	const int USER_QUIT = -1;
}

#endif
