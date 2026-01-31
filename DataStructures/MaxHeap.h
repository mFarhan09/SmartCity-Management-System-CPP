#pragma once
#include <iostream>
using namespace std;

struct HeapNode
{
    double priority;
    void* data;

    HeapNode() : priority(0), data(NULL) {}
    HeapNode(double p, void* d) : priority(p), data(d) {}
};

class MaxHeap
{
private:
    HeapNode* heap;
    int size;
    int capacity;

    void swap(int i, int j)
    {
        HeapNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index)
    {
        if (index == 0) return;

        int parent = (index - 1) / 2;
        if (heap[index].priority > heap[parent].priority)
        {
            swap(index, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left].priority > heap[largest].priority)
        {
            largest = left;
        }
        if (right < size && heap[right].priority > heap[largest].priority)
        {
            largest = right;
        }

        if (largest != index)
        {
            swap(index, largest);
            heapifyDown(largest);
        }
    }

public:
    MaxHeap(int cap = 100) : size(0), capacity(cap)
    {
        heap = new HeapNode[capacity];
    }

    void insert(double priority, void* data)
    {
        if (size >= capacity)
        {
            cout << "Heap is full!" << endl;
            return;
        }

        heap[size] = HeapNode(priority, data);
        heapifyUp(size);
        size++;
    }

    HeapNode extractMax()
    {
        if (size == 0)
        {
            return HeapNode(-1, NULL);
        }

        HeapNode max = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return max;
    }

    HeapNode peek()
    {
        if (size == 0)
        {
            return HeapNode(-1, NULL);
        }
        return heap[0];
    }

    bool isEmpty()
    {
        return size == 0;
    }

    int getSize()
    {
        return size;
    }

    ~MaxHeap()
    {
        delete[] heap;
    }
};
