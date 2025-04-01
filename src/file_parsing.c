#include "file_parsing.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

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
		while (file = readdir(directory)) {
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

void GetFiles(char* files[], char* path) {
	DIR *directory;
	struct dirent *file;
	int i = 0;
	char* filepath;

	directory = opendir(path);
	if (directory != NULL) {
		while (file = readdir(directory)) {
			filepath = malloc(sizeof(path) + sizeof(file->d_name) + 1);		
			strcpy(filepath, path);
			strcat(filepath, file->d_name);
			if (file->d_name[0] != '.') {		// Ignore hidden files
				files[i] = malloc(sizeof(char*));
				strcpy(files[i], file->d_name);
				i++;
			}
			free(filepath);
		}
		(void) closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}
}
