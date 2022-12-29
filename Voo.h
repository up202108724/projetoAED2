//
// Created by andre on 29-12-2022.
//

#ifndef PROJETOAED2_VOO_H
#define PROJETOAED2_VOO_H


#include <list>
#include <vector>
#include "Aeroportos.h"

class Voo {

    struct Edge{
        float weight;
        string dest;
    };
    struct Node{
        list <Edge> destinos;
        bool visited;
        string sigla;
    };
    bool hasDirection;
    vector<Node> nodes;
public:
    Voo(bool direction=false);
    void addEdge(string src, string dest);
    void dfs(string v);
};


#endif //PROJETOAED2_VOO_H
