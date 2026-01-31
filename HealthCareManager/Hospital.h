#pragma once
#include <iostream>
#include <cstring>
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/NaryTree.h"
#include "../DataStructures/MaxHeap.h"
#include "Bed.h"
using namespace std;

struct Ward
{
    char wardId[20];
    char wardName[100];
    char wardType[50];
    int totalBeds;
    int availableBeds;
    LinkedList* beds;

    Ward() : totalBeds(0), availableBeds(0), beds(NULL)
    {
        wardId[0] = '\0';
        wardName[0] = '\0';
        wardType[0] = '\0';
    }

    Ward(const char* id, const char* name, const char* type, int total)
        : totalBeds(total), availableBeds(total)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19) { wardId[i] = id[i]; i++; }
        wardId[i] = '\0';

        i = 0;
        while (name[i] != '\0' && i < 99) { wardName[i] = name[i]; i++; }
        wardName[i] = '\0';

        i = 0;
        while (type[i] != '\0' && i < 49) { wardType[i] = type[i]; i++; }
        wardType[i] = '\0';

        beds = new LinkedList();
    }
};

struct Block
{
    char blockId[20];
    char blockName[100];
    char blockType[50];
    int totalBeds;
    int availableBeds;
    int floorNumber;

    Block() : totalBeds(0), availableBeds(0), floorNumber(0)
    {
        blockId[0] = '\0';
        blockName[0] = '\0';
        blockType[0] = '\0';
    }

    Block(const char* id, const char* name, const char* type, int floor)
        : totalBeds(0), availableBeds(0), floorNumber(floor)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19) { blockId[i] = id[i]; i++; }
        blockId[i] = '\0';

        i = 0;
        while (name[i] != '\0' && i < 99) { blockName[i] = name[i]; i++; }
        blockName[i] = '\0';

        i = 0;
        while (type[i] != '\0' && i < 49) { blockType[i] = type[i]; i++; }
        blockType[i] = '\0';
    }
};

struct Hospital
{
    char hospitalId[20];
    char name[100];
    char sector[20];
    int totalBeds;
    int availableBeds;
    char** specializations;
    int numSpecializations;
    NaryTree* hierarchy;
    MaxHeap* emergencyQueue;
    double latitude;
    double longitude;
    char contactNumber[20];

    Hospital() : totalBeds(0), availableBeds(0), specializations(NULL),
        numSpecializations(0), hierarchy(NULL), emergencyQueue(NULL),
        latitude(0.0), longitude(0.0)
    {
        hospitalId[0] = '\0';
        name[0] = '\0';
        sector[0] = '\0';
        contactNumber[0] = '\0';
    }

    Hospital(const char* id, const char* n, const char* sec,
        int beds, double lat, double lon, const char* specList)
        : totalBeds(beds), availableBeds(beds), numSpecializations(0),
        latitude(lat), longitude(lon)
    {
        // Copy hospital ID
        int i = 0;
        while (id[i] != '\0' && i < 19) { hospitalId[i] = id[i]; i++; }
        hospitalId[i] = '\0';

        // Copy name
        i = 0;
        while (n[i] != '\0' && i < 99) { name[i] = n[i]; i++; }
        name[i] = '\0';

        // Copy sector
        i = 0;
        while (sec[i] != '\0' && i < 19) { sector[i] = sec[i]; i++; }
        sector[i] = '\0';

        contactNumber[0] = '\0';

        // Initialize specializations array
        specializations = new char* [20];

        // Parse specialization list
        if (specList != NULL && specList[0] != '\0')
        {
            char specCopy[256];
            i = 0;
            while (specList[i] != '\0' && i < 255) { specCopy[i] = specList[i]; i++; }
            specCopy[i] = '\0';

            int start = 0;
            int pos = 0;

            while (specCopy[pos] != '\0' && numSpecializations < 20)
            {
                if (specCopy[pos] == ',')
                {
                    while (specCopy[start] == ' ') start++;

                    int end = pos - 1;
                    while (end > start && specCopy[end] == ' ') end--;

                    int len = end - start + 1;
                    if (len > 0)
                    {
                        specializations[numSpecializations] = new char[len + 1];
                        for (int j = 0; j < len; j++)
                            specializations[numSpecializations][j] = specCopy[start + j];
                        specializations[numSpecializations][len] = '\0';
                        numSpecializations++;
                    }
                    start = pos + 1;
                }
                pos++;
            }

            // Last specialization after final comma
            while (specCopy[start] == ' ') start++;
            int end = pos - 1;
            while (end > start && specCopy[end] == ' ') end--;

            int len = end - start + 1;
            if (len > 0 && numSpecializations < 20)
            {
                specializations[numSpecializations] = new char[len + 1];
                for (int j = 0; j < len; j++)
                    specializations[numSpecializations][j] = specCopy[start + j];
                specializations[numSpecializations][len] = '\0';
                numSpecializations++;
            }
        }

        hierarchy = new NaryTree();
        emergencyQueue = new MaxHeap(100);
    }

