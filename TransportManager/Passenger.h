#pragma once
#pragma once
#include <iostream>
using namespace std;

struct Passenger {
    char passengerId[20];
    char name[100];
    char sourceStop[20];
    char destinationStop[20];
    char contactNumber[15];
    bool hasBoarded;

    Passenger() : hasBoarded(false) {
        passengerId[0] = '\0';
        name[0] = '\0';
        sourceStop[0] = '\0';
        destinationStop[0] = '\0';
        contactNumber[0] = '\0';
    }

    Passenger(const char* id, const char* n, const char* source,
        const char* dest, const char* contact = "") : hasBoarded(false) {
        int i = 0;
        while (id[i] != '\0' && i < 19) {
            passengerId[i] = id[i];
            i++;
        }
        passengerId[i] = '\0';

        i = 0;
        while (n[i] != '\0' && i < 99) {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (source[i] != '\0' && i < 19) {
            sourceStop[i] = source[i];
            i++;
        }
        sourceStop[i] = '\0';

        i = 0;
        while (dest[i] != '\0' && i < 19) {
            destinationStop[i] = dest[i];
            i++;
        }
        destinationStop[i] = '\0';

        i = 0;
        while (contact[i] != '\0' && i < 14) {
            contactNumber[i] = contact[i];
            i++;
        }
        contactNumber[i] = '\0';
    }

    void display() {
        cout << "  [" << passengerId << "] " << name;
        cout << " | From: " << sourceStop << " -> To: " << destinationStop;
        if (contactNumber[0] != '\0') {
            cout << " | Contact: " << contactNumber;
        }
        cout << " | Status: " << (hasBoarded ? "Boarded" : "Waiting") << endl;
    }

    void displayShort() {
        cout << name << " (" << passengerId << ") -> " << destinationStop << endl;
    }
};