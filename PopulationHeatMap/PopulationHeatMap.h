#pragma once
#pragma once
#include <iostream>
#include "../DataStructures/HashTable.h"
#include "../DataStructures/LinkedList.h"

using namespace std;

struct SectorData {
    char sectorId[20];
    char sectorName[50];
    int population;
    int households;
    double area;  // in sq km
    double density;  // population per sq km
    int maleCount;
    int femaleCount;
    double avgIncome;
    double avgAge;

    SectorData() : population(0), households(0), area(1.0), density(0),
        maleCount(0), femaleCount(0), avgIncome(0), avgAge(0) {
        sectorId[0] = '\0';
        sectorName[0] = '\0';
    }

    SectorData(const char* id, const char* name, double ar)
        : population(0), households(0), area(ar), density(0),
        maleCount(0), femaleCount(0), avgIncome(0), avgAge(0) {
        int i = 0;
        while (id[i] != '\0' && i < 19) { sectorId[i] = id[i]; i++; }
        sectorId[i] = '\0';
        i = 0;
        while (name[i] != '\0' && i < 49) { sectorName[i] = name[i]; i++; }
        sectorName[i] = '\0';
    }

    void updateDensity() {
        if (area > 0) {
            density = population / area;
        }
    }

    void display() {
        cout << sectorName << " (" << sectorId << ")" << endl;
        cout << "  Population: " << population << endl;
        cout << "  Households: " << households << endl;
        cout << "  Area: " << area << " sq km" << endl;
        cout << "  Density: " << density << " per sq km" << endl;
        cout << "  Male/Female: " << maleCount << "/" << femaleCount << endl;
        cout << "  Avg Income: PKR " << avgIncome << endl;
        cout << "  Avg Age: " << avgAge << " years" << endl;
    }
};

enum HeatmapType {
    POPULATION_DENSITY,
    INCOME_LEVEL,
    AGE_DISTRIBUTION,
    GENDER_RATIO,
    HOUSEHOLD_DENSITY
};

class PopulationHeatmap {
private:
    HashTable* sectorRegistry;
    LinkedList* allSectors;
    int totalPopulation;
    int totalSectors;

    // Color codes for console visualization
    const char* getDensityColor(double density, double maxDensity) {
        double ratio = density / maxDensity;
        if (ratio < 0.2) return "░░";  // Very Low
        if (ratio < 0.4) return "▒▒";  // Low
        if (ratio < 0.6) return "▓▓";  // Medium
        if (ratio < 0.8) return "██";  // High
        return "▓█";  // Very High
    }

    const char* getHeatLevel(double value, double maxValue) {
        double ratio = value / maxValue;
        if (ratio < 0.2) return "VERY LOW";
        if (ratio < 0.4) return "LOW";
        if (ratio < 0.6) return "MEDIUM";
        if (ratio < 0.8) return "HIGH";
        return "VERY HIGH";
    }

public:
    PopulationHeatmap() : totalPopulation(0), totalSectors(0) {
        sectorRegistry = new HashTable(50);
        allSectors = new LinkedList();
        cout << "Population Heatmap System: Initialized" << endl;
    }

    // SECTOR MANAGEMENT
    void addSector(const char* sectorId, const char* sectorName, double area) {
        SectorData* sector = new SectorData(sectorId, sectorName, area);
        sectorRegistry->insert(sectorId, (void*)sector);
        allSectors->insertAtEnd((void*)sector);
        totalSectors++;

        cout << "Sector added: " << sectorName << " (" << area << " sq km)" << endl;
    }

    void updateSectorPopulation(const char* sectorId, int population, int males, int females) {
        SectorData* sector = (SectorData*)sectorRegistry->search(sectorId);
        if (sector == NULL) {
            cout << "Sector " << sectorId << " not found!" << endl;
            return;
        }

        totalPopulation -= sector->population;
        sector->population = population;
        sector->maleCount = males;
        sector->femaleCount = females;
        sector->updateDensity();
        totalPopulation += population;

        cout << "Updated population for " << sector->sectorName << ": " << population << endl;
    }

