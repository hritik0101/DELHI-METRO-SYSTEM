# DELHI-METRO-SYSTEM
This project implements a metro network management system using advanced data structures and algorithms in C++. The application allows users to manage stations, paths, and find optimal routes based on distance, time, and number of changes in a metro network.

#Key Features:

Graph-based Representation: 
The metro network is represented as an undirected weighted graph, where vertices are metro stations and edges represent the direct paths between stations, with associated distances and travel times.


Dijkstra's Algorithm:
Used to find the shortest path between two stations based on distance or time, providing an optimal route for commuters.


Breadth-First Search (BFS):
Calculates the minimum number of intermediate stations (or "hops") required to travel between two stations, helping users find the quickest possible changeover route.


Heap for Efficient Pathfinding: 
A priority queue (min-heap) is employed to efficiently manage the search for the shortest paths in the graph using Dijkstra's algorithm.


#Data Structures and Algorithms:
Graph: 
The core of the system is a graph where nodes represent metro stations, and edges represent the paths between them with associated weight (distance) and time.

Heap (Priority Queue): 
Utilized for efficient pathfinding with Dijkstra’s algorithm, ensuring that the shortest path is found in an optimal time.

Breadth-First Search (BFS): 
Applied for determining the minimum number of intermediate stations between the source and destination.

#Purpose:
This project is aimed at providing a simulation of real-world metro networks and optimizing the travel time for passengers by calculating efficient routes using different algorithms.
