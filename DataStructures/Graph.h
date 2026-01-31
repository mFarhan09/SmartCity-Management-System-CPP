#pragma once
#include <iostream>
using namespace std;

struct EdgeNode
{
    char destinationId[20];
    double weight;
    EdgeNode* next;

    EdgeNode(const char* dest, double w) : weight(w), next(NULL)
    {
        int i = 0;
        while (dest[i] != '\0' && i < 19)
        {
            destinationId[i] = dest[i];
            i++;
        }
        destinationId[i] = '\0';
    }
};

struct GraphNode
{
    char id[20];
    char name[100];
    double latitude;
    double longitude;
    EdgeNode* edges;

    GraphNode(const char* i, const char* n, double lat, double lon)
        : latitude(lat), longitude(lon), edges(NULL)
    {
        int idx = 0;
        while (i[idx] != '\0' && idx < 19)
        {
            id[idx] = i[idx];
            idx++;
        }
        id[idx] = '\0';

        idx = 0;
        while (n[idx] != '\0' && idx < 99)
        {
            name[idx] = n[idx];
            idx++;
        }
        name[idx] = '\0';
    }

    void addEdge(const char* destination, double weight)
    {
        EdgeNode* newEdge = new EdgeNode(destination, weight);
        newEdge->next = edges;
        edges = newEdge;
    }
};

class PathArray
{
public:
    char** paths;
    int size;
    int capacity;

    PathArray() : size(0), capacity(10)
    {
        paths = new char* [capacity];
    }

    void add(const char* str)
    {
        if (size >= capacity)
        {
            capacity *= 2;
            char** newPaths = new char* [capacity];
            for (int i = 0; i < size; i++)
            {
                newPaths[i] = paths[i];
            }
            delete[] paths;
            paths = newPaths;
        }

        paths[size] = new char[20];
        int i = 0;
        while (str[i] != '\0' && i < 19)
        {
            paths[size][i] = str[i];
            i++;
        }
        paths[size][i] = '\0';
        size++;
    }

    ~PathArray()
    {
        for (int i = 0; i < size; i++)
        {
            delete[] paths[i];
        }
        delete[] paths;
    }
};

struct DijkstraNode
{
    double distance;
    int vertexIndex;

    DijkstraNode() : distance(0), vertexIndex(-1) {}
    DijkstraNode(double d, int idx) : distance(d), vertexIndex(idx) {}
};

class MinHeap
{
private:
    DijkstraNode* heap;
    int size;
    int capacity;

