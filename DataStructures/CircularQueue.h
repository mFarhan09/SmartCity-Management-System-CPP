#pragma once
#include <iostream>
using namespace std;

class CircularQueue {
private:
    void** items;
    int front;
    int rear;
    int capacity;
    int currentSize;

public:
    CircularQueue(int cap = 20) : capacity(cap), front(-1), rear(-1), currentSize(0) {
        items = new void* [capacity];
        for (int i = 0; i < capacity; i++) {
            items[i] = NULL;
        }
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    bool isFull() {
        return currentSize == capacity;
    }

    int getSize() {
        return currentSize;
    }

    int getCapacity() {
        return capacity;
    }

    bool enqueue(void* data) {
        if (isFull()) {
            cout << "Queue is full! Cannot add more items." << endl;
            return false;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        }
        else {
            // Circular wrap-around: after last index, go back to 0
            rear = (rear + 1) % capacity;
        }

        items[rear] = data;
        currentSize++;
        return true;
    }

    void* dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty! Nothing to dequeue." << endl;
            return NULL;
        }

        void* data = items[front];
        items[front] = NULL;

        if (front == rear) {
            // Queue becomes empty after this dequeue
            front = -1;
            rear = -1;
        }
        else {
            // Circular wrap-around
            front = (front + 1) % capacity;
        }

        currentSize--;
        return data;
    }

    void* peek() {
        if (isEmpty()) {
            return NULL;
        }
        return items[front];
    }

    // Get item at specific position (0 = front)
    void* getAt(int index) {
        if (index < 0 || index >= currentSize) {
            return NULL;
        }
        int actualIndex = (front + index) % capacity;
        return items[actualIndex];
    }

    // Display using a custom print function
    void display(void (*printFunc)(void*)) {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        cout << "\n=== CIRCULAR QUEUE ===" << endl;
        cout << "Size: " << currentSize << "/" << capacity << endl;
        cout << "----------------------" << endl;

        int index = front;
        int count = 0;
        while (count < currentSize) {
            cout << (count + 1) << ". ";
            printFunc(items[index]);
            index = (index + 1) % capacity;
            count++;
        }
    }

    ~CircularQueue() {
        delete[] items;
    }
};