    ~Hospital()
    {
        for (int i = 0; i < numSpecializations; i++)
            delete[] specializations[i];
        delete[] specializations;
        delete hierarchy;
        delete emergencyQueue;
    }

    void addSpecialization(const char* spec)
    {
        if (numSpecializations < 20)
        {
            specializations[numSpecializations] = new char[50];
            int i = 0;
            while (spec[i] != '\0' && i < 49)
            {
                specializations[numSpecializations][i] = spec[i];
                i++;
            }
            specializations[numSpecializations][i] = '\0';
            numSpecializations++;
        }
    }

    void display()
    {
        cout << "\n.....HOSPITAL DETAILS....." << endl;
        cout << "ID: " << hospitalId << endl;
        cout << "Name: " << name << endl;
        cout << "Sector: " << sector << endl;
        cout << "Total Beds: " << totalBeds << endl;
        cout << "Available Beds: " << availableBeds << endl;
        cout << "Occupied Beds: " << (totalBeds - availableBeds) << endl;
        cout << "Occupancy Rate: "
            << (totalBeds > 0 ? (100.0 * (totalBeds - availableBeds) / totalBeds) : 0)
            << "%" << endl;
        cout << "Specializations: ";
        for (int i = 0; i < numSpecializations; i++)
        {
            cout << specializations[i];
            if (i < numSpecializations - 1) cout << ", ";
        }
        cout << endl;
        cout << "Contact: " << contactNumber << endl;
    }

    void displayDetailedStructure()
    {
        cout << endl;
        cout << "   HOSPITAL DETAILED STRUCTURE......" << endl;
        cout << endl;
        cout << "Hospital: " << name << " (" << hospitalId << ")" << endl;
        cout << "Sector: " << sector << endl;
        cout << "Total Capacity: " << totalBeds << " beds" << endl;
        cout << "Currently Available: " << availableBeds << " beds" << endl;

        int occupied = totalBeds - availableBeds;
        double occupancyRate = (totalBeds > 0) ? (100.0 * occupied / totalBeds) : 0.0;
        cout << "Occupancy: " << occupied << "/" << totalBeds << " (" << occupancyRate << "%)" << endl;

        if (hierarchy == NULL)
        {
            cout << "\n[ERROR: Hierarchy is NULL]" << endl;
            return;
        }

        TreeNode* root = hierarchy->getRoot();
        if (root == NULL)
        {
            cout << "\n[ERROR: Hierarchy root is NULL]" << endl;
            return;
        }

        if (root->numChildren == 0)
        {
            cout << "\n[No blocks added yet]" << endl;
            return;
        }

        cout << endl;

        int actualBlockCount = 0;
        for (int i = 0; i < root->numChildren && i < root->capacity; i++)
        {
            TreeNode* blockNode = root->children[i];
            if (blockNode == NULL) continue;

            Block* block = (Block*)blockNode->data;
            if (block == NULL) continue;

            actualBlockCount++;

            cout << "\n[BLOCK " << actualBlockCount << "] " << block->blockName << endl;
            cout << "  Type: " << block->blockType << endl;
            cout << "  Floor: " << block->floorNumber << endl;
            cout << "  Total Beds: " << block->totalBeds << endl;
            cout << "  Available: " << block->availableBeds << "/" << block->totalBeds << endl;

            if (blockNode->numChildren == 0)
            {
                cout << "  [No wards in this block]" << endl;
                continue;
            }

            int actualWardCount = 0;
            for (int j = 0; j < blockNode->numChildren && j < blockNode->capacity; j++)
            {
                TreeNode* wardNode = blockNode->children[j];
                if (wardNode == NULL) continue;

                Ward* ward = (Ward*)wardNode->data;
                if (ward == NULL) continue;

                actualWardCount++;

                cout << "\n  Ward " << actualWardCount << ": " << ward->wardName << endl;
                cout << "    Type: " << ward->wardType << endl;
                cout << "    Beds: " << ward->availableBeds << "/" << ward->totalBeds << " available" << endl;
                cout << "    Occupied: " << (ward->totalBeds - ward->availableBeds) << " beds" << endl;
            }
        }

        cout << endl;
        cout.flush();
    }
};