    void swap(int i, int j)
    {
        DijkstraNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int index)
    {
        if (index == 0) return;

        int parent = (index - 1) / 2;
        if (heap[index].distance < heap[parent].distance)
        {
            swap(index, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index)
    {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].distance < heap[smallest].distance)
        {
            smallest = left;
        }
        if (right < size && heap[right].distance < heap[smallest].distance)
        {
            smallest = right;
        }

        if (smallest != index)
        {
            swap(index, smallest);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap(int cap = 100) : size(0), capacity(cap)
    {
        heap = new DijkstraNode[capacity];
    }

    void insert(double distance, int vertexIndex)
    {
        if (size >= capacity) return;

        heap[size] = DijkstraNode(distance, vertexIndex);
        heapifyUp(size);
        size++;
    }

    DijkstraNode extractMin()
    {
        if (size == 0) return DijkstraNode(-1, -1);

        DijkstraNode min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return min;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    ~MinHeap()
    {
        delete[] heap;
    }
};

class Graph
{
private:
    GraphNode** vertices;
    int capacity;
    int numVertices;



    bool stringCompare(const char* s1, const char* s2)
    {
        int i = 0;
        while (s1[i] != '\0' && s2[i] != '\0')
        {
            if (s1[i] != s2[i]) return false;
            i++;
        }
        return s1[i] == s2[i];
    }

public:


    int findVertexIndex(const char* id)
    {
        for (int i = 0; i < numVertices; i++)
        {
            int j = 0;
            bool match = true;
            while (vertices[i]->id[j] != '\0' || id[j] != '\0')
            {
                if (vertices[i]->id[j] != id[j])
                {
                    match = false;
                    break;
                }
                j++;
            }
            if (match) return i;
        }
        return -1;
    }
    Graph(int cap = 100) : capacity(cap), numVertices(0)
    {
        vertices = new GraphNode * [capacity];
    }

    void addVertex(const char* id, const char* name, double lat, double lon)
    {
        if (numVertices >= capacity)
        {
            cout << "Graph is full!" << endl;
            return;
        }
        vertices[numVertices++] = new GraphNode(id, name, lat, lon);
        cout << "Added location: " << name << " (" << id << ")" << endl;
    }

    void addEdge(const char* from, const char* to, double weight)
    {
        int fromIdx = findVertexIndex(from);
        int toIdx = findVertexIndex(to);

        if (fromIdx == -1 || toIdx == -1)
        {
            cout << "Error: One or both locations not found!" << endl;
            return;
        }

        vertices[fromIdx]->addEdge(to, weight);
        vertices[toIdx]->addEdge(from, weight);

        cout << "Connected " << vertices[fromIdx]->name << " <-> "
            << vertices[toIdx]->name << " (" << weight << " km)" << endl;
    }

    PathArray* dijkstra(const char* startId, const char* endId)
    {
        PathArray* path = new PathArray();
        int startIdx = findVertexIndex(startId);
        int endIdx = findVertexIndex(endId);

        if (startIdx == -1 || endIdx == -1)
        {
            cout << "Start or end location not found!" << endl;
            return path;
        }

        double* distances = new double[numVertices];
        int* previous = new int[numVertices];
        bool* visited = new bool[numVertices];

        for (int i = 0; i < numVertices; i++)
        {
            distances[i] = 999999.9;
            previous[i] = -1;
            visited[i] = false;
        }

        distances[startIdx] = 0;
        MinHeap pq(numVertices * 10);
        pq.insert(0, startIdx);

        while (!pq.isEmpty())
        {
            DijkstraNode current = pq.extractMin();
            int u = current.vertexIndex;

            if (u == -1 || visited[u]) continue;
            visited[u] = true;

            if (u == endIdx) break;

            EdgeNode* edge = vertices[u]->edges;
            while (edge != NULL)
            {
                int v = findVertexIndex(edge->destinationId);
                if (v != -1 && !visited[v])
                {
                    double newDist = distances[u] + edge->weight;
                    if (newDist < distances[v])
                    {
                        distances[v] = newDist;
                        previous[v] = u;
                        pq.insert(newDist, v);
                    }
                }
                edge = edge->next;
            }
        }

        if (distances[endIdx] < 999999.0)
        {
            int current = endIdx;
            int pathLength = 0;
            int temp = current;

            while (temp != -1)
            {
                pathLength++;
                temp = previous[temp];
            }

            char** tempPath = new char* [pathLength];
            current = endIdx;
            for (int i = pathLength - 1; i >= 0; i--)
            {
                tempPath[i] = vertices[current]->id;
                current = previous[current];
            }

            for (int i = 0; i < pathLength; i++)
            {
                path->add(tempPath[i]);
            }
            delete[] tempPath;

            cout << "\nShortest path from " << vertices[startIdx]->name
                << " to " << vertices[endIdx]->name << ":" << endl;
            cout << "Distance: " << distances[endIdx] << " km" << endl;
            cout << "Route: ";
            for (int i = 0; i < path->size; i++)
            {
                int idx = findVertexIndex(path->paths[i]);
                cout << vertices[idx]->name;
                if (i < path->size - 1) cout << " -> ";
            }
            cout << endl;
        }
        else
        {
            cout << "No path found!" << endl;
        }

        delete[] distances;
        delete[] previous;
        delete[] visited;

        return path;
    }

    const char* findNearest(const char* startId, const char* searchName)
    {
        int startIdx = findVertexIndex(startId);
        if (startIdx == -1)
        {
            cout << "Start location not found!" << endl;
            return NULL;
        }

        bool* visited = new bool[numVertices];
        int* queue = new int[numVertices];
        int front = 0, rear = 0;

        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false;
        }

        visited[startIdx] = true;
        queue[rear++] = startIdx;

        const char* result = NULL;

        while (front < rear)
        {
            int current = queue[front++];

            bool found = true;
            int i = 0;
            while (searchName[i] != '\0')
            {
                bool charFound = false;
                int j = 0;
                while (vertices[current]->name[j] != '\0')
                {
                    if (vertices[current]->name[j] == searchName[i])
                    {
                        charFound = true;
                        break;
                    }
                    j++;
                }
                if (!charFound)
                {
                    found = false;
                    break;
                }
                i++;
            }

            if (found && current != startIdx)
            {
                result = vertices[current]->id;
                break;
            }

            EdgeNode* edge = vertices[current]->edges;
            while (edge != NULL)
            {
                int neighborIdx = findVertexIndex(edge->destinationId);
                if (neighborIdx != -1 && !visited[neighborIdx])
                {
                    visited[neighborIdx] = true;
                    queue[rear++] = neighborIdx;
                }
                edge = edge->next;
            }
        }

        delete[] visited;
        delete[] queue;

        return result;
    }

    void display()
    {
        cout << "\n\t\t\t........CITY ROAD NETWORK....." << endl;
        cout << endl;
        for (int i = 0; i < numVertices; i++)
        {
            cout << "\t" << vertices[i]->name << " [" << vertices[i]->id << "]:" << endl;
            EdgeNode* edge = vertices[i]->edges;
            while (edge != NULL)
            {
                int destIdx = findVertexIndex(edge->destinationId);
                if (destIdx != -1)
                {
                    cout << "\t\t" << "  |-> " << vertices[destIdx]->name
                        << " ......" << edge->weight << " km" << endl;
                }
                edge = edge->next;
            }
            cout << endl;
        }
    }

    ~Graph()
    {
        for (int i = 0; i < numVertices; i++)
        {
            EdgeNode* edge = vertices[i]->edges;
            while (edge != NULL)
            {
                EdgeNode* temp = edge;
                edge = edge->next;
                delete temp;
            }
            delete vertices[i];
        }
        delete[] vertices;
    }
};