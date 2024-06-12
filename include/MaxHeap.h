#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include "Song.h"
using namespace std;

class MaxHeap
{
private:
    int size;
    // int capacity;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    vector<Song *> heap;
    MaxHeap() : size(0){};
    //~MaxHeap();

    // Methods
    void insert(Song *song);
    Song *extractMax();
    void heapify(int i);
    void printHeap();
    void percolateUp(int i, MaxHeap &heap);

    // GETTERS
    int getSize() { return size; }
    // int getCapacity() { return capacity; }
    vector<Song *> getHeap() { return heap; }
    int getParent(int i) { return parent(i); }
    int getLeft(int i) { return left(i); }
    int getRight(int i) { return right(i); }

    // SETTERS
    void decrementSize() { this->size = size - 1; }
    int removeHeapNullPtrs(int i);
};
