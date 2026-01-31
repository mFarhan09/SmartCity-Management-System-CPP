#pragma once

#include <iostream>
#include "../DataStructures/HashTable.h"
#include "../DataStructures/NaryTree.h"
#include "../DataStructures/Stack.h"
#include "../Demographics/Demographics.h"
#include "Citizen.h"
#include "House.h"
#include "FamilyTree.h"
#include "Survey.h"
#include "../DataStructures/Graph.h"
#include "sector.h"

using namespace std;

class PopulationManager
{
private:

    NaryTree* housingHierarchy;
    HashTable* citizenRegistry;
    HashTable* familyRegistry;
    Demographics* demographics;
    SurveyManager* surveyManager;
    Stack* surveyHistory;

    Graph* cityGraph;
    SectorManager* sectorSystem;


    // City statistics
    int totalPopulation;
    int totalHouses;
    int totalFamilies;
    char cityName[100];

public:
    PopulationManager(Graph* graph)
    {
        housingHierarchy = new NaryTree();
        TreeNode* cityRoot = new TreeNode("CITY-ROOT", "Islamabad", NULL);
        housingHierarchy->setRoot(cityRoot); 

        // Initialize registries
        citizenRegistry = new HashTable(10000);  // Large capacity for citizens
        familyRegistry = new HashTable(1000);    // For families

        // Initialize systems
        demographics = new Demographics();
        surveyManager = new SurveyManager();
        surveyHistory = new Stack();

        // Set city graph
        cityGraph = graph;

        // Initialize statistics
        totalPopulation = 0;
        totalHouses = 0;
        totalFamilies = 0;

        int i = 0;
        const char* defaultName = "Islamabad";
        while (defaultName[i] != '\0' && i < 99)
        {
            cityName[i] = defaultName[i];
            i++;
        }
        cityName[i] = '\0';

        cout << "Population Management System initialized" << endl;
        cout << "- Residential Hierarchy: Ready" << endl;
        cout << "- Citizen Registry: Ready" << endl;
        cout << "- Family Registry: Ready" << endl;
        cout << "- Demographics: Ready" << endl;
        cout << "- Survey System: Ready" << endl;
    }

    // RESIDENTIAL HIERARCHY FUNCTION
    void addSector(const char* sectorName)
    {
        TreeNode* cityRoot = housingHierarchy->getRoot();
        TreeNode* sectorNode = new TreeNode(sectorName, sectorName, NULL);

        cityRoot->addChild(sectorNode);

        cout << "Sector '" << sectorName << "' added to city" << endl;
    }

    void addStreet(const char* sector, const char* streetName)
    {
        TreeNode* sectorNode = housingHierarchy->search(sector);

        if (sectorNode == NULL)
        {
            cout << "Sector '" << sector << "' not found!" << endl;
            cout << "Please add sector first" << endl;
            return;
        }

        // Create street ID
        char streetId[100];
        int idx = 0, i = 0;
        while (sector[i] != '\0' && idx < 90) {
            streetId[idx++] = sector[i++];
        }
        streetId[idx++] = '-';
        i = 0;
        while (streetName[i] != '\0' && idx < 99) {
            if (streetName[i] != ' ') {
                streetId[idx++] = streetName[i];
            }
            i++;
        }
        streetId[idx] = '\0';

        TreeNode* streetNode = new TreeNode(streetId, streetName, NULL);
        sectorNode->addChild(streetNode);

        cout << "Street '" << streetName << "' added to " << sector << endl;
    }

