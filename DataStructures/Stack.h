#pragma once
#include <iostream>

using namespace std;

class StackNode
{
public:
    void* data;
    StackNode* next;

    StackNode(void* val)
    {
        data = val;
        next = NULL;
    }
};

class Stack
{
private:
    StackNode* top;
    int size;

public:
    Stack()
    {
        top = NULL;
        size = 0;
    }

    void push(void* data)
    {
        StackNode* newNode = new StackNode(data);
        newNode->next = top;
        top = newNode;
        size++;
    }

    void* pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return NULL;
        }

        StackNode* temp = top;
        void* data = temp->data;
        top = top->next;
        delete temp;
        size--;

        return data;
    }

    void* peek()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return NULL;
        }

        return top->data;
    }

    bool isEmpty()
    {
        return top == NULL;
    }

    int getSize()
    {
        return size;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return;
        }

        cout << "\n=== Stack Contents (Top to Bottom) ===" << endl;
        StackNode* current = top;
        int index = 1;

        while (current != NULL)
        {
            cout << index << ". [Data at " << current->data << "]" << endl;
            current = current->next;
            index++;
        }
        cout << "Total items: " << size << endl;
    }

    void clear()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    ~Stack()
    {
        clear();
    }
};