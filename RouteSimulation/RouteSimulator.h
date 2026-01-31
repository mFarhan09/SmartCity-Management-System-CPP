#pragma once
#include <iostream>
#include "../DataStructures/Graph.h"
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/Stack.h"

using namespace std;

enum VehicleType {
    CAR,
    BUS,
    AMBULANCE,
    MOTORCYCLE,
    TRUCK,
    PEDESTRIAN
};

struct SimulatedVehicle {
    char vehicleId[20];
    char name[50];
    VehicleType type;
    char currentLocation[50];
    char destination[50];
    double speed;  // km/h
    bool isMoving;
    LinkedList* routePath;
    int currentPathIndex;
    double totalDistance;
    double distanceCovered;

    SimulatedVehicle() : type(CAR), speed(0), isMoving(false), routePath(NULL),
        currentPathIndex(0), totalDistance(0), distanceCovered(0) {
        vehicleId[0] = '\0';
        name[0] = '\0';
        currentLocation[0] = '\0';
        destination[0] = '\0';
    }

    SimulatedVehicle(const char* id, const char* n, VehicleType t, double spd)
        : type(t), speed(spd), isMoving(false), currentPathIndex(0),
        totalDistance(0), distanceCovered(0) {
        int i = 0;
        while (id[i] != '\0' && i < 19) { vehicleId[i] = id[i]; i++; }
        vehicleId[i] = '\0';
        i = 0;
        while (n[i] != '\0' && i < 49) { name[i] = n[i]; i++; }
        name[i] = '\0';
        currentLocation[0] = '\0';
        destination[0] = '\0';
        routePath = new LinkedList();
    }

    const char* getTypeString() {
        switch (type) {
        case CAR: return "Car";
        case BUS: return "Bus";
        case AMBULANCE: return "Ambulance";
        case MOTORCYCLE: return "Motorcycle";
        case TRUCK: return "Truck";
        case PEDESTRIAN: return "Pedestrian";
        default: return "Unknown";
        }
    }

    double getDefaultSpeed() {
        switch (type) {
        case CAR: return 60.0;
        case BUS: return 40.0;
        case AMBULANCE: return 80.0;
        case MOTORCYCLE: return 50.0;
        case TRUCK: return 35.0;
        case PEDESTRIAN: return 5.0;
        default: return 30.0;
        }
    }

    void display() {
        cout << "\n=== VEHICLE STATUS ===" << endl;
        cout << "ID: " << vehicleId << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << getTypeString() << endl;
        cout << "Speed: " << speed << " km/h" << endl;
        cout << "Status: " << (isMoving ? "Moving" : "Stopped") << endl;
        cout << "Current Location: " << (currentLocation[0] != '\0' ? currentLocation : "Not Set") << endl;
        cout << "Destination: " << (destination[0] != '\0' ? destination : "Not Set") << endl;
        if (totalDistance > 0) {
            cout << "Progress: " << distanceCovered << "/" << totalDistance << " km ("
                << (distanceCovered * 100 / totalDistance) << "%)" << endl;
        }
    }
};

struct RouteSegment {
    char fromId[50];
    char toId[50];
    double distance;
    int estimatedTimeMinutes;

    RouteSegment(const char* from, const char* to, double dist, int time)
        : distance(dist), estimatedTimeMinutes(time) {
        int i = 0;
        while (from[i] != '\0' && i < 49) { fromId[i] = from[i]; i++; }
        fromId[i] = '\0';
        i = 0;
        while (to[i] != '\0' && i < 49) { toId[i] = to[i]; i++; }
        toId[i] = '\0';
    }
};

class RouteSimulator {
private:
    Graph* cityGraph;
    HashTable* vehicleRegistry;
    LinkedList* activeVehicles;
    Stack* simulationHistory;
    int simulationStep;
    bool isSimulationRunning;

