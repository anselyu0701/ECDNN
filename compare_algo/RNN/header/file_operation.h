#ifndef __FILE_OPERATION_H__
#define __FILE_OPERATION_H__

#include <fstream>
#include <sstream>
#include <string.h>
#include <iostream>
#include <vector>


/**
 * @brief Read the file and save the data in 1-D array
 * @param file_name Name of the file 
 * @return An 1-D float array 
*/
std::vector<int> readLabelFile (char* path, char* file_name);

/**
 * @brief Read the file and save the data in 2-D array
 * @param file_name Name of the file 
 * @return An 2-D float array 
*/
std::vector<std::vector<float>> readDataFile (char* path, char* file_name);

void writeResultFile(char* path, int k, float result);

char* setFilePath (char* path, char* file_name);

#endif