    void addHouse(const char* sector, const char* street, House* house)
    {
        // Find street node
        char streetId[100];
        int idx = 0, i = 0;
        while (sector[i] != '\0' && idx < 90) {
            streetId[idx++] = sector[i++];
        }
        streetId[idx++] = '-';
        i = 0;
        while (street[i] != '\0' && idx < 99) {
            if (street[i] != ' ') {
                streetId[idx++] = street[i];
            }
            i++;
        }
        streetId[idx] = '\0';

        TreeNode* streetNode = housingHierarchy->search(streetId);

        if (streetNode == NULL)
        {
            cout << "Street '" << street << "' not found in " << sector << "!" << endl;
            cout << "Please add street first" << endl;
            return;
        }

        // Create house node
        TreeNode* houseNode = new TreeNode(house->houseId, house->houseNumber, (void*)house);
        streetNode->addChild(houseNode);

        // Add house to city graph
        cityGraph->addVertex(house->houseId, house->houseNumber,
            house->latitude, house->longitude);

        totalHouses++;

        cout << "House '" << house->houseNumber << "' added to " << street
            << ", " << sector << endl;
        cout << "Total houses: " << totalHouses << endl;
    }

    // FAMILY MANAGEMENT
    void registerFamily(const char* familyId, const char* houseId,
        const char* headCNIC, const char* headName,
        const char* headRelation, int headAge, const char* headGender)
    {
        // Create family tree with head
        FamilyTreeNode* head = new FamilyTreeNode(headCNIC, headName, headRelation,
            headAge, headGender);
        FamilyTree* family = new FamilyTree(familyId, head);

        // Add to family registry
        familyRegistry->insert(familyId, (void*)family);

        // Link house to family
        TreeNode* houseNode = housingHierarchy->search(houseId);
        if (houseNode != NULL && houseNode->data != NULL)
        {
            House* house = (House*)houseNode->data;
            int i = 0;
            while (familyId[i] != '\0' && i < 19) {
                house->familyId[i] = familyId[i];
                i++;
            }
            house->familyId[i] = '\0';
            house->familyTree = head;
            house->numResidents = 1;
        }

        totalFamilies++;

        cout << "\n*** Family Registered ***" << endl;
        cout << "Family ID: " << familyId << endl;
        cout << "Head: " << headName << " (" << headCNIC << ")" << endl;
        cout << "Total families: " << totalFamilies << endl;
    }

    void addFamilyMember(const char* familyId, const char* cnic, const char* name,
        const char* relation, int age, const char* gender,
        const char* parentCNIC = NULL)
    {
        FamilyTree* family = (FamilyTree*)familyRegistry->search(familyId);

        if (family == NULL)
        {
            cout << "Family " << familyId << " not found!" << endl;
            return;
        }

        FamilyTreeNode* newMember = new FamilyTreeNode(cnic, name, relation, age, gender);

        // Determine relationship type
        bool isSpouse = false;
        int i = 0;
        while (relation[i] != '\0') {
            if ((relation[i] == 'S' || relation[i] == 's') &&
                (relation[i + 1] == 'p' || relation[i + 1] == 'P')) {
                isSpouse = true;
                break;
            }
            i++;
        }

        if (isSpouse)
        {
            family->addSpouse(newMember);
        }
        else if (parentCNIC != NULL)
        {
            // Find parent and add as child
            FamilyTreeNode* parent = family->findMember(parentCNIC);
            if (parent != NULL)
            {
                parent->addChild(newMember);
                family->totalMembers++;
            }
        }
        else
        {
            family->addChild(newMember);
        }

        cout << "Family member '" << name << "' added to family " << familyId << endl;
    }

    void displayFamilyTree(const char* familyId)
    {
        FamilyTree* family = (FamilyTree*)familyRegistry->search(familyId);

        if (family == NULL)
        {
            cout << "Family " << familyId << " not found!" << endl;
            return;
        }

        family->displayTree();
    }

    void listFamilyMembers(const char* familyId)
    {
        FamilyTree* family = (FamilyTree*)familyRegistry->search(familyId);

        if (family == NULL)
        {
            cout << "Family " << familyId << " not found!" << endl;
            return;
        }

        family->listAllMembers();
    }

