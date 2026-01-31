#pragma once
#include <iostream>
#include "../DataStructures/Graph.h"
#include "../DataStructures/HashTable.h"
#include "../DataStructures/Stack.h"

using namespace std;

// Emergency Priority Levels
enum EmergencyLevel {
    CRITICAL = 1,    // Life-threatening
    HIGH = 2,        // Serious,
    MEDIUM = 3,      // Moderate,
    LOW = 4          // Non-urgent
};

struct EmergencyRequest {
    char requestId[20];
    char location[50];
    char destination[50];      // Usually hospital
    char patientName[100];
    char condition[200];
    EmergencyLevel priority;
    bool isActive;
    double estimatedDistance;

    EmergencyRequest() : priority(MEDIUM), isActive(true), estimatedDistance(0) {
        requestId[0] = '\0';
        location[0] = '\0';
        destination[0] = '\0';
        patientName[0] = '\0';
        condition[0] = '\0';
    }

    EmergencyRequest(const char* id, const char* loc, const char* dest,
        const char* patient, const char* cond, EmergencyLevel prio)
        : priority(prio), isActive(true), estimatedDistance(0) {

        int i = 0;
        while (id[i] != '\0' && i < 19) { requestId[i] = id[i]; i++; }
        requestId[i] = '\0';

        i = 0;
        while (loc[i] != '\0' && i < 49) { location[i] = loc[i]; i++; }
        location[i] = '\0';

        i = 0;
        while (dest[i] != '\0' && i < 49) { destination[i] = dest[i]; i++; }
        destination[i] = '\0';

        i = 0;
        while (patient[i] != '\0' && i < 99) { patientName[i] = patient[i]; i++; }
        patientName[i] = '\0';

        i = 0;
        while (cond[i] != '\0' && i < 199) { condition[i] = cond[i]; i++; }
        condition[i] = '\0';
    }

    void display() {
        const char* priorityStr;
        switch (priority) {
        case CRITICAL: priorityStr = "CRITICAL"; break;
        case HIGH: priorityStr = "HIGH"; break;
        case MEDIUM: priorityStr = "MEDIUM"; break;
        default: priorityStr = "LOW";
        }

        cout << "  ID: " << requestId << endl;
        cout << "  Patient: " << patientName << endl;
        cout << "  Condition: " << condition << endl;
        cout << "  Priority: " << priorityStr << endl;
        cout << "  From: " << location << " -> " << destination << endl;
        cout << "  Est. Distance: " << estimatedDistance << " km" << endl;
        cout << "  Status: " << (isActive ? "ACTIVE" : "COMPLETED") << endl;
    }
};

// Max Heap for Emergency Priority Queue (Critical emergencies first)
class EmergencyPriorityQueue {
private:
    EmergencyRequest** heap;
    int size;
    int capacity;

