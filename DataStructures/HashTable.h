#pragma once

#include <iostream>
using namespace std;

struct HashNode {
    char key[50];
    void* value;
    HashNode* next;

    HashNode(const char* k, void* v) : value(v), next(NULL) {
        int i = 0;
        while (k[i] != '\0' && i < 49) {
            key[i] = k[i];
            i++;
        }
        key[i] = '\0';
    }
};

class HashTable {
private:
    HashNode** table;
    int tableSize;
    int currentSize;

    // Polynomial rolling hash
    int hashFunction(const char* key) {
        int hash = 0;
        int prime = 31;
        int i = 0;

        while (key[i] != '\0') {
            hash = (hash * prime + key[i]) % tableSize;
            i++;
        }

        return (hash < 0) ? -hash : hash;
    }

    bool stringCompare(const char* s1, const char* s2) {
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0') {
            if (s1[i] != s2[i]) return false;
            i++;
        }
        return s1[i] == s2[i];
    }

    void resize() {
        cout << "Resizing hash table..." << endl;
        int oldSize = tableSize;
        tableSize = tableSize * 2;

        HashNode** oldTable = table;
        table = new HashNode * [tableSize];

        for (int i = 0; i < tableSize; i++) {
            table[i] = NULL;
        }

        currentSize = 0;

        // Rehash all items
        for (int i = 0; i < oldSize; i++) {
            HashNode* current = oldTable[i];
            while (current != NULL) {
                insert(current->key, current->value);
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] oldTable;
    }

public:
    HashTable(int size = 100) : tableSize(size), currentSize(0) {
        table = new HashNode * [tableSize];
        for (int i = 0; i < tableSize; i++) {
            table[i] = NULL;
        }
    }

    void insert(const char* key, void* value) {
        // Check load factor
        if ((double)currentSize / tableSize > 0.75) {
            resize();
        }

        int index = hashFunction(key);

        // Check if key already exists
        HashNode* current = table[index];
        while (current != NULL) {
            if (stringCompare(current->key, key)) {
                current->value = value;  // Update existing
                return;
            }
            current = current->next;
        }

        // Insert new node at head of chain
        HashNode* newNode = new HashNode(key, value);
        newNode->next = table[index];
        table[index] = newNode;
        currentSize++;
    }

    HashNode** getTable()
    {
        return table;
    }

    int getTableSize()
    {
        return tableSize;
    }

    void* search(const char* key) {
        int index = hashFunction(key);
        HashNode* current = table[index];

        while (current != NULL) {
            if (stringCompare(current->key, key)) {
                return current->value;
            }
            current = current->next;
        }

        return NULL;
    }

    bool remove(const char* key) {
        int index = hashFunction(key);
        HashNode* current = table[index];
        HashNode* prev = NULL;

        while (current != NULL) {
            if (stringCompare(current->key, key)) {
                if (prev == NULL) {
                    table[index] = current->next;
                }
                else {
                    prev->next = current->next;
                }
                delete current;
                currentSize--;
                return true;
            }
            prev = current;
            current = current->next;
        }

        return false;
    }

    void display() {
        cout << "\n=== HASH TABLE CONTENTS ===" << endl;
        cout << "Size: " << currentSize << " / " << tableSize << endl;
        for (int i = 0; i < tableSize; i++) {
            if (table[i] != NULL) {
                cout << "Index " << i << ": ";
                HashNode* current = table[i];
                while (current != NULL) {
                    cout << current->key;
                    if (current->next != NULL) cout << " -> ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }

    ~HashTable() {
        for (int i = 0; i < tableSize; i++) {
            HashNode* current = table[i];
            while (current != NULL) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
};
