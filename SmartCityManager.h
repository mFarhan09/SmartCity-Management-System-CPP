#pragma once
#include <iostream>
#include <fstream>
#include "DataStructures\Graph.h"
#include "TransportManager\TransportManager.h"
#include "EducationManager\EducationManager.h"
#include "HealthCareManager\MedicalManager.h"
#include "PopulationManager\PopulationManager.h"
#include "PopulationManager\House.h"
#include "FacilityManager\FacilityManager.h"
#include "CommercialManager\CommercialManager.h"
#include "TransportManager\Passenger.h"
#include "DataStructures\CircularQueue.h"
#include "TransportManager\TravelHistory.h"
#include "EmergencyRouter\EmergencyRouter.h"
#include "SchoolBusTracker\SchoolBusTracker.h"
#include "AirportRailManager\AirportRailManager.h"
#include "RouteSimulation\RouteSimulator.h"
#include "PopulationHeatmap\PopulationHeatmap.h"
#include "PopulationManager\sector.h"

using namespace std;

class SmartCityManager
{
private:
    // Core city infrastructure
    Graph *masterCityGraph;

    // System managers
    TransportManager *transportSystem;
    EducationManager *educationSystem;
    MedicalManager *medicalSystem;
    PopulationManager *populationSystem;
    CommercialManager *commercialSystem;
    FacilityManager *facilitySystem;

    // Bonus systems
    EmergencyRouter *emergencySystem;
    SchoolBusTracker *schoolBusSystem;
    AirportRailManager *airportRailSystem;
    RouteSimulator *routeSimulator;
    PopulationHeatmap *heatmapSystem;

    SectorManager *sectorSystem;

    // City metadata
    char cityName[100];
    char country[50];
    double cityLatitude;
    double cityLongitude;
    int totalPopulation;

public:
    SmartCityManager(const char *name = "Smart City", const char *countryName = "Pakistan")
    {
        int i = 0;
        while (name[i] != '\0' && i < 99)
        {
            cityName[i] = name[i];
            i++;
        }
        cityName[i] = '\0';

        i = 0;
        while (countryName[i] != '\0' && i < 49)
        {
            country[i] = countryName[i];
            i++;
        }
        country[i] = '\0';

        cityLatitude = 33.6844;
        cityLongitude = 73.0479;
        totalPopulation = 0;

        // Create the master city graph
        masterCityGraph = new Graph(500);

        // Initialize all subsystems with the SAME graph
        transportSystem = new TransportManager(masterCityGraph);
        educationSystem = new EducationManager(masterCityGraph);
        medicalSystem = new MedicalManager(masterCityGraph);
        populationSystem = new PopulationManager(masterCityGraph);
        commercialSystem = new CommercialManager(masterCityGraph);
        facilitySystem = new FacilityManager(masterCityGraph);

        // Bonus systems
        emergencySystem = new EmergencyRouter(masterCityGraph);
        schoolBusSystem = new SchoolBusTracker(masterCityGraph);
        airportRailSystem = new AirportRailManager(masterCityGraph);
        routeSimulator = new RouteSimulator(masterCityGraph);
        heatmapSystem = new PopulationHeatmap();

        sectorSystem = new SectorManager(masterCityGraph);

        cout << "\n.........................................." << endl;
        cout << "      " << cityName << " SMART CITY SYSTEM           " << endl;
        cout << endl;
        cout << " Transport System:        Ready              " << endl;
        cout << " Education System:        Ready              " << endl;
        cout << " Medical System:          Ready              " << endl;
        cout << " Population System:       Ready              " << endl;
        cout << " Commercial System:       Ready              " << endl;
        cout << " Facility System:         Ready              " << endl;
        cout << " Emergency Router:        Ready              " << endl;
        cout << " School Bus Tracker:      Ready              " << endl;
        cout << " Airport/Rail System:     Ready              " << endl;
        cout << " Route Simulator:         Ready              " << endl;
        cout << " Population Heatmap:      Ready             " << endl;
        cout << " Sector System:           Ready              " << endl;
        cout << "............................................ \n"
             << endl;
    }

