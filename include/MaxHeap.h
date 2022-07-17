#include <iostream>
#include <cstring>
#include <cstdlib>

#ifndef MAXHEAP_H
#define MAXHEAP_H
class MaxHeap {
    private:
        int* ids;
        double* heap;
        int curNumScores;
        int maxNumScores;
        void swapScores(int index1, int index2);
        int minIndex(int low, int high);
    public:
        MaxHeap(int k);
        ~MaxHeap() {
            free(heap);
            free(ids);
        };
        void insert(double score, int id);
        int MaxChild(int num1, int num2);
        double remove();
        int getId() {
            return ids[0];
        };
};
#endif