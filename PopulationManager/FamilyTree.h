#pragma once
#include <iostream>
#include "Citizen.h"

using namespace std;

class FamilyTreeNode
{
public:
    char cnic[20];              
    char name[100];             
    char relation[50];
    int age;
    char gender[10];

    // Relationships
    FamilyTreeNode* spouse;     // Pointer to spouse
    FamilyTreeNode** children;  // Array of pointers to children
    int numChildren;
    int childrenCapacity;

    FamilyTreeNode()
    {
        cnic[0] = '\0';
        name[0] = '\0';
        relation[0] = '\0';
        age = 0;
        gender[0] = '\0';
        spouse = NULL;
        children = NULL;
        numChildren = 0;
        childrenCapacity = 0;
    }

    FamilyTreeNode(const char* _cnic, const char* _name, const char* _relation,
        int _age, const char* _gender)
    {
        int i = 0;
        while (_cnic[i] != '\0' && i < 19) {
            cnic[i] = _cnic[i];
            i++;
        }
        cnic[i] = '\0';

        i = 0;
        while (_name[i] != '\0' && i < 99) {
            name[i] = _name[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (_relation[i] != '\0' && i < 49) {
            relation[i] = _relation[i];
            i++;
        }
        relation[i] = '\0';

        i = 0;
        while (_gender[i] != '\0' && i < 9) {
            gender[i] = _gender[i];
            i++;
        }
        gender[i] = '\0';

        age = _age;
        spouse = NULL;
        numChildren = 0;
        childrenCapacity = 10;
        children = new FamilyTreeNode * [childrenCapacity];
        for (int j = 0; j < childrenCapacity; j++) {
            children[j] = NULL;
        }
    }

    void addChild(FamilyTreeNode* child)
    {
        if (children == NULL) {
            childrenCapacity = 10;
            children = new FamilyTreeNode * [childrenCapacity];
            for (int i = 0; i < childrenCapacity; i++) {
                children[i] = NULL;
            }
        }

        if (numChildren < childrenCapacity) {
            children[numChildren] = child;
            numChildren++;
        }
        else {
            cout << "Cannot add more children (capacity reached)" << endl;
        }
    }

    void setSpouse(FamilyTreeNode* spouseNode)
    {
        spouse = spouseNode;
        spouseNode->spouse = this;
    }

    void display(int indent = 0)
    {
        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "?? " << name << " (" << relation << ", " << age << " years, "
            << gender << ")" << endl;

        if (spouse != NULL && indent == 0) {
            for (int i = 0; i < indent + 1; i++) {
                cout << "  ";
            }
            cout << "?? Spouse: " << spouse->name << " (" << spouse->age << " years)" << endl;
        }

        for (int i = 0; i < numChildren; i++) {
            if (children[i] != NULL) {
                children[i]->display(indent + 1);
            }
        }
    }

    ~FamilyTreeNode()
    {
        if (children != NULL) {
            for (int i = 0; i < numChildren; i++) {
                delete children[i];
            }
            delete[] children;
        }
    }
};

class FamilyTree
{
public:
    FamilyTreeNode* root;       // Head of household
    char familyId[20];
    int totalMembers;

    FamilyTree()
    {
        root = NULL;
        familyId[0] = '\0';
        totalMembers = 0;
    }

    FamilyTree(const char* famId, FamilyTreeNode* headOfHousehold)
    {
        int i = 0;
        while (famId[i] != '\0' && i < 19) {
            familyId[i] = famId[i];
            i++;
        }
        familyId[i] = '\0';

        root = headOfHousehold;
        totalMembers = 1;
    }

    void setHead(FamilyTreeNode* head)
    {
        root = head;
        totalMembers = 1;
    }

    void addSpouse(FamilyTreeNode* spouse)
    {
        if (root != NULL) {
            root->setSpouse(spouse);
            totalMembers++;
        }
    }

    void addChild(FamilyTreeNode* child)
    {
        if (root != NULL) {
            root->addChild(child);
            totalMembers++;
        }
    }

    FamilyTreeNode* findMember(const char* cnic, FamilyTreeNode* node = NULL)
    {
        if (node == NULL) {
            node = root;
        }

        if (node == NULL) {
            return NULL;
        }

        // Check if this node matches
        bool match = true;
        int i = 0;
        while (node->cnic[i] != '\0' && cnic[i] != '\0') {
            if (node->cnic[i] != cnic[i]) {
                match = false;
                break;
            }
            i++;
        }
        if (match && node->cnic[i] == cnic[i]) {
            return node;
        }

        // Check spouse
        if (node->spouse != NULL) {
            match = true;
            i = 0;
            while (node->spouse->cnic[i] != '\0' && cnic[i] != '\0') {
                if (node->spouse->cnic[i] != cnic[i]) {
                    match = false;
                    break;
                }
                i++;
            }
            if (match && node->spouse->cnic[i] == cnic[i]) {
                return node->spouse;
            }
        }

        // Search children
        for (int j = 0; j < node->numChildren; j++) {
            if (node->children[j] != NULL) {
                FamilyTreeNode* found = findMember(cnic, node->children[j]);
                if (found != NULL) {
                    return found;
                }
            }
        }

        return NULL;
    }

    void displayTree()
    {
        cout << endl;
        cout << "   FAMILY TREE..... " << familyId << endl;
        cout << endl;
        cout << "Total Members: " << totalMembers << endl;
        cout << "\nFamily Structure:" << endl;

        if (root != NULL) {
            root->display();
        }
        else {
            cout << "No family members registered" << endl;
        }

        cout << endl;
    }

    void listAllMembers(FamilyTreeNode* node = NULL, int indent = 0)
    {
        if (node == NULL) {
            node = root;
            cout << "\nAll Family Members:" << endl;
        }

        if (node == NULL) return;

        for (int i = 0; i < indent; i++) {
            cout << "  ";
        }
        cout << "- " << node->name << " (CNIC: " << node->cnic << ", "
            << node->relation << ")" << endl;

        if (node->spouse != NULL && indent == 0) {
            for (int i = 0; i < indent + 1; i++) {
                cout << "  ";
            }
            cout << "- " << node->spouse->name << " (CNIC: " << node->spouse->cnic
                << ", Spouse)" << endl;
        }

        for (int i = 0; i < node->numChildren; i++) {
            if (node->children[i] != NULL) {
                listAllMembers(node->children[i], indent + 1);
            }
        }
    }

    ~FamilyTree()
    {
        if (root != NULL) {
            delete root;
        }
    }
};