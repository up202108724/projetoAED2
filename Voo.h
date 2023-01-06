//
// Created by andre on 29-12-2022.
//

#ifndef PROJETOAED2_VOO_H
#define PROJETOAED2_VOO_H

#include <list>
#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#include "Aeroporto.h"
#include "CompanhiaAerea.h"

class Voo {
    struct Edge{
        int dest;
        string companhia;
        Aeroporto airportDest;
    };
    struct Node{
        list <Edge> destinos;
        int rootDistance;
        int predecessor;
        bool visited;
        Aeroporto airportSrc;
    };
    bool hasDirection;
    vector<Node> nodes;

public:
    Voo(bool direction=true);
    void addNode(Aeroporto airport);
    void addEdge(int srcIndex, int destIndex, string companhia);
    void printAllNodes(); // debug
    void printAllDestinations(); // debug
    Aeroporto getAirport(int id) const;
    vector<pair<Aeroporto,string>> getAllDestinations(int indexAirport);
    vector<vector<int>> bfs(int origin, int dest);
    unordered_set<string> getPaisesfromAeroporto(int indexAirport);
    unordered_set<string> getCompanhiasAeriasfromAeroporto(int indexAirport);
    void bfs_nvoos(int v);
    unordered_set<string> reachablecitiesbynflights(int v, int arbitrary);
    unordered_set<string> reachablecountriesbynflights(int v, int arbitrary);
};


#endif //PROJETOAED2_VOO_H
