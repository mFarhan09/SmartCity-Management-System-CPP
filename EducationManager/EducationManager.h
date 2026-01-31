#pragma once
#include <iostream>
#include "../DataStructures/HashTable.h"
#include "../DataStructures/MaxHeap.h"
#include "../DataStructures/NaryTree.h"
#include "../DataStructures/Graph.h"
#include "School.h"
#include "Teacher.h"
#include "Student.h"
using namespace std;

class EducationManager
{
private:
    HashTable* schoolRegistry;
    HashTable* teacherRegistry;
    MaxHeap* schoolRankings;
    Graph* cityGraph;


public:
    EducationManager(Graph* graph)
    {
        schoolRegistry = new HashTable(100);
        teacherRegistry = new HashTable(100);
        schoolRankings = new MaxHeap(100);
        cityGraph = graph;
    }

    void registerSchool(const char* id, const char* name, const char* sector,
        double rating, const char* subjects)
    {
        // Create a new School object with subjects instead of lat/lon
        School* school = new School(id, name, sector, rating, subjects);

        // Insert into registry and rankings
        schoolRegistry->insert(id, (void*)school);
        schoolRankings->insert(rating, (void*)school);

        // Initialize organogram
        TreeNode* root = new TreeNode(id, name, (void*)school);
        school->organogram->setRoot(root);

        // No lat/lon for cityGraph, optionally skip or use sector as placeholder
        cityGraph->addVertex(id, name,0.0,0.0); // Adjust addVertex to accept only id + name

        cout << "School registered: " << name << " (Rating: " << rating << ")" <<" location :" << sector <<" subjects:" <<subjects<< endl;
        
    }


    School* getSchool(const char* schoolId)
    {
        return (School*)schoolRegistry->search(schoolId);
    }


    void addSubjectToSchool(const char* schoolId, const char* subject)
    {
        School* school = (School*)schoolRegistry->search(schoolId);
        if (school == NULL)
        {
            cout << "School not found!" << endl;
            return;
        }

        school->addSubject(subject);
        cout << "Added subject " << subject << " to " << school->name << endl;
    }

    void addDepartment(const char* schoolId, const char* deptId,
        const char* deptName, const char* head)
    {
        School* school = (School*)schoolRegistry->search(schoolId);
        if (school == NULL)
        {
            cout << "School not found!" << endl;
            return;
        }

        Department* dept = new Department(deptId, deptName, head);
        TreeNode* deptNode = new TreeNode(deptId, deptName, (void*)dept);

        TreeNode* schoolNode = school->organogram->getRoot();
        if (schoolNode != NULL)
        {
            schoolNode->addChild(deptNode);
            cout << "Added department " << deptName << " to " << school->name << endl;
        }
    }

    void addClass(const char* schoolId, const char* deptId,
        const char* classId, const char* className, int capacity)
    {
        School* school = (School*)schoolRegistry->search(schoolId);
        if (school == NULL)
        {
            cout << "School not found!" << endl;
            return;
        }

        TreeNode* deptNode = school->organogram->search(deptId);
        if (deptNode == NULL)
        {
            cout << "Department not found!" << endl;
            return;
        }

        Class* classObj = new Class(classId, className, capacity);
        TreeNode* classNode = new TreeNode(classId, className, (void*)classObj);
        deptNode->addChild(classNode);

        Department* dept = (Department*)deptNode->data;
        dept->numClasses++;

        cout << "Added class " << className << " to department" << endl;
    }

    void registerTeacher(const char* id, const char* name, const char* qual,
        const char* spec, const char* schoolId, int salary, int exp)
    {
        Teacher* teacher = new Teacher(id, name, qual, spec, schoolId, salary, exp);
        teacherRegistry->insert(id, (void*)teacher);

        School* school = (School*)schoolRegistry->search(schoolId);
        if (school != NULL)
        {
            school->totalTeachers++;
        }

        cout << "Teacher registered: " << name << " (" << spec << ")" << endl;
    }

