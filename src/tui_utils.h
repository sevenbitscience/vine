#ifndef TUI_UTILS_H
#define TUI_UTILS_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <filesystem>

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
 * @param n_files The number of files to be listed
 * @param selected The index of the selected file
 */
void DrawFiles(std::vector<std::filesystem::directory_entry>, int selected, int p_top, int p_bot);

/**
 * Draw some text, horizontally centered
 *
 * @param string The text to be displayed
 * @param y The vertical location for the text
 */
void drawCenteredText(char* string, int y);

/**
 * Show menu for selecting an item from a list
 *
 *	Will return the index of the course a user wants to select
 *	Returns -1 if the user wishes to quit the program 
 *
 * @param courses The array of items
 * @param size The number of elements in the array
 * @return the index of the item that was selected
 */
int SelectMenu(std::vector<char*> items, int size);

#endif