    // UNIVERSAL NAVIGATION
    void navigateBetweenLocations(const char *from, const char *to)
    {
        cout << "\n............................................" << endl;
        cout << "          CITY NAVIGATION SYSTEM               " << endl;
        cout << "..............................................." << endl;
        cout << "From: " << from << endl;
        cout << "To: " << to << endl;
        cout << "--------------------------------------------" << endl;
        masterCityGraph->dijkstra(from, to);
    }

    void findNearestLocation(const char *from, const char *searchTerm)
    {
        cout << "\n FINDING NEAREST: " << searchTerm << " ===" << endl;
        const char *nearest = masterCityGraph->findNearest(from, searchTerm);
        if (nearest != NULL)
        {
            cout << "Found: " << nearest << endl;
            cout << "\nCalculating route..." << endl;
            masterCityGraph->dijkstra(from, nearest);
        }
        else
        {
            cout << "No matching location found!" << endl;
        }
    }

    void connectLocations(const char *loc1, const char *loc2, double distance)
    {
        masterCityGraph->addEdge(loc1, loc2, distance);
    }

    void displayCityMap()
    {
        cout << "\n............................................." << endl;
        cout << "            COMPLETE CITY MAP                 " << endl;
        cout << "..............................................." << endl;
        masterCityGraph->display();
    }

    void registerBus(
        const char *busNumber,
        const char *company,
        const char *currentStop,
        const char *route)
    {
        transportSystem->registerBus(busNumber, company, currentStop, route);
    }
    void addBusStop(const char *stopId, const char *name, double lat, double lon)
    {
        transportSystem->addBusStop(stopId, name, lat, lon);
    }

    void addStopToBusRoute(const char *busNumber, const char *stopId)
    {
        transportSystem->addStopToBusRoute(busNumber, stopId);
    }

    void trackBusLocation(const char *busNumber)
    {
        transportSystem->trackBusLocation(busNumber);
    }

    void showBusRoute(const char *busNumber)
    {
        transportSystem->showBusRoute(busNumber);
    }

    void displayAllBuses() { transportSystem->displayAllBuses(); }
    void displayAllStops() { transportSystem->displayAllStops(); }
    void findShortestPath(const char *from, const char *to)
    {
        transportSystem->findShortestPath(from, to);
    }

    // Passenger Queue
    void addPassengerToStop(const char *stopId, const char *passengerId,
                            const char *name, const char *destination, const char *contact = "")
    {
        transportSystem->addPassengerToStop(stopId, passengerId, name, destination, contact);
    }
    void displayStopQueue(const char *stopId)
    {
        transportSystem->displayStopQueue(stopId);
    }
    void simulateBusArrival(const char *busNumber, const char *stopId)
    {
        transportSystem->simulateBusArrival(busNumber, stopId);
    }
    void simulatePassengerArrivals(const char *stopId, int count)
    {
        transportSystem->simulatePassengerArrivals(stopId, count);
    }

    // Travel History
    void displayTravelHistory()
    {
        transportSystem->displayTravelHistory();
    }
    void displayRecentTrips(int count)
    {
        transportSystem->displayRecentTrips(count);
    }
    void undoLastTrip()
    {
        transportSystem->undoLastTrip();
    }
    void getTravelStats()
    {
        transportSystem->getTravelStats();
    }
    void clearTravelHistory()
    {
        transportSystem->clearTravelHistory();
    }

    // CSV Loading
    void loadStopsFromCSV(const char *filename)
    {
        transportSystem->loadStopsFromCSV(filename);
    }
    void loadBusesFromCSV(const char *filename)
    {
        transportSystem->loadBusesFromCSV(filename);
    }

