#pragma once
#include <iostream>
#include "..\DataStructures\Graph.h"
#include "..\DataStructures\HashTable.h"
#include "..\DataStructures\LinkedList.h"
#include "..\DataStructures\Stack.h"

using namespace std;

struct SchoolBus
{
    char busId[20];
    char schoolId[20];
    char driverName[100];
    char currentLocation[50];
    int capacity;
    int currentStudents;
    bool isActive;
    LinkedList *route;            // List of stop IDs
    LinkedList *assignedStudents; // List of student IDs
    int currentStopIndex;

    SchoolBus() : capacity(0), currentStudents(0), isActive(false),
                  route(NULL), assignedStudents(NULL), currentStopIndex(0)
    {
        busId[0] = '\0';
        schoolId[0] = '\0';
        driverName[0] = '\0';
        currentLocation[0] = '\0';
    }

    SchoolBus(const char *id, const char *school, const char *driver, int cap)
        : capacity(cap), currentStudents(0), isActive(true), currentStopIndex(0)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            busId[i] = id[i];
            i++;
        }
        busId[i] = '\0';

        i = 0;
        while (school[i] != '\0' && i < 19)
        {
            schoolId[i] = school[i];
            i++;
        }
        schoolId[i] = '\0';

        i = 0;
        while (driver[i] != '\0' && i < 99)
        {
            driverName[i] = driver[i];
            i++;
        }
        driverName[i] = '\0';

        currentLocation[0] = '\0';
        route = new LinkedList();
        assignedStudents = new LinkedList();
    }

    void display()
    {
        cout << "\n=== SCHOOL BUS DETAILS ===" << endl;
        cout << "Bus ID: " << busId << endl;
        cout << "School: " << schoolId << endl;
        cout << "Driver: " << driverName << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Current Students: " << currentStudents << endl;
        cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
        cout << "Current Location: " << (currentLocation[0] != '\0' ? currentLocation : "At School") << endl;
        cout << "Route Stops: " << route->getSize() << endl;
    }
};

struct BusRouteStop
{
    char stopId[50];
    char stopName[100];
    int pickupOrder;
    int studentsAtStop;
    double latitude;
    double longitude;

    BusRouteStop(const char *id, const char *name, int order, double lat, double lon)
        : pickupOrder(order), studentsAtStop(0), latitude(lat), longitude(lon)
    {
        int i = 0;
        while (id[i] != '\0' && i < 49)
        {
            stopId[i] = id[i];
            i++;
        }
        stopId[i] = '\0';
        i = 0;
        while (name[i] != '\0' && i < 99)
        {
            stopName[i] = name[i];
            i++;
        }
        stopName[i] = '\0';
    }
};

class SchoolBusTracker
{
private:
    Graph *cityGraph;
    HashTable *busRegistry;   // busId -> SchoolBus*
    HashTable *schoolBuses;   // schoolId -> LinkedList of buses
    HashTable *studentBusMap; // studentId -> busId
    Stack *tripHistory;
    int totalBuses;

public:
    SchoolBusTracker(Graph *graph) : totalBuses(0)
    {
        cityGraph = graph;
        busRegistry = new HashTable(100);
        schoolBuses = new HashTable(50);
        studentBusMap = new HashTable(500);
        tripHistory = new Stack();
        cout << "School Bus Tracker: Initialized" << endl;
    }

    void registerSchoolBus(const char *busId, const char *schoolId,
                           const char *driverName, int capacity)
    {
        SchoolBus *bus = new SchoolBus(busId, schoolId, driverName, capacity);
        busRegistry->insert(busId, (void *)bus);

        // Add to school's bus list
        LinkedList *busList = (LinkedList *)schoolBuses->search(schoolId);
        if (busList == NULL)
        {
            busList = new LinkedList();
            schoolBuses->insert(schoolId, (void *)busList);
        }
        busList->insertAtEnd((void *)bus);

        totalBuses++;
        cout << "School bus " << busId << " registered for school " << schoolId << endl;
    }

    void addStopToRoute(const char *busId, const char *stopId, const char *stopName,
                        double lat, double lon)
    {
        SchoolBus *bus = (SchoolBus *)busRegistry->search(busId);
        if (bus == NULL)
        {
            cout << "Bus " << busId << " not found!" << endl;
            return;
        }

        int order = bus->route->getSize() + 1;
        BusRouteStop *stop = new BusRouteStop(stopId, stopName, order, lat, lon);
        bus->route->insertAtEnd((void *)stop);

        // Add stop to city graph if not exists
        if (cityGraph->findVertexIndex(stopId) == -1)
        {
            cityGraph->addVertex(stopId, stopName, lat, lon);
        }

        cout << "Added stop " << stopName << " to bus " << busId << " route (Order: " << order << ")" << endl;
    }

