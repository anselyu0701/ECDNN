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
int k, number_cluster;


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

int assignCluster (KnnHeap* kh, int test_idx)
{
    // KNN
    int predict_label = 0;
    
    std::vector<int> class_counter(number_cluster, 0);

    for (int idx = 1; idx <= k; idx++)
    {
        class_counter[trained_label_data[kh->heap[idx]->id]]++;
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

KnnHeap* findEachInstanceKnn (std::vector<float> testing)
{
    KnnHeap* kh = new KnnHeap(k);
    float distance;
    int dim_idx, idx;
    for (int trained_idx = 0; trained_idx < trained_data.size(); trained_idx++)
    {
        distance = calculateDistance(testing, trained_data[trained_idx]);
        // std::cout << distance << std::endl;
        kh->push(trained_idx, distance);
    }
    kh->printAll(trained_label_data);
    return kh;
}


std::vector<int> findCluster(std::vector<std::vector<float>> trained_data_,  
                                    std::vector<int> trained_label_data_,
                                    std::vector<std::vector<float>> test_data_,
                                    std::vector<int> test_label_data_,
                                    int k_, int number_cluster_)
{
    // declare global variable
    trained_data        = trained_data_;
    trained_label_data  = trained_label_data_;
    test_data           = test_data_;
    test_label_data     = test_label_data_;
    k = k_;
    number_cluster = number_cluster_;

    std::vector<int> prediction;

    for (int run_time = 0; run_time < 1; run_time++)
    {
        for (int test_idx = 0; test_idx < test_data.size(); test_idx++)
        {
            std::cout << "Testing " << test_idx+1 << ": " << std::endl;
            KnnHeap* kh = findEachInstanceKnn (test_data[test_idx]);
            prediction.push_back(assignCluster(kh, test_idx));
            std::cout << "Predict Label : " << prediction.back() << std::endl;
            std::cout << "Expected Label : " << test_label_data[test_idx] << std::endl << std::endl;
            delete (kh);
        }
    }
    return prediction;
}