#pragma once
#include <iostream>
#include "../DataStructures/Graph.h"
#include "../DataStructures/HashTable.h"
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/MaxHeap.h"

using namespace std;

enum TransportType {
    AIRPORT,
    RAILWAY_STATION,
    METRO_STATION,
    BUS_TERMINAL
};

struct TransportHub {
    char hubId[20];
    char name[100];
    char sector[20];
    TransportType type;
    double latitude;
    double longitude;
    bool isOperational;
    int dailyCapacity;
    LinkedList* connectedRoutes;

    TransportHub() : type(BUS_TERMINAL), latitude(0), longitude(0),
        isOperational(true), dailyCapacity(0), connectedRoutes(NULL) {
        hubId[0] = '\0';
        name[0] = '\0';
        sector[0] = '\0';
    }

    TransportHub(const char* id, const char* n, const char* sec,
        TransportType t, double lat, double lon, int cap)
        : type(t), latitude(lat), longitude(lon), isOperational(true), dailyCapacity(cap) {
        int i = 0;
        while (id[i] != '\0' && i < 19) { hubId[i] = id[i]; i++; }
        hubId[i] = '\0';
        i = 0;
        while (n[i] != '\0' && i < 99) { name[i] = n[i]; i++; }
        name[i] = '\0';
        i = 0;
        while (sec[i] != '\0' && i < 19) { sector[i] = sec[i]; i++; }
        sector[i] = '\0';

        connectedRoutes = new LinkedList();
    }

    const char* getTypeString() {
        switch (type) {
        case AIRPORT: return "Airport";
        case RAILWAY_STATION: return "Railway Station";
        case METRO_STATION: return "Metro Station";
        case BUS_TERMINAL: return "Bus Terminal";
        default: return "Unknown";
        }
    }

    void display() {
        cout << "\n=== TRANSPORT HUB ===" << endl;
        cout << "ID: " << hubId << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << getTypeString() << endl;
        cout << "Sector: " << sector << endl;
        cout << "Coordinates: (" << latitude << ", " << longitude << ")" << endl;
        cout << "Status: " << (isOperational ? "Operational" : "Closed") << endl;
        cout << "Daily Capacity: " << dailyCapacity << " passengers" << endl;
    }
};

struct TransportRoute {
    char routeId[20];
    char routeName[100];
    char sourceHubId[20];
    char destHubId[20];
    TransportType routeType;
    double distance;
    int durationMinutes;
    double fare;
    bool isActive;

    TransportRoute(const char* id, const char* name, const char* src, const char* dest,
        TransportType type, double dist, int duration, double f)
        : routeType(type), distance(dist), durationMinutes(duration), fare(f), isActive(true) {
        int i = 0;
        while (id[i] != '\0' && i < 19) { routeId[i] = id[i]; i++; }
        routeId[i] = '\0';
        i = 0;
        while (name[i] != '\0' && i < 99) { routeName[i] = name[i]; i++; }
        routeName[i] = '\0';
        i = 0;
        while (src[i] != '\0' && i < 19) { sourceHubId[i] = src[i]; i++; }
        sourceHubId[i] = '\0';
        i = 0;
        while (dest[i] != '\0' && i < 19) { destHubId[i] = dest[i]; i++; }
        destHubId[i] = '\0';
    }

    void display() {
        cout << "Route: " << routeName << " (" << routeId << ")" << endl;
        cout << "  From: " << sourceHubId << " -> To: " << destHubId << endl;
        cout << "  Distance: " << distance << " km | Duration: " << durationMinutes << " min" << endl;
        cout << "  Fare: PKR " << fare << " | Status: " << (isActive ? "Active" : "Inactive") << endl;
    }
};

struct Flight {
    char flightId[20];
    char airline[50];
    char source[50];
    char destination[50];
    char departureTime[10];
    char arrivalTime[10];
    double fare;
    int seatsAvailable;

