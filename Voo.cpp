//
// Created by andre on 29-12-2022.
//

#include <algorithm>
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
int Voo::bfs_nvoos(int v){
    int maxdistance=0;
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
                if (nodes[w].rootDistance>maxdistance){
                    maxdistance=nodes[w].rootDistance;
                }
            }
        }
    }
    return maxdistance;
}
unordered_set<string> Voo::reachablecountriesbynflights(int v, int arbitrary) {

    unordered_set<string> paises;
    bfs_nvoos(v);
    for(int i=0; i <=nodes.size(); i++){
        if (nodes[i].visited && nodes[i].rootDistance <= arbitrary && nodes[i].rootDistance>0 ){
            paises.insert(nodes[i].airportSrc.getCountry());
        }
    }
    return paises;
}
unordered_set<string> Voo::reachablecitiesbynflights(int v, int arbitrary) {

    unordered_set<string> cidades;
    bfs_nvoos(v);
    for(int i=1; i <=nodes.size(); i++){
        if (nodes[i].visited && nodes[i].rootDistance <= arbitrary && nodes[i].rootDistance>0 ){
            cidades.insert(nodes[i].airportSrc.getCity());
        }
    }
    return cidades;
}
unordered_set<string> Voo::reachableairportsbynflights(int v, int arbitrary) {
    unordered_set<string> aeroportos;
    bfs_nvoos(v);
    for(int i=0; i <=nodes.size(); i++){
        if (nodes[i].visited && nodes[i].rootDistance <= arbitrary && nodes[i].rootDistance >0 ){
            aeroportos.insert(nodes[i].airportSrc.getName());
        }
    }
    return aeroportos;
}

void Voo::dfs_scc2(int v, stack<int> &st, list<list<int>> &sccs, int &currCount) {
    nodes[v].visited = true;
    nodes[v].num = currCount++;
    int num = nodes[v].num;
    st.push(v);
    nodes[v].in_stack = true;
    nodes[v].low = num;

    for (const Edge& e : nodes[v].destinos) {
        int w = e.dest;
        if(!nodes[w].visited) {
            dfs_scc2(w,st,sccs,currCount);
            nodes[v].low = min(nodes[v].low, nodes[w].low);
        }
        if (nodes[w].in_stack) {
            nodes[v].low = min(nodes[v].low, nodes[w].num);
        }
    }

    if (nodes[v].low == num) {
        list<int> scc;
        int w;
        do {
            w = st.top();
            st.pop();
            nodes[w].in_stack = false;
            scc.push_front(w);
        } while (nodes[w].num != num);
        sccs.push_back(scc);
    }
}
void Voo::dfs_art(int v, stack<int>& node_stack, list<int>& alist, int index){
    nodes[v].visited=true;
    nodes[v].low=index;
    nodes[v].num=index;
    nodes[v].in_stack=true;
    index++;
    int children=0;
    bool articulation=false;
    node_stack.push(v);

    for (Edge e : nodes[v].destinos){
        int w= e.dest;
        if (!nodes[w].visited){
            children++;
            dfs_art(w,node_stack, alist, index);
            nodes[v].low=min(nodes[w].low,nodes[v].low);
            if (nodes[w].low >=nodes[v].num){
                articulation= true;
            }
        }
        else if (nodes[w].in_stack){
            nodes[v].low=min(nodes[v].low,nodes[w].num);
        }
    }
    nodes[node_stack.top()].in_stack= false;
    node_stack.pop();
    if ((nodes[v].num > 0 && articulation) || (nodes[v].num==0 && children>1))
        alist.push_front(v);
}
list<int> Voo::articulationPoints() {
    vector<string> l;
    list<int> answer;
    stack<int> node_stack;
    for(int i =0; i <nodes.size(); i++){
        nodes[i].visited=false;
        nodes[i].in_stack=false;
        nodes[i].low=0;
        nodes[i].num=0;
    }
    for(int i =0; i <nodes.size(); i++){
        if(!nodes[i].visited) {
            dfs_art(i, node_stack, answer, 0);
        }
    }
    for (int i: answer){
        l.push_back(nodes[i].airportSrc.getName());
    }

    sort(l.begin(), l.end());
    for (auto p:l){
        cout << p << endl;
    }
    cout<< "Existem assim " << answer.size() << " pontos de articulação ao longo da rede." << endl ;
    cout << "\n";
    return answer;

}

list<list<int>> Voo::listSCCs() {
    list<list<int>> sccs;
    stack<int> st;
    int currCount = 0;
    int count=1;
    for (int i = 0; i < nodes.size(); i ++) {
        nodes[i].visited = false;
        nodes[i].in_stack = false;
    }

    for (int i = 0; i < nodes.size(); i++)
        if(!nodes[i].visited) {
            dfs_scc2(i,st,sccs,currCount);
        }
    for (auto it= sccs.begin(); it!=sccs.end(); it++) {
        count++;
        cout << count << "º componente conexo" << endl;
        for (int j: *it){
            cout <<nodes[j].airportSrc.getName() <<" ";
        }
        cout << endl;

    }
    return sccs;
}

Aeroporto Voo::getAirportFromID(int id) {
    return nodes.at(id).airportSrc;
}

vector<vector<int>> Voo::bfs_airlines(int origin, int dest, const vector<string> &airlines) {
    if (origin==dest){
        nodes.at(origin).rootDistance=0;
        return {};
    }
    for(Node n : nodes){
        n.visited=false;
        n.predecessor=-1;
        n.rootDistance=-1;
    }
    queue<int> q;
    q.push(origin);
    nodes.at(origin).visited=true;
    nodes.at(origin).rootDistance=0;
    vector<vector<int>> paths;
    int max = INT32_MAX;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        if (nodes.at(u).rootDistance+1<=max) {
            for (auto e: nodes[u].destinos) {
                if (find(airlines.begin(), airlines.end(), e.companhia) == airlines.end()) continue;
                int w = e.dest;
                if (w == dest) {
                    if (nodes.at(dest).rootDistance == -1) {
                        nodes.at(dest).rootDistance = nodes.at(u).rootDistance + 1;
                        nodes.at(dest).predecessor = u;
                        max = nodes.at(dest).rootDistance;
                    }
                    vector<int> path = {w};
                    int temp =u;
                    while (nodes.at(temp).predecessor != -1) {
                        path.push_back(temp);
                        temp = nodes.at(temp).predecessor;
                    }
                    path.push_back(temp);
                    paths.push_back(path);
                    continue;
                }
                if (!nodes.at(w).visited) {
                    nodes.at(w).visited = true;
                    nodes.at(w).rootDistance = nodes.at(u).rootDistance + 1;
                    nodes.at(w).predecessor = u;
                    q.push(w);
                }
            }

        }
    }
    return paths;
}
int Voo::getDiameter(){
    int diameter=0;
    for(int i=0; i < nodes.size(); i++ ){
        int curr= bfs_nvoos(i);
        if (diameter< curr){
            diameter=curr;
        }
    }
    return diameter;
}