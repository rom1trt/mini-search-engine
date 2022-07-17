#include "MaxHeap.h"

using namespace std;

MaxHeap::MaxHeap(int k) {
    maxNumScores = k;
    curNumScores = 0;
    heap = (double*) malloc(maxNumScores*sizeof(double));
    ids = (int*) malloc(maxNumScores*sizeof(int));
}

int MaxHeap::minIndex(int low, int high) {
    int min = -1;
    double minScore = 1000000.0;
    for (int i=low;i<high;i++) {
        if (heap[i] < minScore) {
            min = i;
            minScore = heap[i];
        }
    }
    return min;
}

void MaxHeap::swapScores(int index1, int index2) {
    double temp = 0.0;
    temp = heap[index1];
    int tempId = ids[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
    ids[index1] = ids[index2];
    ids[index2] = tempId;
}

void MaxHeap::insert(double score, int id) {
    int index;
    if (curNumScores != maxNumScores) {
        index = curNumScores;
        curNumScores++;
    }
    else {
        int tempIndex = minIndex(maxNumScores/2, maxNumScores);
        if (score > heap[tempIndex])
            index = tempIndex;
        else
            return;
    }
    heap[index] = score;
    ids[index] = id;

    while (heap[index] > heap[(index-1)/2]) {
        swapScores(index, (index-1)/2);
        index = (index - 1 ) / 2;
    }
}

int MaxHeap::MaxChild(int num1, int num2) {
    if (num1 < curNumScores && num2 < curNumScores) {
        if (heap[num1] > heap[num2])
            return num1;
        else
            return num2;
    }
    else if (num1 < curNumScores)
        return num1;
    else if (num2 < curNumScores)
        return num2;
    return -1;
}

double MaxHeap::remove() {
    int index = 0;
    int chosenChild;
    double returnValue = 0.0;
    if (curNumScores > 0) {
        returnValue = heap[0];
        curNumScores--;
        heap[0] = heap[curNumScores];
        ids[0] = ids[curNumScores];
        while (1) {
            chosenChild = MaxChild(2*index+1, 2*index+2);
            if (chosenChild != -1 && heap[chosenChild] > heap[index]) {
                swapScores(chosenChild, index);
                index = chosenChild;
            }
            else
                break;
        }
    }
    return returnValue;
}