    void registerSchool(const char *id, const char *name, const char *sector,
                        double rating, const char *subjects)
    {
        educationSystem->registerSchool(id, name, sector, rating, subjects);
        //  sectorSystem->linkSchoolToSector(sector, name, name, educationSystem->getSchool(id));
    }

    void addSubjectToSchool(const char *schoolId, const char *subject)
    {
        educationSystem->addSubjectToSchool(schoolId, subject);
    }

    void addDepartment(const char *schoolId, const char *deptId,
                       const char *deptName, const char *headOfDept)
    {
        educationSystem->addDepartment(schoolId, deptId, deptName, headOfDept);
    }

    void addClass(const char *schoolId, const char *deptId,
                  const char *classId, const char *className, int capacity)
    {
        educationSystem->addClass(schoolId, deptId, classId, className, capacity);
    }

    void registerTeacher(const char *id, const char *name, const char *qualification,
                         const char *specialization, const char *schoolId, int salary, int experience)
    {
        educationSystem->registerTeacher(id, name, qualification, specialization, schoolId, salary, experience);
    }

    void assignTeacherToClass(const char *schoolId, const char *classId, const char *teacherId)
    {
        educationSystem->assignTeacherToClass(schoolId, classId, teacherId);
    }

    void enrollStudent(const char *schoolId, const char *classId,
                       const char *studentId, const char *name, int age, const char *section)
    {
        educationSystem->enrollStudent(schoolId, classId, studentId, name, age, section);
    }
    void displayTopSchools(int count)
    {
        educationSystem->displayTopSchools(count);
    }

    void searchSchoolsBySubject(const char *subject)
    {
        educationSystem->searchSchoolsBySubject(subject);
    }

    void displaySchoolHierarchy(const char *schoolId)
    {
        educationSystem->displaySchoolHierarchy(schoolId);
    }

    void displaySchoolDetails(const char *schoolId)
    {
        educationSystem->displaySchoolDetails(schoolId);
    }

    void displayTeacherDetails(const char *teacherId)
    {
        educationSystem->displayTeacherDetails(teacherId);
    }

    void displayAllSchools()
    {
        educationSystem->displayAllSchools();
    }

    // loading

    void loadSchoolsFromCSV(const char *filename) { educationSystem->loadSchoolsFromCSV(filename); }

    // MEDICAL SYSTEM INTERFACE
    void registerHospital(const char *id, const char *name, const char *sector,
                          int totalBeds, double lat, double lon, const char *specializationList)
    {
        medicalSystem->registerHospital(id, name, sector, totalBeds, lat, lon, specializationList);
        //    sectorSystem->linkHospitalToSector(sector, id, name, medicalSystem->getHospital(id));
    }

    void addSpecializationToHospital(const char *hospitalId, const char *spec)
    {
        medicalSystem->addSpecializationToHospital(hospitalId, spec);
    }

    void addBlock(const char *hospitalId, const char *blockId,
                  const char *blockName, const char *blockType, int floor)
    {
        medicalSystem->addBlock(hospitalId, blockId, blockName, blockType, floor);
    }

    void addWard(const char *hospitalId, const char *blockId,
                 const char *wardId, const char *wardName, const char *wardType, int numBeds)
    {
        medicalSystem->addWard(hospitalId, blockId, wardId, wardName, wardType, numBeds);
    }
    void registerDoctor(const char *id, const char *name, const char *spec,
                        const char *hospitalId, int exp, int fee)
    {
        medicalSystem->registerDoctor(id, name, spec, hospitalId, exp, fee);
    }

    void registerPatient(const char *id, const char *cnic, const char *name,
                         int age, const char *gender, const char *bloodType)
    {
        medicalSystem->registerPatient(id, cnic, name, age, gender, bloodType);
    }

    void addEmergencyPatient(const char *hospitalId, const char *patientId,
                             const char *condition, int severity)
    {
        medicalSystem->addEmergencyPatient(hospitalId, patientId, condition, severity);
    }

