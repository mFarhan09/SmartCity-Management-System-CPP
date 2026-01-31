#pragma once
#include <iostream>
#include "../DataStructures/Stack.h"
using namespace std;

struct TravelRecord {
    char fromLocation[50];
    char toLocation[50];
    char busNumber[20];
    char timestamp[30];
    double distance;

    TravelRecord() : distance(0) {
        fromLocation[0] = '\0';
        toLocation[0] = '\0';
        busNumber[0] = '\0';
        timestamp[0] = '\0';
    }

    TravelRecord(const char* from, const char* to, const char* bus,
        const char* time, double dist) : distance(dist) {
        int i = 0;
        while (from[i] != '\0' && i < 49) {
            fromLocation[i] = from[i];
            i++;
        }
        fromLocation[i] = '\0';

        i = 0;
        while (to[i] != '\0' && i < 49) {
            toLocation[i] = to[i];
            i++;
        }
        toLocation[i] = '\0';

        i = 0;
        while (bus[i] != '\0' && i < 19) {
            busNumber[i] = bus[i];
            i++;
        }
        busNumber[i] = '\0';

        i = 0;
        while (time[i] != '\0' && i < 29) {
            timestamp[i] = time[i];
            i++;
        }
        timestamp[i] = '\0';
    }

    void display() {
        cout << "  " << fromLocation << " -> " << toLocation
            << " | Bus: " << busNumber
            << " | Distance: " << distance << " km"
            << " | Time: " << timestamp << endl;
    }
};

class TravelHistory {
private:
    Stack* historyStack;
    int totalTrips;
    double totalDistance;

public:
    TravelHistory() : totalTrips(0), totalDistance(0) {
        historyStack = new Stack();
    }

    void recordTrip(const char* from, const char* to, const char* busNumber,
        const char* timestamp, double distance) {
        TravelRecord* record = new TravelRecord(from, to, busNumber, timestamp, distance);
        historyStack->push((void*)record);
        totalTrips++;
        totalDistance += distance;

        cout << "Trip recorded: " << from << " -> " << to << endl;
    }

    TravelRecord* getLastTrip() {
        if (historyStack->isEmpty()) {
            cout << "No travel history available." << endl;
            return NULL;
        }
        return (TravelRecord*)historyStack->peek();
    }

    TravelRecord* undoLastTrip() {
        if (historyStack->isEmpty()) {
            cout << "No trips to undo." << endl;
            return NULL;
        }

        TravelRecord* record = (TravelRecord*)historyStack->pop();
        totalTrips--;
        totalDistance -= record->distance;

        cout << "Trip removed from history: " << record->fromLocation
            << " -> " << record->toLocation << endl;

        return record;
    }

    void displayHistory() {
        if (historyStack->isEmpty()) {
            cout << "\n=== TRAVEL HISTORY ===" << endl;
            cout << "No travel history available." << endl;
            return;
        }

        cout << "\n=== TRAVEL HISTORY (Most Recent First) ===" << endl;
        cout << "Total Trips: " << totalTrips << endl;
        cout << "Total Distance: " << totalDistance << " km" << endl;
        cout << "-------------------------------------------" << endl;

        // We need to temporarily store and restore to display all
        Stack* tempStack = new Stack();
        int count = 1;

        while (!historyStack->isEmpty()) {
            TravelRecord* record = (TravelRecord*)historyStack->pop();
            cout << count++ << ". ";
            record->display();
            tempStack->push((void*)record);
        }

        // Restore the stack
        while (!tempStack->isEmpty()) {
            historyStack->push(tempStack->pop());
        }

        delete tempStack;
    }

    void displayLastNTrips(int n) {
        if (historyStack->isEmpty()) {
            cout << "No travel history available." << endl;
            return;
        }

        cout << "\n=== LAST " << n << " TRIPS ===" << endl;

        Stack* tempStack = new Stack();
        int count = 0;

        while (!historyStack->isEmpty() && count < n) {
            TravelRecord* record = (TravelRecord*)historyStack->pop();
            cout << (count + 1) << ". ";
            record->display();
            tempStack->push((void*)record);
            count++;
        }

        // Restore the stack
        while (!tempStack->isEmpty()) {
            historyStack->push(tempStack->pop());
        }

        delete tempStack;
    }

    int getTotalTrips() {
        return totalTrips;
    }

    double getTotalDistance() {
        return totalDistance;
    }

    void clearHistory() {
        while (!historyStack->isEmpty()) {
            TravelRecord* record = (TravelRecord*)historyStack->pop();
            delete record;
        }
        totalTrips = 0;
        totalDistance = 0;
        cout << "Travel history cleared." << endl;
    }

    bool isEmpty() {
        return historyStack->isEmpty();
    }

    ~TravelHistory() {
        clearHistory();
        delete historyStack;
    }
};