    void copyString(char* dest, const char* src, int maxLen) {
        int i = 0;
        while (src[i] != '\0' && i < maxLen - 1) {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

public:
    RouteSimulator(Graph* graph) : simulationStep(0), isSimulationRunning(false) {
        cityGraph = graph;
        vehicleRegistry = new HashTable(100);
        activeVehicles = new LinkedList();
        simulationHistory = new Stack();
        cout << "Route Simulator: Initialized" << endl;
    }

    // VEHICLE MANAGEMENT
    void createVehicle(const char* vehicleId, const char* name, int type) {
        VehicleType vType;
        switch (type) {
        case 1: vType = CAR; break;
        case 2: vType = BUS; break;
        case 3: vType = AMBULANCE; break;
        case 4: vType = MOTORCYCLE; break;
        case 5: vType = TRUCK; break;
        case 6: vType = PEDESTRIAN; break;
        default: vType = CAR;
        }

        SimulatedVehicle* vehicle = new SimulatedVehicle(vehicleId, name, vType, 0);
        vehicle->speed = vehicle->getDefaultSpeed();
        vehicleRegistry->insert(vehicleId, (void*)vehicle);

        cout << "Vehicle created: " << name << " (" << vehicle->getTypeString() << ")" << endl;
    }

    void setVehicleLocation(const char* vehicleId, const char* locationId) {
        SimulatedVehicle* vehicle = (SimulatedVehicle*)vehicleRegistry->search(vehicleId);
        if (vehicle == NULL) {
            cout << "Vehicle " << vehicleId << " not found!" << endl;
            return;
        }

        copyString(vehicle->currentLocation, locationId, 50);
        cout << "Vehicle " << vehicleId << " location set to " << locationId << endl;
    }

    void setVehicleDestination(const char* vehicleId, const char* destinationId) {
        SimulatedVehicle* vehicle = (SimulatedVehicle*)vehicleRegistry->search(vehicleId);
        if (vehicle == NULL) {
            cout << "Vehicle " << vehicleId << " not found!" << endl;
            return;
        }

        copyString(vehicle->destination, destinationId, 50);
        cout << "Vehicle " << vehicleId << " destination set to " << destinationId << endl;
    }

    void setVehicleSpeed(const char* vehicleId, double speed) {
        SimulatedVehicle* vehicle = (SimulatedVehicle*)vehicleRegistry->search(vehicleId);
        if (vehicle == NULL) {
            cout << "Vehicle " << vehicleId << " not found!" << endl;
            return;
        }

        vehicle->speed = speed;
        cout << "Vehicle " << vehicleId << " speed set to " << speed << " km/h" << endl;
    }

    // ROUTE SIMULATION
    void planRoute(const char* vehicleId) {
        SimulatedVehicle* vehicle = (SimulatedVehicle*)vehicleRegistry->search(vehicleId);
        if (vehicle == NULL) {
            cout << "Vehicle " << vehicleId << " not found!" << endl;
            return;
        }

        if (vehicle->currentLocation[0] == '\0' || vehicle->destination[0] == '\0') {
            cout << "Please set both current location and destination first!" << endl;
            return;
        }

        cout << "\n=== PLANNING ROUTE FOR " << vehicle->name << " ===" << endl;
        cout << "From: " << vehicle->currentLocation << endl;
        cout << "To: " << vehicle->destination << endl;
        cout << "Vehicle Type: " << vehicle->getTypeString() << endl;
        cout << "Speed: " << vehicle->speed << " km/h" << endl;
        cout << "----------------------------------------" << endl;

        // Use Dijkstra to find the route
        cityGraph->dijkstra(vehicle->currentLocation, vehicle->destination);
    }

    void simulateRoute(const char* vehicleId) {
        SimulatedVehicle* vehicle = (SimulatedVehicle*)vehicleRegistry->search(vehicleId);
        if (vehicle == NULL) {
            cout << "Vehicle " << vehicleId << " not found!" << endl;
            return;
        }

        if (vehicle->currentLocation[0] == '\0' || vehicle->destination[0] == '\0') {
            cout << "Please set both current location and destination first!" << endl;
            return;
        }

        cout  << endl;
        cout << "   REAL-TIME ROUTE SIMULATION" << endl;
        cout  << endl;
        cout << "Vehicle: " << vehicle->name << " (" << vehicle->getTypeString() << ")" << endl;
        cout << "Speed: " << vehicle->speed << " km/h" << endl;
        cout << "--------------------------------------------" << endl;

        vehicle->isMoving = true;
        activeVehicles->insertAtEnd((void*)vehicle);

        // Get the path using Dijkstra
        PathArray* path = cityGraph->dijkstra(vehicle->currentLocation, vehicle->destination);

        if (path->size < 2) {
            cout << "Could not find valid route!" << endl;
            vehicle->isMoving = false;
            delete path;
            return;
        }

        cout << "\n--- SIMULATION START ---" << endl;

        double totalDist = 0;
        double totalTimeMinutes = 0;

        for (int i = 0; i < path->size - 1; i++) {
            const char* from = path->paths[i];
            const char* to = path->paths[i + 1];

            // Estimate segment distance 
            double segmentDist = 2.5;  // Approximate 2.5 km per segment
            double segmentTime = (segmentDist / vehicle->speed) * 60;  // minutes

            totalDist += segmentDist;
            totalTimeMinutes += segmentTime;

            cout << "\nStep " << (i + 1) << ":" << endl;
            cout << "  Moving from " << from << " to " << to << endl;
            cout << "  Distance: " << segmentDist << " km" << endl;
            cout << "  Time: " << segmentTime << " minutes" << endl;
            cout << "  Status: En route..." << endl;

            // Update current location
            copyString(vehicle->currentLocation, to, 50);
            vehicle->distanceCovered = totalDist;
        }

        vehicle->totalDistance = totalDist;
        vehicle->isMoving = false;

        cout << "\n--- SIMULATION COMPLETE ---" << endl;
        cout << "Total Distance: " << totalDist << " km" << endl;
        cout << "Total Time: " << totalTimeMinutes << " minutes" << endl;
        cout << "Final Location: " << vehicle->currentLocation << endl;
        cout <<   endl;

        delete path;
    }

    void simulateEmergencyRoute(const char* fromLocation, const char* toLocation) {
        cout << endl;
        cout << "   EMERGENCY VEHICLE SIMULATION" << endl;
        cout << endl;
        cout << "Emergency Type: Ambulance" << endl;
        cout << "Priority: CRITICAL" << endl;
        cout << "From: " << fromLocation << endl;
        cout << "To: " << toLocation << endl;
        cout << "--------------------------------------------" << endl;

        // Create temporary ambulance
        SimulatedVehicle ambulance("EMR-001", "Emergency Ambulance", AMBULANCE, 80.0);
        copyString(ambulance.currentLocation, fromLocation, 50);
        copyString(ambulance.destination, toLocation, 50);

        cout << "\n*** EMERGENCY LIGHTS ACTIVATED ***" << endl;
        cout << "Speed: 80 km/h (Emergency Mode)" << endl;
        cout << "\nCalculating fastest route..." << endl;

        PathArray* path = cityGraph->dijkstra(fromLocation, toLocation);

        if (path->size >= 2) {
            double totalDist = (path->size - 1) * 2.5;
            double totalTimeMinutes = (totalDist / 80.0) * 60;

            cout << "\n*** ROUTE FOUND ***" << endl;
            cout << "Estimated Distance: " << totalDist << " km" << endl;
            cout << "Estimated Time: " << totalTimeMinutes << " minutes" << endl;
            cout << "*** DISPATCHING EMERGENCY VEHICLE ***" << endl;
        }

        cout << endl;
        delete path;
    }

    
    // TRAFFIC SIMULATION
    void simulateTraffic(const char* locationId, int vehicleCount) {
        cout << "\n=== TRAFFIC SIMULATION AT " << locationId << " ===" << endl;
        cout << "Simulating " << vehicleCount << " vehicles..." << endl;

        int cars = vehicleCount * 60 / 100;
        int bikes = vehicleCount * 25 / 100;
        int buses = vehicleCount * 10 / 100;
        int trucks = vehicleCount * 5 / 100;

        cout << "\nTraffic Composition:" << endl;
        cout << "  Cars: " << cars << " (60%)" << endl;
        cout << "  Motorcycles: " << bikes << " (25%)" << endl;
        cout << "  Buses: " << buses << " (10%)" << endl;
        cout << "  Trucks: " << trucks << " (5%)" << endl;

        // Calculate congestion level
        int congestion = 0;
        if (vehicleCount < 20) congestion = 1;
        else if (vehicleCount < 50) congestion = 2;
        else if (vehicleCount < 100) congestion = 3;
        else if (vehicleCount < 200) congestion = 4;
        else congestion = 5;

        cout << "\nCongestion Level: ";
        for (int i = 0; i < congestion; i++) cout << "?";
        for (int i = congestion; i < 5; i++) cout << "?";
        cout << " (" << congestion << "/5)" << endl;

        const char* congestionStatus;
        switch (congestion) {
        case 1: congestionStatus = "Free Flow"; break;
        case 2: congestionStatus = "Light Traffic"; break;
        case 3: congestionStatus = "Moderate Traffic"; break;
        case 4: congestionStatus = "Heavy Traffic"; break;
        default: congestionStatus = "Severe Congestion";
        }
        cout << "Status: " << congestionStatus << endl;

        // Estimate delay
        double delayFactor = 1.0 + (congestion - 1) * 0.25;
        cout << "Estimated Delay Factor: " << delayFactor << "x normal travel time" << endl;
    }

    // DISPLAY FUNCTIONS
    void displayVehicleStatus(const char* vehicleId) {
        SimulatedVehicle* vehicle = (SimulatedVehicle*)vehicleRegistry->search(vehicleId);
        if (vehicle == NULL) {
            cout << "Vehicle " << vehicleId << " not found!" << endl;
            return;
        }
        vehicle->display();
    }

    void displayActiveVehicles() {
        cout << "\n=== ACTIVE VEHICLES ===" << endl;
        if (activeVehicles->getSize() == 0) {
            cout << "No vehicles currently active." << endl;
            return;
        }

        ListNode* current = activeVehicles->getHead();
        while (current != NULL) {
            SimulatedVehicle* v = (SimulatedVehicle*)current->data;
            cout << v->vehicleId << " | " << v->name << " | " << v->getTypeString()
                << " | " << (v->isMoving ? "Moving" : "Stopped") << endl;
            current = current->next;
        }
    }

    void displayAllVehicles() {
        cout << "\n=== ALL REGISTERED VEHICLES ===" << endl;
        vehicleRegistry->display();
    }

    ~RouteSimulator() {
        delete vehicleRegistry;
        delete activeVehicles;
        delete simulationHistory;
        cout << "Route Simulator: Shut down" << endl;
    }
};