//
// Krishna Langille assignment_3
// CSS343; Professor Si
// 5/14/2022
// CLion environment
// C++ version 14
//

#include "GraphL.h"

GraphL::GraphL() {
    size = 0;
//    graph = new GraphNode[MAXNODES];
    for(int i = 0; i < MAXNODES; i++){
        graph[i].data = nullNode;
        graph[i].edgeHead = nullptr;
        graph[i].visited = false;
    }
}

GraphL::~GraphL() {
    for(int i = 1; i < size + 1; i++){
        if(graph[i].edgeHead != nullptr){
            deleteHelper(i, graph[i].edgeHead);
        }
        delete graph[i].data;
    }
    delete nullNode;
}

void GraphL::deleteHelper(int node, GraphL::EdgeNode *edge) {
    if(edge->nextEdge != nullptr){
        deleteHelper(node, edge->nextEdge);
    }
    delete edge;
}

void GraphL::buildGraph(ifstream &file) {
    string tempSize;
    getline(file, tempSize);
    if(tempSize.empty()){
        return;
    }
    size = stoi(tempSize);

    for(int i = 1; i < size + 1; i++){
        string newData;
        getline(file, newData);
        if(newData.length() > 50){
            newData = newData.substr(0, 50);
        }
        auto *newNode = new NodeData(newData);
        graph[i].data = newNode;
    }

    while(true){
        string temp;
        getline(file, temp);
        if(temp[0] == '0'){
            break;
        }
        int n1, n2;
        n1 = stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(temp.find(' ') + 1);
        while(!temp.find(' ')){
            temp = temp.substr(1, temp.size());
        }
        n2 = stoi(temp.substr(0, temp.find(' ')));
        if(graph[n1].edgeHead == nullptr){
            graph[n1].edgeHead = new EdgeNode();
            graph[n1].edgeHead->adjGraphNode = n2;
        }
        else{
            EdgeNode *current = graph[n1].edgeHead;
            while(current->nextEdge != nullptr){
                current = current->nextEdge;
            }
            current->nextEdge = new EdgeNode();
            current->nextEdge->adjGraphNode = n2;
        }
    }
}

void GraphL::displayGraph() const {
    cout << "Graph:" << endl;
    for(int i = 1; i < size + 1; i++){
        cout << "Node " << i << "          " << *graph[i].data << endl;
        if(graph[i].edgeHead != nullptr){
            displayHelper(i, graph[i].edgeHead);
        }
    }
}

void GraphL::displayHelper(int node, EdgeNode* edge) const {
    if(edge->nextEdge != nullptr){
        displayHelper(node, edge->nextEdge);
    }
    cout << "   edge " << node << " " << edge->adjGraphNode << endl;
}

void GraphL::depthFirstSearch() {
    cout << "Depth-first ordering: ";
    for(int i = 1; i < size + 1; i++){
        if(!graph[i].visited){
//            cout << i << " ";
            dfsHelper(i, graph[i].edgeHead);
        }
    }
    cout << endl;
}

void GraphL::dfsHelper(int node, GraphL::EdgeNode *edge) {
    if(graph[node].visited){
        return;
    }
    if(edge == nullptr){
        cout << node << " ";
        graph[node].visited = true;
        return;
    }
    if(edge->nextEdge != nullptr && !graph[edge->nextEdge->adjGraphNode].visited){
        dfsHelper(node, edge->nextEdge);
    }
    if(!graph[node].visited){
        cout << node << " ";
        graph[node].visited = true;
    }
    node = edge->adjGraphNode;
    dfsHelper(node, graph[node].edgeHead);
}
