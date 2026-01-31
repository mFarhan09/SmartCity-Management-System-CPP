#include <iostream>
#include "SmartCityManager.h"

using namespace std;

// Input validation helpers
bool getInt(int &value)
{
    cin >> value;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input! Please enter a number." << endl;
        return false;
    }
    cin.ignore();
    return true;
}

bool getDouble(double &value)
{
    cin >> value;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input! Please enter a valid number." << endl;
        return false;
    }
    return true;
}

bool isEmpty(const char *str) { return str[0] == '\0'; }

// Menu Display Functions
void displayMainMenu()
{
    cout << "\n.......................SMART CITY MANAGEMENT SYSTEM................................." << endl;
    cout << endl;
    cout << "\t\t  1. Transport Sector            " << endl;
    cout << "\t\t  2. Education Sector            " << endl;
    cout << "\t\t  3. Health Sector               " << endl;
    cout << "\t\t  4. Population Sector           " << endl;
    cout << "\t\t  5. Commercial Sector           " << endl;
    cout << "\t\t  6. Public Facilities Sector    " << endl;
    cout << endl;
    cout << "\t\t  7. City Navigation             " << endl;
    cout << "\t\t  8. City Map and Statistics     " << endl;
    cout << endl;
    cout << "\t BONUS FEATURES          " << endl;
    cout << "\t\t  9.  Emergency Routing System   " << endl;
    cout << "\t\t  10. School Bus Tracking        " << endl;
    cout << "\t\t  11. Airport & Rail Integration " << endl;
    cout << "\t\t  12. Real-Time Route Simulation " << endl;
    cout << "\t\t  13. Population Heatmap         " << endl;
    cout << endl;
    cout << "\t 0. Exit " << endl;
    cout << endl;
    cout << "Enter your choice: ";
}

