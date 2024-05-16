/**
 * @author Ansel Lyu
 * @date 2024/04/19
*/

#include "header/proposed.h"
#include "header/f1_score.h"
#include <string>

// ./random_knn trained_data.txt, trained_sample_size,  test_data.txt, trained_sample_size, dimension, k, number_cluster
int main(int argc, char* argv[])
{
    char trained_file[]         = "trained_data.txt";
    char trained_label_file[]   = "trained_label.txt";
    char test_file[]            = "testing_data.txt";
    char test_label_file[]      = "testing_label.txt";
    char* path; 
    char* _path;
    int k, number_cluster; 
    std::vector<std::vector<float>> trained_data;
    std::vector<int> trained_label_data;
    std::vector<std::vector<float>> testing_data;
    std::vector<int> test_label_data;
    std::vector<int> prediction;
    float result;  
    timespec start, end;

    if (argc != 4)
    {
        std::cout << "Invalid Arguments, argc is " << argc << std::endl;
        exit(0);
    }
    else 
    {
        _path =                 argv[1];   
        k =                     strtol(argv[2], NULL, 10);
        number_cluster =        strtol(argv[3], NULL, 10);
    }

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int folder_idx = 1; folder_idx < 101; folder_idx++)
    {    
        path = _path;
        std::string str_num = std::to_string(folder_idx) + "/";
        char* char_ptr = new char[str_num.length() + 1]; // +1 是為了存放 null 終止符
        strcpy(char_ptr, str_num.c_str());
        path = setFilePath(path, char_ptr);
        // read file
        std::cout << "Loading File..." << std::endl;
        trained_data        = readDataFile(path, trained_file);
        trained_label_data  = readLabelFile(path, trained_label_file);
        testing_data        = readDataFile(path, test_file);
        test_label_data     = readLabelFile(path, test_label_file);

        std::cout << "================= Dataset =================" << std::endl;
        std::cout << "Dataset name: " << path << std::endl;
        std::cout << "Trained Data Size: " << trained_data.size() << std::endl;
        std::cout << "Testing Data Size: " << testing_data.size() << std::endl;
        std::cout << "Number of Classes: " << number_cluster << std::endl;
        std::cout << "K: " << k << std::endl;
        std::cout << "===========================================" << std::endl << std::endl;

        // ECDNN
        std::cout << "**************** Starting Algorithm... ****************" << std::endl;
        prediction = findCluster(trained_data, trained_label_data, testing_data, test_label_data, 
                            k, number_cluster);

        std::cout << std::endl << "**************** Calculating F1 Score... ****************" << std::endl;
        result = calculateF1Score (test_label_data, prediction, number_cluster);    
        writeResultFile (_path, k, result);

        std::cout << "Finished Program!" << std::endl << std::endl;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    std::cout << "Time passed is: " << 
          (end.tv_sec - start.tv_sec)*1000 + (end.tv_nsec - start.tv_nsec)/1000000 << "ms" << std::endl;
}