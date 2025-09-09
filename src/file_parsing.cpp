#include "file_parsing.h"
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

/*
int getFileCount(std::string path) {
	DIR *directory;						// The directory we are searching in
	struct dirent *file;				// A directory entry
	int fileCount = 0;

	directory = opendir(path);
	if (directory != NULL) {
		while ((file = readdir(directory)) != NULL) {
			if (file->d_name[0] != '.') {		// Ignore hidden files
				fileCount++;
			}
		}
		(void) closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}

	return fileCount;
}
*/

std::vector<fs::directory_entry> GetFiles(std::string path) {
	std::vector<fs::directory_entry> files;

	fs::directory_entry path_dirent{fs::path{path}};

	if (!path_dirent.exists()) 
		throw std::invalid_argument("Directory path does not exist!");

	if (!path_dirent.is_directory()) 
		throw std::invalid_argument("Directory path does not refer to a directory!");

	for (const auto& dirent : fs::directory_iterator(path)) {
		files.push_back(dirent);
	}
	return files;
}

/*
char* concatPath(std::string path, std::string item) {
	char* out = NULL;
	if (path[(strlen(path)/sizeof(char))-1] == '/') {		// Does the path end in a forward slash?
		out = (char*)malloc(sizeof(char) * (strlen(path) + strlen(item) + 0));
		sprintf(out, "%s%s", path, item);
	} else {									// We need to add a forward slash to the path
		out = (char*)malloc(sizeof(char) * (strlen(path) + strlen(item) + 1));
		sprintf(out, "%s/%s", path, item);
	}
	return out;
}
*/
