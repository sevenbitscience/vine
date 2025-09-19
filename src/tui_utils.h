#ifndef TUI_UTILS_H
#define TUI_UTILS_H

#include <ncurses.h>

#include "utils.h"

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
void drawFileList(std::vector<std::filesystem::directory_entry> &files, int &selected, int p_top, unsigned int &l_start, unsigned int &l_end);

/**
 * Draw some text, horizontally centered
 *
 * @param string The text to be displayed
 * @param y The vertical location for the text
 */
void drawCenteredText(std::string &text, int y);

/**
 * Show menu for selecting a file from a list
 *
 *	Will return the index of the course a user wants to select
 *	Returns -1 if the user wishes to quit the program 
 *
 * @param courses The array of items
 * @param paging The number of items to list per page
 * @return the index of the item that was selected
 */
int FileMenu(std::vector<std::filesystem::directory_entry> &items, std::string &title, unsigned int &paging);

#endif
