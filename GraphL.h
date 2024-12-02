//
// Krishna Langille assignment_3
// CSS343; Professor Si
// 5/14/2022
// CLion environment
// C++ version 14
//

#ifndef ASSIGNMENT3_GRAPHL_H
#define ASSIGNMENT3_GRAPHL_H
#include "NodeData.h"

// GraphL class that stores an directed graph through an adjacency list to preform a Depth-First Search.
// This class will read the data in from a file to gain the size, node data, and edges.
// It contains methods that will preform the dfs and also display the different edges contained within the graph.
class GraphL {
public:
    // Constructor that initializes the size and all variables contained within the graph variable.
    GraphL();
    // Destructor that deletes all the new NodeData and EdgeNodes that are created along with the nullnode.
    ~GraphL();
    // Builds the graph by reading from a file.
    // It first reads the size and names for the nodes.
    // Then it will read all the edges that are in the graph.
    void buildGraph(ifstream& file);
    // This method will display all the edges that are in the graph.
    void displayGraph() const;
    // Depth-first search uses recursion to find the output of the graph given this specific algorithm.
    void depthFirstSearch();
private:
    // Declared so it is known to the rest of the class
    struct EdgeNode;

    // Destructor helper than uses recursion to delete all edges and node data created using new.
    void deleteHelper(int node, EdgeNode* edge);
    // Display helper that uses recursion to display everything nicely when displayGraph is called.
    void displayHelper(int node, EdgeNode* edge) const;
    // Depth-first search helper that utilizes recursion to find the deepest edge inserted (which should be the smallest given the instructions).
    void dfsHelper(int node, EdgeNode* edge);

    // Given struct that contains all the graph node data types.
    // Similar structure to something like a tree where this acts as the root/head.
    struct GraphNode{
        EdgeNode* edgeHead;
        NodeData* data;
        bool visited;
    };

    // Given struct that contains the current node and the next one if it exists.
    struct EdgeNode{
        int adjGraphNode;
        EdgeNode* nextEdge;
    };

    // ---------------------------------------- Private Variables Used ---------------------------------------- //

    static const int MAXNODES = 101;
    int size;
    NodeData *nullNode = new NodeData("");
    GraphNode graph[MAXNODES]{};
};

#endif //ASSIGNMENT3_GRAPHL_H