    void treatNextEmergencyPatient(const char *hospitalId)
    {
        medicalSystem->treatNextEmergencyPatient(hospitalId);
    }

    void admitPatient(const char *hospitalId, const char *patientId,
                      const char *wardId, const char *doctorId)
    {
        medicalSystem->admitPatient(hospitalId, patientId, wardId, doctorId);
    }

    void registerPharmacy(const char *id, const char *name, const char *sector,
                          const char *medicineName, const char *formula, double price)
    {
        // Register the pharmacy with medicine info
        medicalSystem->registerPharmacy(id, name, sector, medicineName, formula, price);
    }

    void addMedicine(const char *name, const char *formula, double price,
                     int stock, const char *pharmacyId, const char *pharmacyName)
    {
        medicalSystem->addMedicine(name, formula, price, stock, pharmacyId, pharmacyName);
    }

    // loading
    void loadHospitalsFromCSV(const char *filename)
    {
        medicalSystem->loadHospitalsFromCSV(filename);
    }

    void loadPharmaciesFromCSV(const char *filename)
    {
        medicalSystem->loadPharmaciesFromCSV(filename);
    }

    void searchMedicine(const char *name)
    {
        medicalSystem->searchMedicine(name);
    }

    void displayHospitalDetails(const char *hospitalId)
    {
        medicalSystem->displayHospitalDetails(hospitalId);
    }

    void displayHospitalHierarchy(const char *hospitalId)
    {
        medicalSystem->displayHospitalHierarchy(hospitalId);
    }

    void displayDoctorDetails(const char *doctorId)
    {
        medicalSystem->displayDoctorDetails(doctorId);
    }

    void displayPatientDetails(const char *patientId)
    {
        medicalSystem->displayPatientDetails(patientId);
    }

    void checkBedAvailability(const char *hospitalId)
    {
        medicalSystem->checkBedAvailability(hospitalId);
    }
    void displayAllHospitals()
    {
        medicalSystem->displayAllHospitals();
    }

    /*POPULATION SYSTEM INTERFACE*/
    void registerCitizen(const char *cnic, const char *name, int age,
                         const char *gender, const char *occupation, const char *education,
                         int income, const char *sector, const char *maritalStatus)
    {
        populationSystem->registerCitizen(cnic, name, age, gender, occupation,
                                          education, income, sector, maritalStatus);
        // Update heatmap
        bool isMale = (gender[0] == 'M' || gender[0] == 'm');
        heatmapSystem->addCitizenToSector(sector, isMale, age, income);
    }

    // void registerCitizen(const char* cnic, const char* name, int age,
    //     const char* sector, const char* street, int houseNo, const char* occupation)
    //{
    //     populationSystem->registerCitizen(cnic, name, age, sector, street, houseNo, occupation);

    //    bool isMale = false;
    //    int income = 0;

    //    heatmapSystem->addCitizenToSector(sector, isMale, age, income);
    //}

    void registerCitizenComplete(const char *cnic, const char *name, int age,
                                 const char *gender, const char *dob, const char *bloodType,
                                 const char *contact, const char *email, const char *occupation,
                                 const char *education, int income, const char *maritalStatus,
                                 const char *sector, const char *street, const char *houseNumber,
                                 double lat, double lon)
    {
        populationSystem->registerCitizenComplete(cnic, name, age, gender, dob,
                                                  bloodType, contact, email, occupation, education, income,
                                                  maritalStatus, sector, street, houseNumber, lat, lon);
        bool isMale = (gender[0] == 'M' || gender[0] == 'm');
        heatmapSystem->addCitizenToSector(sector, isMale, age, income);
    }
    void searchCitizen(const char *cnic)
    {
        populationSystem->searchCitizen(cnic);
    }

    void removeCitizen(const char *cnic)
    {
        populationSystem->removeCitizen(cnic);
    }

    void displayPopulationStatistics()
    {
        populationSystem->displayPopulationStatistics();
    }

