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
        /**
         * @brief indice do node destino
         */
        int dest;
        /**
         * @brief companhia que opera o voo
         */
        string companhia;
        /**
         * @brief aeroporto que corresponde ao node destino
         *
         */
        Aeroporto airportDest;
    };
    struct Node{
        /**
         * @brief conjunto de ligações unidireccionais que partem do node
         */
        list <Edge> destinos;
        /**
         * @brief distância do node ao node no qual se originou a pesquisa
         */
        int rootDistance;
        /**
         * @brief indice de node que precede num voo o node correspondente ao atual
         *
         */
        int predecessor;
        bool visited;
        /**
         * @brief aeroporto que corresponde ao node origem
         *
         */
        Aeroporto airportSrc;
        /**
         * @brief ordem pelo qual o node é visitado
         */
        int num;
        /**
         * @brief a ordem mais baixa alcançável pela sub-árvore que começa no node
         */
        int low;
        /**
         * @brief verdadeiro se o node se encontra na stack de nodes (conceito implementado nas dfs que determinam pontos de articulação e componentes fortemente conexos), caso contrário falso
         */
        bool in_stack;

    };
    bool hasDirection;
    /**
     * @brief Conjunto de todos os nodes pertencentes ao grafo
     */
    vector<Node> nodes; // vetor que guarda todos os nodes do grafo de aeroportos

public:
    Voo(bool direction=true);
    /**
     * @brief Adiciona um objeto do tipo aeroporto ao grafo
     * @param airport
     * @brief Complexidade O(1)
     */
    void addNode(Aeroporto airport);
    /**
     * @brief Establece uma ligação dirigida entre dois nodes do grafo, cujo aeroporto(node) origem é representado por um srcIndex e o aeroporto(node) destino é representado por um dest Index
     *
     * @param srcIndex
     * @param destIndex
     * @param companhia
     * @brief Complxidade O(1)
     */
    void addEdge(int srcIndex, int destIndex, string companhia);
    void printAllNodes(); // debug
    void printAllDestinations(); // debug
    /**
     * @brief Retorna um vetor que representa todos os destinos de voos que partem de um aeroporto cujo índice é indexAirport, que se representam por pares de Aeroporto destino e Companhia que opera esse voo
     * @brief Complexidade O(1)
     * @param indexAirport
     * @return
     */
    vector<pair<Aeroporto,string>> getAllDestinations(int indexAirport);
    /**
     * @brief Devolve o Aeroporto correspondente ao índice(id) pelo qual se deseja procurar
     * @brief Complexidade O(1)
     * @param id
     * @return
     */
    Aeroporto getAirportFromID(int id);
    /**
     * @brief Devolve o diâmetro da rede
     * @brief Complexidade O(|V|*(|V|+|E|))
     * @return
     */
    int getDiameter();
    /**
     * @brief Faz uma pesquisa em largura que começa no aeroporto de índice origin , e guarda todos os percursos possíveis para o aeroporto de índice dest
     * @brief Complexidade O(|V|+|E|)
     * @param origin
     * @param dest
     * @return vetor com vetor de aeroportos que fazem parte de cada percurso possível
     */
    vector<vector<int>> bfs(int origin, int dest);
    /**
     * @brief Faz uma pesquisa em largura que começa no aeroporto de índice origin , e guarda todos os percursos possíveis para o aeroporto de índice dest, cujos percursos apenas podem ser feitos se as
     * companhias correspondentes a cada voo pertencerem ao vetor airlines
     * @brief Complexidade O(|V|+|E|)
     * @param origin
     * @param dest
     * @return vetor com vetor de aeroportos que fazem parte de cada percurso possível
     */
    vector<vector<int>> bfs_airlines(int origin, int dest,const vector<string>& airlines);
    /**
     * @brief Faz uma pesquisa em largura ao longo da rede a começar num aeroporto de índice v, e retorna a distância máxima entre o aeroporto origem de indice v e um dos outros aeroportos.
     * @param v
     * @return distância máxima entre um aeroporto e o aeroporto que inicia a pesquisa
     */
    int bfs_nvoos(int v);
    /**
     * @brief Faz uma leitura em profundidade que começa no node de índice v( atribuindo-lhe um índice inicial index) , acrescentando a alist pontos de articulação eventualmente encontrados, e atualizando a node_stack a fim
     * @param v
     * @param node_stack
     * @param alist
     * @param index
     */
    void dfs_art(int v, stack<int>& node_stack, list<int>& alist, int index);
    /**
     * @brief Baseando-se no algoritmo de Tarjan, faz uma pesquisa em profundiade que começa no node de indice v, atribui-lhe um índice de procura currCount, e
      verifica se pode construir um novo componente fortemente conexo a partir desse node. Se conseguir
     * @param v
     * @param st
     * @param sccs
     * @param currCount
     * Complexidade O(|V|+|E|)
     */
    void dfs_scc2(int v, stack<int> &st, list<list<int>> &sccs, int &currCount);
    /**
     * @brief Método que procura todos os componentes conexos existentes no grafo, retornando uma lista de listas com os indices dos nodes que simbolizam cada componente conexo,
     * e trata também de listar todos os aeroportos correspondentes a cada um dos componentes conexos, numerando cada um destes pela ordem que aparece na lista
     * @return lista de componentes conexos
     */
    list<list<int>> listSCCs();
    /**
     * @brief Método que procura todos os pontos de articulação existentes no grafo, retornando uma lista com os índices dos nodes que representam estes pontos de articulação.
     * @brief Também trata de listar os nomes dos aeroportos correspondentes a estes pontos de articulação por ordem crescente de nome.
     * @return lista de pontos de articulacao
     */
    list<int> articulationPoints();
    /**
     * @brief Determina quais as cidades que podem ser alcançadas a partir de um aeroporto com o máximo de n voos ( n é arbitrário)
     * @return Set desordenado de nomes de cidades alcançáveis a partir do aeroporto de índice v com o máximo de n voos
     */
    unordered_set<string> nFlightsCities(int v, int arbitrary);
    /**
     * @brief Determina quais os países que podem ser alcançadas a partir de um aeroporto com o máximo de n voos ( n é arbitrário)
     * @return Set desordenado de nomes de países alcançáveis a partir do aeroporto de índice v com o máximo de n voos
     */
    unordered_set<string> nFlightsCountries(int v, int arbitrary);
    /**
     * @brief Determina quais os aeroportos que podem ser alcançadas a partir de um aeroporto com o máximo de n voos ( n é arbitrário)
     * @return Set desordenado de nomes de aeroportos alcançáveis a partir do aeroporto de índice v com o máximo de n voos
     */
    unordered_set<string> nFlightsAirports(int v, int arbitrary);
    /**
     * @brief Retona o número de voos total da rede
     * @brief Complexidade O(n)
     * @return NumFlightsTotal
     */
    int getNumFlightsTotal();
};


#endif //PROJETOAED2_VOO_H
