#pragma once
#include <iostream>
#include <fstream>
#include "../DataStructures/Graph.h"
#include "../DataStructures/HashTable.h"
#include "Bus.h"
#include "Passenger.h"
#include "../DataStructures/CircularQueue.h"
#include "TravelHistory.h"

using namespace std;

// Helper function to print passenger in queue display
void printPassenger(void* data) {
    Passenger* p = (Passenger*)data;
    p->displayShort();
}

class TransportManager {
private:
    Graph* cityGraph;
    HashTable* busRegistry;
    HashTable* stopRegistry;
    HashTable* stopQueues;         // CircularQueue of Passengers for each stop
    TravelHistory* travelHistory;  // Stack-based travel history


    // Helper to get current timestamp
    void getCurrentTimestamp(char* buffer) {
        static int tripCount = 0;
        tripCount++;

        int i = 0;
        const char* prefix = "Trip_";
        while (prefix[i] != '\0') {
            buffer[i] = prefix[i];
            i++;
        }

        int temp = tripCount;
        int digits[10];
        int numDigits = 0;

        if (temp == 0) {
            digits[numDigits++] = 0;
        }
        else {
            while (temp > 0) {
                digits[numDigits++] = temp % 10;
                temp /= 10;
            }
        }

        for (int j = numDigits - 1; j >= 0; j--) {
            buffer[i++] = '0' + digits[j];
        }
        buffer[i] = '\0';
    }

public:

    TransportManager(Graph* graph) {
        cityGraph = graph;
        busRegistry = new HashTable(100);
        stopRegistry = new HashTable(100);
        stopQueues = new HashTable(100);
        travelHistory = new TravelHistory();
    }

    // LOCATION MANAGEMENT

    void addLocation(const char* id, const char* name, double lat, double lon) {
        cityGraph->addVertex(id, name, lat, lon);
    }

    void connectLocations(const char* from, const char* to, double distance) {
        cityGraph->addEdge(from, to, distance);
    }

    Bus* getBus(const char* busNumber)
    {
        return (Bus*)busRegistry->search(busNumber);
    }

    BusStop* getStop(const char* stopId)
    {
        return (BusStop*)stopRegistry->search(stopId);
    }

    void findShortestPath(const char* from, const char* to) {
        PathArray* path = cityGraph->dijkstra(from, to);

        // Record this trip in travel history
        if (path->size > 0) {
            char timestamp[30];
            getCurrentTimestamp(timestamp);
            double distance = path->size * 2.5;
            travelHistory->recordTrip(from, to, "N/A", timestamp, distance);
        }

        delete path;
    }

    // BUS OPERATIONS
 
    
    void registerBus(const char* busNumber, const char* company, const char* currentStop, const char* route) {
        Bus* bus = new Bus (busNumber, company, currentStop , route);
        busRegistry->insert(busNumber, (void*)bus);
        cout << "Bus " << busNumber << " registered (" << company << ", "
             << " seats)" <<", " << "currentStop" << " " << currentStop <<", " << "route " << route << endl;
    }

    void addBusStop(const char* stopId, const char* name, double lat, double lon) {
        BusStop* stop = new BusStop(stopId, name, lat, lon);
        stopRegistry->insert(stopId, (void*)stop);

        // Create a passenger queue for this stop (capacity 20 passengers)
        CircularQueue* queue = new CircularQueue(20);
        stopQueues->insert(stopId, (void*)queue);

        // Add to city graph
        cityGraph->addVertex(stopId, name, lat, lon);

        cout << "Bus stop added: " << name << " (" << stopId << ") with passenger queue" << endl;
    }

    void addStopToBusRoute(const char* busNumber, const char* stopId) {
        Bus* bus = (Bus*)busRegistry->search(busNumber);
        BusStop* stop = (BusStop*)stopRegistry->search(stopId);

        if (bus == NULL) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return;
        }
        if (stop == NULL) {
            cout << "Stop " << stopId << " not found!" << endl;
            return;
        }

