#pragma once
#include <iostream>
#include "../DataStructures/HashTable.h"
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/Graph.h"

using namespace std;

// SECTOR ENTITY REFERENCE
struct SectorEntityRef
{
    char entityId[50];
    char entityName[100];
    char entityType[30];
    void* entityPtr;

    SectorEntityRef(const char* id, const char* name, const char* type, void* ptr) : entityPtr(ptr)
    {
        int i = 0;
        while (id[i] != '\0' && i < 49) { entityId[i] = id[i]; i++; }
        entityId[i] = '\0';

        i = 0;
        while (name[i] != '\0' && i < 99) { entityName[i] = name[i]; i++; }
        entityName[i] = '\0';

        i = 0;
        while (type[i] != '\0' && i < 29) { entityType[i] = type[i]; i++; }
        entityType[i] = '\0';
    }

    void display()
    {
        cout << "    [" << entityType << "] " << entityName << " (" << entityId << ")" << endl;
    }
};

// SECTOR STRUCTURE
struct Sector
{
    char sectorId[20];
    char name[100];
    double latitude;
    double longitude;
    double area;

    LinkedList* hospitals;
    LinkedList* schools;
    LinkedList* malls;
    LinkedList* pharmacies;
    LinkedList* busStops;
    LinkedList* facilities;

    int totalPopulation;
    int totalHospitals;
    int totalSchools;
    int totalMalls;
    int totalStops;
    int totalFacilities;
    int totalPharmacies;

    // Population demographics at sector level
    int malePopulation;
    int femalePopulation;
    int totalHouses;

    Sector(const char* id, const char* n, double lat = 0.0, double lon = 0.0, double a = 1.0)
        : latitude(lat), longitude(lon), area(a),
        totalPopulation(0), totalHospitals(0), totalSchools(0), totalMalls(0),
        totalStops(0), totalFacilities(0), totalPharmacies(0),
        malePopulation(0), femalePopulation(0), totalHouses(0)
    {
        int i = 0;
        while (id[i] != '\0' && i < 19) { sectorId[i] = id[i]; i++; }
        sectorId[i] = '\0';

        i = 0;
        while (n[i] != '\0' && i < 99) { name[i] = n[i]; i++; }
        name[i] = '\0';

        hospitals = new LinkedList();
        schools = new LinkedList();
        malls = new LinkedList();
        pharmacies = new LinkedList();
        busStops = new LinkedList();
        facilities = new LinkedList();
    }

    void display()
    {
        cout << "\n=== SECTOR: " << name << " (" << sectorId << ") ===" << endl;
        cout << "  Location: (" << latitude << ", " << longitude << ")" << endl;
        cout << "  Area: " << area << " sq km" << endl;
        cout << "  Population: " << totalPopulation;
        if (totalPopulation > 0) {
            cout << " (M: " << malePopulation << ", F: " << femalePopulation << ")";
        }
        cout << endl;
        if (area > 0) {
            cout << "  Density: " << (totalPopulation / area) << " per sq km" << endl;
        }
        cout << "  Houses: " << totalHouses << endl;
        cout << "  Hospitals: " << totalHospitals << endl;
        cout << "  Schools: " << totalSchools << endl;
        cout << "  Shopping Malls: " << totalMalls << endl;
        cout << "  Pharmacies: " << totalPharmacies << endl;
        cout << "  Bus Stops: " << totalStops << endl;
        cout << "  Facilities: " << totalFacilities << endl;
    }

    ~Sector()
    {
        delete hospitals;
        delete schools;
        delete malls;
        delete pharmacies;
        delete busStops;
        delete facilities;
    }
};

// SECTOR MANAGER CLASS
class SectorManager
{
private:
    HashTable* sectorRegistry;
    LinkedList* allSectors;
    Graph* cityGraph;
    int totalSectors;

public:
    SectorManager(Graph* graph) : cityGraph(graph), totalSectors(0)
    {
        sectorRegistry = new HashTable(100);
        allSectors = new LinkedList();
        cout << "Sector Manager: Initialized (Independent Geographic System)" << endl;
    }

