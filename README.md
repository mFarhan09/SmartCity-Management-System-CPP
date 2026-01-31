🏙️ Smart City Management System (Console-Based)

A console-based Smart City simulation system implemented in C++, designed to demonstrate core and advanced Data Structures through a realistic, real-world problem domain.

This project models a city’s transport, education, medical, commercial, public facilities, and population systems, using custom-built data structures (no STL shortcuts) to manage, search, and optimize city operations.

📌 Project Objectives

Demonstrate deep understanding of Data Structures

Apply DS concepts to a realistic system design

Build scalable, modular, and extensible architecture

Practice algorithmic thinking (graphs, heaps, hashing, trees)

Serve as a strong academic + portfolio project

🧠 System Architecture Overview

The system is divided into four major layers:

Core Data Structures

Business Entities

Management Modules (Business Logic)

Main Smart City Controller

Each layer is loosely coupled and interacts through well-defined interfaces.

1️⃣ Core Data Structures Layer

All data structures are implemented from scratch.

🔹 Graph (Adjacency List)

Used to represent the city road network.

Features

Weighted edges (distance between locations)

Dijkstra’s Algorithm (shortest path)

BFS / DFS traversal

Nearest location search

Used for

Transport routing

Nearest hospital / school / mall

Facility proximity queries

Time Complexity

Add Vertex: O(1)

Add Edge: O(1)

Dijkstra: O((V + E) log V)

BFS / DFS: O(V + E)

🔹 Hash Table (Separate Chaining)

Custom hash table using linked list chaining.

Used for

Citizen lookup by CNIC

Medicine search

Product search

Bus & hospital registries

Time Complexity

Insert: O(1) average

Search: O(1) average

Delete: O(1) average

🔹 N-ary Tree (General Tree)

Supports dynamic number of children per node.

Used for

School hierarchy (School → Department → Class → Students)

Housing hierarchy (Sector → Street → House → Family)

Administrative city divisions

Time Complexity

Insert: O(1) (with parent reference)

Search: O(n)

Traversal: O(n)

🔹 Priority Queue (Binary Heap)

Supports Min-Heap & Max-Heap modes.

Used for

Emergency patient prioritization

School ranking system

Nearest facility prioritization

Time Complexity

Insert: O(log n)

Extract: O(log n)

Peek: O(1)

🔹 Linked List (Singly Linked)

Used for

Bus routes

Hash table collision handling

Student lists

Dynamic collections

🔹 Stack (Linked List Based)

Used for

Undo operations

Route traversal history

Survey history tracking

🔹 Circular Queue (Array Based)

Used for

Passenger boarding simulation

FIFO service queues

2️⃣ Business Entities Layer

Represents real-world city components.

🚍 Transport

Bus

BusStop

🏫 Education

School

Department

Class

Student

🏥 Medical

Hospital

Doctor

Patient

Pharmacy

Medicine

🛍️ Commercial

ShoppingMall

Product

🏢 Public & Population

PublicFacility

Citizen

House

Each entity is data-driven and managed through specialized managers.

3️⃣ Management Modules (Business Logic)

Each manager acts as a controller for its domain.

🚦 TransportManager

City graph management

Bus & stop registration

Shortest path finding

Nearest bus lookup

🎓 EducationManager

School & department management

Student enrollment

School ranking system

Nearest school search

🏥 MedicalManager

Hospital & doctor registry

Emergency bed allocation

Medicine search

Nearest hospital lookup

🛒 CommercialManager

Mall & product management

Category-based product search

Nearest mall lookup

🏛️ FacilityManager

Public facility registry

Type-based and proximity searches

👨‍👩‍👧 PopulationManager

Citizen registration

Housing hierarchy management

Population statistics

Gender ratio & age distribution

4️⃣ SmartCitySystem (Main Controller)

Acts as the central orchestrator.

Responsibilities

System initialization

Sample data loading

Menu-driven interaction

Delegating requests to managers

SmartCitySystem
├── TransportManager
├── EducationManager
├── MedicalManager
├── CommercialManager
├── FacilityManager
└── PopulationManager

🧪 Key Algorithms Used

Dijkstra’s Shortest Path

BFS / DFS

Binary Heap Operations

Hashing with Collision Handling

Tree Traversals

Priority-Based Scheduling

🛠️ Technologies Used

Language: C++

Paradigm: Object-Oriented Programming

Interface: Console-based

Data Structures: Custom (No STL dependency)

🎯 Learning Outcomes

Strong grasp of Data Structures internals

Real-world system design

Efficient algorithm selection

Clean modular architecture

Practical use of DS beyond textbook examples

📌 Future Enhancements

File persistence (save/load city data)

GUI version (Qt-based)

Map visualization

Multi-threaded simulations

API-based city services

📷 UML Diagram

The complete UML diagram is included to visualize:

Class relationships

Data flow

Architectural separation

👤 Author

Muhammad Farhan
Bachelor’s in Computer Science
Focus: Data Structures, Systems Design, C++
