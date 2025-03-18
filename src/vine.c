/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include "file_parsing.c"
#include "tui_utils.c"

#include <stdio.h>


void file_test();

int main() {
	// Find the classes first
	char* path = "./";
	int n_courses = getCourseCount(path);

	// Create the array of classes
	char* course_folders[n_courses];
	GetCourses(course_folders, path);

	Init();

	drawCenteredText("vine", 3);

	DrawFiles(course_folders, n_courses, 0, 5, 2);
	refresh();

	int selected_course = SelectMenu(course_folders, n_courses);

	// Show the options for folders

	char* notes_dir;
	notes_dir = malloc(2 + sizeof(path) + sizeof(course_folders[selected_course]));
	strcpy(notes_dir, path);
	strcat(notes_dir, course_folders[selected_course]);
	strcat(notes_dir, "/");

	endwin();
	printf("%s\n", notes_dir);
	return 0;
}

void file_test() {
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
}
