#ifndef TUI_UTILS_H
#define TUI_UTILS_H

/**
 * Initiallizes ncurses settings
 */
void Init();

/**
 * Draws a list of files on the screen.
 *
 * One of the files is highlighted to show a selection
 *
 * @param files List of strings, i.e. file names
 * @param selected The index of the selected file
 */
void DrawFiles(char* files[], int selected);

/**
 * Draw some text, horizontally centered
 *
 * @param string The text to be displayed
 * @param y The vertical location for the text
 */
void drawCenteredText(char* string, int y);

#endif