    Flight(const char* id, const char* air, const char* src, const char* dest,
        const char* dep, const char* arr, double f, int seats)
        : fare(f), seatsAvailable(seats) {
        int i = 0;
        while (id[i] != '\0' && i < 19) { flightId[i] = id[i]; i++; }
        flightId[i] = '\0';
        i = 0;
        while (air[i] != '\0' && i < 49) { airline[i] = air[i]; i++; }
        airline[i] = '\0';
        i = 0;
        while (src[i] != '\0' && i < 49) { source[i] = src[i]; i++; }
        source[i] = '\0';
        i = 0;
        while (dest[i] != '\0' && i < 49) { destination[i] = dest[i]; i++; }
        destination[i] = '\0';
        i = 0;
        while (dep[i] != '\0' && i < 9) { departureTime[i] = dep[i]; i++; }
        departureTime[i] = '\0';
        i = 0;
        while (arr[i] != '\0' && i < 9) { arrivalTime[i] = arr[i]; i++; }
        arrivalTime[i] = '\0';
    }

    void display() {
        cout << flightId << " | " << airline << " | " << source << " -> " << destination << endl;
        cout << "  Departure: " << departureTime << " | Arrival: " << arrivalTime << endl;
        cout << "  Fare: PKR " << fare << " | Seats: " << seatsAvailable << endl;
    }
};

struct Train {
    char trainId[20];
    char trainName[50];
    char source[50];
    char destination[50];
    char departureTime[10];
    int durationHours;
    double fare;
    int seatsAvailable;

    Train(const char* id, const char* name, const char* src, const char* dest,
        const char* dep, int duration, double f, int seats)
        : durationHours(duration), fare(f), seatsAvailable(seats) {
        int i = 0;
        while (id[i] != '\0' && i < 19) { trainId[i] = id[i]; i++; }
        trainId[i] = '\0';
        i = 0;
        while (name[i] != '\0' && i < 49) { trainName[i] = name[i]; i++; }
        trainName[i] = '\0';
        i = 0;
        while (src[i] != '\0' && i < 49) { source[i] = src[i]; i++; }
        source[i] = '\0';
        i = 0;
        while (dest[i] != '\0' && i < 49) { destination[i] = dest[i]; i++; }
        destination[i] = '\0';
        i = 0;
        while (dep[i] != '\0' && i < 9) { departureTime[i] = dep[i]; i++; }
        departureTime[i] = '\0';
    }

    void display() {
        cout << trainId << " | " << trainName << " | " << source << " -> " << destination << endl;
        cout << "  Departure: " << departureTime << " | Duration: " << durationHours << " hrs" << endl;
        cout << "  Fare: PKR " << fare << " | Seats: " << seatsAvailable << endl;
    }
};

class AirportRailManager {
private:
    Graph* cityGraph;
    HashTable* hubRegistry;
    HashTable* routeRegistry;
    HashTable* flightRegistry;
    HashTable* trainRegistry;
    LinkedList* allHubs;
    LinkedList* allFlights;
    LinkedList* allTrains;

    bool stringCompare(const char* s1, const char* s2) {
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0') {
            if (s1[i] != s2[i]) return false;
            i++;
        }
        return s1[i] == s2[i];
    }

