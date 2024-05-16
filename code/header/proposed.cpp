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

int isHighConfidence (KnnHeap* kh)
{
    int high_confidence = 1; // assume all knn are the same label
    for (int idx = 1; idx < k; idx++)
    {
        if (trained_label_data[kh->heap[idx]->id] != trained_label_data[kh->heap[idx+1]->id])
        {
            high_confidence = 0;
            return high_confidence;
        }
    }
    return high_confidence;
}

int CDNN (KnnHeap* kh, int test_idx)
{
    // calculate the centroid of each cluster
    std::vector<std::vector<float>> sum_cluster(number_cluster, std::vector<float>(trained_data[0].size(), 0));
    std::vector<int> num_cluster_instance(number_cluster, 0);
    std::vector<float> orig_centroid(trained_data[0].size());
    std::vector<float> after_centroid(trained_data[0].size());
    float displacement;
    float min_displacement = MAX_FLOAT;
    int predict_label;

    for (int idx = 1; idx <= k; idx++)
    {
        for (int dimension_th = 0; dimension_th < trained_data[0].size(); dimension_th++)
        {
            sum_cluster[trained_label_data[kh->heap[idx]->id]][dimension_th] += 
                trained_data[kh->heap[idx]->id][dimension_th];
        }
        num_cluster_instance[trained_label_data[kh->heap[idx]->id]]++;
    }

    for (int cluster_idx = 0; cluster_idx < number_cluster; cluster_idx++)
    {
        if (num_cluster_instance[cluster_idx] != 0)
        {
            std::cout << "**************" << std::endl << "Class " << cluster_idx << " Original centroid: ";
            for (int dimension_th = 0; dimension_th < trained_data[0].size(); dimension_th++)
            {
                orig_centroid[dimension_th] = sum_cluster[cluster_idx][dimension_th] / num_cluster_instance[cluster_idx];
                after_centroid[dimension_th] = (sum_cluster[cluster_idx][dimension_th]+test_data[test_idx][dimension_th]) 
                    / (num_cluster_instance[cluster_idx]+1);
            }

            // print original centroid
            for (int dimension_th = 0; dimension_th < trained_data[0].size(); dimension_th++)
            {
                std::cout << orig_centroid[dimension_th] << " ";
            }
            std::cout << std::endl << "After centroid: ";

            // print after centroid
            for (int dimension_th = 0; dimension_th < trained_data[0].size(); dimension_th++)
            {
                std::cout << after_centroid[dimension_th] << " ";
            }
            std::cout << std::endl;

            // calculate displacement
            displacement = calculateDistance(orig_centroid, after_centroid);
            std::cout << "Displacement: " << displacement << std::endl;
            if (displacement < min_displacement)
            {
                min_displacement = displacement;
                predict_label = cluster_idx;
            }
        }
    }
    return predict_label;
}

int assignCluster (KnnHeap* kh, int test_idx)
{
    int predict_label;

    if (isHighConfidence(kh)) // knn
    {
        std::cout << "Using KNN" << std::endl;
        predict_label = trained_label_data[kh->heap[1]->id];
    }
    else // CDNN
    {
        std::cout << "Using CDNN" << std::endl;
        predict_label = CDNN (kh, test_idx);
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