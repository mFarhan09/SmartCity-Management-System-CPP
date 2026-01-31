#pragma once
#include <iostream>

using namespace std;

class Citizen
{
public:
    // Personal Information
    char cnic[20];              
    char name[100];
    int age;
    char gender[10];            
    char dateOfBirth[20];       
    char bloodType[5];          
    char contactNumber[20];
    char email[100];

    // Professional Information
    char occupation[50];
    char education[50];         
    int monthlyIncome;

    // Family Information
    char maritalStatus[20];     
    char familyId[20];          
    char relationToHead[50];    

    // Residential Information
    char sector[20];            
    char street[50];            
    char houseNumber[20];       
    char fullAddress[200];      
    double residenceLat;
    double residenceLon;
    char moveInDate[20];        

    // Additional Information
    char nationality[50];
    bool isAlive;               
    char emergencyContact[20];
    char emergencyRelation[50];

    Citizen()
    {
        cnic[0] = '\0';
        name[0] = '\0';
        age = 0;
        gender[0] = '\0';
        dateOfBirth[0] = '\0';
        bloodType[0] = '\0';
        contactNumber[0] = '\0';
        email[0] = '\0';
        occupation[0] = '\0';
        education[0] = '\0';
        monthlyIncome = 0;
        maritalStatus[0] = '\0';
        familyId[0] = '\0';
        relationToHead[0] = '\0';
        sector[0] = '\0';
        street[0] = '\0';
        houseNumber[0] = '\0';
        fullAddress[0] = '\0';
        residenceLat = 0.0;
        residenceLon = 0.0;
        moveInDate[0] = '\0';
        nationality[0] = '\0';
        isAlive = true;
        emergencyContact[0] = '\0';
        emergencyRelation[0] = '\0';
    }

    Citizen(const char* _cnic, const char* _name, int _age, const char* _gender,
        const char* _occupation, const char* _education, int _income,
        const char* _sector, const char* _maritalStatus)
    {
        // Copy basic info
        int i = 0;
        while (_cnic[i] != '\0' && i < 19) {
            cnic[i] = _cnic[i];
            i++;
        }
        cnic[i] = '\0';

        i = 0;
        while (_name[i] != '\0' && i < 99) {
            name[i] = _name[i];
            i++;
        }
        name[i] = '\0';

        age = _age;

        i = 0;
        while (_gender[i] != '\0' && i < 9) {
            gender[i] = _gender[i];
            i++;
        }
        gender[i] = '\0';

        i = 0;
        while (_occupation[i] != '\0' && i < 49) {
            occupation[i] = _occupation[i];
            i++;
        }
        occupation[i] = '\0';

        i = 0;
        while (_education[i] != '\0' && i < 49) {
            education[i] = _education[i];
            i++;
        }
        education[i] = '\0';

        monthlyIncome = _income;

        i = 0;
        while (_sector[i] != '\0' && i < 19) {
            sector[i] = _sector[i];
            i++;
        }
        sector[i] = '\0';

        i = 0;
        while (_maritalStatus[i] != '\0' && i < 19) {
            maritalStatus[i] = _maritalStatus[i];
            i++;
        }
        maritalStatus[i] = '\0';

        // Initialize other fields
        dateOfBirth[0] = '\0';
        bloodType[0] = '\0';
        contactNumber[0] = '\0';
        email[0] = '\0';
        familyId[0] = '\0';
        relationToHead[0] = '\0';
        street[0] = '\0';
        houseNumber[0] = '\0';
        fullAddress[0] = '\0';
        residenceLat = 0.0;
        residenceLon = 0.0;
        moveInDate[0] = '\0';
        nationality[0] = '\0';
        isAlive = true;
        emergencyContact[0] = '\0';
        emergencyRelation[0] = '\0';
    }

    void display()
    {
        cout << endl;
        cout << "         CITIZEN INFORMATION.........." << endl;
        cout  << endl;
        cout << "CNIC:            " << cnic << endl;
        cout << "Name:            " << name << endl;
        cout << "Age:             " << age << " years" << endl;
        cout << "Gender:          " << gender << endl;
        cout << "Blood Type:      " << bloodType << endl;
        cout << "Contact:         " << contactNumber << endl;
        cout << "Email:           " << email << endl;
        cout << "\n--- Professional Info ---" << endl;
        cout << "Occupation:      " << occupation << endl;
        cout << "Education:       " << education << endl;
        cout << "Monthly Income:  " << monthlyIncome << " PKR" << endl;
        cout << "\n--- Family Info ---" << endl;
        cout << "Marital Status:  " << maritalStatus << endl;
        cout << "Family ID:       " << familyId << endl;
        cout << "Relation:        " << relationToHead << endl;
        cout << "\n--- Residential Info ---" << endl;
        cout << "Address:         " << fullAddress << endl;
        cout << "Sector:          " << sector << endl;
        cout << "Street:          " << street << endl;
        cout << "House:           " << houseNumber << endl;
        cout << "Coordinates:     (" << residenceLat << ", " << residenceLon << ")" << endl;
        cout << "Move-in Date:    " << moveInDate << endl;
        cout << endl;
    }

    ~Citizen() {
       
    }
};