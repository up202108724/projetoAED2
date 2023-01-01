//
// Created by andre on 29-12-2022.
//

#include "Voo.h"
Voo::Voo(bool direction) {
    hasDirection=direction;
}

int Voo::getTagID(const string& tag){
    for(int k = 0; k<nodes.size(); k++){
        if (nodes.at(k).airportSrc.getCode()==tag) return k;
    }
    return -1;
}

void Voo::addNode(Aeroporto airport) {
    Node newnode = {{}, false, static_cast<int>(nodes.size()), airport};
    nodes.push_back(newnode);
}

void Voo::addEdge(string tagSrc, string tagDest) {
    int srcIndex = getTagID(tagSrc);
    int destIndex = getTagID(tagDest);
    if (srcIndex==-1 or destIndex==-1){
        cout << "O aeroporto de destino ou de origem não existe.\n";
        return;
    }
    double distance = nodes[srcIndex].airportSrc.calculateDistance(nodes[destIndex].airportSrc);
    Edge flight = {distance, destIndex, nodes[destIndex].airportSrc};
    nodes[srcIndex].destinos.push_back(flight);
}

void Voo::printAllNodes() {
    for (Node n : nodes) cout << n.airportSrc.getCode() << "\n";
}

void Voo::dfs(int origin, int dest) {
    nodes[origin].visited = true;
    for (auto e : nodes[origin].destinos){
        int w = e.index;
        if (!nodes[w].visited) dfs(w);
    }
}