    void assignTeacherToClass(const char* schoolId, const char* classId,
        const char* teacherId)
    {
        School* school = (School*)schoolRegistry->search(schoolId);
        Teacher* teacher = (Teacher*)teacherRegistry->search(teacherId);

        if (school == NULL || teacher == NULL)
        {
            cout << "School or teacher not found!" << endl;
            return;
        }

        TreeNode* classNode = school->organogram->search(classId);
        if (classNode == NULL)
        {
            cout << "Class not found!" << endl;
            return;
        }

        Class* classObj = (Class*)classNode->data;
        int i = 0;
        while (teacherId[i] != '\0' && i < 19)
        {
            classObj->teacherId[i] = teacherId[i];
            i++;
        }
        classObj->teacherId[i] = '\0';

        teacher->isAvailable = false;

        cout << "Assigned " << teacher->name << " to " << classObj->className << endl;
    }

    void enrollStudent(const char* schoolId, const char* classId,
        const char* studentId, const char* name, int age, const char* section)
    {
        School* school = (School*)schoolRegistry->search(schoolId);
        if (school == NULL)
        {
            cout << "School not found!" << endl;
            return;
        }

        TreeNode* classNode = school->organogram->search(classId);
        if (classNode == NULL)
        {
            cout << "Class not found!" << endl;
            return;
        }

        Class* classObj = (Class*)classNode->data;
        if (classObj->currentStrength >= classObj->capacity)
        {
            cout << "Class is full!" << endl;
            return;
        }

        Student* student = new Student(studentId, name, age, section);
        classObj->students->insertAtEnd((void*)student);
        classObj->currentStrength++;
        school->totalStudents++;

        cout << "Enrolled " << name << " in " << classObj->className << endl;
    }

    void displayTopSchools(int count)
    {
        cout << "\n=== TOP " << count << " SCHOOLS ===" << endl;

        MaxHeap tempHeap(100);
        int extracted = 0;

        while (extracted < count && !schoolRankings->isEmpty())
        {
            HeapNode node = schoolRankings->extractMax();
            School* school = (School*)node.data;

            cout << extracted + 1 << ". " << school->name
                << " - Rating: " << school->rating << "/5" << endl;

            tempHeap.insert(node.priority, node.data);
            extracted++;
        }

        while (!tempHeap.isEmpty())
        {
            HeapNode node = tempHeap.extractMax();
            schoolRankings->insert(node.priority, node.data);
        }
    }

    void searchSchoolsBySubject(const char* subject)
    {
        cout << "\n=== SCHOOLS OFFERING " << subject << " ===" << endl;
        bool found = false;

        HashNode** table = schoolRegistry->getTable();
        int tableSize = schoolRegistry->getTableSize();

        for (int i = 0; i < tableSize; i++)
        {
            HashNode* current = table[i];
            while (current != NULL)
            {
                School* school = (School*)current->value;
                if (school->hasSubject(subject))
                {
                    cout << "- " << school->name << " (" << school->sector
                        << ") - Rating: " << school->rating << "/5" << endl;
                    found = true;
                }
                current = current->next;
            }
        }

        if (!found)
        {
            cout << "No schools found offering " << subject << endl;
        }
    }

