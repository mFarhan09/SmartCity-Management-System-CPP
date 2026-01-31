#pragma once
#include <iostream>
using namespace std;

struct Medicine
{
    char medicineName[100];
    char formula[200];
    double price;
    int stock;
    char pharmacyId[20];
    char pharmacyName[100];
    bool prescriptionRequired;

    Medicine() : price(0.0), stock(0), prescriptionRequired(false)
    {
        medicineName[0] = '\0';
        formula[0] = '\0';
        pharmacyId[0] = '\0';
        pharmacyName[0] = '\0';
    }

    Medicine(const char* name, const char* form, double p,
        int s, const char* pharmId, const char* pharmName)
        : price(p), stock(s), prescriptionRequired(false)
    {
        int i = 0;
        while (name[i] != '\0' && i < 99)
        {
            medicineName[i] = name[i];
            i++;
        }
        medicineName[i] = '\0';

        i = 0;
        while (form[i] != '\0' && i < 199)
        {
            formula[i] = form[i];
            i++;
        }
        formula[i] = '\0';

        i = 0;
        while (pharmId[i] != '\0' && i < 19)
        {
            pharmacyId[i] = pharmId[i];
            i++;
        }
        pharmacyId[i] = '\0';

        i = 0;
        while (pharmName[i] != '\0' && i < 99)
        {
            pharmacyName[i] = pharmName[i];
            i++;
        }
        pharmacyName[i] = '\0';
    }

    void display()
    {
        cout << "Medicine: " << medicineName << endl;
        cout << "Formula: " << formula << endl;
        cout << "Price: " << price << " PKR" << endl;
        cout << "Stock: " << stock << " units" << endl;
        cout << "Pharmacy: " << pharmacyName << endl;
        cout << "Prescription Required: " << (prescriptionRequired ? "Yes" : "No") << endl;
    }
};

struct Pharmacy
{
    char pharmacyId[20];
    char name[100];
    char sector[20];

    // Medicine info (single medicine per pharmacy for now)
    char medicineName[100];
    char formula[100];
    double price;

    char operatingHours[50];
    bool is24Hour;
    char contactNumber[20];

    Pharmacy() : price(0.0), is24Hour(false)
    {
        pharmacyId[0] = '\0';
        name[0] = '\0';
        sector[0] = '\0';
        medicineName[0] = '\0';
        formula[0] = '\0';
        operatingHours[0] = '\0';
        contactNumber[0] = '\0';
    }

    Pharmacy(const char* id, const char* n, const char* sec,
        const char* medName, const char* medFormula, double medPrice)
        : price(medPrice), is24Hour(false)
    {
        strncpy_s(pharmacyId, sizeof(pharmacyId), id, _TRUNCATE);
        strncpy_s(name, sizeof(name), n, _TRUNCATE);
        strncpy_s(sector, sizeof(sector), sec, _TRUNCATE);

        strncpy_s(medicineName, sizeof(medicineName), medName, _TRUNCATE);
        strncpy_s(formula, sizeof(formula), medFormula, _TRUNCATE);

        operatingHours[0] = '\0';
        contactNumber[0] = '\0';
    }

    ~Pharmacy()
    {
 
        pharmacyId[0] = '\0';
        name[0] = '\nu';
        sector[0] = '\0';
        medicineName[0] = '\0';
        formula[0] = '\0';
        operatingHours[0] = '\0';
        contactNumber[0] = '\0';

        price = 0.0;
        is24Hour = false;

       
    }


};