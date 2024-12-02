//
// Krishna Langille assignment_3
// CSS343; Professor Si
// 5/14/2022
// CLion environment
// C++ version 14
//

#include "GraphM.h"

GraphM::GraphM() {
    size = 0;
    for(int i = 0; i < MAXNODES; i++){
        data[i] = *nullNode;
        for(int j = 0; j < MAXNODES; j++){
            C[i][j] = 0;
            T[i][j].path = 0;
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
        }
    }
}

GraphM::~GraphM() {
    delete nullNode;
}

void GraphM::buildGraph(ifstream& file) {
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
        NodeData newNode(newData);
        data[i] = newNode;
    }

    while(true){
        string temp;
        getline(file, temp);
        if(temp[0] == '0'){
            break;
        }
        int n1, n2, value;
        n1 = stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(temp.find(' ') + 1);
        while(!temp.find(' ')){
            temp = temp.substr(1, temp.size());
        }
        n2 = stoi(temp.substr(0, temp.find(' ')));
        temp = temp.substr(temp.find(' ') + 1);
        while(!temp.find(' ')){
            temp = temp.substr(1, temp.size());
        }
        value = stoi(temp.substr(0, temp.find(' ')));
        insertEdge(n1, n2, value);
    }
}

bool GraphM::insertEdge(int n1, int n2, int value) {
    if(n1 > size || n2 > size){
        return false;
    }
    C[n1][n2] = value;
    return true;
}

bool GraphM::removeEdge(int n1, int n2) {
    if(C[n1][n2] == 0){
        return false;
    }
    C[n1][n2] = 0;
    return true;
}

void GraphM::findShortestPath() {
    for(int source = 1; source < size + 1; source++){
        T[source][source].dist = 0;
//        T[source][source].visited = true;

        for(int i = 1; i < size + 1; i++){
            int v = 1;
            int minDist = INT_MAX;

            for(int j = 1; j < size + 1; j++){
                if(!T[source][j].visited && T[source][j].dist < minDist){
                    minDist = T[source][j].dist;
                    v = j;
                }
            }
            T[source][v].visited = true;

            for(int j = 1; j < size + 1; j++){
                if(!T[source][j].visited && C[v][j] && T[source][v].dist != INT_MAX && T[source][v].dist + C[v][j] < T[source][j].dist){
                    T[source][j].dist = C[v][j] + T[source][v].dist;
                    T[source][j].path = v;
                }
            }
        }
    }
}

void GraphM::displayAll() const {
    cout << "Description  From node  To Node  Dijkstra's  Path" << endl;
    for(int i = 1; i < size + 1; i++){
        cout << data[i] << endl << endl;
        for(int j = 1; j < size + 1; j++){
            if(i != j){
                displayAllHelper(i, j);
            }
        }
    }
    cout << endl;
}

void GraphM::displayAllHelper(int n1, int n2) const {
    string Dijkstra;
    if(T[n1][n2].dist == INT_MAX || T[n1][n2].dist == 0){
        Dijkstra = "----";
    }
    else{
        Dijkstra = to_string(T[n1][n2].dist);
    }

    string pathTaken;
    int pathArray[100];
    int length = 0;
    if(Dijkstra != "----"){
        int prev = T[n1][n2].path;
        pathArray[length] = n2;
        length++;
        while(prev != T[n1][n1].path){
            pathArray[length] = prev;
            length++;
            prev = T[n1][prev].path;
        }
        for(int i = length - 1; i >= 0; i--){
            pathTaken += to_string(pathArray[i]) + " ";
        }
    }

    cout << "\t\t" << n1 << "\t   " << n2 << "\t    " << Dijkstra << "      " << pathTaken << endl;
}

void GraphM::display(int n1, int n2) const {
    string Dijkstra;
    if(T[n1][n2].dist == INT_MAX || T[n1][n2].dist == 0){
        Dijkstra = "----";
    }
    else{
        Dijkstra = to_string(T[n1][n2].dist);
    }

    string pathTaken;
    int pathArray[100];
    int length = 0;
    NodeData names[MAXNODES];
    int i = 0;
    if(Dijkstra != "----"){
        int prev = T[n1][n2].path;
        pathArray[length] = n2;
        length++;
        names[i] = *&data[n2];
        i++;
        while(prev != T[n1][n1].path){
            pathArray[length] = prev;
            length++;
            names[i] = *&data[prev];
            i++;
            prev = T[n1][prev].path;
        }
        for(int j = length - 1; j >= 0; j--){
            pathTaken += to_string(pathArray[j]) + " ";
        }
    }

    cout << n1 << "\t   " << n2 << "\t    " << Dijkstra << "      " << pathTaken;
    for(int j = i; j >= 0; j--){
        cout << names[j] << endl << endl;
    }
}
