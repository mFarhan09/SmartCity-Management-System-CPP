#pragma once
#include <iostream>
using namespace std;

struct Doctor
{
    char doctorId[20];
    char name[100];
    char specialization[50];
    char hospitalId[20];
    bool isAvailable;
    int experience;
    int consultationFee;
    char contactNumber[20];

    Doctor() : isAvailable(true), experience(0), consultationFee(0)
    {
        doctorId[0] = '\0';
        name[0] = '\0';
        specialization[0] = '\0';
        hospitalId[0] = '\0';
        contactNumber[0] = '\0';
    }

    Doctor(const char* id, const char* n, const char* spec,
        const char* hospital, int exp, int fee)
        : isAvailable(true), experience(exp), consultationFee(fee)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            doctorId[i] = id[i];
            i++;
        }
        doctorId[i] = '\0';

        i = 0;
        while (n[i] != '\0' && i < 99)
        {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (spec[i] != '\0' && i < 49)
        {
            specialization[i] = spec[i];
            i++;
        }
        specialization[i] = '\0';

        i = 0;
        while (hospital[i] != '\0' && i < 19)
        {
            hospitalId[i] = hospital[i];
            i++;
        }
        hospitalId[i] = '\0';

        contactNumber[0] = '\0';
    }

    void display()
    {
        cout << "\nDOCTOR DETAILS...." << endl;
        cout << "ID: " << doctorId << endl;
        cout << "Name: " << name << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "Hospital: " << hospitalId << endl;
        cout << "Experience: " << experience << " years" << endl;
        cout << "Consultation Fee: " << consultationFee << " PKR" << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};