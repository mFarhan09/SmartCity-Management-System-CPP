#pragma once
#include <iostream>
using namespace std;


struct Teacher
{
    char teacherId[20];
    char name[100];
    char qualification[100];
    char specialization[50];
    char schoolId[20];
    int salary;
    int experience;
    bool isAvailable;

    Teacher() : salary(0), experience(0), isAvailable(true)
    {
        teacherId[0] = '\0';
        name[0] = '\0';
        qualification[0] = '\0';
        specialization[0] = '\0';
        schoolId[0] = '\0';
    }

    Teacher(const char* id, const char* n, const char* qual,
        const char* spec, const char* school, int sal, int exp)
        : salary(sal), experience(exp), isAvailable(true)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            teacherId[i] = id[i];
            i++;
        }
        teacherId[i] = '\0';

        i = 0;
        while (n[i] != '\0' && i < 99)
        {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (qual[i] != '\0' && i < 99)
        {
            qualification[i] = qual[i];
            i++;
        }
        qualification[i] = '\0';

        i = 0;
        while (spec[i] != '\0' && i < 49)
        {
            specialization[i] = spec[i];
            i++;
        }
        specialization[i] = '\0';

        i = 0;
        while (school[i] != '\0' && i < 19)
        {
            schoolId[i] = school[i];
            i++;
        }
        schoolId[i] = '\0';
    }

    void display()
    {
        cout << "\n=== TEACHER DETAILS ===" << endl;
        cout << "ID: " << teacherId << endl;
        cout << "Name: " << name << endl;
        cout << "Qualification: " << qualification << endl;
        cout << "Specialization: " << specialization << endl;
        cout << "School: " << schoolId << endl;
        cout << "Salary: " << salary << " PKR" << endl;
        cout << "Experience: " << experience << " years" << endl;
        cout << "Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};
