#pragma once
#include <iostream>

using namespace std;

// Forward declaration
class FamilyTreeNode;

class House
{
public:
    char houseNumber[20];       
    char street[50];            
    char sector[20];            
    char houseId[50];           

    // Owner information
    char ownerCNIC[20];         
    char ownerName[100];        

    // Family information
    char familyId[20];          
    FamilyTreeNode* familyTree; 
    int numResidents;           

    // House details
    char houseType[50];        
    int numRooms;
    double area;               

    // Location
    double latitude;
    double longitude;

    House()
    {
        houseNumber[0] = '\0';
        street[0] = '\0';
        sector[0] = '\0';
        houseId[0] = '\0';
        ownerCNIC[0] = '\0';
        ownerName[0] = '\0';
        familyId[0] = '\0';
        familyTree = NULL;
        numResidents = 0;
        houseType[0] = '\0';
        numRooms = 0;
        area = 0.0;
        latitude = 0.0;
        longitude = 0.0;
    }

    House(const char* houseNo, const char* str, const char* sect,
        const char* owner, const char* famId)
    {
        int i = 0;
        while (houseNo[i] != '\0' && i < 19) {
            houseNumber[i] = houseNo[i];
            i++;
        }
        houseNumber[i] = '\0';

        i = 0;
        while (str[i] != '\0' && i < 49) {
            street[i] = str[i];
            i++;
        }
        street[i] = '\0';

        i = 0;
        while (sect[i] != '\0' && i < 19) {
            sector[i] = sect[i];
            i++;
        }
        sector[i] = '\0';

        i = 0;
        while (owner[i] != '\0' && i < 19) {
            ownerCNIC[i] = owner[i];
            i++;
        }
        ownerCNIC[i] = '\0';

        i = 0;
        while (famId[i] != '\0' && i < 19) {
            familyId[i] = famId[i];
            i++;
        }
        familyId[i] = '\0';

        // Build houseId
        buildHouseId();

        familyTree = NULL;
        numResidents = 0;
        ownerName[0] = '\0';
        houseType[0] = '\0';
        numRooms = 0;
        area = 0.0;
        latitude = 0.0;
        longitude = 0.0;
    }

    void buildHouseId()
    {
        int idx = 0;
        int i = 0;

        // Add sector
        while (sector[i] != '\0' && idx < 49) {
            if (sector[i] != ' ' && sector[i] != '-') {
                houseId[idx++] = sector[i];
            }
            i++;
        }
        houseId[idx++] = '-';

        // Add street
        i = 0;
        while (street[i] != '\0' && idx < 49) {
            if (street[i] != ' ') {
                houseId[idx++] = street[i];
            }
            i++;
        }
        houseId[idx++] = '-';

        // Add house number
        i = 0;
        while (houseNumber[i] != '\0' && idx < 49) {
            if (houseNumber[i] != ' ' && houseNumber[i] != '#') {
                houseId[idx++] = houseNumber[i];
            }
            i++;
        }
        houseId[idx] = '\0';
    }

    void display()
    {
        cout << endl;
        cout << "         HOUSE INFORMATION........" << endl;
        cout << endl;
        cout << "House ID:        " << houseId << endl;
        cout << "Address:         " << houseNumber << ", " << street << ", " << sector << endl;
        cout << "Owner:           " << ownerName << " (" << ownerCNIC << ")" << endl;
        cout << "Family ID:       " << familyId << endl;
        cout << "Residents:       " << numResidents << endl;
        cout << "House Type:      " << houseType << endl;
        cout << "Rooms:           " << numRooms << endl;
        cout << "Area:            " << area << " sq ft" << endl;
        cout << "Coordinates:     (" << latitude << ", " << longitude << ")" << endl;
        cout << endl;
    }
};