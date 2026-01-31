#pragma once
#include <iostream>
using namespace std;

struct Patient
{
    char patientId[20];
    char cnic[20];
    char name[100];
    int age;
    char gender[10];
    char bloodType[5];
    char allergies[200];
    char chronicDiseases[200];
    char emergencyContact[20];
    char contactNumber[20];

    char currentHospital[20];
    bool isAdmitted;
    char assignedDoctor[20];
    char assignedBed[20];

    char currentCondition[200];
    int severity;

    Patient() : age(0), isAdmitted(false), severity(0)
    {
        patientId[0] = '\0';
        cnic[0] = '\0';
        name[0] = '\0';
        gender[0] = '\0';
        bloodType[0] = '\0';
        allergies[0] = '\0';
        chronicDiseases[0] = '\0';
        emergencyContact[0] = '\0';
        contactNumber[0] = '\0';
        currentHospital[0] = '\0';
        assignedDoctor[0] = '\0';
        assignedBed[0] = '\0';
        currentCondition[0] = '\0';
    }

    Patient(const char* id, const char* cnicNum, const char* n,
        int a, const char* gen, const char* blood)
        : age(a), isAdmitted(false), severity(0)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            patientId[i] = id[i];
            i++;
        }
        patientId[i] = '\0';

        i = 0;
        while (cnicNum[i] != '\0' && i < 19)
        {
            cnic[i] = cnicNum[i];
            i++;
        }
        cnic[i] = '\0';

        i = 0;
        while (n[i] != '\0' && i < 99)
        {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (gen[i] != '\0' && i < 9)
        {
            gender[i] = gen[i];
            i++;
        }
        gender[i] = '\0';

        i = 0;
        while (blood[i] != '\0' && i < 4)
        {
            bloodType[i] = blood[i];
            i++;
        }
        bloodType[i] = '\0';

        allergies[0] = '\0';
        chronicDiseases[0] = '\0';
        emergencyContact[0] = '\0';
        contactNumber[0] = '\0';
        currentHospital[0] = '\0';
        assignedDoctor[0] = '\0';
        assignedBed[0] = '\0';
        currentCondition[0] = '\0';
    }

    void display()
    {
        cout << "\n=== PATIENT DETAILS ===" << endl;
        cout << "ID: " << patientId << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Blood Type: " << bloodType << endl;
        cout << "Allergies: " << allergies << endl;
        cout << "Chronic Diseases: " << chronicDiseases << endl;

        if (isAdmitted)
        {
            cout << "\nCURRENTLY ADMITTED:" << endl;
            cout << "Hospital: " << currentHospital << endl;
            cout << "Bed: " << assignedBed << endl;
            cout << "Doctor: " << assignedDoctor << endl;
            cout << "Condition: " << currentCondition << endl;
            cout << "Severity: " << severity << "/10" << endl;
        }
    }
};