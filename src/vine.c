/**
 * Vim Notes Explorer
 *
 * Joey Milausnic, March 2025
 */

#include "file_parsing.c"
#include "tui_utils.c"

#include <stdio.h>

#define TITLE "vine"

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

	if (selected_course == -1) {
		endwin();
		return 0;
	}

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

	if (selected_note == -1) {
		free(notes_dir);
		endwin();
		return 0;
	}

	endwin();

	char* vim_call = malloc(sizeof("vim ") + sizeof(notes_dir) + sizeof(notes[selected_note] + 1));
	strcpy(vim_call, "vim ");
	strcat(vim_call, notes_dir);
	strcat(vim_call, notes[selected_note]);
	system(vim_call);

	free(vim_call);
	free(notes_dir);
	return 0;
}
