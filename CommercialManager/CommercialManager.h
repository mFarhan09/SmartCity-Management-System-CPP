#pragma once
#include <iostream>
#include "../DataStructures/Graph.h"
#include "../DataStructures/HashTable.h"
#include "../DataStructures/LinkedList.h" 
#include "../PopulationManager/sector.h"

using namespace std;

struct Product;
struct ShoppingMall;


struct Product
{
    char productId[50];
    char name[100];
    char category[50]; // e.g., 'Electronics', 'Clothing', 'Food'
    double price;
    char mallId[20];

    Product(const char* id, const char* n, const char* cat, double p, const char* mId) : price(p)
    {
        // ... (String copy implementation - simplified for brevity)
        int i = 0;
        while (id[i] != '\0' && i < 49) { productId[i] = id[i]; i++; } productId[i] = '\0';
        i = 0;
        while (n[i] != '\0' && i < 99) { name[i] = n[i]; i++; } name[i] = '\0';
        i = 0;
        while (cat[i] != '\0' && i < 49) { category[i] = cat[i]; i++; } category[i] = '\0';
        i = 0;
        while (mId[i] != '\0' && i < 19) { mallId[i] = mId[i]; i++; } mallId[i] = '\0';
    }

    void display()
    {
        cout << "  [Product] ID: " << productId << ", Name: " << name
            << ", Category: " << category << ", Price: $" << price
            << ", Mall ID: " << mallId << endl;
    }
};

struct ShoppingMall
{
    char mallId[20];
    char name[100];
    char sector[20];
    double latitude;
    double longitude;
    // HashTable of Product* (key: productId) is conceptual, using a simple list here for entity simplicity
    // The manager's productRegistry will handle the global product lookup.

    ShoppingMall(const char* id, const char* n, const char* s, double lat, double lon)
        : latitude(lat), longitude(lon)
    {
        // ... (String copy implementation - simplified for brevity)
        int i = 0;
        while (id[i] != '\0' && i < 19) { mallId[i] = id[i]; i++; } mallId[i] = '\0';
        i = 0;
        while (n[i] != '\0' && i < 99) { name[i] = n[i]; i++; } name[i] = '\0';
        i = 0;
        while (s[i] != '\0' && i < 19) { sector[i] = s[i]; i++; } sector[i] = '\0';
    }

    void display()
    {
        cout << "  [Mall] ID: " << mallId << ", Name: " << name
            << ", Sector: " << sector << ", Coords: (" << latitude << ", " << longitude << ")" << endl;
    }
};


class CommercialManager
{
private:
    Graph* cityGraph;
    HashTable* mallRegistry;    // Key: mallId, Value: ShoppingMall*
    HashTable* productRegistry; // Key: productId, Value: Product*
    LinkedList* allMalls;       // For easy iteration and listing
    SectorManager* sectorSystem;


    bool stringCompare(const char* s1, const char* s2)
    {
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0') {
            if (s1[i] != s2[i]) return false;
            i++;
        }
        return s1[i] == s2[i];
    }