    void swap(int i, int j) {
        EmergencyRequest* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // Higher priority (lower number) should be at top
    bool hasHigherPriority(int i, int j) {
        return heap[i]->priority < heap[j]->priority;
    }

    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (hasHigherPriority(index, parent)) {
            swap(index, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int highest = index;

        if (left < size && hasHigherPriority(left, highest)) {
            highest = left;
        }
        if (right < size && hasHigherPriority(right, highest)) {
            highest = right;
        }

        if (highest != index) {
            swap(index, highest);
            heapifyDown(highest);
        }
    }

public:
    EmergencyPriorityQueue(int cap = 50) : size(0), capacity(cap) {
        heap = new EmergencyRequest * [capacity];
    }

    void insert(EmergencyRequest* request) {
        if (size >= capacity) {
            cout << "Emergency queue is full!" << endl;
            return;
        }
        heap[size] = request;
        heapifyUp(size);
        size++;
    }

    EmergencyRequest* extractHighestPriority() {
        if (size == 0) return NULL;

        EmergencyRequest* top = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return top;
    }

    EmergencyRequest* peek() {
        if (size == 0) return NULL;
        return heap[0];
    }

    bool isEmpty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    void display() {
        if (size == 0) {
            cout << "No active emergencies." << endl;
            return;
        }

        cout << "\n=== EMERGENCY QUEUE (" << size << " active) ===" << endl;
        for (int i = 0; i < size; i++) {
            cout << "\n--- Emergency " << (i + 1) << " ---" << endl;
            heap[i]->display();
        }
    }

    ~EmergencyPriorityQueue() {
        delete[] heap;
    }
};

class EmergencyRouter {
private:
    Graph* cityGraph;
    EmergencyPriorityQueue* emergencyQueue;
    HashTable* hospitalRegistry;
    Stack* completedEmergencies;
    int emergencyCount;

    void generateEmergencyId(char* buffer) {
        emergencyCount++;
        const char* prefix = "EMR";
        int i = 0;
        while (prefix[i] != '\0') {
            buffer[i] = prefix[i];
            i++;
        }

        int temp = emergencyCount;
        int digits[10];
        int numDigits = 0;

        while (temp > 0) {
            digits[numDigits++] = temp % 10;
            temp /= 10;
        }

        // Pad with zeros
        for (int j = numDigits; j < 4; j++) {
            buffer[i++] = '0';
        }

        for (int j = numDigits - 1; j >= 0; j--) {
            buffer[i++] = '0' + digits[j];
        }
        buffer[i] = '\0';
    }

public:
    EmergencyRouter(Graph* graph) : emergencyCount(0) {
        cityGraph = graph;
        emergencyQueue = new EmergencyPriorityQueue(100);
        hospitalRegistry = new HashTable(50);
        completedEmergencies = new Stack();
    }

    void registerHospitalForEmergency(const char* hospitalId, const char* name) {
        char* nameCopy = new char[100];
        int i = 0;
        while (name[i] != '\0' && i < 99) {
            nameCopy[i] = name[i];
            i++;
        }
        nameCopy[i] = '\0';
        hospitalRegistry->insert(hospitalId, (void*)nameCopy);
    }

    void createEmergencyRequest(const char* location, const char* patientName,
        const char* condition, int priorityLevel) {
        char emergencyId[20];
        generateEmergencyId(emergencyId);

        // Find nearest hospital using BFS
        const char* nearestHospital = cityGraph->findNearest(location, "Hospital");

        char destination[50];
        if (nearestHospital != NULL) {
            int i = 0;
            while (nearestHospital[i] != '\0' && i < 49) {
                destination[i] = nearestHospital[i];
                i++;
            }
            destination[i] = '\0';
        }
        else {
            // Default to PIMS if no hospital found
            const char* defaultHosp = "HOSP001";
            int i = 0;
            while (defaultHosp[i] != '\0') {
                destination[i] = defaultHosp[i];
                i++;
            }
            destination[i] = '\0';
        }

        EmergencyLevel priority;
        switch (priorityLevel) {
        case 1: priority = CRITICAL; break;
        case 2: priority = HIGH; break;
        case 3: priority = MEDIUM; break;
        default: priority = LOW;
        }

        EmergencyRequest* request = new EmergencyRequest(
            emergencyId, location, destination, patientName, condition, priority
        );

        emergencyQueue->insert(request);

        cout << "\n======================================" << endl;
        cout << "   EMERGENCY REQUEST CREATED" << endl;
        cout << "======================================" << endl;
        cout << "Emergency ID: " << emergencyId << endl;
        cout << "Patient: " << patientName << endl;
        cout << "Condition: " << condition << endl;
        cout << "Priority: " << priorityLevel << " (1=Critical, 4=Low)" << endl;
        cout << "Destination Hospital: " << destination << endl;
        cout << "======================================\n" << endl;
    }

    void dispatchNextEmergency() {
        if (emergencyQueue->isEmpty()) {
            cout << "No emergencies in queue." << endl;
            return;
        }

        EmergencyRequest* emergency = emergencyQueue->extractHighestPriority();

        cout << endl;
        cout << "   DISPATCHING EMERGENCY RESPONSE" << endl;
        cout << endl;
        emergency->display();

        cout << "\n--- CALCULATING OPTIMAL ROUTE ---" << endl;
        PathArray* path = cityGraph->dijkstra(emergency->location, emergency->destination);

        if (path->size > 0) {
            emergency->estimatedDistance = path->size * 2.0;  // Approximate
            cout << "Estimated distance: " << emergency->estimatedDistance << " km" << endl;
            cout << "Estimated time: " << (emergency->estimatedDistance / 60.0 * 60.0) << " minutes" << endl;
        }

        delete path;

        // Mark as completed and push to history
        emergency->isActive = false;
        completedEmergencies->push((void*)emergency);

        cout << "\nEmergency dispatched successfully!" << endl;
        cout << "======================================\n" << endl;
    }

    void planEmergencyRoute(const char* from, const char* to) {
        cout << "\n=== EMERGENCY ROUTE PLANNING ===" << endl;
        cout << "From: " << from << endl;
        cout << "To: " << to << endl;
        cout << "=================================" << endl;

        PathArray* path = cityGraph->dijkstra(from, to);

        if (path->size > 0) {
            cout << "\nRoute found with " << path->size << " stops." << endl;
            cout << "Estimated time for emergency vehicle: "
                << (path->size * 2.0 / 80.0 * 60.0) << " minutes" << endl;
            cout << "(Assuming 80 km/h emergency speed)" << endl;
        }
        else {
            cout << "No route found! Consider alternative paths." << endl;
        }

        delete path;
    }

    void displayActiveEmergencies() {
        emergencyQueue->display();
    }

    void displayEmergencyHistory() {
        if (completedEmergencies->isEmpty()) {
            cout << "No completed emergencies in history." << endl;
            return;
        }

        cout << "\n=== COMPLETED EMERGENCIES ===" << endl;

        Stack* tempStack = new Stack();
        int count = 1;

        while (!completedEmergencies->isEmpty()) {
            EmergencyRequest* req = (EmergencyRequest*)completedEmergencies->pop();
            cout << "\n--- Completed Emergency " << count++ << " ---" << endl;
            req->display();
            tempStack->push((void*)req);
        }

        // Restore
        while (!tempStack->isEmpty()) {
            completedEmergencies->push(tempStack->pop());
        }

        delete tempStack;
    }

    void getEmergencyStats() {
        cout << "\n=== EMERGENCY STATISTICS ===" << endl;
        cout << "Total emergencies created: " << emergencyCount << endl;
        cout << "Active emergencies: " << emergencyQueue->getSize() << endl;
        cout << "Completed emergencies: " << completedEmergencies->getSize() << endl;
    }

    ~EmergencyRouter() {
        delete emergencyQueue;
        delete hospitalRegistry;

        while (!completedEmergencies->isEmpty()) {
            EmergencyRequest* req = (EmergencyRequest*)completedEmergencies->pop();
            delete req;
        }
        delete completedEmergencies;
    }
};