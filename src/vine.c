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

	int selected_line = 0;

	DrawFiles(course_folders, n_courses, selected_line, 5, 2);
	refresh();

	for (;;) {
		// Wait for user input
		char input = getch();

		switch (input) {
			case 'q':
				// End ncurses
				endwin();
				return 0;
				break;
			case 'j':
				if (selected_line < n_courses-1) {
					selected_line = (selected_line + 1);
					DrawFiles(course_folders, n_courses, selected_line, 5, 2);
					refresh();
				}
				break;
			case 'k':
				if (selected_line > 0) {
					selected_line = (selected_line - 1);
					DrawFiles(course_folders, n_courses, selected_line, 5, 2);
					refresh();
				}
				break;
			
		}
	}

	endwin();
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