    // CORE SECTOR FUNCTIONS

    bool addSector(const char* sectorId, const char* name, double lat = 0.0, double lon = 0.0, double area = 1.0)
    {
        if (sectorId[0] == '\0')
        {
            cout << "Error: Sector ID cannot be empty!" << endl;
            return false;
        }

        if (sectorRegistry->search(sectorId) != NULL)
        {
            return true; // Already exists
        }

        Sector* newSector = new Sector(sectorId, name, lat, lon, area);
        sectorRegistry->insert(sectorId, newSector);
        allSectors->insertAtEnd(newSector);

        cityGraph->addVertex(sectorId, name, lat, lon);

        totalSectors++;
        cout << "Sector registered: " << name << " (" << sectorId << ")" << endl;
        return true;
    }

    Sector* getSector(const char* sectorId)
    {
        return (Sector*)sectorRegistry->search(sectorId);
    }

    Sector* getOrCreateSector(const char* sectorId)
    {
        if (sectorId[0] == '\0') return NULL;

        Sector* sector = getSector(sectorId);
        if (sector == NULL)
        {
            addSector(sectorId, sectorId, 33.68 + (totalSectors * 0.01), 73.04 + (totalSectors * 0.01));
            sector = getSector(sectorId);
        }
        return sector;
    }

    // ENTITY LINKING FUNCTIONS

    bool linkHospitalToSector(const char* sectorId, const char* hospitalId, const char* hospitalName, void* hospitalPtr)
    {
        Sector* sector = getOrCreateSector(sectorId);
        if (sector == NULL) return false;

        SectorEntityRef* ref = new SectorEntityRef(hospitalId, hospitalName, "Hospital", hospitalPtr);
        sector->hospitals->insertAtEnd(ref);
        sector->totalHospitals++;

        cityGraph->addEdge(hospitalId, sectorId, 0.5);
        return true;
    }

    bool linkSchoolToSector(const char* sectorId, const char* schoolId, const char* schoolName, void* schoolPtr)
    {
        Sector* sector = getOrCreateSector(sectorId);
        if (sector == NULL) return false;

        SectorEntityRef* ref = new SectorEntityRef(schoolId, schoolName, "School", schoolPtr);
        sector->schools->insertAtEnd(ref);
        sector->totalSchools++;

        cityGraph->addEdge(schoolId, sectorId, 0.5);
        return true;
    }

    bool linkMallToSector(const char* sectorId, const char* mallId, const char* mallName, void* mallPtr)
    {
        Sector* sector = getOrCreateSector(sectorId);
        if (sector == NULL) return false;

        SectorEntityRef* ref = new SectorEntityRef(mallId, mallName, "Mall", mallPtr);
        sector->malls->insertAtEnd(ref);
        sector->totalMalls++;

        cityGraph->addEdge(mallId, sectorId, 0.5);
        return true;
    }

    bool linkPharmacyToSector(const char* sectorId, const char* pharmacyId, const char* pharmacyName, void* pharmacyPtr)
    {
        Sector* sector = getOrCreateSector(sectorId);
        if (sector == NULL) return false;

        SectorEntityRef* ref = new SectorEntityRef(pharmacyId, pharmacyName, "Pharmacy", pharmacyPtr);
        sector->pharmacies->insertAtEnd(ref);
        sector->totalPharmacies++;

        cityGraph->addEdge(pharmacyId, sectorId, 0.3);
        return true;
    }

    bool linkBusStopToSector(const char* sectorId, const char* stopId, const char* stopName, void* stopPtr)
    {
        Sector* sector = getOrCreateSector(sectorId);
        if (sector == NULL) return false;

        SectorEntityRef* ref = new SectorEntityRef(stopId, stopName, "BusStop", stopPtr);
        sector->busStops->insertAtEnd(ref);
        sector->totalStops++;

        cityGraph->addEdge(stopId, sectorId, 0.3);
        return true;
    }

