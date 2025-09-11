#include "file_parsing.h"

namespace fs = std::filesystem;

int getFileCount(std::string path) {
	fs::directory_entry path_dirent{fs::path{path}};

	if (!path_dirent.exists()) 
		throw std::invalid_argument("Directory path does not exist!");

	if (!path_dirent.is_directory()) 
		throw std::invalid_argument("Directory path does not refer to a directory!");

	int count = 0;
	for (const auto& _: fs::directory_iterator(path)) {
		count++;
	}
	return count;
}

std::vector<fs::directory_entry> GetFiles(std::filesystem::path path) {
	fs::directory_entry path_dirent{fs::path{path}};

	if (!path_dirent.exists()) 
		throw std::invalid_argument("Directory path does not exist!");

	if (!path_dirent.is_directory()) 
		throw std::invalid_argument("Directory path does not refer to a directory!");

	std::vector<fs::directory_entry> files;

	for (const auto& dirent : fs::directory_iterator(path)) {
		files.push_back(dirent);
	}
	return files;
}