        bus->addStopToRoute(stop);
        cout << "Added " << stop->name << " to " << busNumber << " route" << endl;
    }

    void trackBusLocation(const char* busNumber) {
        Bus* bus = (Bus*)busRegistry->search(busNumber);

        if (bus == NULL) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return;
        }

        cout << "\n=== BUS TRACKING ===" << endl;
        cout << "Bus: " << bus->busNumber << endl;
        cout << "Company: " << bus->company << endl;
        cout << "Current Location: " << bus->currentStop << endl;
        cout << "Passengers: " << bus->currentPassengers << " / "
            << bus->capacity << endl;
    }

    void showBusRoute(const char* busNumber) {
        Bus* bus = (Bus*)busRegistry->search(busNumber);

        if (bus == NULL) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return;
        }

        cout << "\n";
        bus->displayRoute();
    }

    // PASSENGER QUEUE OPERATIONS (CIRCULAR QUEUE)

    void addPassengerToStop(const char* stopId, const char* passengerId,
        const char* name, const char* destination,
        const char* contact = "") {
        CircularQueue* queue = (CircularQueue*)stopQueues->search(stopId);
        BusStop* stop = (BusStop*)stopRegistry->search(stopId);

        if (queue == NULL || stop == NULL) {
            cout << "Stop " << stopId << " not found!" << endl;
            return;
        }

        Passenger* passenger = new Passenger(passengerId, name, stopId, destination, contact);

        if (queue->enqueue((void*)passenger)) {
            cout << "Passenger " << name << " added to queue at " << stop->name << endl;
            cout << "Destination: " << destination << endl;
            cout << "Queue position: " << queue->getSize() << "/" << queue->getCapacity() << endl;
        }
        else {
            cout << "Failed to add passenger - stop queue is full!" << endl;
            delete passenger;
        }
    }

    void displayStopQueue(const char* stopId) {
        CircularQueue* queue = (CircularQueue*)stopQueues->search(stopId);
        BusStop* stop = (BusStop*)stopRegistry->search(stopId);

        if (queue == NULL || stop == NULL) {
            cout << "Stop " << stopId << " not found!" << endl;
            return;
        }

        cout << "\n=== PASSENGER QUEUE AT " << stop->name << " ===" << endl;
        cout << "Stop ID: " << stopId << endl;

        if (queue->isEmpty()) {
            cout << "No passengers waiting." << endl;
        }
        else {
            queue->display(printPassenger);
        }
    }

    void simulateBusArrival(const char* busNumber, const char* stopId) {
        Bus* bus = (Bus*)busRegistry->search(busNumber);
        CircularQueue* queue = (CircularQueue*)stopQueues->search(stopId);
        BusStop* stop = (BusStop*)stopRegistry->search(stopId);

        if (bus == NULL) {
            cout << "Bus " << busNumber << " not found!" << endl;
            return;
        }
        if (queue == NULL || stop == NULL) {
            cout << "Stop " << stopId << " not found!" << endl;
            return;
        }

        cout << "   BUS " << bus->busNumber << " ARRIVED AT " << stop->name << endl;

        int availableSeats = bus->capacity - bus->currentPassengers;
        cout << "Bus capacity: " << bus->capacity << endl;
        cout << "Current passengers on bus: " << bus->currentPassengers << endl;
        cout << "Available seats: " << availableSeats << endl;
        cout << "Passengers waiting: " << queue->getSize() << endl;
        cout << "--------------------------------------------" << endl;

        if (queue->isEmpty()) {
            cout << "No passengers waiting at this stop." << endl;
        }
        else if (availableSeats <= 0) {
            cout << "Bus is full! No passengers can board." << endl;
        }
        else {
            int boarded = 0;

            cout << "\n--- BOARDING ---" << endl;
            while (!queue->isEmpty() && boarded < availableSeats) {
                Passenger* p = (Passenger*)queue->dequeue();
                if (p != NULL) {
                    p->hasBoarded = true;
                    cout << "Boarded: " << p->name << " -> " << p->destinationStop << endl;
                    boarded++;

                    // Record this trip in travel history
                    char timestamp[30];
                    getCurrentTimestamp(timestamp);
                    travelHistory->recordTrip(stopId, p->destinationStop, busNumber, timestamp, 5.0);
                }
            }

            bus->currentPassengers += boarded;

            // Update current stop
            int i = 0;
            while (stopId[i] != '\0' && i < 19) {
                bus->currentStop[i] = stopId[i];
                i++;
            }
            bus->currentStop[i] = '\0';

            cout << "--------------------------------------------" << endl;
            cout << "Total boarded: " << boarded << endl;
            cout << "Updated passengers on bus: " << bus->currentPassengers << "/" << bus->capacity << endl;

            if (!queue->isEmpty()) {
                cout << "Remaining in queue: " << queue->getSize() << " (waiting for next bus)" << endl;
            }
        }

        cout << "============================================\n" << endl;
    }

    // Simulate passengers arriving at random stops
    void simulatePassengerArrivals(const char* stopId, int count) {
        CircularQueue* queue = (CircularQueue*)stopQueues->search(stopId);
        BusStop* stop = (BusStop*)stopRegistry->search(stopId);

        if (queue == NULL || stop == NULL) {
            cout << "Stop " << stopId << " not found!" << endl;
            return;
        }

        cout << "\n=== SIMULATING " << count << " PASSENGER ARRIVALS ===" << endl;
        cout << "Location: " << stop->name << endl;

        const char* sampleNames[] = { "Ali", "Sara", "Hassan", "Fatima", "Usman",
                                      "Ayesha", "Bilal", "Zainab", "Ahmed", "Maryam" };
        const char* sampleDests[] = { "STOP001", "STOP002", "STOP003", "STOP004", "STOP005" };

        for (int i = 0; i < count; i++) {
            char passengerId[20];
            passengerId[0] = 'P';
            passengerId[1] = '0' + (i / 100) % 10;
            passengerId[2] = '0' + (i / 10) % 10;
            passengerId[3] = '0' + i % 10;
            passengerId[4] = '\0';

            const char* name = sampleNames[i % 10];
            const char* dest = sampleDests[i % 5];

            Passenger* p = new Passenger(passengerId, name, stopId, dest, "0300-1234567");

            if (queue->enqueue((void*)p)) {
                cout << "  " << name << " arrived (going to " << dest << ")" << endl;
            }
            else {
                cout << "  Queue full - " << name << " couldn't join" << endl;
                delete p;
                break;
            }
        }

        cout << "Current queue size: " << queue->getSize() << "/" << queue->getCapacity() << endl;
    }

    // ==========================================
    // TRAVEL HISTORY OPERATIONS (STACK)
    // ==========================================

    void recordTravel(const char* from, const char* to, const char* busNumber, double distance) {
        char timestamp[30];
        getCurrentTimestamp(timestamp);
        travelHistory->recordTrip(from, to, busNumber, timestamp, distance);
    }

    void displayTravelHistory() {
        travelHistory->displayHistory();
    }

    void displayRecentTrips(int count) {
        travelHistory->displayLastNTrips(count);
    }

    void undoLastTrip() {
        TravelRecord* record = travelHistory->undoLastTrip();
        if (record != NULL) {
            delete record;
        }
    }

    void getTravelStats() {
        cout << "\n=== TRAVEL STATISTICS ===" << endl;
        cout << "Total trips: " << travelHistory->getTotalTrips() << endl;
        cout << "Total distance: " << travelHistory->getTotalDistance() << " km" << endl;
    }

    void clearTravelHistory() {
        travelHistory->clearHistory();
    }

    // CSV LOADING

    void loadStopsFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file " << filename << endl;
            return;
        }

        char line[500];
        int count = 0;
        bool isHeader = true;

        cout << "\n=== Loading Bus Stops from " << filename << " ===" << endl;

        while (file.getline(line, 500)) {
            if (isHeader) {
                isHeader = false;
                continue;
            }

            char stopId[20], name[100];
            double lat = 0, lon = 0;

            int charIndex = 0;
            int field = 0;
            char currentField[100];

            int i = 0;
            while (line[i] != '\0') {
                if (line[i] == ',' || line[i] == '\n' || line[i] == '\r') {
                    currentField[charIndex] = '\0';

                    int start = 0, end = charIndex - 1;
                    while (start < charIndex && (currentField[start] == '"' || currentField[start] == ' ')) start++;
                    while (end > 0 && (currentField[end] == '"' || currentField[end] == ' ')) end--;

                    char trimmed[100];
                    int j = 0;
                    for (int k = start; k <= end; k++) {
                        trimmed[j++] = currentField[k];
                    }
                    trimmed[j] = '\0';

                    switch (field) {
                    case 0:
                        j = 0;
                        while (trimmed[j] != '\0' && j < 19) {
                            stopId[j] = trimmed[j];
                            j++;
                        }
                        stopId[j] = '\0';
                        break;
                    case 1:
                        j = 0;
                        while (trimmed[j] != '\0' && j < 99) {
                            name[j] = trimmed[j];
                            j++;
                        }
                        name[j] = '\0';
                        break;
                    case 2:
                        lat = atof(trimmed);
                        break;
                    case 3:
                        lon = atof(trimmed);
                        break;
                    }

                    field++;
                    charIndex = 0;
                }
                else {
                    currentField[charIndex++] = line[i];
                }
                i++;
            }

            if (charIndex > 0) {
                currentField[charIndex] = '\0';
                lon = atof(currentField);
            }

            if (field >= 3) {
                addBusStop(stopId, name, lat, lon);
                count++;
            }
        }

        file.close();
        cout << "Loaded " << count << " bus stops from CSV." << endl;
    }

    void loadBusesFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file " << filename << endl;
            return;
        }

        char line[500];
        int count = 0;
        bool isHeader = true;

        cout << "\n=== Loading Buses from " << filename << " ===" << endl;

        while (file.getline(line, 500)) {

            // Skip the header
            if (isHeader) {
                isHeader = false;
                continue;
            }

            char busNumber[50], company[50], currentStop[50], route[300];

            int charIndex = 0;
            int field = 0;
            char currentField[300];

            int i = 0;

            // Parse CSV manually
            while (line[i] != '\0') {
                if (line[i] == ',' || line[i] == '\r' || line[i] == '\n') {

                    currentField[charIndex] = '\0';

                    // Trim spaces/quotes
                    int start = 0, end = charIndex - 1;
                    while (start < charIndex && (currentField[start] == '"' || currentField[start] == ' '))
                        start++;
                    while (end > 0 && (currentField[end] == '"' || currentField[end] == ' '))
                        end--;

                    char trimmed[300];
                    int j = 0;
                    for (int k = start; k <= end; k++)
                        trimmed[j++] = currentField[k];
                    trimmed[j] = '\0';
                    switch (field) {
                    case 0:
                        strncpy_s(busNumber, sizeof(busNumber), trimmed, _TRUNCATE);
                        break;
                    case 1:
                        strncpy_s(company, sizeof(company), trimmed, _TRUNCATE);
                        break;
                    case 2:
                        strncpy_s(currentStop, sizeof(currentStop), trimmed, _TRUNCATE);
                        break;
                    case 3:
                        strncpy_s(route, sizeof(route), trimmed, _TRUNCATE);
                        break;
                    }


                    field++;
                    charIndex = 0;
                }
                else {
                    currentField[charIndex++] = line[i];
                }
                i++;
            }

            // Handle last field (route)
            if (charIndex > 0 && field == 3) {
                currentField[charIndex] = '\0';
                strncpy_s(route, sizeof(route), currentField, _TRUNCATE);

                field++;
            }

            // Register bus only if all 4 fields exist
            if (field >= 4) {
                registerBus(busNumber, company, currentStop, route);
                count++;
            }
        }

        file.close();
        cout << "Loaded " << count << " buses from CSV." << endl;
    }


    // DISPLAY FUNCTIONS
    void displayCityNetwork() {
        cityGraph->display();
    }

    void displayAllStops()
    {
        cout << "\nALL REGISTERED BUS STOPS........" << endl;

        HashNode** table = stopRegistry->getTable();
        int tableSize = stopRegistry->getTableSize();

        bool found = false;
        int count = 0;

        for (int i = 0; i < tableSize; i++)
        {
            HashNode* current = table[i];
            while (current != NULL)
            {
                BusStop* stop = (BusStop*)current->value;
                count++;
                cout << "\n" << count << ". Stop ID: " << stop->stopId << endl;
                cout << "   Name: " << stop->name << endl;
                cout << "   Location: (" << stop->latitude << ", " << stop->longitude << ")" << endl;

                // Show queue size if available
                CircularQueue* queue = (CircularQueue*)stopQueues->search(stop->stopId);
                if (queue != NULL)
                {
                    cout << "   Passengers Waiting: " << queue->getSize() << endl;
                }

                found = true;
                current = current->next;
            }
        }

        if (!found)
        {
            cout << "No bus stops registered yet." << endl;
        }
        else
        {
            cout << "\n--- Total: " << count << " stops ---" << endl;
        }
    }



    void displayAllBuses()
    {
        cout << "\nALL REGISTERED BUSES..." << endl;

        HashNode** table = busRegistry->getTable();
        int tableSize = busRegistry->getTableSize();

        bool found = false;
        int count = 0;

        for (int i = 0; i < tableSize; i++)
        {
            HashNode* current = table[i];
            while (current != NULL)
            {
                Bus* bus = (Bus*)current->value;
                count++;
                cout << "\n" << count << ". Bus Number: " << bus->busNumber << endl;
                cout << "   Company: " << bus->company << endl;
                cout << "   Capacity: " << bus->capacity << " seats" << endl;
                cout << "   Current Passengers: " << bus->currentPassengers << endl;
                cout << "   Current Stop: " << bus->currentStop << endl;
                cout << "   Route: " << bus->route << endl;
                found = true;
                current = current->next;
            }
        }

        if (!found)
        {
            cout << "No buses registered yet." << endl;
        }
        else
        {
            cout << "\n--- Total: " << count << " buses ---" << endl;
        }
    }

  /*  void displayTransportMenu() {
        cout << "\n.............TRANSPORT MANAGEMENT ................." << endl;
        cout << "\n--- Bus & Stop Management ---" << endl;
        cout << "1.  Register Bus" << endl;
        cout << "2.  Add Bus Stop" << endl;
        cout << "3.  Add Stop to Bus Route" << endl;
        cout << "4.  Track Bus Location" << endl;
        cout << "5.  Show Bus Route" << endl;
        cout << "6.  Find Shortest Path" << endl;
        cout << "7.  Display All Buses" << endl;
        cout << "8.  Display All Stops" << endl;
        cout << "9.  Display City Network" << endl;
        cout << "\n--- Passenger Queue (Circular Queue) ---" << endl;
        cout << "10. Add Passenger to Stop Queue" << endl;
        cout << "11. Display Stop Queue" << endl;
        cout << "12. Simulate Bus Arrival (Board Passengers)" << endl;
        cout << "13. Simulate Multiple Passenger Arrivals" << endl;
        cout << "\n--- Travel History (Stack) ---" << endl;
        cout << "14. Display Travel History" << endl;
        cout << "15. Display Recent Trips" << endl;
        cout << "16. Undo Last Trip" << endl;
        cout << "17. Travel Statistics" << endl;
        cout << "18. Clear Travel History" << endl;
        cout << "\n--- CSV Operations ---" << endl;
        cout << "19. Load Stops from CSV" << endl;
        cout << "20. Load Buses from CSV" << endl;
        cout << "\n0.  Back to Main Menu" << endl;
        cout << "=====================================================" << endl;
        cout << "Enter choice: ";
    }*/

    ~TransportManager() {
        delete busRegistry;
        delete stopRegistry;
        delete stopQueues;
        delete travelHistory;
    }
};