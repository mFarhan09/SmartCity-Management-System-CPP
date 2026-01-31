#pragma once
#include <iostream>
#include "../DataStructures/Graph.h"
#include "../DataStructures/HashTable.h"
#include "../DataStructures/LinkedList.h"

using namespace std;

struct PublicFacility
{
    char facilityId[20];
    char name[100];
    char type[50]; // e.g., 'Park', 'Library', 'Police', 'Fire'
    char sector[20];
    double latitude;
    double longitude;

    PublicFacility(const char* id, const char* n, const char* t, const char* s, double lat, double lon)
        : latitude(lat), longitude(lon)
    {
        // String copy implementation
        int i = 0;
        while (id[i] != '\0' && i < 19) { facilityId[i] = id[i]; i++; } facilityId[i] = '\0';
        i = 0;
        while (n[i] != '\0' && i < 99) { name[i] = n[i]; i++; } name[i] = '\0';
        i = 0;
        while (t[i] != '\0' && i < 49) { type[i] = t[i]; i++; } type[i] = '\0';
        i = 0;
        while (s[i] != '\0' && i < 19) { sector[i] = s[i]; i++; } sector[i] = '\0';
    }

    void display()
    {
        cout << "  [Facility] ID: " << facilityId << ", Name: " << name
            << ", Type: " << type << ", Sector: " << sector
            << ", Coords: (" << latitude << ", " << longitude << ")" << endl;
    }
};

// FACILITY MANAGER CLASS
class FacilityManager
{
private:
    Graph* cityGraph;
    HashTable* facilityRegistry; // Key: facilityId, Value: PublicFacility*
    LinkedList* allFacilities;  // For listing and iteration

    // Helper function for string comparison
    bool stringCompare(const char* s1, const char* s2)
    {
        int i = 0;
        while (s1[i] != '\0' || s2[i] != '\0') {
            if (s1[i] != s2[i]) return false;
            i++;
        }
        return true;
    }

public:
    FacilityManager(Graph* graph) : cityGraph(graph)
    {
        facilityRegistry = new HashTable(100);
        allFacilities = new LinkedList();
        cout << "Facility Manager: Initialized" << endl;
    }

    // --- Core Functions ---

    void addFacility(const char* id, const char* name, const char* type,
        const char* sector, double lat, double lon)
    {
        if (cityGraph->findVertexIndex(id) != -1) {
            cout << "Error: Location ID already exists in the city graph!" << endl;
            return;
        }

        PublicFacility* newFacility = new PublicFacility(id, name, type, sector, lat, lon);
        facilityRegistry->insert(id, newFacility);
        allFacilities->insertAtEnd(newFacility);
        cityGraph->addVertex(id, name, lat, lon); // Add to master city graph

        cout << "Added Public Facility: " << name << " (" << type << ")" << endl;
    }

    PublicFacility* searchFacility(const char* facilityId)
    {
        PublicFacility* f = (PublicFacility*)facilityRegistry->search(facilityId);
        if (f == NULL) {
            cout << "Facility ID " << facilityId << " not found." << endl;
        }
        else {
            cout << "Facility found:" << endl;
            f->display();
        }
        return f;
    }

    void getFacilitiesByType(const char* type)
    {
        cout << "\n--- Facilities of Type: " << type << " ---" << endl;
        bool found = false;

        // Iterate through the whole allFacilities list
        ListNode* current = allFacilities->getHead();
        while (current != NULL)
        {
            PublicFacility* f = (PublicFacility*)current->data;
            if (stringCompare(f->type, type))
            {
                f->display();
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No facilities of type '" << type << "' found." << endl;
        }
    }

    // --- Integrated Functions ---

    void findNearestFacility(const char* fromLocation, const char* facilityType)
    {
        cout << "\n=== FINDING NEAREST FACILITY (Type: " << facilityType << ") ===" << endl;
        cout << "Searching from location: " << fromLocation << endl;

        // Use Graph's findNearest, which uses substring match on the name
        const char* nearest = cityGraph->findNearest(fromLocation, facilityType);

        if (nearest != NULL)
        {
            cout << "Nearest " << facilityType << " found: " << nearest << endl;
            cout << "\nCalculating shortest route..." << endl;
            cityGraph->dijkstra(fromLocation, nearest);
        }
        else
        {
            cout << "No " << facilityType << " found in the city network!" << endl;
        }
    }

    void displayAllFacilities()
    {
        cout << "\n--- ALL REGISTERED PUBLIC FACILITIES ---" << endl;
        ListNode* current = allFacilities->getHead();
        while (current != NULL)
        {
            ((PublicFacility*)current->data)->display();
            current = current->next;
        }
        if (allFacilities->getSize() == 0) {
            cout << "No public facilities registered." << endl;
        }
    }

    ~FacilityManager()
    {
        // Clean up entities in allFacilities
        ListNode* current = allFacilities->getHead();
        while (current != NULL)
        {
            delete (PublicFacility*)current->data;
            current = current->next;
        }
        // ListNodes are deleted by the LinkedList destructor

        // HashNodes are deleted by the HashTable destructor
        delete facilityRegistry;
        delete allFacilities;
        cout << "Facility Manager: Shut down" << endl;
    }
};