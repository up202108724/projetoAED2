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
#include <stack>
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
        int num;
        int low;
        bool in_stack;

    };
    bool hasDirection;
    vector<Node> nodes;

public:
    Voo(bool direction=true);
    void addNode(Aeroporto airport);
    void addEdge(int srcIndex, int destIndex, string companhia);
    void printAllNodes(); // debug
    void printAllDestinations(); // debug
    vector<pair<Aeroporto,string>> getAllDestinations(int indexAirport);
    Aeroporto getAirportFromID(int id);
    int getDiameter();
    vector<vector<int>> bfs(int origin, int dest);
    vector<vector<int>> bfs_airlines(int origin, int dest,const vector<string>& airlines);
    int bfs_nvoos(int v);
    void dfs_art(int v, stack<int>& node_stack, list<int>& alist, int index);
    void dfs_scc2(int v, stack<int> &st, list<list<int>> &sccs, int &currCount);
    list<list<int>> listSCCs();
    list<int> articulationPoints();
    unordered_set<string> nFlightsCities(int v, int arbitrary);
    unordered_set<string> nFlightsCountries(int v, int arbitrary);
    unordered_set<string> nFlightsAirports(int v, int arbitrary);
    int getNumFlightsTotal();
};


#endif //PROJETOAED2_VOO_H
