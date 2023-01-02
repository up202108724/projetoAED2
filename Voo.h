//
// Created by andre on 29-12-2022.
//

#ifndef PROJETOAED2_VOO_H
#define PROJETOAED2_VOO_H

#include <list>
#include <vector>
#include <iostream>
#include <utility>
#include "Aeroporto.h"
#include "CompanhiaAerea.h"

class Voo {
    struct Edge{
        double weight;
        int dest;
        CompanhiaAerea companhia;
        Aeroporto airportDest;
    };
    struct Node{
        list <Edge> destinos;
        bool visited;
        Aeroporto airportSrc;
    };
    bool hasDirection;
    vector<Node> nodes;
public:
    Voo(bool direction=true);
    void addNode(Aeroporto airport);
    void addEdge(int srcIndex, int destIndex, CompanhiaAerea companhia);
    void printAllNodes(); // debug
    void printAllDestinations(); // debug
    vector<pair<Aeroporto,CompanhiaAerea>> getAllDestinations(int indexAirport);
    void dfs(int origin, int dest);
};


#endif //PROJETOAED2_VOO_H
