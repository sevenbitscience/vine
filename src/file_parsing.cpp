#include "file_parsing.h"

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int getFileCount(const char* path) {
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

/*
void GetFiles(char* files[], char* path) {
	DIR *directory;
	struct dirent *file;
	int i = 0;
	char* filepath;

	directory = opendir(path);
	if (directory != NULL) {
		while ((file = readdir(directory)) != NULL) {
			if (file->d_name[0] != '.') {		// Ignore hidden files
				*filepath = *path;
				strcat(filepath, path);
				strcat(filepath, file->d_name);
				printf("%ld,%ld\n", sizeof(file->d_name), sizeof(filepath));
				files[i] = malloc(sizeof(file->d_name));
				strcpy(files[i], file->d_name);
				i++;
				//free(filepath);
			}
		}
		(void) closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}
}
*/

char** GetFiles(const char* path) {
	DIR *directory;
	struct dirent *file;
	char** files = NULL;

	int filecount = getFileCount(path);
	files = (char**)realloc(files, sizeof(char*) * filecount);

	directory = opendir(path);
	if (directory == NULL) {
		perror("Could not open the directory!");
		return NULL;
	}
	
	int i = 0;
	while ((file = readdir(directory)) != NULL) {
		if (file->d_name[0] != '.' ) {
			files[i] = strdup(file->d_name);
			i++;
		}
	}
	return files;
}

char* concatPath(char* path, char* item) {
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
