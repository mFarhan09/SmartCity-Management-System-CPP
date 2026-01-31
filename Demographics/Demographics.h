#pragma once
#pragma once

#include <iostream>
#include "../DataStructures/HashTable.h"

using namespace std;

class Demographics
{
private:
  
    HashTable* ageDistribution;        
    HashTable* genderDistribution;     
    HashTable* occupationStats;        
    HashTable* educationStats;         
    HashTable* incomeStats;            
    HashTable* sectorPopulation;       
    HashTable* maritalStats;           

    // get count
    int* getOrCreateCount(HashTable* table, const char* key)
    {
        int* count = (int*)table->search(key);
        if (count == NULL)
        {
            count = new int(0);
            table->insert(key, (void*)count);
        }
        return count;
    }

    // Helper function to get count 
    int getCount(HashTable* table, const char* key)
    {
        int* count = (int*)table->search(key);
        return count ? *count : 0;
    }

public:
    Demographics()
    {
        ageDistribution = new HashTable(50);
        genderDistribution = new HashTable(10);
        occupationStats = new HashTable(100);
        educationStats = new HashTable(50);
        incomeStats = new HashTable(50);
        sectorPopulation = new HashTable(100);
        maritalStats = new HashTable(10);

        cout << "Demographics system initialized" << endl;
    }

    // HELPER FUNCTIONS - Categorization
    const char* getAgeRange(int age)
    {
        if (age >= 0 && age <= 10) return "0-10";
        if (age >= 11 && age <= 20) return "11-20";
        if (age >= 21 && age <= 30) return "21-30";
        if (age >= 31 && age <= 40) return "31-40";
        if (age >= 41 && age <= 50) return "41-50";
        if (age >= 51 && age <= 60) return "51-60";
        return "61+";
    }

    const char* getIncomeRange(int income)
    {
        if (income < 20000) return "Below-20000";
        if (income < 50000) return "20000-50000";
        if (income < 100000) return "50000-100000";
        if (income < 200000) return "100000-200000";
        return "Above-200000";
    }

    // INCREMENT OPERATIONS (Adding citizens)
    void incrementAge(int age)
    {
        const char* range = getAgeRange(age);
        int* count = getOrCreateCount(ageDistribution, range);
        (*count)++;
    }

    void incrementGender(const char* gender)
    {
        int* count = getOrCreateCount(genderDistribution, gender);
        (*count)++;
    }

    void incrementOccupation(const char* occupation)
    {
        int* count = getOrCreateCount(occupationStats, occupation);
        (*count)++;
    }

    void incrementEducation(const char* education)
    {
        int* count = getOrCreateCount(educationStats, education);
        (*count)++;
    }

    void incrementIncome(int income)
    {
        const char* range = getIncomeRange(income);
        int* count = getOrCreateCount(incomeStats, range);
        (*count)++;
    }

    void incrementSector(const char* sector)
    {
        int* count = getOrCreateCount(sectorPopulation, sector);
        (*count)++;
    }

    void incrementMaritalStatus(const char* status)
    {
        int* count = getOrCreateCount(maritalStats, status);
        (*count)++;
    }

    // DECREMENT OPERATIONS (Removing citizens)
    void decrementAge(int age)
    {
        const char* range = getAgeRange(age);
        int* count = (int*)ageDistribution->search(range);
        if (count && *count > 0) (*count)--;
    }

    void decrementGender(const char* gender)
    {
        int* count = (int*)genderDistribution->search(gender);
        if (count && *count > 0) (*count)--;
    }

    void decrementOccupation(const char* occupation)
    {
        int* count = (int*)occupationStats->search(occupation);
        if (count && *count > 0) (*count)--;
    }

    void decrementEducation(const char* education)
    {
        int* count = (int*)educationStats->search(education);
        if (count && *count > 0) (*count)--;
    }

    void decrementIncome(int income)
    {
        const char* range = getIncomeRange(income);
        int* count = (int*)incomeStats->search(range);
        if (count && *count > 0) (*count)--;
    }

    void decrementSector(const char* sector)
    {
        int* count = (int*)sectorPopulation->search(sector);
        if (count && *count > 0) (*count)--;
    }

    void decrementMaritalStatus(const char* status)
    {
        int* count = (int*)maritalStats->search(status);
        if (count && *count > 0) (*count)--;
    }

    // BULK UPDATE (Used when registering citizen)
    void updateAllDemographics(int age, const char* gender,
        const char* occupation, const char* education,
        int income, const char* sector,
        const char* maritalStatus)
    {
        incrementAge(age);
        incrementGender(gender);
        incrementOccupation(occupation);
        incrementEducation(education);
        incrementIncome(income);
        incrementSector(sector);
        incrementMaritalStatus(maritalStatus);
    }

    void removeAllDemographics(int age, const char* gender,
        const char* occupation, const char* education,
        int income, const char* sector,
        const char* maritalStatus)
    {
        decrementAge(age);
        decrementGender(gender);
        decrementOccupation(occupation);
        decrementEducation(education);
        decrementIncome(income);
        decrementSector(sector);
        decrementMaritalStatus(maritalStatus);
    }

    // QUERY OPERATIONS
    int getAgeCount(const char* ageRange)
    {
        return getCount(ageDistribution, ageRange);
    }

    int getGenderCount(const char* gender)
    {
        return getCount(genderDistribution, gender);
    }

    int getOccupationCount(const char* occupation)
    {
        return getCount(occupationStats, occupation);
    }

    int getEducationCount(const char* education)
    {
        return getCount(educationStats, education);
    }

    int getIncomeCount(const char* incomeRange)
    {
        return getCount(incomeStats, incomeRange);
    }

    int getSectorCount(const char* sector)
    {
        return getCount(sectorPopulation, sector);
    }

