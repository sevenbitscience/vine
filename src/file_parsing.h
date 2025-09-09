#ifndef FILE_PARSING_H
#define FILE_PARSING_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <filesystem>

/**
 * Counts the number of files and directories in a directory
 *
 * @param path Path to the directory to search in
 */
int getFileCount(std::string path);

/**
 * Create an array of file or directory names
 *
 * Generic function for creating an array of objects in a directory
 *
 * @param path The path to search at
 * @return char** containing filenames of the files at path
 */
std::vector<std::filesystem::path> GetFiles(std::filesystem::path path);

/**
 * Concat parts of a file path
 */
char* concatPath(std::string path, std::string item);

#endif
