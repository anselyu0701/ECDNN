#ifndef __KNN_HEAP_H__
#define __KNN_HEAP_H__

#include <vector>
#include <iostream>

class Node
{
    public:
        int id;
        float distance;

        Node (int id, float distance);
};

class KnnHeap
{    
    private:
        int k;

        void maxHeapify (int idx);

        void buildMaxHeap ();

        void exchangeValue(int a, int b);

    public:
        std::vector<Node*>   heap;

        KnnHeap (int k);

        void push (int id, float distance);
        
        void printDetail(std::vector<std::vector<float>> test_data);

        void printAll (std::vector<int> trained_label);

};

#endif