    // CITIZEN REGISTRATION
    void registerCitizen(const char* cnic, const char* name, int age,
        const char* gender, const char* occupation,
        const char* education, int income, const char* sector,
        const char* maritalStatus)
    {
        // Check if citizen already exists
        Citizen* existing = (Citizen*)citizenRegistry->search(cnic);
        if (existing != NULL)
        {
            cout << "Error: Citizen with CNIC " << cnic << " already registered!" << endl;
            return;
        }

        // Create new citizen
        Citizen* citizen = new Citizen(cnic, name, age, gender, occupation,
            education, income, sector, maritalStatus);

        // Add to registry
        citizenRegistry->insert(cnic, (void*)citizen);

        // Update demographics
        demographics->updateAllDemographics(age, gender, occupation, education,
            income, sector, maritalStatus);

        // Increment population
        totalPopulation++;

        cout << "\n*** Citizen Registered Successfully ***" << endl;
        cout << "Name: " << name << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Total Population: " << totalPopulation << endl;
    }

    void registerCitizenComplete(const char* cnic, const char* name, int age,
        const char* gender, const char* dob, const char* bloodType,
        const char* contact, const char* email,
        const char* occupation, const char* education, int income,
        const char* maritalStatus, const char* sector,
        const char* street, const char* houseNumber,
        double lat, double lon)
    {
        // Check if citizen already exists
        Citizen* existing = (Citizen*)citizenRegistry->search(cnic);
        if (existing != NULL)
        {
            cout << "Error: Citizen with CNIC " << cnic << " already registered!" << endl;
            return;
        }

        // Create new citizen with full details
        Citizen* citizen = new Citizen(cnic, name, age, gender, occupation,
            education, income, sector, maritalStatus);

        // Copy additional fields
        int i = 0;
        while (dob[i] != '\0' && i < 19) {
            citizen->dateOfBirth[i] = dob[i];
            i++;
        }
        citizen->dateOfBirth[i] = '\0';

        i = 0;
        while (bloodType[i] != '\0' && i < 4) {
            citizen->bloodType[i] = bloodType[i];
            i++;
        }
        citizen->bloodType[i] = '\0';

        i = 0;
        while (contact[i] != '\0' && i < 19) {
            citizen->contactNumber[i] = contact[i];
            i++;
        }
        citizen->contactNumber[i] = '\0';

        i = 0;
        while (email[i] != '\0' && i < 99) {
            citizen->email[i] = email[i];
            i++;
        }
        citizen->email[i] = '\0';

        i = 0;
        while (street[i] != '\0' && i < 49) {
            citizen->street[i] = street[i];
            i++;
        }
        citizen->street[i] = '\0';

        i = 0;
        while (houseNumber[i] != '\0' && i < 19) {
            citizen->houseNumber[i] = houseNumber[i];
            i++;
        }
        citizen->houseNumber[i] = '\0';

        citizen->residenceLat = lat;
        citizen->residenceLon = lon;

        // Build full address
        char fullAddr[200];
        int idx = 0;

        // Add house number
        i = 0;
        while (houseNumber[i] != '\0' && idx < 199) {
            fullAddr[idx++] = houseNumber[i++];
        }
        fullAddr[idx++] = ',';
        fullAddr[idx++] = ' ';

        // Add street
        i = 0;
        while (street[i] != '\0' && idx < 199) {
            fullAddr[idx++] = street[i++];
        }
        fullAddr[idx++] = ',';
        fullAddr[idx++] = ' ';

        // Add sector
        i = 0;
        while (sector[i] != '\0' && idx < 199) {
            fullAddr[idx++] = sector[i++];
        }
        fullAddr[idx] = '\0';

        i = 0;
        while (fullAddr[i] != '\0' && i < 199) {
            citizen->fullAddress[i] = fullAddr[i];
            i++;
        }
        citizen->fullAddress[i] = '\0';

        // Add to registry
        citizenRegistry->insert(cnic, (void*)citizen);

        // Update demographics
        demographics->updateAllDemographics(age, gender, occupation, education,
            income, sector, maritalStatus);

        // Add residence to city graph
        char locationId[50];
        idx = 0;
        i = 0;
        while (sector[i] != '\0' && idx < 49) {
            locationId[idx++] = sector[i++];
        }
        locationId[idx++] = '-';
        i = 0;
        while (street[i] != '\0' && idx < 49) {
            if (street[i] != ' ') {
                locationId[idx++] = street[i];
            }
            i++;
        }
        locationId[idx++] = '-';
        i = 0;
        while (houseNumber[i] != '\0' && idx < 49) {
            if (houseNumber[i] != ' ' && houseNumber[i] != '#') {
                locationId[idx++] = houseNumber[i];
            }
            i++;
        }
        locationId[idx] = '\0';

        cityGraph->addVertex(locationId, fullAddr, lat, lon);

        // Increment population
        totalPopulation++;

        cout << "\n*** Citizen Registered Successfully ***" << endl;
        cout << "Name: " << name << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Address: " << fullAddr << endl;
        cout << "Total Population: " << totalPopulation << endl;
    }

