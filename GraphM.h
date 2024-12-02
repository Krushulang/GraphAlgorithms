//
// Krishna Langille assignment_3
// CSS343; Professor Si
// 5/14/2022
// CLion environment
// C++ version 14
//

#ifndef ASSIGNMENT3_GRAPHM_H
#define ASSIGNMENT3_GRAPHM_H
#include "NodeData.h"
#include <climits>

// GraphM class that will store the costs of traversal from nodes to other nodes in a graph structure by reading through a file.
// Uses an adjacency matrix to store the different costs as it finds the shortest path from each node to each other node.
// It finds the shortest path using Dijkstra's algorithm.
// This class can also display all the nodes with the shortest paths, or display a select distance from one node to another.
class GraphM {
public:
    // Constructor that initializes the variables used for this class
    // Each index in data array set to nullptr, costs set to 0, T variable sets path to 0, visited to false, and distance to infinity (INT_MAX).
    GraphM();
    // Deletes the nullnode created.
    ~GraphM();
    // Reads from a file and allocates the size, data, and costs by parsing through the file.
    void buildGraph(ifstream& file);
    // When called, it will insert an edge from one node to another when given the 2 nodes and a value.
    // Since this is a directional graph, the edge will only be true from node 1 to 2.
    bool insertEdge(int n1, int n2, int value);
    // Deletes the edge that spans from the first node to the second.
    bool removeEdge(int n1, int n2);
    // This method find the shortest path from each node to each other node.
    // This is achieved by implementing Dijkstra's algorithm.
    // It uses 3 nested for loops which makes this implementation fairly inefficient.
    // Derived through psudocode provided.
    void findShortestPath();
    // Displays the lowest cost and shortest path from each node to each other name.
    // Makes sure to do it in the correct order and also displays the node data.
    void displayAll() const;
    // Smaller version of displayAll that only displays the smallest cost and shortest path from the first node to the second.
    // The method also displays the node data from the path it takes in the order of the path.
    void display(int n1, int n2) const;
private:
    // Helper method that aids in displaying the data in the displayAll method.
    void displayAllHelper(int n1, int n2) const;

    // TableType sturct that stores 3 variables: a boolean visited, integer distance, and integer path.
    // Visited represents if the edge from one node to another is visited during Dijkstra's.
    // Distance represents the shortest distance known so far.
    // Path represents the node that was last visited before getting the current position.
    struct TableType {
        bool visited;
        int dist;
        int path;
    };

    // ---------------------------------------- Private Variables Used ---------------------------------------- //

    static const int MAXNODES = 101;
    NodeData data[MAXNODES];
    int C[MAXNODES][MAXNODES];
    int size;
    TableType T[MAXNODES][MAXNODES];

    NodeData *nullNode = new NodeData("");
};


#endif //ASSIGNMENT3_GRAPHM_H
