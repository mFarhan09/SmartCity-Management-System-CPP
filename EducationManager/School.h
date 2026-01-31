#pragma once

#include <iostream>
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/NaryTree.h"
using namespace std;

struct Class
{
    char classId[20];
    char className[50];
    char teacherId[20];
    LinkedList* students;
    int capacity;
    int currentStrength;

    Class() : students(NULL), capacity(0), currentStrength(0) {}

    Class(const char* id, const char* name, int cap)
        : capacity(cap), currentStrength(0)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            classId[i] = id[i];
            i++;
        }
        classId[i] = '\0';

        i = 0;
        while (name[i] != '\0' && i < 49)
        {
            className[i] = name[i];
            i++;
        }
        className[i] = '\0';

        teacherId[0] = '\0';
        students = new LinkedList();
    }
};

struct Department
{
    char deptId[20];
    char name[100];
    char headOfDept[100];
    int numClasses;

    Department() : numClasses(0) {}

    Department(const char* id, const char* n, const char* head)
        : numClasses(0)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19)
        {
            deptId[i] = id[i];
            i++;
        }
        deptId[i] = '\0';

        i = 0;
        while (n[i] != '\0' && i < 99)
        {
            name[i] = n[i];
            i++;
        }
        name[i] = '\0';

        i = 0;
        while (head[i] != '\0' && i < 99)
        {
            headOfDept[i] = head[i];
            i++;
        }
        headOfDept[i] = '\0';
    }
};

struct School
{
    char schoolId[20];
    char name[100];
    char sector[20];
    double rating;
    char** subjects;
    int numSubjects;
    NaryTree* organogram;
    double latitude;    // optional
    double longitude;   // optional
    int totalStudents;
    int totalTeachers;

    // Default constructor
    School() : subjects(nullptr), numSubjects(0), organogram(nullptr),
        latitude(0.0), longitude(0.0), totalStudents(0), totalTeachers(0) {
    }

    // Constructor for CSV input with subjects
    School(const char* id, const char* n, const char* sec,
        double rat, const char* subjList)
        : rating(rat), numSubjects(0), totalStudents(0), totalTeachers(0),
        latitude(0.0), longitude(0.0)
    {
        // Copy schoolId
        int i = 0;
        while (id[i] != '\0' && i < 19) { schoolId[i] = id[i]; i++; }
        schoolId[i] = '\0';

        // Copy name
        i = 0;
        while (n[i] != '\0' && i < 99) { name[i] = n[i]; i++; }
        name[i] = '\0';

        // Copy sector
        i = 0;
        while (sec[i] != '\0' && i < 19) { sector[i] = sec[i]; i++; }
        sector[i] = '\0';

        // Parse subjects from CSV string (comma-separated)
        subjects = new char* [10];  // max 10 subjects
        char subjCopy[256];
        strcpy_s(subjCopy, sizeof(subjCopy), subjList);  // safe copy

        char* context = nullptr;
        char* token = strtok_s(subjCopy, ",", &context);  // safe tokenization

        while (token != nullptr && numSubjects < 10)
        {
            // Trim leading spaces
            while (*token == ' ') token++;

            int len = strlen(token);
            subjects[numSubjects] = new char[len + 1];
            strcpy_s(subjects[numSubjects], len + 1, token);  // safe copy
            numSubjects++;

            token = strtok_s(nullptr, ",", &context);
        }


        // Initialize organogram
        organogram = new NaryTree();
    }



    void addSubject(const char* subject)
    {
        if (numSubjects < 10)
        {
            subjects[numSubjects] = new char[50];
            int i = 0;
            while (subject[i] != '\0' && i < 49)
            {
                subjects[numSubjects][i] = subject[i];
                i++;
            }
            subjects[numSubjects][i] = '\0';
            numSubjects++;
        }
    }

    bool hasSubject(const char* subject)
    {
        for (int i = 0; i < numSubjects; i++)
        {
            int j = 0;
            bool match = true;
            while (subjects[i][j] != '\0' || subject[j] != '\0')
            {
                if (subjects[i][j] != subject[j])
                {
                    match = false;
                    break;
                }
                j++;
            }
            if (match) return true;
        }
        return false;
    }

    void display()
    {
        cout << "\n=== SCHOOL DETAILS ===" << endl;
        cout << "ID: " << schoolId << endl;
        cout << "Name: " << name << endl;
        cout << "Sector: " << sector << endl;
        cout << "Rating: " << rating << "/5" << endl;
        cout << "Subjects: ";
        for (int i = 0; i < numSubjects; i++)
        {
            cout << subjects[i];
            if (i < numSubjects - 1) cout << ", ";
        }
        cout << endl;
        cout << "Total Students: " << totalStudents << endl;
        cout << "Total Teachers: " << totalTeachers << endl;
    }

        ~School() {
            if (organogram) {
                delete organogram;
            }
            for (int i = 0; i < numSubjects; i++) {
                delete[] subjects[i];
            }
            delete[] subjects;
        }
    
};
