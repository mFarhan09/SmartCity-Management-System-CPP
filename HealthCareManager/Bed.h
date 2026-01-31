#pragma once
#include <iostream>
using namespace std;

struct Bed
{
    char bedId[20];
    char bedNumber[10];
    char wardId[20];
    bool isOccupied;
    char patientId[20];
    char admissionDate[20];
    char assignedDoctor[20];

    Bed() : isOccupied(false)
    {
        bedId[0] = '\0';
        bedNumber[0] = '\0';
        wardId[0] = '\0';
        patientId[0] = '\0';
        admissionDate[0] = '\0';
        assignedDoctor[0] = '\0';
    }

    Bed(const char* id, const char* num, const char* ward)
        : isOccupied(false)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            bedId[i] = id[i];
            i++;
        }
        bedId[i] = '\0';

        i = 0;
        while (num[i] != '\0' && i < 9)
        {
            bedNumber[i] = num[i];
            i++;
        }
        bedNumber[i] = '\0';

        i = 0;
        while (ward[i] != '\0' && i < 19)
        {
            wardId[i] = ward[i];
            i++;
        }
        wardId[i] = '\0';

        patientId[0] = '\0';
        admissionDate[0] = '\0';
        assignedDoctor[0] = '\0';
    }
};