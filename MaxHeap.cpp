#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
#include "./include/MaxHeap.h"

void MaxHeap::insert(Song *song)
{
    // Make sure there is still space in the heap
    // if (size == capacity)
    // {
    //     capacity *= 2;
    //     heap.resize(capacity);
    // }

    // Increse the amount of elements in the heap
    // size++;

    // Insert the new key at the end

    heap.push_back(song);

    int i = heap.size() - 1;

    // Fix the max heap property
    // Moves the element up until i >= parent or root
    while (i != 0 && heap[parent(i)]->getListenTime() < heap[i]->getListenTime())
    {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

int MaxHeap::removeHeapNullPtrs(int i)
{
    // swap
    Song *tmpPtr = heap[heap.size() - 1];
    heap[heap.size() - 1] = heap[i];
    heap[i] = tmpPtr;

    heap.pop_back();

    return heap.size();
}

void MaxHeap::heapify(int i)
{
    while (i >= 0)
    {
        // Set initial conditions
        int l = left(i);
        int r = right(i);
        int largest = i;

        // Find the largest element of the three
        if (l < heap.size())
        {
            if (heap[l] != NULL && (l < heap.size()) && (heap[l]->getListenTime() > heap[largest]->getListenTime()))
            {
                largest = l;
            }
        }

        if (r < heap.size())
        {
            if (heap[r] != NULL && (r < heap.size()) && (heap[r]->getListenTime() > heap[largest]->getListenTime()))
            {
                largest = r;
            }
        }

        // If the largest of l or r, continue heapify
        if (largest != i)
        {
            // swap indices first
            int tmp = heap[i]->getOriginalIndexFromHeap();
            heap[i]->setOriginalHeapIndex(largest);
            heap[largest]->setOriginalHeapIndex(tmp);

            swap(heap[i], heap[largest]);
            heapify(largest);
        }

        i--;
    }
}

Song *MaxHeap::extractMax()
{
    // Check if the heap is empty
    if (heap.size() == 0)
    {
        cout << "EMPTY HEAP" << endl;
        return NULL;
    }
    else if (heap.size() == 1)
    {
        Song *tmp = heap[0];
        heap[0] = nullptr;
        heap.pop_back();

        return tmp;
    }
    else
    {
        // Store the max at root
        Song *root = heap[0];

        // Send to back and delete it
        heap[0] = heap[heap.size() - 1];
        heap.pop_back();

        heapify(0);

        // Return min element
        return root;
    }
}

void MaxHeap::percolateUp(int i, MaxHeap &heap)
{
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (heap.heap[i]->getListenTime() <= heap.heap[parent]->getListenTime())
        {
            return;
        }
        else
        {
            // Swap indicies to update original index
            int tmp = heap.heap[i]->getOriginalIndexFromHeap();
            heap.heap[i]->setOriginalHeapIndex(parent);
            heap.heap[parent]->setOriginalHeapIndex(tmp);

            swap(heap.heap[i], heap.heap[parent]);

            i = parent;
        }
    }
}

void MaxHeap::printHeap()
{
    if (heap.size() == 0)
    {
        cout << "EMPTY HEAP" << endl;
        return;
    }

    int power = 0;
    int value = 1;
    for (int i = 0; i < heap.size(); i++)
    {
        if (i == value)
        {
            cout << endl;
            power += 1;
            value += (1 << power);
        }
        cout << heap[i]->getTitle() << "(" << heap[i]->getListenTime() << ") ";
    }
    cout << endl;
}

// void MaxHeap::printHeap()
// {
//     if (size == 0)
//     {
//         cout << "EMPTY HEAP" << endl;
//         return;
//     }

//     for (int i = 0; i < size; i++)
//     {
//         cout << "P: " << heap[i]-> << " LC: " << heap[(2 * i) + 1]->getListenTime << "RC: " << heap[(2 * i) + 2]->getListenTime << endl;
//     }
//     cout << endl;
// }
