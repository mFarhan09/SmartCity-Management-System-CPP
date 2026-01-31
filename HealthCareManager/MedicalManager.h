#pragma once
#include <iostream>
#include "../DataStructures/HashTable.h"
#include "../DataStructures/MaxHeap.h"
#include "../DataStructures/NaryTree.h"
#include "../DataStructures/Graph.h"
#include "Hospital.h"
#include "Doctor.h"
#include "Patient.h"
#include "Medicine.h"
using namespace std;

class MedicalManager
{
private:
    HashTable* hospitalRegistry;
    HashTable* doctorRegistry;
    HashTable* patientRegistry;
    HashTable* medicineRegistry;
    HashTable* pharmacyRegistry;
    Graph* cityGraph;


    bool stringContains(const char* str, const char* substr)
    {
        int i = 0;
        while (str[i] != '\0')
        {
            int j = 0;
            int k = i;
            while (substr[j] != '\0' && str[k] != '\0' && str[k] == substr[j])
            {
                j++;
                k++;
            }
            if (substr[j] == '\0') return true;
            i++;
        }
        return false;
    }

public:
    MedicalManager(Graph* graph)
    {
        hospitalRegistry = new HashTable(100);
        doctorRegistry = new HashTable(200);
        patientRegistry = new HashTable(500);
        medicineRegistry = new HashTable(300);
        pharmacyRegistry = new HashTable(50);
        cityGraph = graph;
    }

    void registerHospital(const char* id, const char* name, const char* sector,
        int totalBeds, double lat, double lon, const char* specializationList)
    {
        Hospital* hospital = new Hospital(id, name, sector, totalBeds, lat, lon, specializationList);


        hospitalRegistry->insert(id, (void*)hospital);

        TreeNode* root = new TreeNode(id, name, (void*)hospital);
        hospital->hierarchy->setRoot(root);

        cityGraph->addVertex(id, name, lat, lon);

        cout << "Hospital registered: " << name << " (" << totalBeds << " beds)" << " Specializations: " << specializationList << endl;
    }

    Hospital* getHospital(const char* hospitalId)
    {
        return (Hospital*)hospitalRegistry->search(hospitalId);
    }


    void addSpecializationToHospital(const char* hospitalId, const char* specialization)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        if (hospital == NULL)
        {
            cout << "Hospital not found!" << endl;
            return;
        }