    bool linkFacilityToSector(const char* sectorId, const char* facilityId, const char* facilityName, void* facilityPtr)
    {
        Sector* sector = getOrCreateSector(sectorId);
        if (sector == NULL) return false;

        SectorEntityRef* ref = new SectorEntityRef(facilityId, facilityName, "Facility", facilityPtr);
        sector->facilities->insertAtEnd(ref);
        sector->totalFacilities++;

        cityGraph->addEdge(facilityId, sectorId, 0.4);
        return true;
    }

    // POPULATION TRACKING (FOR DEMOGRAPHICS)

    void updateSectorPopulation(const char* sectorId, int change, bool isMale = true)
    {
        Sector* sector = getSector(sectorId);
        if (sector != NULL)
        {
            sector->totalPopulation += change;
            if (isMale) {
                sector->malePopulation += change;
            }
            else {
                sector->femalePopulation += change;
            }
        }
    }

    void updateSectorHouses(const char* sectorId, int change)
    {
        Sector* sector = getSector(sectorId);
        if (sector != NULL)
        {
            sector->totalHouses += change;
        }
    }

    void connectSectors(const char* sector1, const char* sector2, double distance)
    {
        if (getSector(sector1) == NULL || getSector(sector2) == NULL)
        {
            cout << "Error: One or both sectors not found!" << endl;
            return;
        }
        cityGraph->addEdge(sector1, sector2, distance);
        cout << "Connected: " << sector1 << " <-> " << sector2 << " (" << distance << " km)" << endl;
    }

    // QUERY FUNCTIONS

    int getSectorPopulation(const char* sectorId)
    {
        Sector* sector = getSector(sectorId);
        return sector ? sector->totalPopulation : 0;
    }

    double getSectorDensity(const char* sectorId)
    {
        Sector* sector = getSector(sectorId);
        if (sector && sector->area > 0) {
            return sector->totalPopulation / sector->area;
        }
        return 0.0;
    }

    // DISPLAY FUNCTIONS

    void displaySectorDetails(const char* sectorId)
    {
        Sector* sector = getSector(sectorId);
        if (sector == NULL)
        {
            cout << "Error: Sector '" << sectorId << "' not found!" << endl;
            return;
        }

        sector->display();

        cout << "\n  --- Hospitals ---" << endl;
        ListNode* current = sector->hospitals->getHead();
        if (current == NULL) cout << "    (None)" << endl;
        while (current != NULL)
        {
            ((SectorEntityRef*)current->data)->display();
            current = current->next;
        }

        cout << "\n  --- Schools ---" << endl;
        current = sector->schools->getHead();
        if (current == NULL) cout << "    (None)" << endl;
        while (current != NULL)
        {
            ((SectorEntityRef*)current->data)->display();
            current = current->next;
        }

        cout << "\n  --- Shopping Malls ---" << endl;
        current = sector->malls->getHead();
        if (current == NULL) cout << "    (None)" << endl;
        while (current != NULL)
        {
            ((SectorEntityRef*)current->data)->display();
            current = current->next;
        }

        cout << "\n  --- Pharmacies ---" << endl;
        current = sector->pharmacies->getHead();
        if (current == NULL) cout << "    (None)" << endl;
        while (current != NULL)
        {
            ((SectorEntityRef*)current->data)->display();
            current = current->next;
        }

        cout << "\n  --- Bus Stops ---" << endl;
        current = sector->busStops->getHead();
        if (current == NULL) cout << "    (None)" << endl;
        while (current != NULL)
        {
            ((SectorEntityRef*)current->data)->display();
            current = current->next;
        }

        cout << "\n  --- Facilities ---" << endl;
        current = sector->facilities->getHead();
        if (current == NULL) cout << "    (None)" << endl;
        while (current != NULL)
        {
            ((SectorEntityRef*)current->data)->display();
            current = current->next;
        }
    }

