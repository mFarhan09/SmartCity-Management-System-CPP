#pragma once
#include <iostream>
using namespace std;

struct Student
{
    char studentId[20];
    char name[100];
    int age;
    char section[20];
    int* grades;
    int numGrades;

    Student() : age(0), grades(NULL), numGrades(0)
    {
        studentId[0] = '\0';
        name[0] = '\0';
        section[0] = '\0';
    }

    Student(const char* id, const char* n, int a, const char* sec)
        : age(a), grades(NULL), numGrades(0)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            studentId[i] = id[i];
            i++;
        }
        studentId[i] = '\0';

        i = 0;
        while (n[i] != '\0' && i < 99)
        {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (sec[i] != '\0' && i < 19)
        {
            section[i] = sec[i];
            i++;
        }
        section[i] = '\0';
    }

    void display()
    {
        cout << studentId << " - " << name << " (Age: " << age
            << ", Section: " << section << ")" << endl;
    }
};
