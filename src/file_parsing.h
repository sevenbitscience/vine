#ifndef FILE_PARSING_H
#define FILE_PARSING_H

/**
 * Checks if a provided string is the name of a markdown file.
 *
 * Checks if the final three characters of the filename are '.md'
 *
 * @param filename A string
 * @return Returns 1 true if the provided filename is a markdown file.
 */
int isMarkdown(const char* filename);

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
 * Counts the number of directories in a parent directory
 *
 * @param path Path to the parent directory to search in
 */
int getCourseCount(const char* path);

/**
 * Counts the number of markdown files in a parent directory
 *
 * @param path Path to the parent directory to search in
 */
int getMarkdownCount(const char* path);

/**
 * Create an array of file or directory names
 *
 * Generic function for creating an array of objects in a directory
 *
 * @param courses The array that the file/folder names will be added to
 * @param path The path to search at
 */
void GetFiles(char* files[], char* path);

/**
 * Create an array of course names
 *
 * The notes for each course are stored in a folder
 * the name of that folder is assumed to be the name of the course
 *
 * @param courses The array that the course names will be added to
 * @param path The path the course folders are stored at
 */
void GetCourses(char* courses[], char* path);

/**
 * Create an array of markdown notes file's names
 *
 * The notes for each course are stored in a folder
 * This function looks at a directory and add all of the names of markdown
 * files to an array
 *
 * @param courses The array that the markdown file names will be added to
 * @param path The path the notes are stored at
 */
void GetNotes(char* files[], char* path);

#endif