public:
    CommercialManager(Graph* graph) : cityGraph(graph)
    {
        mallRegistry = new HashTable(50);
        productRegistry = new HashTable(200);
        allMalls = new LinkedList();
        cout << "Commercial Manager: Initialized" << endl;
    }

    ShoppingMall* getMall(const char* mallId)
    {
        return (ShoppingMall*)mallRegistry->search(mallId);
    }

    // --- Core Functions ---

    void registerMall(const char* id, const char* name, const char* sector, double lat, double lon)
    {
        if (cityGraph->findVertexIndex(id) != -1) {
            cout << "Error: Location ID already exists in the city graph!" << endl;
            return;
        }

        ShoppingMall* newMall = new ShoppingMall(id, name, sector, lat, lon);

        mallRegistry->insert(id, newMall);
        allMalls->insertAtEnd(newMall);
        cityGraph->addVertex(id, name, lat, lon); // Add to master city graph


        cout << "Registered Shopping Mall: " << name << " (" << id << ")" << endl;
    }

    void addProduct(const char* id, const char* name, const char* category, double price, const char* mallId)
    {
        if (mallRegistry->search(mallId) == NULL) {
            cout << "Error: Mall ID " << mallId << " not found!" << endl;
            return;
        }

        Product* newProduct = new Product(id, name, category, price, mallId);
        productRegistry->insert(id, newProduct);
        cout << "Added product: " << name << " to Mall: " << mallId << endl;
    }

    Product* searchProduct(const char* productId)
    {
        Product* p = (Product*)productRegistry->search(productId);
        if (p == NULL) {
            cout << "Product ID " << productId << " not found." << endl;
        }
        else {
            cout << "Product found:" << endl;
            p->display();
        }
        return p;
    }

    void searchProductByCategory(const char* category)
    {
        cout << "\n--- Products in Category: " << category << " ---" << endl;
        bool found = false;

        // Iterate through the whole productRegistry (inefficient but avoids Vector/List)
        HashNode** table = productRegistry->getTable();
        int tableSize = productRegistry->getTableSize();

        for (int i = 0; i < tableSize; i++)
        {
            HashNode* current = table[i];
            while (current != NULL)
            {
                Product* p = (Product*)current->value;
                if (stringCompare(p->category, category))
                {
                    p->display();
                    found = true;
                }
                current = current->next;
            }
        }

        if (!found) {
            cout << "No products found in this category." << endl;
        }
    }

    // --- Integrated Functions ---

    void findNearestMall(const char* fromLocation)
    {
        cout << "\n=== FINDING NEAREST SHOPPING MALL ===" << endl;
        cout << "Searching from location: " << fromLocation << endl;

        // Reuse the Graph's findNearest, searching for a name containing 'Mall'
        const char* nearest = cityGraph->findNearest(fromLocation, "Mall");

        if (nearest != NULL)
        {
            cout << "Nearest Mall found: " << nearest << endl;
            cout << "\nCalculating shortest route..." << endl;
            cityGraph->dijkstra(fromLocation, nearest);
        }
        else
        {
            cout << "No Shopping Malls found in the city network!" << endl;
        }
    }

    void loadMallsFromCSV(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    char line[512];
    int count = 0;
    bool isHeader = true;

    cout << "\n=== Loading Shopping Malls from " << filename << " ===" << endl;

    while (file.getline(line, sizeof(line))) {
        if (isHeader) {
            isHeader = false;
            continue; // skip CSV header
        }

        char id[50], name[100], sector[50];
        double lat = 0.0, lon = 0.0;

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
                    case 0: strncpy_s(id, sizeof(id), trimmed, _TRUNCATE); break;
                    case 1: strncpy_s(name, sizeof(name), trimmed, _TRUNCATE); break;
                    case 2: strncpy_s(sector, sizeof(sector), trimmed, _TRUNCATE); break;
                    case 3: lat = atof(trimmed); break;
                    case 4: lon = atof(trimmed); break;
                }

                field++;
                charIndex = 0;
            } else {
                currentField[charIndex++] = line[i];
            }
            i++;
        }

        // Handle last field if line did not end with comma
        if (field == 4 && charIndex > 0) {
            currentField[charIndex] = '\0';
            lon = atof(currentField);
            field++;
        }

        if (field >= 5) {
            registerMall(id, name, sector, lat, lon);
            count++;
        }
    }

    file.close();
    cout << "Loaded " << count << " shopping malls from CSV." << endl;
}

    void displayAllMalls()
    {
        cout << "\n--- ALL REGISTERED SHOPPING MALLS ---" << endl;
        ListNode* current = allMalls->getHead();
        while (current != NULL)
        {
            ((ShoppingMall*)current->data)->display();
            current = current->next;
        }
        if (allMalls->getSize() == 0) {
            cout << "No malls registered." << endl;
        }
    }

    ~CommercialManager()
    {
        // Clean up entities in allMalls and productRegistry
        ListNode* currentMall = allMalls->getHead();
        while (currentMall != NULL)
        {
            delete (ShoppingMall*)currentMall->data;
            currentMall = currentMall->next;
        }

        HashNode** pTable = productRegistry->getTable();
        int pTableSize = productRegistry->getTableSize();
        for (int i = 0; i < pTableSize; i++)
        {
            HashNode* current = pTable[i];
            while (current != NULL)
            {
                delete (Product*)current->value;
                current = current->next;
            }
        }

        delete mallRegistry;
        delete productRegistry;
        delete allMalls;
        cout << "Commercial Manager: Shut down" << endl;
    }
};
#pragma once