    void addCitizenToSector(const char* sectorId, bool isMale, int age, double income) {
        SectorData* sector = (SectorData*)sectorRegistry->search(sectorId);
        if (sector == NULL) {
            // Auto-create sector with default area
            addSector(sectorId, sectorId, 5.0);
            sector = (SectorData*)sectorRegistry->search(sectorId);
        }

        sector->population++;
        if (isMale) sector->maleCount++;
        else sector->femaleCount++;

        // Update averages
        double totalAge = sector->avgAge * (sector->population - 1);
        sector->avgAge = (totalAge + age) / sector->population;

        double totalIncome = sector->avgIncome * (sector->population - 1);
        sector->avgIncome = (totalIncome + income) / sector->population;

        sector->updateDensity();
        totalPopulation++;
    }

    void setSectorHouseholds(const char* sectorId, int households) {
        SectorData* sector = (SectorData*)sectorRegistry->search(sectorId);
        if (sector == NULL) {
            cout << "Sector " << sectorId << " not found!" << endl;
            return;
        }

        sector->households = households;
    }

    // HEATMAP GENERATION
    void generateDensityHeatmap() {
        cout << endl;
        cout << "         POPULATION DENSITY HEATMAP                 " << endl;
        cout  << endl;

        // Find max density
        double maxDensity = 0;
        ListNode* current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;
            if (s->density > maxDensity) maxDensity = s->density;
            current = current->next;
        }

        if (maxDensity == 0) maxDensity = 1;  // Prevent division by zero

        current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;
            cout << "║ ";

            // Print sector name (padded)
            int nameLen = 0;
            while (s->sectorName[nameLen] != '\0') nameLen++;
            cout << s->sectorName;
            for (int i = nameLen; i < 12; i++) cout << " ";

            cout << " │ ";

            // Print heat bar
            int bars = (int)((s->density / maxDensity) * 20);
            for (int i = 0; i < bars; i++) cout << "█";
            for (int i = bars; i < 20; i++) cout << "░";

            cout << " │ " << (int)s->density << "/km²";

            // Pad to align
            int densityLen = 1;
            int temp = (int)s->density;
            while (temp >= 10) { temp /= 10; densityLen++; }
            for (int i = densityLen; i < 6; i++) cout << " ";

            cout << "║" << endl;

