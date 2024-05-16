#include "file_operation.h"

char* setFilePath (char* path, char* file_name)
{
    size_t new_length = strlen(path) + strlen(file_name) + 1;
    char* new_path = new char[new_length];
    strcpy(new_path, path);
    strcat(new_path, file_name);
    return new_path;
}

std::vector<int> readLabelFile (char* path, char* file_name)
{
    path = setFilePath(path, file_name);
    std::string line, str;
    std::ifstream input_file(path);
    std::stringstream string_line(line);  
    std::vector<int> vec;

    if (!input_file.is_open()) 
    {
        std::cout << "Could not open the file - '" << path << "'" << std::endl;
        exit(0);
    }

    while (getline(input_file, line))
    {   
        string_line.clear();
        string_line.str(line); 
        while (string_line >> str)
        {
            vec.push_back(stof(str));
        }
    } 

    input_file.close();
    return vec;
}

std::vector<std::vector<float>> readDataFile (char* path, char* file_name)
{
    path = setFilePath(path, file_name);
    std::string line, str;
    std::ifstream input_file(path);
    std::stringstream string_line(line);  
    std::vector<std::vector<float>> array;    

    if (!input_file.is_open()) 
    {
        std::cout << "Could not open the file - '" << path << "'" << std::endl;
        exit(0);
    }

    while (getline(input_file, line))
    {   
        string_line.clear();
        string_line.str(line);
        std::vector<float> temp_vector; 
        while (string_line >> str)
        {
            temp_vector.push_back(stof(str));
        }
        array.push_back(temp_vector);
    }  

    input_file.close();
    return array;
}

void writeResultFile(char* path, int k, float result)
{
    char file_name[] = "Result.txt";
    path = setFilePath(path, file_name);
    std::ofstream output_file(path, std::ios::app);
    if (output_file.is_open()) {
        output_file << result << std::endl;
        output_file.close();
    } 
    else {
        std::cout << "Couldn't open File!" << std::endl;
        std::cout << path << std::endl;
    }
}