public:
    AirportRailManager(Graph* graph) {
        cityGraph = graph;
        hubRegistry = new HashTable(50);
        routeRegistry = new HashTable(100);
        flightRegistry = new HashTable(200);
        trainRegistry = new HashTable(100);
        allHubs = new LinkedList();
        allFlights = new LinkedList();
        allTrains = new LinkedList();
        cout << "Airport & Rail Manager: Initialized" << endl;
    }

    // ==========================================
    // HUB MANAGEMENT
    // ==========================================

    void addTransportHub(const char* id, const char* name, const char* sector,
        int type, double lat, double lon, int capacity) {
        TransportType hubType;
        switch (type) {
        case 1: hubType = AIRPORT; break;
        case 2: hubType = RAILWAY_STATION; break;
        case 3: hubType = METRO_STATION; break;
        default: hubType = BUS_TERMINAL;
        }

        TransportHub* hub = new TransportHub(id, name, sector, hubType, lat, lon, capacity);
        hubRegistry->insert(id, (void*)hub);
        allHubs->insertAtEnd((void*)hub);

        // Add to city graph
        cityGraph->addVertex(id, name, lat, lon);

        cout << "Added " << hub->getTypeString() << ": " << name << endl;
    }

    void connectHubs(const char* hub1Id, const char* hub2Id, double distance) {
        TransportHub* hub1 = (TransportHub*)hubRegistry->search(hub1Id);
        TransportHub* hub2 = (TransportHub*)hubRegistry->search(hub2Id);

        if (hub1 == NULL || hub2 == NULL) {
            cout << "One or both hubs not found!" << endl;
            return;
        }

        cityGraph->addEdge(hub1Id, hub2Id, distance);
        cout << "Connected " << hub1->name << " <-> " << hub2->name << " (" << distance << " km)" << endl;
    }

    // ==========================================
    // FLIGHT MANAGEMENT
    // ==========================================

    void addFlight(const char* flightId, const char* airline, const char* source,
        const char* dest, const char* depTime, const char* arrTime,
        double fare, int seats) {
        Flight* flight = new Flight(flightId, airline, source, dest, depTime, arrTime, fare, seats);
        flightRegistry->insert(flightId, (void*)flight);
        allFlights->insertAtEnd((void*)flight);

        cout << "Flight added: " << flightId << " (" << airline << ")" << endl;
    }

    void searchFlights(const char* source, const char* destination) {
        cout << "\n=== FLIGHTS FROM " << source << " TO " << destination << " ===" << endl;
        bool found = false;

        ListNode* current = allFlights->getHead();
        while (current != NULL) {
            Flight* f = (Flight*)current->data;
            if (stringCompare(f->source, source) && stringCompare(f->destination, destination)) {
                f->display();
                cout << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No flights found for this route." << endl;
        }
    }

    void displayAllFlights() {
        cout << "\n=== ALL FLIGHTS ===" << endl;
        ListNode* current = allFlights->getHead();
        while (current != NULL) {
            Flight* f = (Flight*)current->data;
            f->display();
            cout << endl;
            current = current->next;
        }
        if (allFlights->getSize() == 0) {
            cout << "No flights registered." << endl;
        }
    }

    // ==========================================
    // TRAIN MANAGEMENT
    // ==========================================

    void addTrain(const char* trainId, const char* trainName, const char* source,
        const char* dest, const char* depTime, int duration,
        double fare, int seats) {
        Train* train = new Train(trainId, trainName, source, dest, depTime, duration, fare, seats);
        trainRegistry->insert(trainId, (void*)train);
        allTrains->insertAtEnd((void*)train);

        cout << "Train added: " << trainId << " (" << trainName << ")" << endl;
    }

    void searchTrains(const char* source, const char* destination) {
        cout << "\n=== TRAINS FROM " << source << " TO " << destination << " ===" << endl;
        bool found = false;

        ListNode* current = allTrains->getHead();
        while (current != NULL) {
            Train* t = (Train*)current->data;
            if (stringCompare(t->source, source) && stringCompare(t->destination, destination)) {
                t->display();
                cout << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No trains found for this route." << endl;
        }
    }

    void displayAllTrains() {
        cout << "\n=== ALL TRAINS ===" << endl;
        ListNode* current = allTrains->getHead();
        while (current != NULL) {
            Train* t = (Train*)current->data;
            t->display();
            cout << endl;
            current = current->next;
        }
        if (allTrains->getSize() == 0) {
            cout << "No trains registered." << endl;
        }
    }

    // ==========================================
    // NAVIGATION & ROUTING
    // ==========================================

    void findRouteToAirport(const char* fromLocation) {
        cout << "\n=== FINDING ROUTE TO NEAREST AIRPORT ===" << endl;

        const char* nearestAirport = cityGraph->findNearest(fromLocation, "Airport");
        if (nearestAirport != NULL) {
            cout << "Nearest Airport: " << nearestAirport << endl;
            cityGraph->dijkstra(fromLocation, nearestAirport);
        }
        else {
            cout << "No airport found in city network!" << endl;
        }
    }

    void findRouteToStation(const char* fromLocation) {
        cout << "\n=== FINDING ROUTE TO NEAREST RAILWAY STATION ===" << endl;

        const char* nearestStation = cityGraph->findNearest(fromLocation, "Railway");
        if (nearestStation != NULL) {
            cout << "Nearest Railway Station: " << nearestStation << endl;
            cityGraph->dijkstra(fromLocation, nearestStation);
        }
        else {
            cout << "No railway station found in city network!" << endl;
        }
    }

    void planMultiModalTrip(const char* fromLocation, const char* finalDestination) {
        cout << "\n============================================" << endl;
        cout << "   MULTI-MODAL TRIP PLANNER" << endl;
        cout << "============================================" << endl;
        cout << "From: " << fromLocation << endl;
        cout << "To: " << finalDestination << endl;
        cout << "--------------------------------------------" << endl;

        cout << "\nOption 1: Direct Route" << endl;
        cityGraph->dijkstra(fromLocation, finalDestination);

        cout << "\nOption 2: Via Airport" << endl;
        const char* airport = cityGraph->findNearest(fromLocation, "Airport");
        if (airport != NULL) {
            cout << "Step 1: To Airport" << endl;
            cityGraph->dijkstra(fromLocation, airport);
            cout << "Step 2: Flight to destination city" << endl;
            cout << "(Check available flights)" << endl;
        }

        cout << "\nOption 3: Via Railway" << endl;
        const char* station = cityGraph->findNearest(fromLocation, "Railway");
        if (station != NULL) {
            cout << "Step 1: To Railway Station" << endl;
            cityGraph->dijkstra(fromLocation, station);
            cout << "Step 2: Train to destination city" << endl;
            cout << "(Check available trains)" << endl;
        }

        cout << "============================================\n" << endl;
    }

    // ==========================================
    // DISPLAY FUNCTIONS
    // ==========================================

    void displayAllHubs() {
        cout << "\n=== ALL TRANSPORT HUBS ===" << endl;
        ListNode* current = allHubs->getHead();
        while (current != NULL) {
            TransportHub* hub = (TransportHub*)current->data;
            cout << hub->hubId << " | " << hub->name << " | " << hub->getTypeString()
                << " | " << hub->sector << endl;
            current = current->next;
        }
        if (allHubs->getSize() == 0) {
            cout << "No transport hubs registered." << endl;
        }
    }

    void displayHubDetails(const char* hubId) {
        TransportHub* hub = (TransportHub*)hubRegistry->search(hubId);
        if (hub == NULL) {
            cout << "Hub " << hubId << " not found!" << endl;
            return;
        }
        hub->display();
    }

    void displayTransportStats() {
        cout << "\n=== TRANSPORT STATISTICS ===" << endl;
        cout << "Total Hubs: " << allHubs->getSize() << endl;
        cout << "Total Flights: " << allFlights->getSize() << endl;
        cout << "Total Trains: " << allTrains->getSize() << endl;

        // Count by type
        int airports = 0, railways = 0, metros = 0, terminals = 0;
        ListNode* current = allHubs->getHead();
        while (current != NULL) {
            TransportHub* hub = (TransportHub*)current->data;
            switch (hub->type) {
            case AIRPORT: airports++; break;
            case RAILWAY_STATION: railways++; break;
            case METRO_STATION: metros++; break;
            case BUS_TERMINAL: terminals++; break;
            }
            current = current->next;
        }

        cout << "\nBy Type:" << endl;
        cout << "  Airports: " << airports << endl;
        cout << "  Railway Stations: " << railways << endl;
        cout << "  Metro Stations: " << metros << endl;
        cout << "  Bus Terminals: " << terminals << endl;
    }

    ~AirportRailManager() {
        delete hubRegistry;
        delete routeRegistry;
        delete flightRegistry;
        delete trainRegistry;
        delete allHubs;
        delete allFlights;
        delete allTrains;
        cout << "Airport & Rail Manager: Shut down" << endl;
    }
};