    // CITIZEN LOOKUP
    void searchCitizen(const char* cnic)
    {
        Citizen* citizen = (Citizen*)citizenRegistry->search(cnic);

        if (citizen == NULL)
        {
            cout << "\nCitizen with CNIC " << cnic << " not found!" << endl;
            return;
        }

        citizen->display();
    }

    void updateCitizenInfo(const char* cnic, const char* field, const char* newValue)
    {
        Citizen* citizen = (Citizen*)citizenRegistry->search(cnic);

        if (citizen == NULL)
        {
            cout << "\nCitizen with CNIC " << cnic << " not found!" << endl;
            return;
        }

        // Simple field update (can be expanded)
        cout << "Updating " << field << " for " << citizen->name << "..." << endl;
        cout << "Note: Full update functionality to be implemented" << endl;
    }

    void removeCitizen(const char* cnic)
    {
        Citizen* citizen = (Citizen*)citizenRegistry->search(cnic);

        if (citizen == NULL)
        {
            cout << "\nCitizen with CNIC " << cnic << " not found!" << endl;
            return;
        }

        cout << "\nRemoving citizen: " << citizen->name << endl;

        // Update demographics (decrement)
        demographics->removeAllDemographics(citizen->age, citizen->gender,
            citizen->occupation, citizen->education,
            citizen->monthlyIncome, citizen->sector,
            citizen->maritalStatus);

        // Remove from registry
        citizenRegistry->remove(cnic);

        // Decrement population
        totalPopulation--;

        cout << "Citizen removed successfully" << endl;
        cout << "Total Population: " << totalPopulation << endl;

        delete citizen;
    }

    // DEMOGRAPHIC QUERIES
    void displayPopulationStatistics()
    {
        cout << endl;
        cout << "     POPULATION STATISTICS" << endl;
        cout << endl;
        cout << "City: " << cityName << endl;
        cout << "Total Population: " << totalPopulation << endl;
        cout << "\nMale:   " << demographics->getGenderCount("Male") << endl;
        cout << "Female: " << demographics->getGenderCount("Female") << endl;
        cout << "\nEmployed:   " << (totalPopulation - demographics->getOccupationCount("Unemployed")) << endl;
        cout << "Unemployed: " << demographics->getOccupationCount("Unemployed") << endl;
        cout << "Students:   " << demographics->getOccupationCount("Student") << endl;
        cout << endl;
    }

    void displayAgeDistribution()
    {
        demographics->displayAgeDistribution();
    }

    void displayGenderDistribution()
    {
        demographics->displayGenderDistribution();
    }

    void displayOccupationStats()
    {
        demographics->displayOccupationStats();
    }

    void displayEducationStats()
    {
        demographics->displayEducationStats();
    }

    void displayIncomeStats()
    {
        demographics->displayIncomeStats();
    }

    void displaySectorPopulation()
    {
        demographics->displaySectorPopulation();
    }

    void displayMaritalStats()
    {
        demographics->displayMaritalStats();
    }

    void displayCompleteDemographics()
    {
        demographics->displayAllDemographics();
    }

    // POPULATION QUERIES
    int getTotalPopulation()
    {
        return totalPopulation;
    }

    int getSectorPopulation(const char* sector)
    {
        return demographics->getSectorCount(sector);
    }

