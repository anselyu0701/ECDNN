#include "knn_heap.h"

Node::Node (int id, float distance)
{
    this->id = id;
    this->distance = distance;
}
        
KnnHeap::KnnHeap (int k)
{
    Node* new_node = new Node(-1, -1.0); // heap[0]
    this->heap.push_back(new_node);
    this->k = k;
}

void KnnHeap::exchangeValue(int a, int b)
{
    int temp_id; 
    float temp_distance;
    temp_id = heap[a]->id;
    temp_distance = heap[a]->distance;
    heap[a]->id = heap[b]->id;
    heap[a]->distance = heap[b]->distance;
    heap[b]->id = temp_id;
    heap[b]->distance = temp_distance;
    // std::cout << "Exchange: " << heap[a]->id << " " << heap[a]->distance << ", " << heap[b]->id << " " << heap[b]->distance << std::endl;
}

void KnnHeap::maxHeapify (int idx)
{
    int largest = idx;
    int left = 2 * idx;
    int right = 2 * idx + 1;

    if ((left <= k) && (heap[left]->distance > heap[largest]->distance))
    {
        largest = left;
    }
    if ((right <= k) && (heap[right]->distance > heap[largest]->distance))
    {
        largest = right;
    }
    if (largest != idx)
    {
        exchangeValue(largest, idx);
        maxHeapify (largest);
    }
}

void KnnHeap::buildMaxHeap ()
{
    for (int idx = (k/2); idx >= 1; idx--)
    {
        maxHeapify(idx);
    }
}

void KnnHeap::push (int id, float distance)
{
    // std::cout << "Heap Size:" << heap.size() << std::endl;
    if (heap.size() <= k) // we need to create a node and adding
    {
        Node *new_node = new Node(id, distance);
        heap.push_back(new_node);
        if (heap.size() == k+1)
        {
            buildMaxHeap();
        }
    }
    else // heap is full
    {
        // std::cout << "Fall: " << distance << " " << heap[1]->distance << std::endl;
        if (distance < heap[1]->distance)
        {
            // std::cout << "Switch:" << id << std::endl;
            heap[1]->id = id;
            heap[1]->distance = distance;
            maxHeapify(1);
        }
    }          
}

void KnnHeap::printDetail(std::vector<std::vector<float>> test_data)
{
    for (int idx = 1; idx <= k; idx++)
    {
        for (int dim = 0; dim < test_data[0].size(); dim++)
        {
            std::cout << test_data[heap[idx]->id][dim] << " ";
        }        
        std::cout << std::endl;
    }
}

void KnnHeap::printAll (std::vector<int> trained_label)
{
    std::cout << "Knn Node ID : ";
    for (int idx = 1; idx <= k; idx++)
    {
        std::cout << heap[idx]->id << " ";
    }
    std::cout << std::endl << "Knn Node Label : ";
    for (int idx = 1; idx <= k; idx++)
    {
        std::cout << trained_label[heap[idx]->id] << " ";
    }
    std::cout << std::endl;
}