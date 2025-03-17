/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include <stdio.h>
#include "file_parsing.c"

int main() {
	char* path = "./";
	int dirCount = getCourseCount(path);

	printf("There are %d directories\n", dirCount);

	char* folders[dirCount];
	GetCourses(folders, path);

	for (int n = 0; n < dirCount; n++) {
		printf("%s\n", folders[n]);
		free(folders[n]);
	}

	int mdCount = getMarkdownCount(path);

	printf("There are %d markdown files\n", mdCount);

	char* notes[mdCount];
	GetNotes(notes, path);

	for (int n = 0; n < mdCount; n++) {
		printf("%s\n", notes[n]);
		free(notes[n]);
	}

	return 0;
}

