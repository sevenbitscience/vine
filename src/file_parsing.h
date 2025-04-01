#ifndef FILE_PARSING_H
#define FILE_PARSING_H

/**
 * Checks if the object at a path is a directory
 *
 * @param path Path to the thing to check 
 * @return Returns 1 if it is a directory, otherwise 0
 */
int isDirectory(const char *path);

/**
 * Counts the number of files and directories in a directory
 *
 * @param path Path to the directory to search in
 */
int getFileCount(const char* path);

/**
 * Create an array of file or directory names
 *
 * Generic function for creating an array of objects in a directory
 *
 * @param courses The array that the file/folder names will be added to
 * @param path The path to search at
 */
void GetFiles(char* files[], char* path);

#endif