    void displayAgeDistribution()
    {
        populationSystem->displayAgeDistribution();
    }

    void displayGenderDistribution()
    {
        populationSystem->displayGenderDistribution();
    }

    void displayOccupationStats()
    {
        populationSystem->displayOccupationStats();
    }
    void displayEducationStats()
    {
        populationSystem->displayEducationStats();
    }

    void displayIncomeStats()
    {
        populationSystem->displayIncomeStats();
    }

    void displaySectorPopulation()
    {
        populationSystem->displaySectorPopulation();
    }

    void displayMaritalStats()
    {
        populationSystem->displayMaritalStats();
    }

    void displayCompleteDemographics()
    {
        populationSystem->displayCompleteDemographics();
    }

    void generatePopulationReport()
    {
        populationSystem->generatePopulationReport();
    }

    void displayCityAnalytics()
    {
        populationSystem->displayCityAnalytics();
    }

    void listAllCitizens()
    {
        populationSystem->listAllCitizens();
    }

    void addSector(const char *sectorName)
    {
        populationSystem->addSector(sectorName);
        heatmapSystem->addSector(sectorName, sectorName, 5.0);
    }

    void addStreet(const char *sector, const char *streetName)
    {
        populationSystem->addStreet(sector, streetName);
    }

    void addHouse(const char *sector, const char *street, House *house)
    {
        populationSystem->addHouse(sector, street, house);
    }

    void displayResidentialHierarchy()
    {
        populationSystem->displayResidentialHierarchy();
    }
    void displayHouseDetails(const char *houseId)
    {
        populationSystem->displayHouseDetails(houseId);
    }

    void registerFamily(const char *familyId, const char *houseId,
                        const char *headCNIC, const char *headName,
                        const char *headRelation, int headAge, const char *headGender)
    {
        populationSystem->registerFamily(familyId, houseId, headCNIC, headName, headRelation, headAge, headGender);
    }

    void addFamilyMember(const char *familyId, const char *cnic, const char *name,
                         const char *relation, int age, const char *gender, const char *parentCNIC = NULL)
    {
        populationSystem->addFamilyMember(familyId, cnic, name, relation, age, gender, parentCNIC);
    }

    void displayFamilyTree(const char *familyId)
    {
        populationSystem->displayFamilyTree(familyId);
    }

    void listFamilyMembers(const char *familyId)
    {
        populationSystem->listFamilyMembers(familyId);
    }

    void createSurvey(const char *surveyId, const char *title, const char *desc)
    {
        populationSystem->createSurvey(surveyId, title, desc);
    }

    void addSurveyQuestion(const char *surveyId, const char *question)
    {
        populationSystem->addSurveyQuestion(surveyId, question);
    }

    void submitSurveyResponse(const char *cnic, const char *surveyId,
                              int *answers, int numAnswers, const char *feedback)
    {
        populationSystem->submitSurveyResponse(cnic, surveyId, answers, numAnswers, feedback);
    }
    void displaySurvey(const char *surveyId)
    {
        populationSystem->displaySurvey(surveyId);
    }

    void closeSurvey(const char *surveyId)
    {
        populationSystem->closeSurvey(surveyId);
    }

    void displayActiveSurveys()
    {
        populationSystem->displayActiveSurveys();
    }

    // loading
    void loadCitizensFromCSV(const char *filename)
    {
        populationSystem->loadCitizensFromCSV(filename);
    }

    void loadFamiliesFromCSV(const char *filename)
    {
        populationSystem->loadFamiliesFromCSV(filename);
    }

    void registerMall(const char *id, const char *name, const char *sector, double lat, double lon)
    {
        commercialSystem->registerMall(id, name, sector, lat, lon);
        sectorSystem->linkMallToSector(sector, id, name, commercialSystem->getMall(id));
    }

    void addProduct(const char *id, const char *name, const char *category, double price, const char *mallId)
    {
        commercialSystem->addProduct(id, name, category, price, mallId);
    }
    void searchProductByCategory(const char *category)
    {
        commercialSystem->searchProductByCategory(category);
    }

