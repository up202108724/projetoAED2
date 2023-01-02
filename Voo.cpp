//
// Created by andre on 29-12-2022.
//

#include "Voo.h"
Voo::Voo(bool direction) {
    hasDirection=direction;
}

void Voo::addNode(Aeroporto airport) {
    Node newnode = {{}, false, airport};
    nodes.push_back(newnode);
}

void Voo::addEdge(int srcIndex, int destIndex) {
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

void Voo::printAllDestinations(){
    for (Node n : nodes){
        cout << "\t";
        cout << n.airportSrc.getCode() << "\n";
        for (Edge e : n.destinos) cout << e.airportDest.getCode() << ",";
        cout << endl;
    }
}

vector<Aeroporto> Voo::getAllDestinations(int indexAirport) {
    vector<Aeroporto> result;
    for (Edge e : nodes[indexAirport].destinos){
        result.push_back(e.airportDest);
    }
    return result;
}