    int getMaritalCount(const char* status)
    {
        return getCount(maritalStats, status);
    }

    // DISPLAY OPERATIONS
    void displayAgeDistribution()
    {
        cout << endl;
        cout << "         AGE DISTRIBUTION........." << endl;
        cout << endl;
        cout << "0-10 years:   " << getAgeCount("0-10") << " people" << endl;
        cout << "11-20 years:  " << getAgeCount("11-20") << " people" << endl;
        cout << "21-30 years:  " << getAgeCount("21-30") << " people" << endl;
        cout << "31-40 years:  " << getAgeCount("31-40") << " people" << endl;
        cout << "41-50 years:  " << getAgeCount("41-50") << " people" << endl;
        cout << "51-60 years:  " << getAgeCount("51-60") << " people" << endl;
        cout << "61+ years:    " << getAgeCount("61+") << " people" << endl;
        cout << endl;
    }

    void displayGenderDistribution()
    {
        cout << endl;
        cout << "        GENDER DISTRIBUTION.........." << endl;
        cout << endl;
        cout << "Male:   " << getGenderCount("Male") << " people" << endl;
        cout << "Female: " << getGenderCount("Female") << " people" << endl;
        cout << "Other:  " << getGenderCount("Other") << " people" << endl;

        int total = getGenderCount("Male") + getGenderCount("Female") + getGenderCount("Other");
        if (total > 0)
        {
            float malePercent = (float)getGenderCount("Male") * 100 / total;
            float femalePercent = (float)getGenderCount("Female") * 100 / total;
            cout << "\nMale:   " << malePercent << "%" << endl;
            cout << "Female: " << femalePercent << "%" << endl;
        }
        cout << endl;
    }

    void displayOccupationStats()
    {
        cout << endl;
        cout << "      OCCUPATION STATISTICS........" << endl;
        cout << endl;
        cout << "Engineer:     " << getOccupationCount("Engineer") << " people" << endl;
        cout << "Doctor:       " << getOccupationCount("Doctor") << " people" << endl;
        cout << "Teacher:      " << getOccupationCount("Teacher") << " people" << endl;
        cout << "Student:      " << getOccupationCount("Student") << " people" << endl;
        cout << "Business:     " << getOccupationCount("Business") << " people" << endl;
        cout << "Government:   " << getOccupationCount("Government") << " people" << endl;
        cout << "Unemployed:   " << getOccupationCount("Unemployed") << " people" << endl;
        cout << "Retired:      " << getOccupationCount("Retired") << " people" << endl;
        cout << endl;
    }

    void displayEducationStats()
    {
        cout << endl;
        cout << "       EDUCATION STATISTICS......." << endl;
        cout << endl;
        cout << "No Education:  " << getEducationCount("None") << " people" << endl;
        cout << "Primary:       " << getEducationCount("Primary") << " people" << endl;
        cout << "Secondary:     " << getEducationCount("Secondary") << " people" << endl;
        cout << "Matric:        " << getEducationCount("Matric") << " people" << endl;
        cout << "Intermediate:  " << getEducationCount("Intermediate") << " people" << endl;
        cout << "Bachelor:      " << getEducationCount("Bachelor") << " people" << endl;
        cout << "Master:        " << getEducationCount("Master") << " people" << endl;
        cout << "PhD:           " << getEducationCount("PhD") << " people" << endl;
        cout << endl;
    }

    void displayIncomeStats()
    {
        cout << endl;
        cout << "        INCOME DISTRIBUTION........" << endl;
        cout << endl;
        cout << "Below 20,000:       " << getIncomeCount("Below-20000") << " people" << endl;
        cout << "20,000-50,000:      " << getIncomeCount("20000-50000") << " people" << endl;
        cout << "50,000-100,000:     " << getIncomeCount("50000-100000") << " people" << endl;
        cout << "100,000-200,000:    " << getIncomeCount("100000-200000") << " people" << endl;
        cout << "Above 200,000:      " << getIncomeCount("Above-200000") << " people" << endl;
        cout << endl;
    }

    void displaySectorPopulation()
    {
        cout << endl;
        cout << "       SECTOR POPULATION......" << endl;
        cout << endl;
        cout << "F-7:  " << getSectorCount("F-7") << " people" << endl;
        cout << "G-8:  " << getSectorCount("G-8") << " people" << endl;
        cout << "H-9:  " << getSectorCount("H-9") << " people" << endl;
        cout << "I-10: " << getSectorCount("I-10") << " people" << endl;
        cout << "E-11: " << getSectorCount("E-11") << " people" << endl;
        cout << endl;
    }

    void displayMaritalStats()
    {
        cout << endl;
        cout << "      MARITAL STATUS STATISTICS......" << endl;
        cout  << endl;
        cout << "Single:   " << getMaritalCount("Single") << " people" << endl;
        cout << "Married:  " << getMaritalCount("Married") << " people" << endl;
        cout << "Divorced: " << getMaritalCount("Divorced") << " people" << endl;
        cout << "Widowed:  " << getMaritalCount("Widowed") << " people" << endl;
        cout  << endl;
    }

    void displayAllDemographics()
    {
        cout << "\n" << endl;
        cout << endl;
        cout << "           COMPLETE DEMOGRAPHIC REPORT....." << endl;
        cout << endl;

        displayAgeDistribution();
        displayGenderDistribution();
        displayOccupationStats();
        displayEducationStats();
        displayIncomeStats();
        displaySectorPopulation();
        displayMaritalStats();

        cout << endl;
    }

    // DESTRUCTOR
    ~Demographics()
    {
        delete ageDistribution;
        delete genderDistribution;
        delete occupationStats;
        delete educationStats;
        delete incomeStats;
        delete sectorPopulation;
        delete maritalStats;
    }
};