    void loadSchoolsFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file " << filename << endl;
            return;
        }

        char line[1024];
        int count = 0;
        bool isHeader = true;

        cout << "\n=== Loading Schools from " << filename << " ===" << endl;

        while (file.getline(line, sizeof(line))) {
            if (isHeader) {
                isHeader = false;
                continue; // skip header row
            }

            char id[30] = { 0 }, name[100] = { 0 }, sector[50] = { 0 }, subjects[256] = { 0 };
            double rating = 0.0;

            char currentField[1024];
            int charIndex = 0;
            int field = 0;
            bool inQuotes = false;

            for (int i = 0; line[i] != '\0'; i++) {
                char c = line[i];

                if (c == '"') {
                    inQuotes = !inQuotes; // toggle in/out of quotes
                }
                else if (c == ',' && !inQuotes) {
                    // End of field
                    currentField[charIndex] = '\0';

                    // Trim leading/trailing spaces
                    int start = 0, end = charIndex - 1;
                    while (start <= end && currentField[start] == ' ') start++;
                    while (end >= start && currentField[end] == ' ') end--;

                    char trimmed[1024];
                    int j = 0;
                    for (int k = start; k <= end; k++)
                        trimmed[j++] = currentField[k];
                    trimmed[j] = '\0';

                    // Assign fields
                    switch (field) {
                    case 0: strncpy_s(id, trimmed, sizeof(id) - 1); break;
                    case 1: strncpy_s(name, trimmed, sizeof(name) - 1); break;
                    case 2: strncpy_s(sector, trimmed, sizeof(sector) - 1); break;
                    case 3: rating = atof(trimmed); break;
                    case 4: strncpy_s(subjects, trimmed, sizeof(subjects) - 1); break;
                    }

                    field++;
                    charIndex = 0;
                }
                else {
                    currentField[charIndex++] = c;
                }
            }

            // Handle last field if line doesn't end with comma
            if (charIndex > 0) {
                currentField[charIndex] = '\0';
                // Trim spaces
                int start = 0, end = charIndex - 1;
                while (start <= end && currentField[start] == ' ') start++;
                while (end >= start && currentField[end] == ' ') end--;

                char trimmed[1024];
                int j = 0;
                for (int k = start; k <= end; k++)
                    trimmed[j++] = currentField[k];
                trimmed[j] = '\0';

                if (field == 4) strncpy_s(subjects, trimmed, sizeof(subjects) - 1);
            }

            // Now we have all 5 fields; call registerSchool
            registerSchool(id, name, sector, rating, subjects);
            count++;
        }

        file.close();
        cout << "Loaded " << count << " schools from CSV." << endl;
    }


    void displaySchoolHierarchy(const char* schoolId)
    {
        School* school = (School*)schoolRegistry->search(schoolId);
        if (school == NULL)
        {
            cout << "School not found!" << endl;
            return;
        }

        cout << "\n=== " << school->name << " HIERARCHY ===" << endl;
        school->organogram->display();
    }

    void displaySchoolDetails(const char* schoolId)
    {
        School* school = (School*)schoolRegistry->search(schoolId);
        if (school == NULL)
        {
            cout << "School not found!" << endl;
            return;
        }

        school->display();
    }

    void displayTeacherDetails(const char* teacherId)
    {
        Teacher* teacher = (Teacher*)teacherRegistry->search(teacherId);
        if (teacher == NULL)
        {
            cout << "Teacher not found!" << endl;
            return;
        }

        teacher->display();
    }

    void displayAllSchools()
    {
        cout << "\nALL REGISTERED SCHOOLS....." << endl;

        HashNode** table = schoolRegistry->getTable();
        int tableSize = schoolRegistry->getTableSize();

        bool found = false;
        int count = 0;

        for (int i = 0; i < tableSize; i++)
        {
            HashNode* current = table[i];
            while (current != NULL)
            {
                School* school = (School*)current->value;
                count++;
                cout << "\n" << count << ". " << school->name << " (" << school->schoolId << ")" << endl;
                cout << "   Sector: " << school->sector << endl;
                cout << "   Rating: " << school->rating << "/5.0" << endl;
                cout << "   Students: " << school->totalStudents << endl;
                cout << "   Teachers: " << school->totalTeachers << endl;
                cout << "   Subjects: " << school->subjects << endl;
                found = true;
                current = current->next;
            }
        }

        if (!found)
        {
            cout << "No schools registered yet." << endl;
        }
        else
        {
            cout << "\n--- Total: " << count << " schools ---" << endl;
        }
    }

    ~EducationManager()
    {
        delete schoolRegistry;
        delete teacherRegistry;
        delete schoolRankings;
    }
};