    int getOccupationCount(const char* occupation)
    {
        return demographics->getOccupationCount(occupation);
    }

    void listAllCitizens()
    {
        cout << "\nALL REGISTERED CITIZENS...." << endl;

        HashNode** table = citizenRegistry->getTable();
        int tableSize = citizenRegistry->getTableSize();

        bool found = false;
        int count = 0;

        for (int i = 0; i < tableSize; i++)
        {
            HashNode* current = table[i];
            while (current != NULL)
            {
                Citizen* citizen = (Citizen*)current->value;
                count++;
                cout << "\n" << count << ". " << citizen->name << " (" << citizen->cnic << ")" << endl;
                cout << "   Age: " << citizen->age << " | Gender: " << citizen->gender << endl;
                cout << "   Sector: " << citizen->sector << endl;
                cout << "   Occupation: " << citizen->occupation << endl;
                cout << "   Education: " << citizen->education << endl;
                cout << "   Marital Status: " << citizen->maritalStatus << endl;
                found = true;
                current = current->next;
            }
        }

        if (!found)
        {
            cout << "No citizens registered yet." << endl;
        }
        else
        {
            cout << "\n--- Total: " << count << " citizens ---" << endl;
        }
    }

    // ANALYTICS
    void generatePopulationReport()
    {
        cout << endl;
        cout << "           COMPLETE POPULATION REPORT" << endl;
        cout << endl;

        displayPopulationStatistics();
        demographics->displayAllDemographics();

        cout << endl;
        cout << "               END OF REPORT" << endl;
        cout << endl;
    }

    float getAverageAge()
    {
        if (totalPopulation == 0) return 0.0;

        // Calculate based on age distribution
        int totalAge = 0;
        totalAge += demographics->getAgeCount("0-10") * 5;
        totalAge += demographics->getAgeCount("11-20") * 15;
        totalAge += demographics->getAgeCount("21-30") * 25;
        totalAge += demographics->getAgeCount("31-40") * 35;
        totalAge += demographics->getAgeCount("41-50") * 45;
        totalAge += demographics->getAgeCount("51-60") * 55;
        totalAge += demographics->getAgeCount("61+") * 70;

        return (float)totalAge / totalPopulation;
    }

    float getEmploymentRate()
    {
        if (totalPopulation == 0) return 0.0;

        int unemployed = demographics->getOccupationCount("Unemployed");
        int employed = totalPopulation - unemployed;

        return (float)employed * 100 / totalPopulation;
    }

    float getLiteracyRate()
    {
        if (totalPopulation == 0) return 0.0;

        int noEducation = demographics->getEducationCount("None");
        int literate = totalPopulation - noEducation;

        return (float)literate * 100 / totalPopulation;
    }

    void displayCityAnalytics()
    {
        cout << endl;
        cout << "         CITY ANALYTICS" << endl;
        cout << endl;
        cout << "Total Population:    " << totalPopulation << endl;
        cout << "Total Families:      " << totalFamilies << endl;
        cout << "Total Houses:        " << totalHouses << endl;
        cout << "Average Age:         " << getAverageAge() << " years" << endl;
        cout << "Employment Rate:     " << getEmploymentRate() << "%" << endl;
        cout << "Literacy Rate:       " << getLiteracyRate() << "%" << endl;

        if (totalHouses > 0) {
            float avgResidents = (float)totalPopulation / totalHouses;
            cout << "Avg Residents/House: " << avgResidents << endl;
        }

        cout << endl;
    }

    double calculatePopulationDensity()
    {
        // Simplified: Population per house
        if (totalHouses == 0) return 0.0;
        return (double)totalPopulation / totalHouses;
    }

    // SURVEY FUNCTIONS
    void createSurvey(const char* surveyId, const char* title, const char* description)
    {
        surveyManager->createSurvey(surveyId, title, description);
    }

    void addSurveyQuestion(const char* surveyId, const char* question)
    {
        surveyManager->addQuestionToSurvey(surveyId, question);
    }