    void assignStudentToBus(const char *studentId, const char *busId, const char *pickupStop)
    {
        SchoolBus *bus = (SchoolBus *)busRegistry->search(busId);
        if (bus == NULL)
        {
            cout << "Bus " << busId << " not found!" << endl;
            return;
        }

        if (bus->currentStudents >= bus->capacity)
        {
            cout << "Bus " << busId << " is at full capacity!" << endl;
            return;
        }

        // Store student ID
        char *studentCopy = new char[50];
        int i = 0;
        while (studentId[i] != '\0' && i < 49)
        {
            studentCopy[i] = studentId[i];
            i++;
        }
        studentCopy[i] = '\0';

        bus->assignedStudents->insertAtEnd((void *)studentCopy);
        bus->currentStudents++;
        studentBusMap->insert(studentId, (void *)bus);

        cout << "Student " << studentId << " assigned to bus " << busId << endl;
    }

    void updateBusLocation(const char *busId, const char *locationId)
    {
        SchoolBus *bus = (SchoolBus *)busRegistry->search(busId);
        if (bus == NULL)
        {
            cout << "Bus " << busId << " not found!" << endl;
            return;
        }

        int i = 0;
        while (locationId[i] != '\0' && i < 49)
        {
            bus->currentLocation[i] = locationId[i];
            i++;
        }
        bus->currentLocation[i] = '\0';

        cout << "Bus " << busId << " location updated to " << locationId << endl;
    }

    void simulateBusTrip(const char *busId)
    {
        SchoolBus *bus = (SchoolBus *)busRegistry->search(busId);
        if (bus == NULL)
        {
            cout << "Bus " << busId << " not found!" << endl;
            return;
        }

        if (bus->route->getSize() == 0)
        {
            cout << "No route defined for bus " << busId << endl;
            return;
        }

        cout << endl;
        cout << "   SIMULATING SCHOOL BUS TRIP: " << busId << endl;
        cout << endl;
        cout << "School: " << bus->schoolId << endl;
        cout << "Driver: " << bus->driverName << endl;
        cout << "Total Stops: " << bus->route->getSize() << endl;
        cout << "--------------------------------------------" << endl;

        ListNode *current = bus->route->getHead();
        int stopNum = 1;
        const char *prevStop = bus->schoolId;

        while (current != NULL)
        {
            BusRouteStop *stop = (BusRouteStop *)current->data;

            cout << "\nStop " << stopNum << ": " << stop->stopName << endl;
            cout << "  Calculating route from " << prevStop << "..." << endl;

            // Use Dijkstra to find path
            cityGraph->dijkstra(prevStop, stop->stopId);

            // Update bus location
            int i = 0;
            while (stop->stopId[i] != '\0' && i < 49)
            {
                bus->currentLocation[i] = stop->stopId[i];
                i++;
            }
            bus->currentLocation[i] = '\0';

            prevStop = stop->stopId;
            stopNum++;
            current = current->next;
        }

        // Final leg to school
        cout << "\nFinal Leg: Returning to School " << bus->schoolId << endl;
        cityGraph->dijkstra(prevStop, bus->schoolId);

        bus->currentLocation[0] = '\0'; // Back at school

        cout << endl;
        cout << "   TRIP COMPLETED - All students delivered!" << endl;
        cout << endl;
    }

    void trackBus(const char *busId)
    {
        SchoolBus *bus = (SchoolBus *)busRegistry->search(busId);
        if (bus == NULL)
        {
            cout << "Bus " << busId << " not found!" << endl;
            return;
        }

        bus->display();

        cout << "\n--- ROUTE ---" << endl;
        ListNode *current = bus->route->getHead();
        int stopNum = 1;
        while (current != NULL)
        {
            BusRouteStop *stop = (BusRouteStop *)current->data;
            cout << stopNum << ". " << stop->stopName << " (" << stop->stopId << ")" << endl;
            stopNum++;
            current = current->next;
        }
    }

    void displaySchoolBuses(const char *schoolId)
    {
        LinkedList *busList = (LinkedList *)schoolBuses->search(schoolId);
        if (busList == NULL || busList->getSize() == 0)
        {
            cout << "No buses registered for school " << schoolId << endl;
            return;
        }

        cout << "\n=== BUSES FOR SCHOOL " << schoolId << " ===" << endl;
        ListNode *current = busList->getHead();
        while (current != NULL)
        {
            SchoolBus *bus = (SchoolBus *)current->data;
            cout << "- " << bus->busId << " | Driver: " << bus->driverName
                 << " | Students: " << bus->currentStudents << "/" << bus->capacity << endl;
            current = current->next;
        }
    }

    void findStudentBus(const char *studentId)
    {
        SchoolBus *bus = (SchoolBus *)studentBusMap->search(studentId);
        if (bus == NULL)
        {
            cout << "No bus assigned to student " << studentId << endl;
            return;
        }

        cout << "\nStudent " << studentId << " is assigned to:" << endl;
        cout << "Bus: " << bus->busId << endl;
        cout << "School: " << bus->schoolId << endl;
        cout << "Driver: " << bus->driverName << endl;
        cout << "Current Location: " << (bus->currentLocation[0] != '\0' ? bus->currentLocation : "At School") << endl;
    }

    void displayAllSchoolBuses()
    {
        cout << "\n=== ALL SCHOOL BUSES ===" << endl;
        cout << "Total Buses: " << totalBuses << endl;
        busRegistry->display();
    }

    ~SchoolBusTracker()
    {
        delete busRegistry;
        delete schoolBuses;
        delete studentBusMap;
        delete tripHistory;
        cout << "School Bus Tracker: Shut down" << endl;
    }
};