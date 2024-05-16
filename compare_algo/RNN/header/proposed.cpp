/**
 * @author Ansel Lyu
 * @date   2023/11/04
*/

#include "proposed.h"
#include <cstring>

#define MAX_FLOAT 100000.0

std::vector<std::vector<float>> trained_data;
std::vector<int> trained_label_data;
std::vector<std::vector<float>> test_data;
std::vector<int> test_label_data;
int number_cluster;
float radius;


float calculateDistance (std::vector<float> testing, std::vector<float> trained)
{
    float distance = 0;
    for (int dimension_th = 0; dimension_th < trained.size(); dimension_th++)
    {
        distance += pow((testing[dimension_th] - trained[dimension_th]), 2);
    }
    distance = sqrt(distance);
    return distance;
}


int assignCluster (std::vector<int> RNN, int test_idx)
{
    // RNN
    int predict_label = 0;

    std::vector<int> class_counter(number_cluster, 0);

    for (int idx = 0; idx < RNN.size(); idx++)
    {
        class_counter[trained_label_data[RNN[idx]]]++;
    }
    
    for (int idx = 0; idx < number_cluster; idx++)
    {
        std::cout << "Label " << idx << ": " << class_counter[idx] << std::endl;

        if (class_counter[idx] > class_counter[predict_label])
        {
            predict_label = idx;
        }
    }

    return predict_label;
}

std::vector<int> findRNN (std::vector<float> testing)
{
    float distance;
    int dim_idx, idx;
    std::vector<int> RNN;

    for (int trained_idx = 0; trained_idx < trained_data.size(); trained_idx++)
    {
        distance = calculateDistance(testing, trained_data[trained_idx]);
        // std::cout << distance << std::endl;
        if (distance <= radius)
        {
            RNN.push_back(trained_idx);
        }
    }
    return RNN;
}


std::vector<int> findCluster(std::vector<std::vector<float>> trained_data_,  
                                    std::vector<int> trained_label_data_,
                                    std::vector<std::vector<float>> test_data_,
                                    std::vector<int> test_label_data_,
                                    float radius_, int number_cluster_)
{
    // declare global variable
    trained_data        = trained_data_;
    trained_label_data  = trained_label_data_;
    test_data           = test_data_;
    test_label_data     = test_label_data_;
    radius = radius_;
    number_cluster = number_cluster_;

    std::vector<int> prediction;

    for (int run_time = 0; run_time < 1; run_time++)
    {
        for (int test_idx = 0; test_idx < test_data.size(); test_idx++)
        {
            std::cout << "Testing " << test_idx+1 << ": " << std::endl;
            std::vector<int> RNN_vector = findRNN (test_data[test_idx]);
            prediction.push_back(assignCluster(RNN_vector, test_idx));
            std::cout << "Predict Label : " << prediction.back() << std::endl;
            std::cout << "Expected Label : " << test_label_data[test_idx] << std::endl << std::endl;
            RNN_vector.clear();
        }
    }
    return prediction;
}