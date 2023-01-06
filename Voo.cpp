//
// Created by andre on 29-12-2022.
//

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

Aeroporto Voo::getAirport(int id) const {
    return nodes.at(id).airportSrc;
}
unordered_set<string> Voo::getCompanhiasAeriasfromAeroporto(int indexAirport) {
    unordered_set<string> CompanhiasAereas;

    for (Edge d: nodes[indexAirport].destinos){
        CompanhiasAereas.insert(d.companhia);
    }
    return CompanhiasAereas;
}
unordered_set<string> Voo::getPaisesfromAeroporto(int indexAirport) {
    unordered_set<string> Paises;

    for (Edge d: nodes[indexAirport].destinos){
        Paises.insert(d.airportDest.getCountry());
    }
    return Paises;
}
void Voo::bfs_nvoos(int v){
    for(int i=0; i<= nodes.size(); i++){
        nodes[i].visited=false;
        nodes[i].rootDistance=0;
    }
    queue<int> q;
    q.push(v);
    nodes[v].rootDistance=0;
    nodes[v].visited=true;
    while (!q.empty()){
        int u= q.front();
        q.pop();
        for (Edge e : nodes[u].destinos){
            int w=e.dest;
            if (!nodes[w].visited){
                q.push(w);
                nodes[w].visited=true;
                nodes[w].rootDistance=nodes[u].rootDistance+1;
            }
        }
    }
}
unordered_set<string> Voo::reachablecountriesbynflights(int v, int arbitrary) {

    unordered_set<string> paises;
    bfs_nvoos(v);
    for(int i=0; i <=nodes.size(); i++){
        if (nodes[i].visited && nodes[i].rootDistance <= arbitrary){
            paises.insert(nodes[i].airportSrc.getCountry());
        }
    }
    return paises;
}
unordered_set<string> Voo::reachablecitiesbynflights(int v, int arbitrary) {

    unordered_set<string> cidades;
    bfs_nvoos(v);
    for(int i=1; i <=nodes.size(); i++){
        if (nodes[i].visited && nodes[i].rootDistance <= arbitrary){
            cidades.insert(nodes[i].airportSrc.getCity());
        }
    }
    return cidades;
}
