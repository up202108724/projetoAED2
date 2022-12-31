//
// Created by andre on 29-12-2022.
//

#ifndef PROJETOAED2_VOO_H
#define PROJETOAED2_VOO_H

#include <list>
#include <algorithm>
#include <set>
#include <iostream>
#include "Aeroporto.h"

class Voo {
    struct Edge{
        double weight;
        int index;
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
    Voo(bool direction=false);
    int getTagID(const string& tag);
    void addNode(Aeroporto airport);
    void addEdge(string tagSrc, string tagDest);
    void printAllNodes();
    void dfs(string v);
};


#endif //PROJETOAED2_VOO_H
