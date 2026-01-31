#pragma once
#include <iostream>
#include "../DataStructures/LinkedList.h"
using namespace std;

struct BusStop {
    char stopId[20];
    char name[100];
    double latitude;
    double longitude;

    BusStop() : latitude(0), longitude(0) {
        stopId[0] = '\0';
        name[0] = 'm';
    }

    // Full constructor
    BusStop(const char* id, const char* n, double lat, double lon)
        : latitude(lat), longitude(lon)
    {
        strncpy_s(stopId, id, sizeof(stopId) - 1);
        stopId[sizeof(stopId) - 1] = '\0';

        strncpy_s(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    // Constructor needed for route parsing (Stop1 > Stop2)
    BusStop(const char* n) : latitude(0), longitude(0) {
        stopId[0] = '\0';  // Or auto-generate if needed

        strncpy_s(name, n, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
    }

    ~BusStop() {
        // Nothing to free — BusStop uses no dynamic memory.
    }

};

struct Bus {
    char busNumber[20];
    char company[50];
    char currentStop[20];
    LinkedList* route;  // List of BusStop*
    int capacity;
    int currentPassengers;

    Bus() : route(NULL), capacity(0), currentPassengers(0) {}

    Bus(const char* num, const char* comp, const char* curr, const char* routeStr)
        : capacity(15), currentPassengers(0)
    {
        // Copy Bus Number
        strncpy_s(busNumber, num, sizeof(busNumber) - 1);
        busNumber[sizeof(busNumber) - 1] = '\0';

        // Copy Company
        strncpy_s(company, comp, sizeof(company) - 1);
        company[sizeof(company) - 1] = '\0';

        // Copy Current Stop
        strncpy_s(currentStop, curr, sizeof(currentStop) - 1);
        currentStop[sizeof(currentStop) - 1] = '\0';

        // Initialize route list
        route = new LinkedList();

        // Parse the route string "Stop1 > Stop2 > Stop3"
        char temp[200];
        strncpy_s(temp, routeStr, sizeof(temp) - 1);
        temp[sizeof(temp) - 1] = '\0';

        char* context = nullptr; // needed for strtok_s
        char* token = strtok_s(temp, ">", &context);
        while (token != NULL) {
            // Trim spaces
            while (*token == ' ') token++;

            route->insertAtEnd(new BusStop(token));
            token = strtok_s(NULL, ">", &context);
        }

    }

    void addStopToRoute(BusStop* stop) {
        route->insertAtEnd((void*)stop);
        if (route->getSize() == 1) {
            // First stop - set as current
            int i = 0;
            while (stop->stopId[i] != '\0' && i < 19) {
                currentStop[i] = stop->stopId[i];
                i++;
            }
            currentStop[i] = '\0';
        }
    }

    void displayRoute() {
        cout << "Route for " << busNumber << ":" << endl;
        ListNode* current = route->getHead();
        int stopNum = 1;
        while (current != NULL) {
            BusStop* stop = (BusStop*)current->data;
            cout << "  Stop " << stopNum++ << ": " << stop->name
                << " (" << stop->stopId << ")" << endl;
            current = current->next;
        }
    }

    ~Bus() {
        if (route != nullptr) {
            ListNode* current = route->getHead();
            while (current != nullptr) {
                BusStop* stop = (BusStop*)current->data;
                delete stop;          // delete each BusStop
                current = current->next;
            }
            delete route;             // delete the LinkedList
            route = nullptr;
        }
    }

};
