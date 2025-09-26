#include "../includes/file_parsing.h"
#include "../includes/constants.h"

namespace fs = std::filesystem;

int getFileCount(std::string &path) {
	fs::directory_entry path_dirent{fs::path{path}};

	if (!path_dirent.exists()) 
		return vconstants::PATH_DOES_NOT_EXIST;

	if (!path_dirent.is_directory()) 
		return vconstants::PATH_DOES_NOT_EXIST;

	int count = 0;
	for (const auto& _: fs::directory_iterator(path)) {
		count++;
	}
	return vconstants::SUCCESS;
}

int GetFiles(std::vector<fs::directory_entry> &entries, std::filesystem::directory_entry &path) {
	if (!path.exists()) 
		return vconstants::PATH_DOES_NOT_EXIST;

	if (!path.is_directory()) 
		return vconstants::PATH_IS_NOT_DIRECTORY;


	for (const auto& dirent : fs::directory_iterator(path.path())) {
		entries.push_back(dirent);
	}
	return vconstants::SUCCESS;
}
