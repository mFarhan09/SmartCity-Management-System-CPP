#pragma once

#include <iostream>
using namespace std;

struct ListNode {
    void* data;
    ListNode* next;

    ListNode(void* d) : data(d), next(NULL) {}
};

class LinkedList {
private:
    ListNode* head;
    ListNode* tail;
    int size;

public:
    LinkedList() : head(NULL), tail(NULL), size(0) {}

    void insertAtEnd(void* data) {
        ListNode* newNode = new ListNode(data);

        if (head == NULL) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insertAtBeginning(void* data) {
        ListNode* newNode = new ListNode(data);

        if (head == NULL) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void* getAt(int index) {
        if (index < 0 || index >= size) return NULL;

        ListNode* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    int getSize() {
        return size;
    }

    ListNode* getHead() {
        return head;
    }

    void display(void (*printFunc)(void*)) {
        ListNode* current = head;
        int index = 0;
        while (current != NULL) {
            cout << index++ << ". ";
            printFunc(current->data);
            current = current->next;
        }
    }

    ~LinkedList() {
        ListNode* current = head;
        while (current != NULL) {
            ListNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};
