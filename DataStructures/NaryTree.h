#pragma once

#include <iostream>
using namespace std;

struct TreeNode
{
    char id[20];
    char name[100];
    void* data;
    TreeNode** children;
    int numChildren;
    int capacity;

    TreeNode(const char* i, const char* n, void* d, int cap = 10)
        : data(d), numChildren(0), capacity(cap)
    {
        int idx = 0;
        while (i[idx] != '\0' && idx < 19)
        {
            id[idx] = i[idx];
            idx++;
        }
        id[idx] = '\0';

        idx = 0;
        while (n[idx] != '\0' && idx < 99)
        {
            name[idx] = n[idx];
            idx++;
        }
        name[idx] = '\0';

        children = new TreeNode * [capacity];
        for (int i = 0; i < capacity; i++)
        {
            children[i] = NULL;
        }
    }

    void addChild(TreeNode* child)
    {
        if (numChildren < capacity)
        {
            children[numChildren++] = child;
        }
    }

    TreeNode* findChild(const char* childId)
    {
        for (int i = 0; i < numChildren; i++)
        {
            int j = 0;
            bool match = true;
            while (children[i]->id[j] != '\0' || childId[j] != '\0')
            {
                if (children[i]->id[j] != childId[j])
                {
                    match = false;
                    break;
                }
                j++;
            }
            if (match) return children[i];
        }
        return NULL;
    }
};

class NaryTree
{
private:
    TreeNode* root;

    void destroyTree(TreeNode* node)
    {
        if (node == NULL) return;

        for (int i = 0; i < node->numChildren; i++)
        {
            destroyTree(node->children[i]);
        }

        delete[] node->children;
        delete node;
    }

    void displayTree(TreeNode* node, int level)
    {
        if (node == NULL) return;

        for (int i = 0; i < level; i++)
        {
            cout << "  ";
        }
        cout << "- " << node->name << " (" << node->id << ")" << endl;

        for (int i = 0; i < node->numChildren; i++)
        {
            displayTree(node->children[i], level + 1);
        }
    }

public:
    NaryTree() : root(NULL) {}

    void setRoot(TreeNode* node)
    {
        root = node;
    }

    TreeNode* getRoot()
    {
        return root;
    }

    TreeNode* search(const char* id)
    {
        return searchHelper(root, id);
    }

    TreeNode* searchHelper(TreeNode* node, const char* id)
    {
        if (node == NULL) return NULL;

        int i = 0;
        bool match = true;
        while (node->id[i] != '\0' || id[i] != '\0')
        {
            if (node->id[i] != id[i])
            {
                match = false;
                break;
            }
            i++;
        }

        if (match) return node;

        for (int i = 0; i < node->numChildren; i++)
        {
            TreeNode* result = searchHelper(node->children[i], id);
            if (result != NULL) return result;
        }

        return NULL;
    }

    void display()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        displayTree(root, 0);
    }

    ~NaryTree()
    {
        destroyTree(root);
    }
};
