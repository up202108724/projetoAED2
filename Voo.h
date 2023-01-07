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
    Aeroporto getAirport(int id) const;
    vector<pair<Aeroporto,string>> getAllDestinations(int indexAirport);
    vector<vector<int>> bfs(int origin, int dest);
    vector<vector<int>> bfs_airlines(int origin, int dest,const vector<string>& airlines);
    unordered_set<string> getPaisesfromAeroporto(int indexAirport);
    unordered_set<string> getCompanhiasAeriasfromAeroporto(int indexAirport);
    void bfs_nvoos(int v);
    vector<Node> getNodes(){return nodes;};
    unordered_set<string> reachablecitiesbynflights(int v, int arbitrary);
    unordered_set<string> reachablecountriesbynflights(int v, int arbitrary);
    void dfs_art(int v, stack<int>& node_stack, list<int>& alist, int index);
    list<int> articulationPoints();
    int dfs_scc(int v , stack<int>* node_stack);
    int countSCCs();
    void dfs_scc2(int v, stack<int> &st, list<list<int>> &sccs, int &currCount);
    list<list<int>> listSCCs();
    Aeroporto getAirportFromID(int id);
};


#endif //PROJETOAED2_VOO_H
