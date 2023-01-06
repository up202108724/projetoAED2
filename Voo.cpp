//
// Created by andre on 29-12-2022.
//

#include <queue>
#include "Voo.h"
Voo::Voo(bool direction) {
    hasDirection=direction;
}

void Voo::addNode(Aeroporto airport) {
    Node newnode = {{}, -1, -1,false, airport};
    nodes.push_back(newnode);
}

void Voo::addEdge(int srcIndex, int destIndex, string companhia) {
    if (srcIndex==-1 or destIndex==-1){
        cout << "O aeroporto de destino ou de origem não existe.\n";
        return;
    }
    Edge flight = { destIndex, companhia, nodes[destIndex].airportSrc};
    nodes[srcIndex].destinos.push_back(flight);
}

void Voo::printAllNodes() {
    for (Node n : nodes) cout << n.airportSrc.getCode() << "\n";
}

void Voo::printAllDestinations(){
    for (Node n : nodes){
        cout << "\t";
        cout << n.airportSrc.getCode() << "\n";
        for (Edge e : n.destinos) cout << e.airportDest.getCode() << ",";
        cout << endl;
    }
}

vector<pair<Aeroporto,string>> Voo::getAllDestinations(int indexAirport) {
    vector<pair<Aeroporto,string>> result;
    for (Edge e : nodes[indexAirport].destinos){
        pair<Aeroporto,string> combo = pair(e.airportDest,e.companhia);
        result.push_back(combo);
    }
    return result;
}

vector<vector<int>> Voo::bfs(int origin, int dest){
    if (origin==dest){
        nodes.at(origin).rootDistance=0;
        return {};
    }
    for(Node n : nodes){
        n.visited=false;
        n.predecessor=-1;
        n.rootDistance=-1;
    }
    int currentMax = INT32_MAX;
    vector<vector<int>> paths;
    queue<int> q;
    q.push(origin);
    nodes.at(origin).rootDistance=0;
    nodes.at(origin).visited=true;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if (nodes.at(u).rootDistance+1<=currentMax) {
            for (auto e: nodes[u].destinos) {
                int w = e.dest;
                if (w == dest) {
                    if (nodes.at(dest).rootDistance == -1) {
                        nodes.at(dest).rootDistance = nodes.at(u).rootDistance + 1;
                        nodes.at(dest).predecessor = u;
                        currentMax = nodes.at(dest).rootDistance;
                    }
                    vector<int> path = {w};
                    int temp = u;
                    while (nodes.at(temp).predecessor != -1) {
                        path.push_back(temp);
                        temp = nodes.at(temp).predecessor;
                    }
                    path.push_back(temp);
                    paths.push_back(path);
                    continue;
                }
                if (!nodes.at(w).visited) {
                    nodes.at(w).rootDistance = nodes.at(u).rootDistance + 1;
                    nodes.at(w).predecessor = u;
                    nodes.at(w).visited = true;
                    q.push(w);
                }
            }
        }
    }
    return paths;
}