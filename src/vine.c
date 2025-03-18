/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include "file_parsing.c"
#include "tui_utils.c"

#include <stdio.h>

#define TITLE "vine"

void file_test();

int main() {
	// Find the classes first
	char* path = "./";
	int n_courses = getCourseCount(path);

	// Create the array of classes
	char* course_folders[n_courses];
	GetCourses(course_folders, path);

	Init();

	drawCenteredText(TITLE, 3);
	DrawFiles(course_folders, n_courses, 0, 5, 2);
	refresh();

	// Show the options for folders

	int selected_course = SelectMenu(course_folders, n_courses);

	char* notes_dir;
	notes_dir = malloc(2 + sizeof(path) + sizeof(course_folders[selected_course]));
	strcpy(notes_dir, path);
	strcat(notes_dir, course_folders[selected_course]);
	strcat(notes_dir, "/");

	// TODO: Free up `course_folders`

	// Now we can look in the selected folder for notes
	int notes_count = getMarkdownCount(notes_dir);
	char* notes[notes_count];
	GetNotes(notes, notes_dir);

	clear();

	drawCenteredText(TITLE, 3);
	DrawFiles(notes, notes_count, 0, 5, 2);
	refresh();

	// Show the options for folders

	int selected_note = SelectMenu(notes, notes_count);

	endwin();

	char* vim_call = malloc(sizeof("vim ") + sizeof(notes_dir) + sizeof(notes[selected_note] + 1));
	strcpy(vim_call, "vim ");
	strcat(vim_call, notes_dir);
	strcat(vim_call, notes[selected_note]);
	system(vim_call);

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