    void findNearestMall(const char *fromLocation)
    {
        commercialSystem->findNearestMall(fromLocation);
    }

    void loadMallsFromCSV(const char *filename)
    {
        commercialSystem->loadMallsFromCSV(filename);
    }
    void displayAllMalls()
    {
        commercialSystem->displayAllMalls();
    }

    // FACILITY SYSTEM INTERFACE

    void addPublicFacility(const char *id, const char *name, const char *type,
                           const char *sector, double lat, double lon)
    {
        facilitySystem->addFacility(id, name, type, sector, lat, lon);
    }

    void getFacilitiesByType(const char *type)
    {
        facilitySystem->getFacilitiesByType(type);
    }

    void findNearestFacility(const char *from, const char *type)
    {
        facilitySystem->findNearestFacility(from, type);
    }
    void displayAllFacilities() { facilitySystem->displayAllFacilities(); }

    // EMERGENCY SYSTEM

    void createEmergencyRequest(const char *location, const char *patientName,
                                const char *condition, int priorityLevel)
    {
        emergencySystem->createEmergencyRequest(location, patientName, condition, priorityLevel);
    }

    void dispatchNextEmergency()
    {
        emergencySystem->dispatchNextEmergency();
    }

    void planEmergencyRoute(const char *from, const char *to)
    {
        emergencySystem->planEmergencyRoute(from, to);
    }

    void displayActiveEmergencies()
    {
        emergencySystem->displayActiveEmergencies();
    }

    void displayEmergencyHistory()
    {
        emergencySystem->displayEmergencyHistory();
    }

    void getEmergencyStats()
    {
        emergencySystem->getEmergencyStats();
    }

    // SCHOOL BUS TRACKER
    void registerSchoolBus(const char *busId, const char *schoolId,
                           const char *driverName, int capacity)
    {
        schoolBusSystem->registerSchoolBus(busId, schoolId, driverName, capacity);
    }

    void addStopToSchoolBusRoute(const char *busId, const char *stopId,
                                 const char *stopName, double lat, double lon)
    {
        schoolBusSystem->addStopToRoute(busId, stopId, stopName, lat, lon);
    }

    void assignStudentToSchoolBus(const char *studentId, const char *busId, const char *pickupStop)
    {
        schoolBusSystem->assignStudentToBus(studentId, busId, pickupStop);
    }

    void updateSchoolBusLocation(const char *busId, const char *locationId)
    {
        schoolBusSystem->updateBusLocation(busId, locationId);
    }

    void simulateSchoolBusTrip(const char *busId)
    {
        schoolBusSystem->simulateBusTrip(busId);
    }

    void trackSchoolBus(const char *busId)
    {
        schoolBusSystem->trackBus(busId);
    }

    void displaySchoolBuses(const char *schoolId)
    {
        schoolBusSystem->displaySchoolBuses(schoolId);
    }

    void findStudentBus(const char *studentId)
    {
        schoolBusSystem->findStudentBus(studentId);
    }
    void displayAllSchoolBuses()
    {
        schoolBusSystem->displayAllSchoolBuses();
    }

    // AIRPORT/RAIL SYSTEM
    void addTransportHub(const char *id, const char *name, const char *sector,
                         int type, double lat, double lon, int capacity)
    {
        airportRailSystem->addTransportHub(id, name, sector, type, lat, lon, capacity);
    }

    void connectTransportHubs(const char *hub1Id, const char *hub2Id, double distance)
    {
        airportRailSystem->connectHubs(hub1Id, hub2Id, distance);
    }

    void addFlight(const char *flightId, const char *airline, const char *source,
                   const char *dest, const char *depTime, const char *arrTime,
                   double fare, int seats)
    {
        airportRailSystem->addFlight(flightId, airline, source, dest, depTime, arrTime, fare, seats);
    }