    void setSurveyTarget(const char* surveyId, const char* sector, int minAge, int maxAge)
    {
        surveyManager->setSurveyTarget(surveyId, sector, minAge, maxAge);
    }

    void submitSurveyResponse(const char* cnic, const char* surveyId,
        int* answers, int numAnswers, const char* feedback)
    {
        surveyManager->submitResponse(cnic, surveyId, answers, numAnswers, feedback);
    }

    void displaySurvey(const char* surveyId)
    {
        surveyManager->displaySurvey(surveyId);
    }

    void closeSurvey(const char* surveyId)
    {
        surveyManager->closeSurvey(surveyId);
    }

    void loadCitizensFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file " << filename  << endl;
            return;
        }

        char line[700];
        int count = 0;
        bool isHeader = true;

        cout << "\n=== Loading Citizens from " << filename << endl;

        while (file.getline(line, sizeof(line))) {
            if (isHeader) {
                isHeader = false;
                continue; // skip CSV header
            }

            char cnic[30] = { 0 }, name[100] = { 0 }, sector[50] = { 0 }, street[50] = { 0 }, houseNumber[20] = { 0 }, occupation[50] = { 0 };
            int age = 0;

            char gender[10] = "Unknown", education[50] = "None", maritalStatus[20] = "Single";
            char dob[20] = "", bloodType[5] = "", contact[20] = "", email[100] = "";
            double income = 0.0, lat = 0.0, lon = 0.0; // Use 0.0 for Lat/Lon

            char currentField[250];
            int charIndex = 0;
            int field = 0;
            bool inQuotes = false;

            int i = 0;
            while (line[i] != '\0') {
                char c = line[i];

                if (c == '"') {
                    inQuotes = !inQuotes;
                }
                else if ((c == ',' && !inQuotes) || line[i + 1] == '\0' || c == '\n' || c == '\r') {

                    // Handle the last character of the line if it wasn't a comma
                    if ((line[i + 1] == '\0' || c == '\n' || c == '\r') && c != ',') {
                        currentField[charIndex++] = c;
                    }

                    currentField[charIndex] = '\0';

                    int start = 0, end = charIndex - 1;
                    while (start <= end && (currentField[start] == '"' || currentField[start] == ' ')) start++;
                    while (end >= start && (currentField[end] == '"' || currentField[end] == ' ')) end--;

                    char trimmed[250];
                    int j = 0;
                    for (int k = start; k <= end; k++) trimmed[j++] = currentField[k];
                    trimmed[j] = '\0';

                    switch (field) {
                    case 0: strncpy_s(cnic, sizeof(cnic), trimmed, _TRUNCATE); break;
                    case 1: strncpy_s(name, sizeof(name), trimmed, _TRUNCATE); break;
                    case 2: age = atoi(trimmed); break;
                    case 3: strncpy_s(sector, sizeof(sector), trimmed, _TRUNCATE); break;
                    case 4: strncpy_s(street, sizeof(street), trimmed, _TRUNCATE); break;
                    case 5: strncpy_s(houseNumber, sizeof(houseNumber), trimmed, _TRUNCATE); break; // HouseNo is read into houseNumber
                    case 6: strncpy_s(occupation, sizeof(occupation), trimmed, _TRUNCATE); break;
                    }

                    field++;
                    charIndex = 0;
                }
                else {
                    currentField[charIndex++] = c;
                }

                i++;
            }

            if (field >= 7) {

                
                registerCitizenComplete(
                    cnic, name, age, gender, dob, bloodType, contact, email,
                    occupation, education, (int)income, maritalStatus,
                    sector, street, houseNumber, lat, lon
                );

                count++;
            }
            else if (field > 0) {
                cout << "Warning: Skipped incomplete record (Fields found: " << field << ", Expected: 7): " << line << endl;
            }
        }

        file.close();
        cout << "Loaded " << count << " citizens from CSV. ?" << endl;
    }
    void loadFamiliesFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file " << filename << endl;
            return;
        }

        char line[512];
        int count = 0;
        bool isHeader = true;

        cout << "\n=== Loading Families from " << filename << " ===" << endl;

        while (file.getline(line, sizeof(line))) {
            if (isHeader) {
                isHeader = false;
                continue;  // skip CSV header
            }

            // Fields for registerFamily
            char familyId[50], houseId[50], headCNIC[30], headName[100], headRelation[50], headGender[20];
            int headAge = 0;

            char currentField[150];
            int charIndex = 0;
            int field = 0;

            int i = 0;
            while (line[i] != '\0') {
                if (line[i] == ',' || line[i] == '\n' || line[i] == '\r') {
                    currentField[charIndex] = '\0';

                    // Trim spaces and quotes
                    int start = 0, end = charIndex - 1;
                    while (start <= end && (currentField[start] == '"' || currentField[start] == ' '))
                        start++;
                    while (end >= start && (currentField[end] == '"' || currentField[end] == ' '))
                        end--;

                    char trimmed[150];
                    int j = 0;
                    for (int k = start; k <= end; k++)
                        trimmed[j++] = currentField[k];
                    trimmed[j] = '\0';

                    switch (field) {
                    case 0: strncpy_s(familyId, sizeof(familyId), trimmed, _TRUNCATE); break;
                    case 1: strncpy_s(houseId, sizeof(houseId), trimmed, _TRUNCATE); break;
                    case 2: strncpy_s(headCNIC, sizeof(headCNIC), trimmed, _TRUNCATE); break;
                    case 3: strncpy_s(headName, sizeof(headName), trimmed, _TRUNCATE); break;
                    case 4: strncpy_s(headRelation, sizeof(headRelation), trimmed, _TRUNCATE); break;
                    case 5: headAge = atoi(trimmed); break;
                    case 6: strncpy_s(headGender, sizeof(headGender), trimmed, _TRUNCATE); break;
                    }

                    field++;
                    charIndex = 0;
                }
                else {
                    currentField[charIndex++] = line[i];
                }
                i++;
            }

            // Handle last field if line did not end with comma
            if (field == 6 && charIndex > 0) {
                currentField[charIndex] = '\0';
                strncpy_s(headGender, sizeof(headGender), currentField, _TRUNCATE);
                field++;
            }

            if (field >= 7) {
                registerFamily(familyId, houseId, headCNIC, headName, headRelation, headAge, headGender);
                count++;
            }
        }

        file.close();
        cout << "Loaded " << count << " families from CSV." << endl;
    }