        hospital->addSpecialization(specialization);
        cout << "Added specialization " << specialization << " to " << hospital->name << endl;
    }

    void addBlock(const char* hospitalId, const char* blockId,
        const char* blockName, const char* blockType, int floor)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        if (hospital == NULL)
        {
            cout << "Hospital not found!" << endl;
            return;
        }

        Block* block = new Block(blockId, blockName, blockType, floor);
        TreeNode* blockNode = new TreeNode(blockId, blockName, (void*)block);

        TreeNode* root = hospital->hierarchy->getRoot();
        if (root == NULL)
        {
            cout << "Error: Hospital hierarchy not initialized!" << endl;
            return;
        }

        root->addChild(blockNode);
        cout << "Added block " << blockName << " to " << hospital->name << endl;
    }

    void addWard(const char* hospitalId, const char* blockId,
        const char* wardId, const char* wardName,
        const char* wardType, int numBeds)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        if (hospital == NULL)
        {
            cout << "Hospital not found!" << endl;
            return;
        }

        TreeNode* blockNode = hospital->hierarchy->search(blockId);
        if (blockNode == NULL)
        {
            cout << "Block not found!" << endl;
            return;
        }

        // Create ward
        Ward* ward = new Ward(wardId, wardName, wardType, numBeds);
        TreeNode* wardNode = new TreeNode(wardId, wardName, (void*)ward);
        blockNode->addChild(wardNode);

        // Create beds for the ward
        for (int i = 1; i <= numBeds; i++)
        {
            char bedId[20];
            char bedNum[10];

            // Create bed ID (e.g., "W1-01", "W1-02")
            int idx = 0;
            int j = 0;
            while (wardId[j] != '\0' && idx < 10)
            {
                bedId[idx++] = wardId[j++];
            }
            bedId[idx++] = '-';

            // Add bed number
            if (i >= 10)
            {
                bedId[idx++] = '0' + (i / 10);
            }
            bedId[idx++] = '0' + (i % 10);
            bedId[idx] = '\0';

            // Create bed number string
            if (i < 10)
            {
                bedNum[0] = '0' + i;
                bedNum[1] = '\0';
            }
            else
            {
                bedNum[0] = '0' + (i / 10);
                bedNum[1] = '0' + (i % 10);
                bedNum[2] = '\0';
            }

            Bed* bed = new Bed(bedId, bedNum, wardId);
            ward->beds->insertAtEnd((void*)bed);
        }

        // Update block statistics
        Block* block = (Block*)blockNode->data;
        block->totalBeds += numBeds;
        block->availableBeds += numBeds;

        // Update hospital statistics - THIS WAS MISSING!
        hospital->totalBeds += numBeds;
        hospital->availableBeds += numBeds;

        cout << "Added ward " << wardName << " with " << numBeds << " beds to "
            << block->blockName << endl;
    }

    void registerDoctor(const char* id, const char* name, const char* specialization,
        const char* hospitalId, int experience, int fee)
    {
        Doctor* doctor = new Doctor(id, name, specialization, hospitalId, experience, fee);
        doctorRegistry->insert(id, (void*)doctor);

        cout << "Doctor registered: " << name << " (" << specialization << ")" << endl;
    }

    void registerPatient(const char* id, const char* cnic, const char* name,
        int age, const char* gender, const char* bloodType)
    {
        Patient* patient = new Patient(id, cnic, name, age, gender, bloodType);

        patientRegistry->insert(id, (void*)patient);
        patientRegistry->insert(cnic, (void*)patient);

        cout << "Patient registered: " << name << " (" << id << ")" << endl;
    }

    void addEmergencyPatient(const char* hospitalId, const char* patientId,
        const char* condition, int severity)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        Patient* patient = (Patient*)patientRegistry->search(patientId);

        if (hospital == NULL || patient == NULL)
        {
            cout << "Hospital or patient not found!" << endl;
            return;
        }

        int i = 0;
        while (condition[i] != '\0' && i < 199)
        {
            patient->currentCondition[i] = condition[i];
            i++;
        }
        patient->currentCondition[i] = '\0';
        patient->severity = severity;

        hospital->emergencyQueue->insert((double)severity, (void*)patient);

        cout << "Added " << patient->name << " to emergency queue (Severity: "
            << severity << "/10)" << endl;
    }

    void treatNextEmergencyPatient(const char* hospitalId)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        if (hospital == NULL)
        {
            cout << "Hospital not found!" << endl;
            return;
        }

        if (hospital->emergencyQueue->isEmpty())
        {
            cout << "No patients in emergency queue!" << endl;
            return;
        }

        HeapNode node = hospital->emergencyQueue->extractMax();
        Patient* patient = (Patient*)node.data;

        cout << "\n=== TREATING EMERGENCY PATIENT ===" << endl;
        cout << "Priority: " << node.priority << "/10" << endl;
        cout << "Patient: " << patient->name << endl;
        cout << "Condition: " << patient->currentCondition << endl;
        cout << "Blood Type: " << patient->bloodType << endl;
        cout << "Allergies: " << patient->allergies << endl;
    }

    void admitPatient(const char* hospitalId, const char* patientId,
        const char* wardId, const char* doctorId)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        Patient* patient = (Patient*)patientRegistry->search(patientId);
        Doctor* doctor = (Doctor*)doctorRegistry->search(doctorId);

        if (hospital == NULL || patient == NULL || doctor == NULL)
        {
            cout << "Hospital, patient, or doctor not found!" << endl;
            return;
        }

        TreeNode* wardNode = hospital->hierarchy->search(wardId);
        if (wardNode == NULL)
        {
            cout << "Ward not found!" << endl;
            return;
        }

        Ward* ward = (Ward*)wardNode->data;
        if (ward->availableBeds <= 0)
        {
            cout << "No beds available in this ward!" << endl;
            return;
        }

        // Find first available bed
        ListNode* current = ward->beds->getHead();
        while (current != NULL)
        {
            Bed* bed = (Bed*)current->data;
            if (!bed->isOccupied)
            {
                bed->isOccupied = true;

                int i = 0;
                while (patientId[i] != '\0' && i < 19)
                {
                    bed->patientId[i] = patientId[i];
                    i++;
                }
                bed->patientId[i] = '\0';

                i = 0;
                while (doctorId[i] != '\0' && i < 19)
                {
                    bed->assignedDoctor[i] = doctorId[i];
                    i++;
                }
                bed->assignedDoctor[i] = '\0';

                patient->isAdmitted = true;
                i = 0;
                while (hospitalId[i] != '\0' && i < 19)
                {
                    patient->currentHospital[i] = hospitalId[i];
                    i++;
                }
                patient->currentHospital[i] = '\0';

                i = 0;
                while (bed->bedId[i] != '\0' && i < 19)
                {
                    patient->assignedBed[i] = bed->bedId[i];
                    i++;
                }
                patient->assignedBed[i] = '\0';

                i = 0;
                while (doctorId[i] != '\0' && i < 19)
                {
                    patient->assignedDoctor[i] = doctorId[i];
                    i++;
                }
                patient->assignedDoctor[i] = '\0';

                ward->availableBeds--;
                hospital->availableBeds--;
                doctor->isAvailable = false;

                cout << "Patient " << patient->name << " admitted to "
                    << bed->bedId << " in " << ward->wardName << endl;
                cout << "Assigned to Dr. " << doctor->name << endl;

                return;
            }
            current = current->next;
        }
    }

    void registerPharmacy(const char* id, const char* name, const char* sector,
        const char* medicineName, const char* formula, double price)
    {
        // Create a Pharmacy object with medicine info
        Pharmacy* pharmacy = new Pharmacy(id, name, sector, medicineName, formula, price);

        // Insert into the registry
        pharmacyRegistry->insert(id, (void*)pharmacy);

        // Print confirmation
        cout << "Pharmacy registered: " << name << " (" << sector << ")"
            << ", Medicine: " << medicineName
            << ", Formula: " << formula
            << ", Price: " << price << endl;
    }


    void addMedicine(const char* name, const char* formula, double price,
        int stock, const char* pharmacyId, const char* pharmacyName)
    {
        Medicine* medicine = new Medicine(name, formula, price, stock,
            pharmacyId, pharmacyName);
        medicineRegistry->insert(name, (void*)medicine);

        cout << "Medicine added: " << name << " (" << price << " PKR)" << endl;
    }

    void searchMedicine(const char* name)
    {
        Medicine* medicine = (Medicine*)medicineRegistry->search(name);
        if (medicine == NULL)
        {
            cout << "Medicine not found!" << endl;
            return;
        }

        cout << "\n";
        medicine->display();
    }

    void loadHospitalsFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file " << filename <<  endl;
            return;
        }

        char line[600];
        int count = 0;
        bool isHeader = true;

        cout << "\n=== Loading Hospitals from " << filename  << endl;

        while (file.getline(line, sizeof(line))) {
            if (isHeader) {
                isHeader = false;
                continue;    // skip the header
            }

            char id[30] = { 0 }, name[100] = { 0 }, sector[50] = { 0 }, specializations[256] = { 0 };
            int totalBeds = 0;
            double lat = 0.0, lon = 0.0; // Hardcoded 0.0, 0.0 since lat/lon are missing in CSV

            char currentField[200];
            int charIndex = 0;
            int field = 0;

            int i = 0;
          

            while (line[i] != '\0') {
                char c = line[i];

                if (c == ',' || line[i] == '\n' || line[i] == '\r' || line[i + 1] == '\0') {
                    // If the next character is null, this is the last field.
                    if (line[i + 1] == '\0' && c != ',' && c != '\n' && c != '\r') {
                        currentField[charIndex++] = c;
                    }

                    currentField[charIndex] = '\0';

                    // --- TRIM LOGIC START ---
                    int start = 0, end = charIndex - 1;

                    // Trim leading quote/spaces
                    while (start < charIndex && (currentField[start] == '"' || currentField[start] == ' '))
                        start++;

                    // Trim trailing quote/spaces
                    while (end >= start && (currentField[end] == '"' || currentField[end] == ' '))
                        end--;

                    char trimmed[200];
                    int j = 0;
                    for (int k = start; k <= end; k++)
                        trimmed[j++] = currentField[k];
                    trimmed[j] = '\0';
                    // --- TRIM LOGIC END ---

                    // Assign fields (5 fields total)
                    switch (field) {
                    case 0: strncpy_s(id, sizeof(id), trimmed, _TRUNCATE); break;
                    case 1: strncpy_s(name, sizeof(name), trimmed, _TRUNCATE); break;
                    case 2: strncpy_s(sector, sizeof(sector), trimmed, _TRUNCATE); break;
                    case 3: totalBeds = atoi(trimmed); break; // EmergencyBeds
                    case 4: strncpy_s(specializations, sizeof(specializations), trimmed, _TRUNCATE); break; // Specialization
                        // Fields 5 and 6 (lat/lon) are absent in the CSV
                    }

                    field++;
                    charIndex = 0;
                }
                else {
                    currentField[charIndex++] = c;
                }

                i++;
            }

            // Must have 5 fields total (field index 0 to 4)
            if (field >= 5) {
                // Register with 0.0 lat/lon since they aren't in the CSV
                registerHospital(id, name, sector, totalBeds, lat, lon, specializations);
                count++;
            }
            else if (field > 0) {
                // Log an error if a line was partially read but didn't meet 5 fields
                cout << "Warning: Skipped incomplete record (Fields found: " << field << "): " << line << endl;
            }
        }

        file.close();
        cout << "Loaded " << count << " hospitals from CSV successfully. ?" << endl;
    }

    void loadPharmaciesFromCSV(const char* filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error: Cannot open file " << filename << endl;
            return;
        }

        char line[500];
        int count = 0;
        bool isHeader = true;

        cout << "\n=== Loading Pharmacies from " << filename << " ===" << endl;

        while (file.getline(line, sizeof(line))) {
            if (isHeader) {
                isHeader = false;
                continue;   // skip header row
            }

            char id[30], name[100], sector[50], medName[100], formula[100];
            double price = 0.0;

            char currentField[200];
            int charIndex = 0;
            int field = 0;

            int i = 0;
            while (line[i] != '\0') {
                if (line[i] == ',' || line[i] == '\n' || line[i] == '\r') {
                    currentField[charIndex] = '\0';

                    // Trim quotes and spaces
                    int start = 0, end = charIndex - 1;
                    while (start < charIndex && (currentField[start] == '"' || currentField[start] == ' '))
                        start++;
                    while (end >= 0 && (currentField[end] == '"' || currentField[end] == ' '))
                        end--;

                    char trimmed[200];
                    int j = 0;
                    for (int k = start; k <= end; k++)
                        trimmed[j++] = currentField[k];
                    trimmed[j] = '\0';

                    // Assign fields
                    switch (field) {
                    case 0: strncpy_s(id, sizeof(id), trimmed, _TRUNCATE); break;
                    case 1: strncpy_s(name, sizeof(name), trimmed, _TRUNCATE); break;
                    case 2: strncpy_s(sector, sizeof(sector), trimmed, _TRUNCATE); break;
                    case 3: strncpy_s(medName, sizeof(medName), trimmed, _TRUNCATE); break;
                    case 4: strncpy_s(formula, sizeof(formula), trimmed, _TRUNCATE); break;
                    case 5: price = atof(trimmed); break;
                    }

                    field++;
                    charIndex = 0;
                }
                else {
                    currentField[charIndex++] = line[i];
                }
                i++;
            }

            // Handle last field if no trailing comma
            if (field == 5 && charIndex > 0) {
                currentField[charIndex] = '\0';
                price = atof(currentField);
                field++;
            }

            // Must have exactly 6 fields
            if (field >= 6) {
                registerPharmacy(id, name, sector, medName, formula, price);
                count++;
            }
        }

        file.close();
        cout << "Loaded " << count << " pharmacies from CSV." << endl;
    }


    void displayHospitalHierarchy(const char* hospitalId)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        if (hospital == NULL)
        {
            cout << "Hospital not found!" << endl;
            return;
        }

        cout << "\n=== " << hospital->name << " HIERARCHY ===" << endl;
        if (hospital->hierarchy->getRoot() == NULL)
        {
            cout << "No hierarchy structure found!" << endl;
            return;
        }
        hospital->hierarchy->display();
    }

    void displayDoctorDetails(const char* doctorId)
    {
        Doctor* doctor = (Doctor*)doctorRegistry->search(doctorId);
        if (doctor == NULL)
        {
            cout << "Doctor not found!" << endl;
            return;
        }

        doctor->display();
    }

    void displayPatientDetails(const char* patientId)
    {
        Patient* patient = (Patient*)patientRegistry->search(patientId);
        if (patient == NULL)
        {
            cout << "Patient not found!" << endl;
            return;
        }

        patient->display();
    }

    void checkBedAvailability(const char* hospitalId)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        if (hospital == NULL)
        {
            cout << "Hospital not found!" << endl;
            return;
        }

        cout << "\n=== BED AVAILABILITY: " << hospital->name << " ===" << endl;
        cout << "Total Beds: " << hospital->totalBeds << endl;
        cout << "Available: " << hospital->availableBeds << endl;
        cout << "Occupied: " << (hospital->totalBeds - hospital->availableBeds) << endl;

        if (hospital->totalBeds > 0)
        {
            cout << "Occupancy Rate: "
                << (100.0 * (hospital->totalBeds - hospital->availableBeds) / hospital->totalBeds)
                << "%" << endl;
        }
        else
        {
            cout << "Occupancy Rate: 0%" << endl;
        }
    }

    void displayHospitalDetails(const char* hospitalId)
    {
        Hospital* hospital = (Hospital*)hospitalRegistry->search(hospitalId);
        if (hospital == NULL)
        {
            cout << "Hospital not found!" << endl;
            return;
        }

        // Use the detailed structure display from Hospital class
        hospital->displayDetailedStructure();
    }

    

    void displayAllHospitals()
    {
        cout << "\n...ALL REGISTERED HOSPITALS...." << endl;

        HashNode** table = hospitalRegistry->getTable();
        int tableSize = hospitalRegistry->getTableSize();

        bool found = false;
        for (int i = 0; i < tableSize; i++)
        {
            HashNode* current = table[i];
            while (current != NULL)
            {
                Hospital* hospital = (Hospital*)current->value;
                cout << "\n" << hospital->name << " (" << hospital->hospitalId << ")" << endl;
                cout << "  Sector: " << hospital->sector << endl;
                cout << "  Beds: " << hospital->availableBeds << "/" << hospital->totalBeds << " available" << endl;
                found = true;
                current = current->next;
            }
        }

        if (!found)
        {
            cout << "No hospitals registered yet." << endl;
        }
    }

    ~MedicalManager()
    {
        delete hospitalRegistry;
        delete doctorRegistry;
        delete patientRegistry;
        delete medicineRegistry;
        delete pharmacyRegistry;
    }
};