    void searchFlights(const char *source, const char *dest)
    {
        airportRailSystem->searchFlights(source, dest);
    }

    void displayAllFlights()
    {
        airportRailSystem->displayAllFlights();
    }

    void addTrain(const char *trainId, const char *trainName, const char *source,
                  const char *dest, const char *depTime, int duration, double fare, int seats)
    {
        airportRailSystem->addTrain(trainId, trainName, source, dest, depTime, duration, fare, seats);
    }

    void searchTrains(const char *source, const char *dest)
    {
        airportRailSystem->searchTrains(source, dest);
    }

    void displayAllTrains()
    {
        airportRailSystem->displayAllTrains();
    }

    void findRouteToAirport(const char *from)
    {
        airportRailSystem->findRouteToAirport(from);
    }
    void findRouteToStation(const char *from)
    {
        airportRailSystem->findRouteToStation(from);
    }

    void planMultiModalTrip(const char *from, const char *to)
    {
        airportRailSystem->planMultiModalTrip(from, to);
    }

    void displayAllTransportHubs()
    {
        airportRailSystem->displayAllHubs();
    }
    void displayTransportStats()
    {
        airportRailSystem->displayTransportStats();
    }

    // ROUTE SIMULATOR
    void createSimVehicle(const char *vehicleId, const char *name, int type)
    {
        routeSimulator->createVehicle(vehicleId, name, type);
    }

    void setSimVehicleLocation(const char *vehicleId, const char *locationId)
    {
        routeSimulator->setVehicleLocation(vehicleId, locationId);
    }

    void setSimVehicleDestination(const char *vehicleId, const char *destId)
    {
        routeSimulator->setVehicleDestination(vehicleId, destId);
    }

    void setSimVehicleSpeed(const char *vehicleId, double speed)
    {
        routeSimulator->setVehicleSpeed(vehicleId, speed);
    }

    void planSimRoute(const char *vehicleId)
    {
        routeSimulator->planRoute(vehicleId);
    }

    void simulateRoute(const char *vehicleId)
    {
        routeSimulator->simulateRoute(vehicleId);
    }

    void simulateEmergencyRouteAnim(const char *from, const char *to)
    {
        routeSimulator->simulateEmergencyRoute(from, to);
    }

    void simulateTraffic(const char *locationId, int vehicleCount)
    {
        routeSimulator->simulateTraffic(locationId, vehicleCount);
    }

    void displaySimVehicleStatus(const char *vehicleId)
    {
        routeSimulator->displayVehicleStatus(vehicleId);
    }

    void displayActiveSimVehicles()
    {
        routeSimulator->displayActiveVehicles();
    }

    void displayAllSimVehicles()
    {
        routeSimulator->displayAllVehicles();
    }

    // POPULATION HEATMAP
    void addHeatmapSector(const char *sectorId, const char *sectorName, double area)
    {
        heatmapSystem->addSector(sectorId, sectorName, area);
    }
    void updateSectorPopulation(const char *sectorId, int pop, int males, int females)
    {
        heatmapSystem->updateSectorPopulation(sectorId, pop, males, females);
    }

    void generateDensityHeatmap()
    {
        heatmapSystem->generateDensityHeatmap();
    }

    void generateIncomeHeatmap()
    {
        heatmapSystem->generateIncomeHeatmap();
    }

    void generateGenderHeatmap()
    {
        heatmapSystem->generateGenderHeatmap();
    }

    void generateAgeHeatmap()
    {
        heatmapSystem->generateAgeHeatmap();
    }

    void displaySectorComparison()
    {
        heatmapSystem->displaySectorComparison();
    }

    void findHighDensityAreas(double threshold)
    {
        heatmapSystem->findHighDensityAreas(threshold);
    }

    void displayAllHeatmapSectors()
    {
        heatmapSystem->displayAllSectors();
    }

