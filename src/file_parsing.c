#include "file_parsing.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int isMarkdown(const char* filename) {
	if (strlen(filename) < 3) {
		return 0;
	} else {
		return filename[strlen(filename)-2] == 'm' && filename[strlen(filename)-1] == 'd';
	}
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int getCourseCount(const char* path) {
	DIR *directory;						// The directory we are searching in
	struct dirent *file;				// A directory entry
	int fileCount = 0;					// So we know how many markdown files there are

	// First count up the number of markdown files, so we can allocate enough memory to store their names
	directory = opendir(path);
	if (directory != NULL) {
		while (file = readdir(directory)) {
			if (file->d_name[0] != '.' && isDirectory(file->d_name)) {		// Ignore hidden files
				fileCount++;
			}
		}
		(void) closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}

	return fileCount;
}

int getMarkdownCount(const char* path) {
	DIR *directory;						// The directory we are searching in
	struct dirent *file;				// A directory entry
	int fileCount = 0;					// So we know how many markdown files there are

	// First count up the number of markdown files, so we can allocate enough memory to store their names
	directory = opendir(path);
	if (directory != NULL) {
		while (file = readdir(directory)) {
			if (file->d_name[0] != '.' && isMarkdown(file->d_name)) {		// Ignore hidden files
				fileCount++;
			}
		}
		(void) closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}

	return fileCount;
}

void GetCourses(char* courses[], char* path) {
	DIR *directory;
	struct dirent *file;
	int i = 0;

	directory = opendir("./");
	if (directory != NULL) {
		while (file = readdir(directory)) {
			if (file->d_name[0] != '.' && isDirectory(file->d_name)) {		// Ignore hidden files
				courses[i] = malloc(sizeof(char*));
				strcpy(courses[i], file->d_name);
				i++;
			}
		}
		(void) closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}
}

void GetNotes(char* files[], char* path) {
	DIR *directory;
	struct dirent *file;
	int i = 0;

	directory = opendir("./");
	if (directory != NULL) {
		while (file = readdir(directory)) {
			if (file->d_name[0] != '.' && isMarkdown(file->d_name)) {		// Ignore hidden files
				files[i] = malloc(sizeof(char*));
				strcpy(files[i], file->d_name);
				i++;
			}
		}
		(void) closedir(directory);
	} else {
		perror("Couldn't open the directory");
	}
}
