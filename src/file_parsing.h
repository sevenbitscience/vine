#ifndef FILE_PARSING_H
#define FILE_PARSING_H

#include <stdio.h>
#include <dirent.h>
#include <string>
#include <stdlib.h>
#include <sys/stat.h>

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
 * @param path The path to search at
 * @return char** containing filenames of the files at path
 */
char** GetFiles(const char* path);

/**
 * Concat parts of a file path
 */
char* concatPath(char* path, char* item);

#endif