    // CITY INFORMATION
    void setCityInfo(const char *name, const char *countryName,
                     double lat, double lon, int population)
    {
        int i = 0;
        while (name[i] != '\0' && i < 99)
        {
            cityName[i] = name[i];
            i++;
        }
        cityName[i] = '\0';
        i = 0;
        while (countryName[i] != '\0' && i < 49)
        {
            country[i] = countryName[i];
            i++;
        }
        country[i] = '\0';
        cityLatitude = lat;
        cityLongitude = lon;
        totalPopulation = population;
    }

    void displayCityStatistics()
    {
        cout << "\n................................................." << endl;
        cout << "            CITY STATISTICS                       " << endl;
        cout << "..................................................." << endl;
        cout << "City: " << cityName << ", " << country << endl;
        cout << "Coordinates: (" << cityLatitude << ", " << cityLongitude << ")" << endl;
        cout << "Population: " << populationSystem->getTotalPopulation() << endl;
        cout << "\n--- All Systems Operational ---" << endl;
    }

    void displayCompleteCityMap() { displayCityMap(); }

    // Getters for subsystems
    TransportManager *getTransportSystem()
    {
        return transportSystem;
    }

    EducationManager *getEducationSystem()
    {
        return educationSystem;
    }

    MedicalManager *getMedicalSystem()
    {
        return medicalSystem;
    }

    PopulationManager *getPopulationSystem()
    {
        return populationSystem;
    }

    CommercialManager *getCommercialSystem()
    {
        return commercialSystem;
    }

    FacilityManager *getFacilitySystem()
    {
        return facilitySystem;
    }

    EmergencyRouter *getEmergencySystem()
    {
        return emergencySystem;
    }

    SchoolBusTracker *getSchoolBusSystem()
    {
        return schoolBusSystem;
    }

    AirportRailManager *getAirportRailSystem()
    {
        return airportRailSystem;
    }

    RouteSimulator *getRouteSimulator()
    {
        return routeSimulator;
    }

    PopulationHeatmap *getHeatmapSystem()
    {
        return heatmapSystem;
    }

    Graph *getCityGraph()
    {
        return masterCityGraph;
    }

    const char *getCityName()
    {
        return cityName;
    }

    // SECTOR MANAGEMENT
    void addSector(const char *sectorId, const char *name, double lat, double lon, double area = 1.0)
    {
        if (sectorId[0] == '\0')
        {
            cout << "Error: Sector ID cannot be empty!" << endl;
            return;
        }
        sectorSystem->addSector(sectorId, name, lat, lon, area);
    }

    void displaySectorDetails(const char *sectorId)
    {
        if (sectorId[0] == '\0')
        {
            cout << "Error: Sector ID cannot be empty!" << endl;
            return;
        }
        sectorSystem->displaySectorDetails(sectorId);
    }

    void displayAllSectors()
    {
        sectorSystem->displayAllSectors();
    }

    void displaySectorSummary()
    {
        sectorSystem->displaySectorSummary();
    }

    void connectSectors(const char *sector1, const char *sector2, double distance)
    {
        if (sector1[0] == '\0' || sector2[0] == '\0')
        {
            cout << "Error: Sector IDs cannot be empty!" << endl;
            return;
        }
        if (distance <= 0)
        {
            cout << "Error: Distance must be positive!" << endl;
            return;
        }
        sectorSystem->connectSectors(sector1, sector2, distance);
    }

    ~SmartCityManager()
    {
        cout << "\n..............................................." << endl;
        cout << "      Shutting down " << cityName << "              " << endl;
        cout << "................................................" << endl;

        delete transportSystem;
        delete educationSystem;
        delete medicalSystem;
        delete populationSystem;
        delete facilitySystem;
        delete commercialSystem;
        delete emergencySystem;
        delete schoolBusSystem;
        delete airportRailSystem;
        delete routeSimulator;
        delete heatmapSystem;
        delete masterCityGraph;

        cout << "All systems shut down successfully." << endl;
    }
};