;


    void displayActiveSurveys()
    {
        surveyManager->displayActiveSurveys();
    }

    // HOUSING HIERARCHY DISPLAY
    void displayResidentialHierarchy()
    {
        cout << endl;
        cout << "    RESIDENTIAL HIERARCHY" << endl;
        cout << endl;
        housingHierarchy->display();
        cout << endl;
    }

    void displayHouseDetails(const char* houseId)
    {
        TreeNode* houseNode = housingHierarchy->search(houseId);

        if (houseNode == NULL || houseNode->data == NULL)
        {
            cout << "House " << houseId << " not found!" << endl;
            return;
        }

        House* house = (House*)houseNode->data;
        house->display();

        // Display family if exists
        if (house->familyTree != NULL)
        {
            FamilyTree* family = (FamilyTree*)familyRegistry->search(house->familyId);
            if (family != NULL)
            {
                family->displayTree();
            }
        }
    }

    // SYSTEM ACCESS
    Demographics* getDemographics()
    {
        return demographics;
    }

    HashTable* getCitizenRegistry()
    {
        return citizenRegistry;
    }

    HashTable* getFamilyRegistry()
    {
        return familyRegistry;
    }

    NaryTree* getHousingHierarchy()
    {
        return housingHierarchy;
    }

    SurveyManager* getSurveyManager()
    {
        return surveyManager;
    }

    // DESTRUCTOR
    ~PopulationManager()
    {
        delete housingHierarchy;
        delete citizenRegistry;
        delete familyRegistry;
        delete demographics;
        delete surveyManager;
        delete surveyHistory;

        cout << "Population Management System shut down" << endl;
    }
};