            current = current->next;
        }

        cout << endl;
        cout << " Legend: ░=Low  ▒=Medium  ▓=High  █=Very High       " << endl;
        cout << endl;
    }

    void generateIncomeHeatmap() {
        cout << endl;
        cout << "           INCOME LEVEL HEATMAP                    " << endl;
        cout << endl;

        double maxIncome = 0;
        ListNode* current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;
            if (s->avgIncome > maxIncome) maxIncome = s->avgIncome;
            current = current->next;
        }

        if (maxIncome == 0) maxIncome = 1;

        current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;
            cout << "║ ";

            int nameLen = 0;
            while (s->sectorName[nameLen] != '\0') nameLen++;
            cout << s->sectorName;
            for (int i = nameLen; i < 12; i++) cout << " ";

            cout << " │ ";

            int bars = (int)((s->avgIncome / maxIncome) * 20);
            for (int i = 0; i < bars; i++) cout << "█";
            for (int i = bars; i < 20; i++) cout << "░";

            cout << "  PKR " << (int)s->avgIncome << "    " << endl;

            current = current->next;
        }

        cout << endl;
        cout << " Legend: ░=Low  █=High Income                      " << endl;
        cout << endl;
    }

    void generateGenderHeatmap() {
        cout << endl;
        cout << "              GENDER DISTRIBUTION HEATMAP               " << endl;
        cout << endl;
        cout << " Sector       │ Male     Female │ Ratio          " << endl;
        cout << endl;

        ListNode* current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;

            int total = s->maleCount + s->femaleCount;
            if (total == 0) total = 1;

            int malePercent = (s->maleCount * 100) / total;
            int femalePercent = 100 - malePercent;

            cout << "║ ";
            int nameLen = 0;
            while (s->sectorName[nameLen] != '\0') nameLen++;
            cout << s->sectorName;
            for (int i = nameLen; i < 12; i++) cout << " ";

            cout << " │ ";

            // Male bars (blue concept)
            int maleBars = malePercent / 10;
            for (int i = 0; i < maleBars; i++) cout << "█";
            for (int i = maleBars; i < 10; i++) cout << "░";

            // Female bars
            int femaleBars = femalePercent / 10;
            for (int i = 0; i < femaleBars; i++) cout << "▓";
            for (int i = femaleBars; i < 10; i++) cout << "░";

            cout << "  " << malePercent << ":" << femalePercent << "        " << endl;

            current = current->next;
        }

        cout << endl;
        cout << " Legend: █ Male  ▓ Female                               " << endl;
        cout << endl;
    }

    void generateAgeHeatmap() {
        cout << endl;
        cout << "          AVERAGE AGE HEATMAP                      " << endl;
        cout << endl;

        ListNode* current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;

            cout << "║ ";
            int nameLen = 0;
            while (s->sectorName[nameLen] != '\0') nameLen++;
            cout << s->sectorName;
            for (int i = nameLen; i < 12; i++) cout << " ";

            cout << " | ";

            // Age-based coloring (younger = green concept, older = red concept)
            int bars = (int)(s->avgAge / 4);  // Scale 0-80 to 0-20
            if (bars > 20) bars = 20;

            for (int i = 0; i < bars; i++) cout << "█";
            for (int i = bars; i < 20; i++) cout << "░";

            cout << " | " << (int)s->avgAge << " years     " << endl;

            current = current->next;
        }

        cout << endl;
        cout << " Legend: Longer bar = Older average population      " << endl;
        cout << endl;
    }

    // ANALYSIS & REPORTS
    void displaySectorComparison() {
        cout << endl;
        cout << "                    SECTOR COMPARISON REPORT" << endl;
        cout << endl;

        cout << "\n┌──────────────┬──────────┬─────────┬──────────┬───────────┐" << endl;
        cout << "  │ Sector       │ Pop.     │ Density │ Avg Inc  │ Avg Age   │" << endl;
        cout << "  ├──────────────┼──────────┼─────────┼──────────┼───────────┤" << endl;

        ListNode* current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;

            cout << "│ ";
            int nameLen = 0;
            while (s->sectorName[nameLen] != '\0') nameLen++;
            cout << s->sectorName;
            for (int i = nameLen; i < 12; i++) cout << " ";

            cout << " │ " << s->population;
            int popLen = 1; int temp = s->population;
            while (temp >= 10) { temp /= 10; popLen++; }
            for (int i = popLen; i < 8; i++) cout << " ";

            cout << " │ " << (int)s->density;
            int denLen = 1; temp = (int)s->density;
            while (temp >= 10) { temp /= 10; denLen++; }
            for (int i = denLen; i < 7; i++) cout << " ";

            cout << " │ " << (int)s->avgIncome;
            int incLen = 1; temp = (int)s->avgIncome;
            while (temp >= 10) { temp /= 10; incLen++; }
            for (int i = incLen; i < 8; i++) cout << " ";

            cout << " │ " << (int)s->avgAge;
            int ageLen = 1; temp = (int)s->avgAge;
            while (temp >= 10) { temp /= 10; ageLen++; }
            for (int i = ageLen; i < 9; i++) cout << " ";

            cout << " │" << endl;

            current = current->next;
        }

        cout << "└──────────────┴──────────┴─────────┴──────────┴───────────┘" << endl;
    }

    void findHighDensityAreas(double threshold) {
        cout << "\n=== HIGH DENSITY AREAS (>" << threshold << "/km²) ===" << endl;
        bool found = false;

        ListNode* current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;
            if (s->density > threshold) {
                cout << "! " << s->sectorName << " - Density: " << s->density << "/km²" << endl;
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No sectors exceed the density threshold." << endl;
        }
    }

    void displayHeatmapMenu() {
        cout << "\n=== POPULATION HEATMAP MENU ===" << endl;
        cout << "1. Population Density Heatmap" << endl;
        cout << "2. Income Level Heatmap" << endl;
        cout << "3. Gender Distribution Heatmap" << endl;
        cout << "4. Age Distribution Heatmap" << endl;
        cout << "5. Sector Comparison Report" << endl;
        cout << "6. Find High Density Areas" << endl;
        cout << "7. Display All Sector Details" << endl;
        cout << "0. Back" << endl;
    }

    void displayAllSectors() {
        cout << "\n=== ALL SECTORS ===" << endl;
        cout << "Total Sectors: " << totalSectors << endl;
        cout << "Total Population: " << totalPopulation << endl;
        cout << "----------------------------" << endl;

        ListNode* current = allSectors->getHead();
        while (current != NULL) {
            SectorData* s = (SectorData*)current->data;
            s->display();
            cout << endl;
            current = current->next;
        }
    }

    int getTotalPopulation() { return totalPopulation; }
    int getTotalSectors() { return totalSectors; }

    ~PopulationHeatmap() {
        delete sectorRegistry;
        delete allSectors;
        cout << "Population Heatmap System: Shut down" << endl;
    }
};