    void displayAllSectors()
    {
        cout << "\n=== ALL REGISTERED SECTORS ===" << endl;

        ListNode* current = allSectors->getHead();
        int count = 0;

        while (current != NULL)
        {
            Sector* sector = (Sector*)current->data;
            count++;
            cout << "\n" << count << ". " << sector->name << " (" << sector->sectorId << ")" << endl;
            cout << "   Population: " << sector->totalPopulation;
            if (sector->totalPopulation > 0) {
                cout << " (M: " << sector->malePopulation << ", F: " << sector->femalePopulation << ")";
            }
            cout << endl;
            cout << "   Hospitals: " << sector->totalHospitals
                << " | Schools: " << sector->totalSchools
                << " | Malls: " << sector->totalMalls
                << " | Pharmacies: " << sector->totalPharmacies << endl;
            cout << "   Bus Stops: " << sector->totalStops
                << " | Facilities: " << sector->totalFacilities
                << " | Houses: " << sector->totalHouses << endl;
            current = current->next;
        }

        if (count == 0)
        {
            cout << "No sectors registered yet." << endl;
        }
        else
        {
            cout << "\n--- Total: " << count << " sectors ---" << endl;
        }
    }

    void displaySectorSummary()
    {
        cout << "\n=== SECTOR SUMMARY ===" << endl;
        cout << "Total Sectors: " << totalSectors << endl;

        int totalH = 0, totalS = 0, totalM = 0, totalP = 0, totalSt = 0, totalF = 0, totalPop = 0, totalHouses = 0;
        int totalMale = 0, totalFemale = 0;

        ListNode* current = allSectors->getHead();
        while (current != NULL)
        {
            Sector* sector = (Sector*)current->data;
            totalH += sector->totalHospitals;
            totalS += sector->totalSchools;
            totalM += sector->totalMalls;
            totalP += sector->totalPharmacies;
            totalSt += sector->totalStops;
            totalF += sector->totalFacilities;
            totalPop += sector->totalPopulation;
            totalHouses += sector->totalHouses;
            totalMale += sector->malePopulation;
            totalFemale += sector->femalePopulation;
            current = current->next;
        }

        cout << "Total Population: " << totalPop;
        if (totalPop > 0) {
            cout << " (Male: " << totalMale << ", Female: " << totalFemale << ")";
        }
        cout << endl;
        cout << "Total Houses: " << totalHouses << endl;
        cout << "Total Hospitals: " << totalH << endl;
        cout << "Total Schools: " << totalS << endl;
        cout << "Total Malls: " << totalM << endl;
        cout << "Total Pharmacies: " << totalP << endl;
        cout << "Total Bus Stops: " << totalSt << endl;
        cout << "Total Facilities: " << totalF << endl;
    }

    int getTotalSectors() { return totalSectors; }

    ~SectorManager()
    {
        ListNode* current = allSectors->getHead();
        while (current != NULL)
        {
            Sector* sector = (Sector*)current->data;

            // Clean up entity references in each sector
            ListNode* refNode = sector->hospitals->getHead();
            while (refNode != NULL) { delete (SectorEntityRef*)refNode->data; refNode = refNode->next; }

            refNode = sector->schools->getHead();
            while (refNode != NULL) { delete (SectorEntityRef*)refNode->data; refNode = refNode->next; }

            refNode = sector->malls->getHead();
            while (refNode != NULL) { delete (SectorEntityRef*)refNode->data; refNode = refNode->next; }

            refNode = sector->pharmacies->getHead();
            while (refNode != NULL) { delete (SectorEntityRef*)refNode->data; refNode = refNode->next; }

            refNode = sector->busStops->getHead();
            while (refNode != NULL) { delete (SectorEntityRef*)refNode->data; refNode = refNode->next; }

            refNode = sector->facilities->getHead();
            while (refNode != NULL) { delete (SectorEntityRef*)refNode->data; refNode = refNode->next; }

            delete sector;
            current = current->next;
        }

        delete sectorRegistry;
        delete allSectors;
        cout << "Sector Manager: Shut down" << endl;
    }
};