void displayTransportMenu()
{
    cout << "\n\t........................TRANSPORT SECTOR...................." << endl;
    cout << "\n\t\t Bus and Stop Management " << endl;
    cout << "\t\t\t 1.  Register Bus" << endl;
    cout << "\t\t\t 2.  Add Bus Stop" << endl;
    cout << "\t\t\t 3.  Add Stop to Bus Route" << endl;
    cout << "\t\t\t 4.  Track Bus Location" << endl;
    cout << "\t\t\t 5.  Show Bus Route" << endl;
    cout << "\t\t\t 6.  Find Shortest Path" << endl;
    cout << "\t\t\t 7.  Display All Buses" << endl;
    cout << "\t\t\t 8.  Display All Stops" << endl;
    cout << "\t\t\t 9.  Display Transport Network" << endl;
    cout << "\n\t\t Passenger Queue " << endl;
    cout << "\t\t\t 10. Add Passenger to Stop Queue" << endl;
    cout << "\t\t\t 11. Display Stop Queue" << endl;
    cout << "\t\t\t 12. Simulate Bus Arrival" << endl;
    cout << "\t\t\t 13. Simulate Multiple Passengers" << endl;
    cout << "\n\t\t Travel History " << endl;
    cout << "\t\t\t 14. Display Travel History" << endl;
    cout << "\t\t\t 15. Display Recent Trips" << endl;
    cout << "\t\t\t 16. Undo Last Trip" << endl;
    cout << "\t\t\t 17. Travel Statistics" << endl;
    cout << "\t\t\t 18. Clear Travel History" << endl;
    cout << "\n\t\t CSV Operations " << endl;
    cout << "\t\t\t 19. Load Stops from CSV" << endl;
    cout << "\t\t\t 20. Load Buses from CSV" << endl;
    cout << "\n\t\t 0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayEducationMenu()
{
    cout << "\n\t.................EDUCATION SECTOR................" << endl;
    cout << "\n\t\t School Management" << endl;
    cout << "\t\t\t  1. Register School" << endl;
    cout << "\t\t\t  2. Add Subject to School" << endl;
    cout << "\t\t\t  3. Add Department" << endl;
    cout << "\t\t\t  4. Add Class" << endl;
    cout << "\t\t\t  5. Display School Hierarchy" << endl;
    cout << "\t\t\t  6. Display School Details" << endl;
    cout << "\t\t\t  7. Display All Schools" << endl;
    cout << "\n\t\t Teacher Management" << endl;
    cout << "\t\t\t  8.  Register Teacher" << endl;
    cout << "\t\t\t  9.  Assign Teacher to Class" << endl;
    cout << "\t\t\t  10. Display Teacher Details" << endl;
    cout << "\n\t\t Student Management" << endl;
    cout << "\t\t\t  11. Enroll Student" << endl;
    cout << "\n\t\t Search and Rankings" << endl;
    cout << "\t\t\t 12. Display Top Schools" << endl;
    cout << "\t\t\t 13. Search Schools by Subject" << endl;
    cout << "\n\t\t Navigation" << endl;
    cout << "\t\t\t 14. Find Nearest School" << endl;
    cout << "\t\t\t 15. Find Route to School" << endl;
    cout << "\n\t\t CSV Operations " << endl;
    cout << "\t\t\t 16. Load Schools from CSV" << endl;
    cout << "\n\t\t 0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayMedicalMenu()
{
    cout << "\n\t...................... HEALTH SECTOR......................" << endl;
    cout << "\n\t\t Hospital Management" << endl;
    cout << "\t\t\t  1.  Register Hospital" << endl;
    cout << "\t\t\t  2.  Add Specialization" << endl;
    cout << "\t\t\t  3.  Add Block" << endl;
    cout << "\t\t\t  4.  Add Ward" << endl;
    cout << "\t\t\t  5.  Display Hospital Hierarchy" << endl;
    cout << "\t\t\t  6.  Display Hospital Details" << endl;
    cout << "\t\t\t  7.  Check Bed Availability" << endl;
    cout << "\t\t\t  8.  Display All Hospitals" << endl;
    cout << "\n\t\t Doctor Management" << endl;
    cout << "\t\t\t  9.  Register Doctor" << endl;
    cout << "\t\t\t  10. Display Doctor Details" << endl;
    cout << "\n\t\t Patient Management" << endl;
    cout << "\t\t\t  11. Register Patient" << endl;
    cout << "\t\t\t  12. Display Patient Details" << endl;
    cout << "\t\t\t  13. Add Emergency Patient" << endl;
    cout << "\t\t\t  14. Treat Next Emergency" << endl;
    cout << "\t\t\t  15. Admit Patient" << endl;
    cout << "\n\t\t Pharmacy" << endl;
    cout << "\t\t\t  16. Register Pharmacy" << endl;
    cout << "\t\t\t  17. Add Medicine" << endl;
    cout << "\t\t\t  18. Search Medicine" << endl;
    cout << "\n\t\t Navigation" << endl;
    cout << "\t\t\t 19. Find Nearest Hospital" << endl;
    cout << "\t\t\t 20. Find Route to Hospital" << endl;
    cout << "\n\t\t CSV Operations " << endl;
    cout << "\t\t\t 21. Load Hospitals from CSV" << endl;
    cout << "\t\t\t 22. Load Pharmacies from CSV" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayPopulationMenu()
{
    cout << "\n......................POPULATION SECTOR...................." << endl;
    cout << "\n\t\t Citizen Management" << endl;
    cout << "\t\t\t  1. Register Citizen (Quick)" << endl;
    cout << "\t\t\t  2. Register Citizen (Complete)" << endl;
    cout << "\t\t\t  3. Search Citizen by CNIC" << endl;
    cout << "\t\t\t  4. Remove Citizen" << endl;
    cout << "\t\t\t  5. List All Citizens" << endl;
    cout << "\n\t\t Housing Hierarchy" << endl;
    cout << "\t\t\t  6. Add Sector" << endl;
    cout << "\t\t\t  7. Add Street" << endl;
    cout << "\t\t\t  8. Add House" << endl;
    cout << "\t\t\t  9. Display Residential Hierarchy" << endl;
    cout << "\t\t\t  10. Display House Details" << endl;
    cout << "\n\t\t Family Management" << endl;
    cout << "\t\t\t  11. Register Family" << endl;
    cout << "\t\t\t  12. Add Family Member" << endl;
    cout << "\t\t\t  13. Display Family Tree" << endl;
    cout << "\t\t\t  14. List Family Members" << endl;
    cout << "\n\t\t Demographics" << endl;
    cout << "\t\t\t  15. Population Statistics" << endl;
    cout << "\t\t\t  16. Age Distribution" << endl;
    cout << "\t\t\t  17. Gender Distribution" << endl;
    cout << "\t\t\t  18. Occupation Statistics" << endl;
    cout << "\t\t\t  19. Education Statistics" << endl;
    cout << "\t\t\t  20. Income Distribution" << endl;
    cout << "\t\t\t  21. Complete Demographics" << endl;
    cout << "\t\t\t  22. City Analytics" << endl;
    cout << "\t\t\t  23. Generate Population Report" << endl;
    cout << "\n\t\t Surveys" << endl;
    cout << "\t\t\t  24. Create Survey" << endl;
    cout << "\t\t\t  25. Display Active Surveys" << endl;
    cout << "\n\t\t CSV Operations " << endl;
    cout << "\t\t\t  26. Load Population from CSV" << endl;
    cout << "\t\t\t  27. Load Families from CSV" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayCommercialMenu()
{
    cout << "\n......................COMMERCIAL SECTOR..................." << endl;
    cout << "\n\t\t  1. Register Shopping Mall" << endl;
    cout << "\t\t  2. Add Product" << endl;
    cout << "\t\t  3. Search Product by Category" << endl;
    cout << "\t\t  4. Find Nearest Mall" << endl;
    cout << "\t\t  5. Display All Malls" << endl;
    cout << "\t\t  6. Find Route to Mall" << endl;
    cout << "\n\t\t CSV Operations " << endl;
    cout << "\t\t  7. Load Malls from CSV" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayFacilityMenu()
{
    cout << "\n...................FACILITIES SECTOR..................." << endl;
    cout << "\n\t\t 1. Add Public Facility" << endl;
    cout << "\t\t  2. Get Facilities by Type" << endl;
    cout << "\t\t  3. Find Nearest Facility" << endl;
    cout << "\t\t  4. Display All Facilities" << endl;
    cout << "\t\t  5. Find Route to Facility" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayNavigationMenu()
{
    cout << "\n...................CITY NAVIGATION......................" << endl;
    cout << "\n\t\t  1. Navigate Between Any Two Locations" << endl;
    cout << "\t\t  2. Find Nearest Hospital" << endl;
    cout << "\t\t  3. Find Nearest School" << endl;
    cout << "\t\t  4. Find Nearest Bus Stop" << endl;
    cout << "\t\t  5. Find Nearest Mall" << endl;
    cout << "\t\t  6. Find Nearest Pharmacy" << endl;
    cout << "\t\t  7. Find Nearest Park" << endl;
    cout << "\t\t  8. Find Nearest Airport" << endl;
    cout << "\t\t  9. Find Nearest Railway Station" << endl;
    cout << "\t\t  10. Custom Search" << endl;
    cout << "\n\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayEmergencyMenu()
{
    cout << "\n.....................EMERGENCY ROUTING....................." << endl;
    cout << "\n\t\t  1. Create Emergency Request" << endl;
    cout << "\t\t  2. Dispatch Next Emergency" << endl;
    cout << "\t\t  3. Plan Emergency Route" << endl;
    cout << "\t\t  4. Display Active Emergencies" << endl;
    cout << "\t\t  5. Display Emergency History" << endl;
    cout << "\t\t  6. Emergency Statistics" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displaySchoolBusMenu()
{
    cout << "\n.................... SCHOOL BUS TRACKING......................" << endl;
    cout << "\n\t\t  1. Register School Bus" << endl;
    cout << "\t\t  2. Add Stop to Bus Route" << endl;
    cout << "\t\t  3. Assign Student to Bus" << endl;
    cout << "\t\t  4. Update Bus Location" << endl;
    cout << "\t\t  5. Track Bus" << endl;
    cout << "\t\t  6. Simulate Bus Trip" << endl;
    cout << "\t\t  7. Display School's Buses" << endl;
    cout << "\t\t  8. Find Student's Bus" << endl;
    cout << "\t\t  9. Display All School Buses" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayAirportRailMenu()
{
    cout << "\n.....................AIRPORT and RAIL.................." << endl;
    cout << "\n\t\t Transport Hubs" << endl;
    cout << "\t\t\t  1. Add Transport Hub" << endl;
    cout << "\t\t\t  2. Connect Hubs" << endl;
    cout << "\t\t\t  3. Display All Hubs" << endl;
    cout << "\n\t\t Flights" << endl;
    cout << "\t\t\t  4. Add Flight" << endl;
    cout << "\t\t\t  5. Search Flights" << endl;
    cout << "\t\t\t  6. Display All Flights" << endl;
    cout << "\n\t\t Trains" << endl;
    cout << "\t\t\t  7. Add Train" << endl;
    cout << "\t\t\t  8. Search Trains" << endl;
    cout << "\t\t\t  9. Display All Trains" << endl;
    cout << "\n\t\t Navigation" << endl;
    cout << "\t\t\t  10. Find Route to Airport" << endl;
    cout << "\t\t\t  11. Find Route to Railway Station" << endl;
    cout << "\t\t\t  12. Plan Multi-Modal Trip" << endl;
    cout << "\t\t\t  13. Transport Statistics" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayRouteSimMenu()
{
    cout << "\n.......................ROUTE SIMULATION....................." << endl;
    cout << "\n\t\t  1. Create Vehicle" << endl;
    cout << "\t\t  2. Set Vehicle Location" << endl;
    cout << "\t\t  3. Set Vehicle Destination" << endl;
    cout << "\t\t  4. Set Vehicle Speed" << endl;
    cout << "\t\t  5. Plan Route" << endl;
    cout << "\t\t  6. Simulate Route" << endl;
    cout << "\t\t  7. Simulate Emergency Route" << endl;
    cout << "\t\t  8. Simulate Traffic" << endl;
    cout << "\t\t  9. Display Vehicle Status" << endl;
    cout << "\t\t  10. Display Active Vehicles" << endl;
    cout << "\t\t  11. Display All Vehicles" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

void displayHeatmapMenu()
{
    cout << "\n..................POPULATION HEATMAP......................" << endl;
    cout << "\n\t\t  1. Add Sector" << endl;
    cout << "\t\t  2. Update Sector Population" << endl;
    cout << "\t\t  3. Population Density Heatmap" << endl;
    cout << "\t\t  4. Income Level Heatmap" << endl;
    cout << "\t\t  5. Gender Distribution Heatmap" << endl;
    cout << "\t\t  6. Age Distribution Heatmap" << endl;
    cout << "\t\t  7. Sector Comparison Report" << endl;
    cout << "\t\t  8. Find High Density Areas" << endl;
    cout << "\t\t  9. Display All Sectors" << endl;
    cout << "\n\t\t  0. Back to Main Menu" << endl;
    cout << endl;
    cout << "Enter choice: ";
}

// Handler Declarations
void handleTransportSystem(SmartCityManager *city);
void handleEducationSystem(SmartCityManager *city);
void handleMedicalSystem(SmartCityManager *city);
void handlePopulationSystem(SmartCityManager *city);
void handleCommercialSystem(SmartCityManager *city);
void handleFacilitySystem(SmartCityManager *city);
void handleNavigation(SmartCityManager *city);
void handleCityInfo(SmartCityManager *city);
void handleEmergencySystem(SmartCityManager *city);
void handleSchoolBusSystem(SmartCityManager *city);
void handleAirportRailSystem(SmartCityManager *city);
void handleRouteSimulator(SmartCityManager *city);
void handleHeatmapSystem(SmartCityManager *city);

// MAIN FUNCTION
int main()
{
    SmartCityManager *city = new SmartCityManager("Islamabad", "Pakistan");
    city->setCityInfo("Islamabad", "Pakistan", 33.6844, 73.0479, 0);

    int choice;

    while (true)
    {
        displayMainMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            handleTransportSystem(city);
            break;
        case 2:
            handleEducationSystem(city);
            break;
        case 3:
            handleMedicalSystem(city);
            break;
        case 4:
            handlePopulationSystem(city);
            break;
        case 5:
            handleCommercialSystem(city);
            break;
        case 6:
            handleFacilitySystem(city);
            break;
        case 7:
            handleNavigation(city);
            break;
        case 8:
            handleCityInfo(city);
            break;
        case 9:
            handleEmergencySystem(city);
            break;
        case 10:
            handleSchoolBusSystem(city);
            break;
        case 11:
            handleAirportRailSystem(city);
            break;
        case 12:
            handleRouteSimulator(city);
            break;
        case 13:
            handleHeatmapSystem(city);
            break;
        case 0:
            cout << "\n    Thank you for using Smart City System!    \n"
                 << endl;
            delete city;
            return 0;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
    return 0;
}

// TRANSPORT HANDLER
void handleTransportSystem(SmartCityManager *city)
{
    int choice, count;
    char busNumber[20], company[50], stopId[20], name[100], destination[20];
    char passengerId[20], contact[20], from[50], to[50], filename[200], stop[20], route[20];
    double lat, lon;

    while (true)
    {
        displayTransportMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Bus Number: ";
            cin.getline(busNumber, 20);
            if (isEmpty(busNumber))
            {
                cout << "Error: Bus number required!" << endl;
                break;
            }
            cout << "Enter Company: ";
            cin.getline(company, 50);
            if (isEmpty(company))
            {
                cout << "Error: Company required!" << endl;
                break;
            }
            cout << "Enter current stop: ";
            cin.getline(stop, 20);
            cout << "Enter route: ";
            cin.getline(route, 20);
            city->registerBus(busNumber, company, stop, route);
            break;
        case 2:
            cout << "\nEnter Stop ID: ";
            cin.getline(stopId, 20);
            if (isEmpty(stopId))
            {
                cout << "Error: Stop ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Latitude: ";
            if (!getDouble(lat))
                break;
            cout << "Enter Longitude: ";
            if (!getDouble(lon))
                break;
            cin.ignore();
            city->addBusStop(stopId, name, lat, lon);
            break;
        case 3:
            cout << "\nEnter Bus Number: ";
            cin.getline(busNumber, 20);
            if (isEmpty(busNumber))
            {
                cout << "Error: Bus number required!" << endl;
                break;
            }
            cout << "Enter Stop ID: ";
            cin.getline(stopId, 20);
            if (isEmpty(stopId))
            {
                cout << "Error: Stop ID required!" << endl;
                break;
            }
            city->addStopToBusRoute(busNumber, stopId);
            break;
        case 4:
            cout << "\nEnter Bus Number: ";
            cin.getline(busNumber, 20);
            if (isEmpty(busNumber))
            {
                cout << "Error: Bus number required!" << endl;
                break;
            }
            city->trackBusLocation(busNumber);
            break;
        case 5:
            cout << "\nEnter Bus Number: ";
            cin.getline(busNumber, 20);
            if (isEmpty(busNumber))
            {
                cout << "Error: Bus number required!" << endl;
                break;
            }
            city->showBusRoute(busNumber);
            break;
        case 6:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter To: ";
            cin.getline(to, 50);
            if (isEmpty(to))
            {
                cout << "Error: To required!" << endl;
                break;
            }
            city->findShortestPath(from, to);
            break;
        case 7:
            city->displayAllBuses();
            break;
        case 8:
            city->displayAllStops();
            break;
        case 9:
            city->displayCityMap();
            break;
        case 10:
            cout << "\nEnter Stop ID: ";
            cin.getline(stopId, 20);
            if (isEmpty(stopId))
            {
                cout << "Error: Stop ID required!" << endl;
                break;
            }
            cout << "Enter Passenger ID: ";
            cin.getline(passengerId, 20);
            if (isEmpty(passengerId))
            {
                cout << "Error: Passenger ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Destination Stop: ";
            cin.getline(destination, 20);
            cout << "Enter Contact (optional): ";
            cin.getline(contact, 20);
            city->addPassengerToStop(stopId, passengerId, name, destination, contact);
            break;
        case 11:
            cout << "\nEnter Stop ID: ";
            cin.getline(stopId, 20);
            if (isEmpty(stopId))
            {
                cout << "Error: Stop ID required!" << endl;
                break;
            }
            city->displayStopQueue(stopId);
            break;
        case 12:
            cout << "\nEnter Bus Number: ";
            cin.getline(busNumber, 20);
            if (isEmpty(busNumber))
            {
                cout << "Error: Bus number required!" << endl;
                break;
            }
            cout << "Enter Stop ID: ";
            cin.getline(stopId, 20);
            if (isEmpty(stopId))
            {
                cout << "Error: Stop ID required!" << endl;
                break;
            }
            city->simulateBusArrival(busNumber, stopId);
            break;
        case 13:
            cout << "\nEnter Stop ID: ";
            cin.getline(stopId, 20);
            if (isEmpty(stopId))
            {
                cout << "Error: Stop ID required!" << endl;
                break;
            }
            cout << "Enter number of passengers: ";
            if (!getInt(count) || count <= 0)
            {
                cout << "Error: Invalid count!" << endl;
                break;
            }
            city->simulatePassengerArrivals(stopId, count);
            break;
        case 14:
            city->displayTravelHistory();
            break;
        case 15:
            cout << "\nHow many trips? ";
            if (!getInt(count) || count <= 0)
            {
                cout << "Error: Invalid count!" << endl;
                break;
            }
            city->displayRecentTrips(count);
            break;
        case 16:
            city->undoLastTrip();
            break;
        case 17:
            city->getTravelStats();
            break;
        case 18:
            city->clearTravelHistory();
            break;
        case 19:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadStopsFromCSV(filename);
            break;
        case 20:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadBusesFromCSV(filename);
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// EDUCATION HANDLER
void handleEducationSystem(SmartCityManager *city)
{
    int choice, capacity, salary, experience, age, count;
    char schoolId[20], name[100], sector[20], subject[50], deptId[20], deptName[50], subs[200];
    char head[50], classId[20], className[50], teacherId[20], qual[50], spec[50];
    char studentId[20], section[10], from[50], filename[200];
    double rating;

    while (true)
    {
        displayEducationMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            if (isEmpty(sector))
            {
                cout << "Error: Sector required!" << endl;
                break;
            }
            cout << "Enter Rating (0-5): ";

            if (!getDouble(rating) || rating < 0 || rating > 5)
            {
                cout << "Error: Rating must be 0-5!" << endl;
                break;
            }
            cin.ignore();

            cout << "Enter Subjects: ";
            cin.getline(subs, 200);
            city->registerSchool(schoolId, name, sector, rating, subs);
            break;
        case 2:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            cout << "Enter Subject: ";
            cin.getline(subject, 50);
            if (isEmpty(subject))
            {
                cout << "Error: Subject required!" << endl;
                break;
            }
            city->addSubjectToSchool(schoolId, subject);
            break;
        case 3:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            cout << "Enter Dept ID: ";
            cin.getline(deptId, 20);
            if (isEmpty(deptId))
            {
                cout << "Error: Dept ID required!" << endl;
                break;
            }
            cout << "Enter Dept Name: ";
            cin.getline(deptName, 50);
            cout << "Enter Head of Dept: ";
            cin.getline(head, 50);
            city->addDepartment(schoolId, deptId, deptName, head);
            break;
        case 4:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            cout << "Enter Dept ID: ";
            cin.getline(deptId, 20);
            if (isEmpty(deptId))
            {
                cout << "Error: Dept ID required!" << endl;
                break;
            }
            cout << "Enter Class ID: ";
            cin.getline(classId, 20);
            if (isEmpty(classId))
            {
                cout << "Error: Class ID required!" << endl;
                break;
            }
            cout << "Enter Class Name: ";
            cin.getline(className, 50);
            cout << "Enter Capacity: ";
            if (!getInt(capacity) || capacity <= 0)
            {
                cout << "Error: Invalid capacity!" << endl;
                break;
            }
            city->addClass(schoolId, deptId, classId, className, capacity);
            break;
        case 5:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            city->displaySchoolHierarchy(schoolId);
            break;
        case 6:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            city->displaySchoolDetails(schoolId);
            break;
        case 7:
            city->displayAllSchools();
            break;
        case 8:
            cout << "\nEnter Teacher ID: ";
            cin.getline(teacherId, 20);
            if (isEmpty(teacherId))
            {
                cout << "Error: Teacher ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Qualification: ";
            cin.getline(qual, 50);
            cout << "Enter Specialization: ";
            cin.getline(spec, 50);
            cout << "Enter School ID: ";
            cin.getline(schoolId, 20);
            cout << "Enter Salary: ";
            if (!getInt(salary) || salary < 0)
            {
                cout << "Error: Invalid salary!" << endl;
                break;
            }
            cout << "Enter Experience: ";
            if (!getInt(experience) || experience < 0)
            {
                cout << "Error: Invalid experience!" << endl;
                break;
            }
            city->registerTeacher(teacherId, name, qual, spec, schoolId, salary, experience);
            break;
        case 9:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            cout << "Enter Class ID: ";
            cin.getline(classId, 20);
            if (isEmpty(classId))
            {
                cout << "Error: Class ID required!" << endl;
                break;
            }
            cout << "Enter Teacher ID: ";
            cin.getline(teacherId, 20);
            if (isEmpty(teacherId))
            {
                cout << "Error: Teacher ID required!" << endl;
                break;
            }
            city->assignTeacherToClass(schoolId, classId, teacherId);
            break;
        case 10:
            cout << "\nEnter Teacher ID: ";
            cin.getline(teacherId, 20);
            if (isEmpty(teacherId))
            {
                cout << "Error: Teacher ID required!" << endl;
                break;
            }
            city->displayTeacherDetails(teacherId);
            break;
        case 11:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            cout << "Enter Class ID: ";
            cin.getline(classId, 20);
            if (isEmpty(classId))
            {
                cout << "Error: Class ID required!" << endl;
                break;
            }
            cout << "Enter Student ID: ";
            cin.getline(studentId, 20);
            if (isEmpty(studentId))
            {
                cout << "Error: Student ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Age: ";
            if (!getInt(age) || age <= 0)
            {
                cout << "Error: Invalid age!" << endl;
                break;
            }
            cout << "Enter Section: ";
            cin.getline(section, 10);
            city->enrollStudent(schoolId, classId, studentId, name, age, section);
            break;
        case 12:
            cout << "\nHow many top schools? ";
            if (!getInt(count) || count <= 0)
            {
                cout << "Error: Invalid count!" << endl;
                break;
            }
            city->displayTopSchools(count);
            break;
        case 13:
            cout << "\nEnter Subject: ";
            cin.getline(subject, 50);
            if (isEmpty(subject))
            {
                cout << "Error: Subject required!" << endl;
                break;
            }
            city->searchSchoolsBySubject(subject);
            break;
        case 14:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "School");
            break;
        case 15:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            city->navigateBetweenLocations(from, schoolId);
            break;
        case 16:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadSchoolsFromCSV(filename);
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// MEDICAL HANDLER
void handleMedicalSystem(SmartCityManager *city)
{
    int choice, totalBeds, floor, numBeds, experience, fee, age, severity, stock;
    char hospitalId[20], name[100], sector[20], spec[50], blockId[20], blockName[50];
    char blockType[20], wardId[20], wardName[50], wardType[20], doctorId[20];
    char patientId[20], cnic[20], gender[10], bloodType[5], condition[200];
    char pharmacyId[20], medicineName[50], formula[100], from[50], filename[200], sp[200];
    double lat, lon, price;

    while (true)
    {
        displayMedicalMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            if (isEmpty(sector))
            {
                cout << "Error: Sector required!" << endl;
                break;
            }
            cout << "Enter Total Beds: ";
            if (!getInt(totalBeds) || totalBeds <= 0)
            {
                cout << "Error: Invalid beds!" << endl;
                break;
            }
            cout << "Enter Latitude: ";
            if (!getDouble(lat))
                break;
            cout << "Enter Longitude: ";
            if (!getDouble(lon))
                break;
            cin.ignore();
            cout << "Enter Specialization(comma separated): ";
            cin.getline(sp, 200);
            city->registerHospital(hospitalId, name, sector, totalBeds, lat, lon, sp);
            break;
        case 2:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            cout << "Enter Specialization: ";
            cin.getline(spec, 50);
            if (isEmpty(spec))
            {
                cout << "Error: Specialization required!" << endl;
                break;
            }
            city->addSpecializationToHospital(hospitalId, spec);
            break;
        case 3:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            cout << "Enter Block ID: ";
            cin.getline(blockId, 20);
            if (isEmpty(blockId))
            {
                cout << "Error: Block ID required!" << endl;
                break;
            }
            cout << "Enter Block Name: ";
            cin.getline(blockName, 50);
            cout << "Enter Block Type: ";
            cin.getline(blockType, 20);
            cout << "Enter Floor: ";
            if (!getInt(floor))
            {
                cout << "Error: Invalid floor!" << endl;
                break;
            }
            city->addBlock(hospitalId, blockId, blockName, blockType, floor);
            break;
        case 4:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            cout << "Enter Block ID: ";
            cin.getline(blockId, 20);
            if (isEmpty(blockId))
            {
                cout << "Error: Block ID required!" << endl;
                break;
            }
            cout << "Enter Ward ID: ";
            cin.getline(wardId, 20);
            if (isEmpty(wardId))
            {
                cout << "Error: Ward ID required!" << endl;
                break;
            }
            cout << "Enter Ward Name: ";
            cin.getline(wardName, 50);
            cout << "Enter Ward Type: ";
            cin.getline(wardType, 20);
            cout << "Enter Num Beds: ";
            if (!getInt(numBeds) || numBeds <= 0)
            {
                cout << "Error: Invalid beds!" << endl;
                break;
            }
            city->addWard(hospitalId, blockId, wardId, wardName, wardType, numBeds);
            break;
        case 5:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            city->displayHospitalHierarchy(hospitalId);
            break;
        case 6:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            city->displayHospitalDetails(hospitalId);
            break;
        case 7:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            city->checkBedAvailability(hospitalId);
            break;
        case 8:
            city->displayAllHospitals();
            break;
        case 9:
            cout << "\nEnter Doctor ID: ";
            cin.getline(doctorId, 20);
            if (isEmpty(doctorId))
            {
                cout << "Error: Doctor ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Specialization: ";
            cin.getline(spec, 50);
            cout << "Enter Hospital ID: ";
            cin.getline(hospitalId, 20);
            cout << "Enter Experience: ";
            if (!getInt(experience) || experience < 0)
            {
                cout << "Error: Invalid experience!" << endl;
                break;
            }
            cout << "Enter Fee: ";
            if (!getInt(fee) || fee < 0)
            {
                cout << "Error: Invalid fee!" << endl;
                break;
            }
            city->registerDoctor(doctorId, name, spec, hospitalId, experience, fee);
            break;
        case 10:
            cout << "\nEnter Doctor ID: ";
            cin.getline(doctorId, 20);
            if (isEmpty(doctorId))
            {
                cout << "Error: Doctor ID required!" << endl;
                break;
            }
            city->displayDoctorDetails(doctorId);
            break;
        case 11:
            cout << "\nEnter Patient ID: ";
            cin.getline(patientId, 20);
            if (isEmpty(patientId))
            {
                cout << "Error: Patient ID required!" << endl;
                break;
            }
            cout << "Enter CNIC: ";
            cin.getline(cnic, 20);
            if (isEmpty(cnic))
            {
                cout << "Error: CNIC required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Age: ";
            if (!getInt(age) || age <= 0)
            {
                cout << "Error: Invalid age!" << endl;
                break;
            }
            cout << "Enter Gender: ";
            cin.getline(gender, 10);
            cout << "Enter Blood Type: ";
            cin.getline(bloodType, 5);
            city->registerPatient(patientId, cnic, name, age, gender, bloodType);
            break;
        case 12:
            cout << "\nEnter Patient ID: ";
            cin.getline(patientId, 20);
            if (isEmpty(patientId))
            {
                cout << "Error: Patient ID required!" << endl;
                break;
            }
            city->displayPatientDetails(patientId);
            break;
        case 13:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            cout << "Enter Patient ID: ";
            cin.getline(patientId, 20);
            if (isEmpty(patientId))
            {
                cout << "Error: Patient ID required!" << endl;
                break;
            }
            cout << "Enter Condition: ";
            cin.getline(condition, 200);
            cout << "Enter Severity (1-10): ";
            if (!getInt(severity) || severity < 1 || severity > 10)
            {
                cout << "Error: Severity 1-10!" << endl;
                break;
            }
            city->addEmergencyPatient(hospitalId, patientId, condition, severity);
            break;
        case 14:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            city->treatNextEmergencyPatient(hospitalId);
            break;
        case 15:
            cout << "\nEnter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            cout << "Enter Patient ID: ";
            cin.getline(patientId, 20);
            if (isEmpty(patientId))
            {
                cout << "Error: Patient ID required!" << endl;
                break;
            }
            cout << "Enter Ward ID: ";
            cin.getline(wardId, 20);
            cout << "Enter Doctor ID: ";
            cin.getline(doctorId, 20);
            city->admitPatient(hospitalId, patientId, wardId, doctorId);
            break;
        case 16:
            cout << "\nEnter Pharmacy ID: ";
            cin.getline(pharmacyId, 20);
            if (isEmpty(pharmacyId))
            {
                cout << "Error: Pharmacy ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            cout << "Enter Medicine Name: ";
            cin.getline(medicineName, 50);
            cout << "Enter Formula: ";
            cin.getline(formula, 100);
            cout << "Enter Price: ";
            if (!getDouble(price) || price < 0)
            {
                cout << "Error: Invalid price!" << endl;
                break;
            }
            cin.ignore();
            city->registerPharmacy(pharmacyId, name, sector, medicineName, formula, price);
            break;
        case 17:
            cout << "\nEnter Medicine Name: ";
            cin.getline(medicineName, 50);
            if (isEmpty(medicineName))
            {
                cout << "Error: Medicine name required!" << endl;
                break;
            }
            cout << "Enter Formula: ";
            cin.getline(formula, 100);
            cout << "Enter Price: ";
            if (!getDouble(price) || price < 0)
            {
                cout << "Error: Invalid price!" << endl;
                break;
            }
            cout << "Enter Stock: ";
            if (!getInt(stock) || stock < 0)
            {
                cout << "Error: Invalid stock!" << endl;
                break;
            }
            cout << "Enter Pharmacy ID: ";
            cin.getline(pharmacyId, 20);
            cout << "Enter Pharmacy Name: ";
            cin.getline(name, 100);
            city->addMedicine(medicineName, formula, price, stock, pharmacyId, name);
            break;
        case 18:
            cout << "\nEnter Medicine Name: ";
            cin.getline(medicineName, 50);
            if (isEmpty(medicineName))
            {
                cout << "Error: Medicine name required!" << endl;
                break;
            }
            city->searchMedicine(medicineName);
            break;
        case 19:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "Hospital");
            break;
        case 20:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter Hospital ID: ";
            cin.getline(hospitalId, 20);
            if (isEmpty(hospitalId))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            city->navigateBetweenLocations(from, hospitalId);
            break;
        case 21:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadHospitalsFromCSV(filename);
            break;
        case 22:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadPharmaciesFromCSV(filename);
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// POPULATION HANDLER
void handlePopulationSystem(SmartCityManager *city)
{
    int choice, age, income;
    char cnic[20], name[100], gender[10], occupation[50], education[50];
    char sector[20], maritalStatus[20], street[50], houseNumber[20];
    char dob[20], bloodType[5], contact[20], email[100];
    char familyId[20], houseId[50], relation[50], parentCNIC[20], filename[200];
    char surveyId[20], title[200], description[500];
    double lat, lon;

    while (true)
    {
        displayPopulationMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter CNIC: ";
            cin.getline(cnic, 20);
            if (isEmpty(cnic))
            {
                cout << "Error: CNIC required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Age: ";
            if (!getInt(age) || age <= 0)
            {
                cout << "Error: Invalid age!" << endl;
                break;
            }
            cout << "Enter Gender: ";
            cin.getline(gender, 10);
            cout << "Enter Occupation: ";
            cin.getline(occupation, 50);
            cout << "Enter Education: ";
            cin.getline(education, 50);
            cout << "Enter Income: ";
            if (!getInt(income) || income < 0)
            {
                cout << "Error: Invalid income!" << endl;
                break;
            }
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            cout << "Enter Marital Status: ";
            cin.getline(maritalStatus, 20);
            city->registerCitizen(cnic, name, age, gender, occupation, education, income, sector, maritalStatus);
            break;
        case 2:
            cout << "\nEnter CNIC: ";
            cin.getline(cnic, 20);
            if (isEmpty(cnic))
            {
                cout << "Error: CNIC required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Age: ";
            if (!getInt(age) || age <= 0)
            {
                cout << "Error: Invalid age!" << endl;
                break;
            }
            cout << "Enter Gender: ";
            cin.getline(gender, 10);
            cout << "Enter DOB: ";
            cin.getline(dob, 20);
            cout << "Enter Blood Type: ";
            cin.getline(bloodType, 5);
            cout << "Enter Contact: ";
            cin.getline(contact, 20);
            cout << "Enter Email: ";
            cin.getline(email, 100);
            cout << "Enter Occupation: ";
            cin.getline(occupation, 50);
            cout << "Enter Education: ";
            cin.getline(education, 50);
            cout << "Enter Income: ";
            if (!getInt(income) || income < 0)
            {
                cout << "Error: Invalid income!" << endl;
                break;
            }
            cout << "Enter Marital Status: ";
            cin.getline(maritalStatus, 20);
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            cout << "Enter Street: ";
            cin.getline(street, 50);
            cout << "Enter House Number: ";
            cin.getline(houseNumber, 20);
            cout << "Enter Latitude: ";
            if (!getDouble(lat))
                break;
            cout << "Enter Longitude: ";
            if (!getDouble(lon))
                break;
            cin.ignore();
            city->registerCitizenComplete(cnic, name, age, gender, dob, bloodType, contact, email,
                                          occupation, education, income, maritalStatus, sector, street, houseNumber, lat, lon);
            break;
        case 3:
            cout << "\nEnter CNIC: ";
            cin.getline(cnic, 20);
            if (isEmpty(cnic))
            {
                cout << "Error: CNIC required!" << endl;
                break;
            }
            city->searchCitizen(cnic);
            break;
        case 4:
            cout << "\nEnter CNIC: ";
            cin.getline(cnic, 20);
            if (isEmpty(cnic))
            {
                cout << "Error: CNIC required!" << endl;
                break;
            }
            city->removeCitizen(cnic);
            break;
        case 5:
            city->listAllCitizens();
            break;
        case 6:
            cout << "\nEnter Sector Name: ";
            cin.getline(sector, 20);
            if (isEmpty(sector))
            {
                cout << "Error: Sector required!" << endl;
                break;
            }
            city->addSector(sector);
            break;
        case 7:
            cout << "\nEnter Sector: ";
            cin.getline(sector, 20);
            if (isEmpty(sector))
            {
                cout << "Error: Sector required!" << endl;
                break;
            }
            cout << "Enter Street Name: ";
            cin.getline(street, 50);
            if (isEmpty(street))
            {
                cout << "Error: Street required!" << endl;
                break;
            }
            city->addStreet(sector, street);
            break;
        case 8:
            cout << "\nUse complete citizen registration." << endl;
            break;
        case 9:
            city->displayResidentialHierarchy();
            break;
        case 10:
            cout << "\nEnter House ID: ";
            cin.getline(houseId, 50);
            if (isEmpty(houseId))
            {
                cout << "Error: House ID required!" << endl;
                break;
            }
            city->displayHouseDetails(houseId);
            break;
        case 11:
            cout << "\nEnter Family ID: ";
            cin.getline(familyId, 20);
            if (isEmpty(familyId))
            {
                cout << "Error: Family ID required!" << endl;
                break;
            }
            cout << "Enter House ID: ";
            cin.getline(houseId, 50);
            cout << "Enter Head CNIC: ";
            cin.getline(cnic, 20);
            if (isEmpty(cnic))
            {
                cout << "Error: CNIC required!" << endl;
                break;
            }
            cout << "Enter Head Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Relation: ";
            cin.getline(relation, 50);
            cout << "Enter Age: ";
            if (!getInt(age) || age <= 0)
            {
                cout << "Error: Invalid age!" << endl;
                break;
            }
            cout << "Enter Gender: ";
            cin.getline(gender, 10);
            city->registerFamily(familyId, houseId, cnic, name, relation, age, gender);
            break;
        case 12:
            cout << "\nEnter Family ID: ";
            cin.getline(familyId, 20);
            if (isEmpty(familyId))
            {
                cout << "Error: Family ID required!" << endl;
                break;
            }
            cout << "Enter CNIC: ";
            cin.getline(cnic, 20);
            if (isEmpty(cnic))
            {
                cout << "Error: CNIC required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Relation: ";
            cin.getline(relation, 50);
            cout << "Enter Age: ";
            if (!getInt(age) || age <= 0)
            {
                cout << "Error: Invalid age!" << endl;
                break;
            }
            cout << "Enter Gender: ";
            cin.getline(gender, 10);
            cout << "Parent CNIC (Enter to skip): ";
            cin.getline(parentCNIC, 20);
            if (parentCNIC[0] != '\0')
                city->addFamilyMember(familyId, cnic, name, relation, age, gender, parentCNIC);
            else
                city->addFamilyMember(familyId, cnic, name, relation, age, gender);
            break;
        case 13:
            cout << "\nEnter Family ID: ";
            cin.getline(familyId, 20);
            if (isEmpty(familyId))
            {
                cout << "Error: Family ID required!" << endl;
                break;
            }
            city->displayFamilyTree(familyId);
            break;
        case 14:
            cout << "\nEnter Family ID: ";
            cin.getline(familyId, 20);
            if (isEmpty(familyId))
            {
                cout << "Error: Family ID required!" << endl;
                break;
            }
            city->listFamilyMembers(familyId);
            break;
        case 15:
            city->displayPopulationStatistics();
            break;
        case 16:
            city->displayAgeDistribution();
            break;
        case 17:
            city->displayGenderDistribution();
            break;
        case 18:
            city->displayOccupationStats();
            break;
        case 19:
            city->displayEducationStats();
            break;
        case 20:
            city->displayIncomeStats();
            break;
        case 21:
            city->displayCompleteDemographics();
            break;
        case 22:
            city->displayCityAnalytics();
            break;
        case 23:
            city->generatePopulationReport();
            break;
        case 24:
            cout << "\nEnter Survey ID: ";
            cin.getline(surveyId, 20);
            if (isEmpty(surveyId))
            {
                cout << "Error: Survey ID required!" << endl;
                break;
            }
            cout << "Enter Title: ";
            cin.getline(title, 200);
            if (isEmpty(title))
            {
                cout << "Error: Title required!" << endl;
                break;
            }
            cout << "Enter Description: ";
            cin.getline(description, 500);
            city->createSurvey(surveyId, title, description);
            break;
        case 25:
            city->displayActiveSurveys();
            break;
        case 26:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadCitizensFromCSV(filename);
            break;
        case 27:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadFamiliesFromCSV(filename);
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// COMMERCIAL HANDLER
void handleCommercialSystem(SmartCityManager *city)
{
    int choice;
    char mallId[20], name[100], sector[20], productId[20], category[50], from[50], filename[200];
    double lat, lon, price;

    while (true)
    {
        displayCommercialMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Mall ID: ";
            cin.getline(mallId, 20);
            if (isEmpty(mallId))
            {
                cout << "Error: Mall ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            cout << "Enter Latitude: ";
            if (!getDouble(lat))
                break;
            cout << "Enter Longitude: ";
            if (!getDouble(lon))
                break;
            cin.ignore();
            city->registerMall(mallId, name, sector, lat, lon);
            break;
        case 2:
            cout << "\nEnter Product ID: ";
            cin.getline(productId, 20);
            if (isEmpty(productId))
            {
                cout << "Error: Product ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Category: ";
            cin.getline(category, 50);
            cout << "Enter Price: ";
            if (!getDouble(price) || price < 0)
            {
                cout << "Error: Invalid price!" << endl;
                break;
            }
            cin.ignore();
            cout << "Enter Mall ID: ";
            cin.getline(mallId, 20);
            city->addProduct(productId, name, category, price, mallId);
            break;
        case 3:
            cout << "\nEnter Category: ";
            cin.getline(category, 50);
            if (isEmpty(category))
            {
                cout << "Error: Category required!" << endl;
                break;
            }
            city->searchProductByCategory(category);
            break;
        case 4:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestMall(from);
            break;
        case 5:
            city->displayAllMalls();
            break;
        case 6:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter Mall ID: ";
            cin.getline(mallId, 20);
            if (isEmpty(mallId))
            {
                cout << "Error: Mall ID required!" << endl;
                break;
            }
            city->navigateBetweenLocations(from, mallId);
            break;
        case 7:
            cout << "\nEnter filename: ";
            cin.getline(filename, 200);
            if (isEmpty(filename))
            {
                cout << "Error: Filename required!" << endl;
                break;
            }
            city->loadMallsFromCSV(filename);
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// FACILITY HANDLER
void handleFacilitySystem(SmartCityManager *city)
{
    int choice;
    char facilityId[20], name[100], type[50], sector[20], from[50];
    double lat, lon;

    while (true)
    {
        displayFacilityMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Facility ID: ";
            cin.getline(facilityId, 20);
            if (isEmpty(facilityId))
            {
                cout << "Error: Facility ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Type: ";
            cin.getline(type, 50);
            if (isEmpty(type))
            {
                cout << "Error: Type required!" << endl;
                break;
            }
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            cout << "Enter Latitude: ";
            if (!getDouble(lat))
                break;
            cout << "Enter Longitude: ";
            if (!getDouble(lon))
                break;
            cin.ignore();
            city->addPublicFacility(facilityId, name, type, sector, lat, lon);
            break;
        case 2:
            cout << "\nEnter Type: ";
            cin.getline(type, 50);
            if (isEmpty(type))
            {
                cout << "Error: Type required!" << endl;
                break;
            }
            city->getFacilitiesByType(type);
            break;
        case 3:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            cout << "Enter Facility Type: ";
            cin.getline(type, 50);
            if (isEmpty(type))
            {
                cout << "Error: Type required!" << endl;
                break;
            }
            city->findNearestFacility(from, type);
            break;
        case 4:
            city->displayAllFacilities();
            break;
        case 5:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter Facility ID: ";
            cin.getline(facilityId, 20);
            if (isEmpty(facilityId))
            {
                cout << "Error: Facility ID required!" << endl;
                break;
            }
            city->navigateBetweenLocations(from, facilityId);
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// NAVIGATION HANDLER
void handleNavigation(SmartCityManager *city)
{
    int choice;
    char from[50], to[50], searchTerm[50];

    while (true)
    {
        displayNavigationMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter To: ";
            cin.getline(to, 50);
            if (isEmpty(to))
            {
                cout << "Error: To required!" << endl;
                break;
            }
            city->navigateBetweenLocations(from, to);
            break;
        case 2:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "Hospital");
            break;
        case 3:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "School");
            break;
        case 4:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "Stop");
            break;
        case 5:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "Mall");
            break;
        case 6:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "Pharmacy");
            break;
        case 7:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findNearestLocation(from, "Park");
            break;
        case 8:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findRouteToAirport(from);
            break;
        case 9:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findRouteToStation(from);
            break;
        case 10:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            cout << "Enter search term: ";
            cin.getline(searchTerm, 50);
            if (isEmpty(searchTerm))
            {
                cout << "Error: Search term required!" << endl;
                break;
            }
            city->findNearestLocation(from, searchTerm);
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// CITY INFO HANDLER
void handleCityInfo(SmartCityManager *city)
{
    int choice;
    cout << "\n....................CITY INFO.........." << endl;
    cout << "\n\t\t  1. Display City Map" << endl;
    cout << "\t\t  2. Display City Statistics" << endl;
    cout << "\n\t\t  0. Back" << endl;
    cout << endl;
    cout << "Enter choice: ";
    if (!getInt(choice))
        return;

    switch (choice)
    {
    case 1:
        city->displayCityMap();
        break;
    case 2:
        city->displayCityStatistics();
        break;
    }
}

// EMERGENCY HANDLER
void handleEmergencySystem(SmartCityManager *city)
{
    int choice, priority;
    char location[50], patientName[100], condition[200], from[50], to[50];

    while (true)
    {
        displayEmergencyMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Location: ";
            cin.getline(location, 50);
            if (isEmpty(location))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            cout << "Enter Patient Name: ";
            cin.getline(patientName, 100);
            if (isEmpty(patientName))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Condition: ";
            cin.getline(condition, 200);
            cout << "Enter Priority (1-4): ";
            if (!getInt(priority) || priority < 1 || priority > 4)
            {
                cout << "Error: Priority 1-4!" << endl;
                break;
            }
            city->createEmergencyRequest(location, patientName, condition, priority);
            break;
        case 2:
            city->dispatchNextEmergency();
            break;
        case 3:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter Hospital ID: ";
            cin.getline(to, 50);
            if (isEmpty(to))
            {
                cout << "Error: Hospital ID required!" << endl;
                break;
            }
            city->planEmergencyRoute(from, to);
            break;
        case 4:
            city->displayActiveEmergencies();
            break;
        case 5:
            city->displayEmergencyHistory();
            break;
        case 6:
            city->getEmergencyStats();
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// SCHOOL BUS HANDLER
void handleSchoolBusSystem(SmartCityManager *city)
{
    int choice, capacity;
    char busId[20], schoolId[20], driverName[100], stopId[50], stopName[100];
    char studentId[20], pickupStop[50], locationId[50];
    double lat, lon;

    while (true)
    {
        displaySchoolBusMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Bus ID: ";
            cin.getline(busId, 20);
            if (isEmpty(busId))
            {
                cout << "Error: Bus ID required!" << endl;
                break;
            }
            cout << "Enter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            cout << "Enter Driver Name: ";
            cin.getline(driverName, 100);
            if (isEmpty(driverName))
            {
                cout << "Error: Driver name required!" << endl;
                break;
            }
            cout << "Enter Capacity: ";
            if (!getInt(capacity) || capacity <= 0)
            {
                cout << "Error: Invalid capacity!" << endl;
                break;
            }
            city->registerSchoolBus(busId, schoolId, driverName, capacity);
            break;
        case 2:
            cout << "\nEnter Bus ID: ";
            cin.getline(busId, 20);
            if (isEmpty(busId))
            {
                cout << "Error: Bus ID required!" << endl;
                break;
            }
            cout << "Enter Stop ID: ";
            cin.getline(stopId, 50);
            if (isEmpty(stopId))
            {
                cout << "Error: Stop ID required!" << endl;
                break;
            }
            cout << "Enter Stop Name: ";
            cin.getline(stopName, 100);
            cout << "Enter Latitude: ";
            if (!getDouble(lat))
                break;
            cout << "Enter Longitude: ";
            if (!getDouble(lon))
                break;
            cin.ignore();
            city->addStopToSchoolBusRoute(busId, stopId, stopName, lat, lon);
            break;
        case 3:
            cout << "\nEnter Student ID: ";
            cin.getline(studentId, 20);
            if (isEmpty(studentId))
            {
                cout << "Error: Student ID required!" << endl;
                break;
            }
            cout << "Enter Bus ID: ";
            cin.getline(busId, 20);
            if (isEmpty(busId))
            {
                cout << "Error: Bus ID required!" << endl;
                break;
            }
            cout << "Enter Pickup Stop: ";
            cin.getline(pickupStop, 50);
            city->assignStudentToSchoolBus(studentId, busId, pickupStop);
            break;
        case 4:
            cout << "\nEnter Bus ID: ";
            cin.getline(busId, 20);
            if (isEmpty(busId))
            {
                cout << "Error: Bus ID required!" << endl;
                break;
            }
            cout << "Enter Location ID: ";
            cin.getline(locationId, 50);
            if (isEmpty(locationId))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->updateSchoolBusLocation(busId, locationId);
            break;
        case 5:
            cout << "\nEnter Bus ID: ";
            cin.getline(busId, 20);
            if (isEmpty(busId))
            {
                cout << "Error: Bus ID required!" << endl;
                break;
            }
            city->trackSchoolBus(busId);
            break;
        case 6:
            cout << "\nEnter Bus ID: ";
            cin.getline(busId, 20);
            if (isEmpty(busId))
            {
                cout << "Error: Bus ID required!" << endl;
                break;
            }
            city->simulateSchoolBusTrip(busId);
            break;
        case 7:
            cout << "\nEnter School ID: ";
            cin.getline(schoolId, 20);
            if (isEmpty(schoolId))
            {
                cout << "Error: School ID required!" << endl;
                break;
            }
            city->displaySchoolBuses(schoolId);
            break;
        case 8:
            cout << "\nEnter Student ID: ";
            cin.getline(studentId, 20);
            if (isEmpty(studentId))
            {
                cout << "Error: Student ID required!" << endl;
                break;
            }
            city->findStudentBus(studentId);
            break;
        case 9:
            city->displayAllSchoolBuses();
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// AIRPORT/RAIL HANDLER
void handleAirportRailSystem(SmartCityManager *city)
{
    int choice, hubType, capacity, duration, seats;
    char hubId[20], name[100], sector[20], hub1[20], hub2[20];
    char flightId[20], airline[50], source[50], dest[50], depTime[10], arrTime[10];
    char trainId[20], trainName[50], from[50], to[50];
    double lat, lon, distance, fare;

    while (true)
    {
        displayAirportRailMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Hub ID: ";
            cin.getline(hubId, 20);
            if (isEmpty(hubId))
            {
                cout << "Error: Hub ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 100);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Sector: ";
            cin.getline(sector, 20);
            cout << "Type (1=Airport,2=Railway,3=Metro,4=Bus): ";
            if (!getInt(hubType) || hubType < 1 || hubType > 4)
            {
                cout << "Error: Type 1-4!" << endl;
                break;
            }
            cout << "Enter Latitude: ";
            if (!getDouble(lat))
                break;
            cout << "Enter Longitude: ";
            if (!getDouble(lon))
                break;
            cout << "Enter Capacity: ";
            if (!getInt(capacity) || capacity <= 0)
            {
                cout << "Error: Invalid capacity!" << endl;
                break;
            }
            city->addTransportHub(hubId, name, sector, hubType, lat, lon, capacity);
            break;
        case 2:
            cout << "\nEnter Hub 1 ID: ";
            cin.getline(hub1, 20);
            if (isEmpty(hub1))
            {
                cout << "Error: Hub 1 required!" << endl;
                break;
            }
            cout << "Enter Hub 2 ID: ";
            cin.getline(hub2, 20);
            if (isEmpty(hub2))
            {
                cout << "Error: Hub 2 required!" << endl;
                break;
            }
            cout << "Enter Distance: ";
            if (!getDouble(distance) || distance <= 0)
            {
                cout << "Error: Invalid distance!" << endl;
                break;
            }
            cin.ignore();
            city->connectTransportHubs(hub1, hub2, distance);
            break;
        case 3:
            city->displayAllTransportHubs();
            break;
        case 4:
            cout << "\nEnter Flight ID: ";
            cin.getline(flightId, 20);
            if (isEmpty(flightId))
            {
                cout << "Error: Flight ID required!" << endl;
                break;
            }
            cout << "Enter Airline: ";
            cin.getline(airline, 50);
            if (isEmpty(airline))
            {
                cout << "Error: Airline required!" << endl;
                break;
            }
            cout << "Enter Source: ";
            cin.getline(source, 50);
            if (isEmpty(source))
            {
                cout << "Error: Source required!" << endl;
                break;
            }
            cout << "Enter Destination: ";
            cin.getline(dest, 50);
            if (isEmpty(dest))
            {
                cout << "Error: Destination required!" << endl;
                break;
            }
            cout << "Enter Departure Time: ";
            cin.getline(depTime, 10);
            cout << "Enter Arrival Time: ";
            cin.getline(arrTime, 10);
            cout << "Enter Fare: ";
            if (!getDouble(fare) || fare < 0)
            {
                cout << "Error: Invalid fare!" << endl;
                break;
            }
            cout << "Enter Seats: ";
            if (!getInt(seats) || seats <= 0)
            {
                cout << "Error: Invalid seats!" << endl;
                break;
            }
            city->addFlight(flightId, airline, source, dest, depTime, arrTime, fare, seats);
            break;
        case 5:
            cout << "\nEnter Source: ";
            cin.getline(source, 50);
            if (isEmpty(source))
            {
                cout << "Error: Source required!" << endl;
                break;
            }
            cout << "Enter Destination: ";
            cin.getline(dest, 50);
            if (isEmpty(dest))
            {
                cout << "Error: Destination required!" << endl;
                break;
            }
            city->searchFlights(source, dest);
            break;
        case 6:
            city->displayAllFlights();
            break;
        case 7:
            cout << "\nEnter Train ID: ";
            cin.getline(trainId, 20);
            if (isEmpty(trainId))
            {
                cout << "Error: Train ID required!" << endl;
                break;
            }
            cout << "Enter Train Name: ";
            cin.getline(trainName, 50);
            if (isEmpty(trainName))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Source: ";
            cin.getline(source, 50);
            if (isEmpty(source))
            {
                cout << "Error: Source required!" << endl;
                break;
            }
            cout << "Enter Destination: ";
            cin.getline(dest, 50);
            if (isEmpty(dest))
            {
                cout << "Error: Destination required!" << endl;
                break;
            }
            cout << "Enter Departure Time: ";
            cin.getline(depTime, 10);
            cout << "Enter Duration (hours): ";
            if (!getInt(duration) || duration <= 0)
            {
                cout << "Error: Invalid duration!" << endl;
                break;
            }
            cout << "Enter Fare: ";
            if (!getDouble(fare) || fare < 0)
            {
                cout << "Error: Invalid fare!" << endl;
                break;
            }
            cout << "Enter Seats: ";
            if (!getInt(seats) || seats <= 0)
            {
                cout << "Error: Invalid seats!" << endl;
                break;
            }
            city->addTrain(trainId, trainName, source, dest, depTime, duration, fare, seats);
            break;
        case 8:
            cout << "\nEnter Source: ";
            cin.getline(source, 50);
            if (isEmpty(source))
            {
                cout << "Error: Source required!" << endl;
                break;
            }
            cout << "Enter Destination: ";
            cin.getline(dest, 50);
            if (isEmpty(dest))
            {
                cout << "Error: Destination required!" << endl;
                break;
            }
            city->searchTrains(source, dest);
            break;
        case 9:
            city->displayAllTrains();
            break;
        case 10:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findRouteToAirport(from);
            break;
        case 11:
            cout << "\nEnter your location: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->findRouteToStation(from);
            break;
        case 12:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter To: ";
            cin.getline(to, 50);
            if (isEmpty(to))
            {
                cout << "Error: To required!" << endl;
                break;
            }
            city->planMultiModalTrip(from, to);
            break;
        case 13:
            city->displayTransportStats();
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// ROUTE SIMULATOR HANDLER
void handleRouteSimulator(SmartCityManager *city)
{
    int choice, vehicleType, vehicleCount;
    char vehicleId[20], name[50], locationId[50], destId[50], from[50], to[50];
    double speed;

    while (true)
    {
        displayRouteSimMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Vehicle ID: ";
            cin.getline(vehicleId, 20);
            if (isEmpty(vehicleId))
            {
                cout << "Error: Vehicle ID required!" << endl;
                break;
            }
            cout << "Enter Name: ";
            cin.getline(name, 50);
            if (isEmpty(name))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Type (1=Car,2=Bus,3=Ambulance,4=Motorcycle,5=Truck,6=Pedestrian): ";
            if (!getInt(vehicleType) || vehicleType < 1 || vehicleType > 6)
            {
                cout << "Error: Type 1-6!" << endl;
                break;
            }
            city->createSimVehicle(vehicleId, name, vehicleType);
            break;
        case 2:
            cout << "\nEnter Vehicle ID: ";
            cin.getline(vehicleId, 20);
            if (isEmpty(vehicleId))
            {
                cout << "Error: Vehicle ID required!" << endl;
                break;
            }
            cout << "Enter Location ID: ";
            cin.getline(locationId, 50);
            if (isEmpty(locationId))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            city->setSimVehicleLocation(vehicleId, locationId);
            break;
        case 3:
            cout << "\nEnter Vehicle ID: ";
            cin.getline(vehicleId, 20);
            if (isEmpty(vehicleId))
            {
                cout << "Error: Vehicle ID required!" << endl;
                break;
            }
            cout << "Enter Destination ID: ";
            cin.getline(destId, 50);
            if (isEmpty(destId))
            {
                cout << "Error: Destination required!" << endl;
                break;
            }
            city->setSimVehicleDestination(vehicleId, destId);
            break;
        case 4:
            cout << "\nEnter Vehicle ID: ";
            cin.getline(vehicleId, 20);
            if (isEmpty(vehicleId))
            {
                cout << "Error: Vehicle ID required!" << endl;
                break;
            }
            cout << "Enter Speed (km/h): ";
            if (!getDouble(speed) || speed <= 0)
            {
                cout << "Error: Invalid speed!" << endl;
                break;
            }
            cin.ignore();
            city->setSimVehicleSpeed(vehicleId, speed);
            break;
        case 5:
            cout << "\nEnter Vehicle ID: ";
            cin.getline(vehicleId, 20);
            if (isEmpty(vehicleId))
            {
                cout << "Error: Vehicle ID required!" << endl;
                break;
            }
            city->planSimRoute(vehicleId);
            break;
        case 6:
            cout << "\nEnter Vehicle ID: ";
            cin.getline(vehicleId, 20);
            if (isEmpty(vehicleId))
            {
                cout << "Error: Vehicle ID required!" << endl;
                break;
            }
            city->simulateRoute(vehicleId);
            break;
        case 7:
            cout << "\nEnter From: ";
            cin.getline(from, 50);
            if (isEmpty(from))
            {
                cout << "Error: From required!" << endl;
                break;
            }
            cout << "Enter To: ";
            cin.getline(to, 50);
            if (isEmpty(to))
            {
                cout << "Error: To required!" << endl;
                break;
            }
            city->simulateEmergencyRouteAnim(from, to);
            break;
        case 8:
            cout << "\nEnter Location ID: ";
            cin.getline(locationId, 50);
            if (isEmpty(locationId))
            {
                cout << "Error: Location required!" << endl;
                break;
            }
            cout << "Enter vehicle count: ";
            if (!getInt(vehicleCount) || vehicleCount <= 0)
            {
                cout << "Error: Invalid count!" << endl;
                break;
            }
            city->simulateTraffic(locationId, vehicleCount);
            break;
        case 9:
            cout << "\nEnter Vehicle ID: ";
            cin.getline(vehicleId, 20);
            if (isEmpty(vehicleId))
            {
                cout << "Error: Vehicle ID required!" << endl;
                break;
            }
            city->displaySimVehicleStatus(vehicleId);
            break;
        case 10:
            city->displayActiveSimVehicles();
            break;
        case 11:
            city->displayAllSimVehicles();
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// HEATMAP HANDLER
void handleHeatmapSystem(SmartCityManager *city)
{
    int choice, population, males, females;
    char sectorId[20], sectorName[50];
    double area, threshold;

    while (true)
    {
        displayHeatmapMenu();
        if (!getInt(choice))
            continue;

        switch (choice)
        {
        case 1:
            cout << "\nEnter Sector ID: ";
            cin.getline(sectorId, 20);

            if (isEmpty(sectorId))
            {
                cout << "Error: Sector ID required!" << endl;
                break;
            }

            cout << "Enter Sector Name: ";
            cin.getline(sectorName, 50);
            if (isEmpty(sectorName))
            {
                cout << "Error: Name required!" << endl;
                break;
            }
            cout << "Enter Area (sq km): ";

            if (!getDouble(area) || area <= 0)
            {
                cout << "Error: Invalid area!" << endl;
                break;
            }
            cin.ignore();
            city->addHeatmapSector(sectorId, sectorName, area);
            break;
        case 2:
            cout << "\nEnter Sector ID: ";
            cin.getline(sectorId, 20);
            if (isEmpty(sectorId))
            {
                cout << "Error: Sector ID required!" << endl;
                break;
            }
            cout << "Enter Population: ";
            if (!getInt(population) || population < 0)
            {
                cout << "Error: Invalid population!" << endl;
                break;
            }
            cout << "Enter Males: ";
            if (!getInt(males) || males < 0)
            {
                cout << "Error: Invalid males!" << endl;
                break;
            }
            cout << "Enter Females: ";
            if (!getInt(females) || females < 0)
            {
                cout << "Error: Invalid females!" << endl;
                break;
            }
            city->updateSectorPopulation(sectorId, population, males, females);
            break;
        case 3:
            city->generateDensityHeatmap();
            break;
        case 4:
            city->generateIncomeHeatmap();
            break;
        case 5:
            city->generateGenderHeatmap();
            break;
        case 6:
            city->generateAgeHeatmap();
            break;
        case 7:
            city->displaySectorComparison();
            break;
        case 8:
            cout << "\nEnter density threshold: ";
            if (!getDouble(threshold) || threshold < 0)
            {
                cout << "Error: Invalid threshold!" << endl;
                break;
            }
            cin.ignore();
            city->findHighDensityAreas(threshold);
            break;
        case 9:
            city->displayAllHeatmapSectors();
            break;
        case 0:
            return;
        default:
            cout << "\nInvalid choice!" << endl;
        }
    }
}

// void handleSectorSystem(SmartCityManager* city)
//{
//     int choice;
//     char sectorId[50], sectorName[100], sector2[50];
//     double lat, lon, distance, area;
//
//     while (true)
//     {
//         cout << "\n....................SECTOR MANAGEMENT................." << endl;
//         cout << "\n\t\t\t1. Add New Sector" << endl;
//         cout << "\t\t\t2. View Sector Details" << endl;
//         cout << "\t\t\t3. Display All Sectors" << endl;
//         cout << "\t\t\t4. Display Sector Summary" << endl;
//         cout << "\t\t\t5. Connect Two Sectors" << endl;
//         cout << "\n\t\t0. Back to Main Menu" << endl;
//         cout <<  endl;
//         cout << "Enter choice: ";
//         cin >> choice;
//         cin.ignore();
//
//         switch (choice)
//         {
//         case 1:
//             cout << "\nEnter Sector ID: ";
//             cin.getline(sectorId, 50);
//             if (sectorId[0] == '\0')
//             {
//                 cout << "Error: Sector ID cannot be empty!" << endl;
//                 break;
//             }
//             cout << "Enter Sector Name: ";
//             cin.getline(sectorName, 100);
//             cout << "Enter Latitude: ";
//             cin >> lat;
//             cout << "Enter Longitude: ";
//             cin >> lon;
//             cout << "Enter Area (sq km): ";
//             cin >> area;
//             cin.ignore();
//             city->addSector(sectorId, sectorName, lat, lon, area);
//             break;
//
//         case 2:
//             cout << "\nEnter Sector ID to view: ";
//             cin.getline(sectorId, 50);
//             if (sectorId[0] == '\0')
//             {
//                 cout << "Error: Sector ID cannot be empty!" << endl;
//                 break;
//             }
//             city->displaySectorDetails(sectorId);
//             break;
//
//         case 3:
//             city->displayAllSectors();
//             break;
//
//         case 4:
//             city->displaySectorSummary();
//             break;
//
//         case 5:
//             cout << "\nEnter First Sector ID: ";
//             cin.getline(sectorId, 50);
//             cout << "Enter Second Sector ID: ";
//             cin.getline(sector2, 50);
//             cout << "Enter Distance (km): ";
//             cin >> distance;
//             cin.ignore();
//             city->connectSectors(sectorId, sector2, distance);
//             break;
//
//         case 0:
//             return;
//
//         default:
//             cout << "\nInvalid choice! Please try again." << endl;
//         }
//     }
// }
