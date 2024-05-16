#ifndef __KNN_H__
#define __KNN_H__

#include <math.h>
#include <time.h>
#include <iostream>
#include <random>
#include "file_operation.h"

/**
 * @brief A function that can predict cluster of the test data set by random Knn
 * @param trained_data An 2-D float array which stored trained data
 * @param trained_sample_size Size of the trained data
 * @param test_data An 2-D float array which stored testing data
 * @param test_sample_size Size of the testing data
 * @param dimension How many features are in data
 * @param k K of the Knn classification
 * @param number_cluster How many clusters are in data
*/
std::vector<int> findCluster(std::vector<std::vector<float>> trained_data_, 
                                    std::vector<int> trained_label_data_, 
                                    std::vector<std::vector<float>> testing_data_,
                                    std::vector<int> test_label_data_, 
                                    float radius_, int number_cluster_);


#endif