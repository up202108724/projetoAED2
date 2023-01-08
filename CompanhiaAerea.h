//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_COMPANHIAAEREA_H
#define PROJETOAED2_COMPANHIAAEREA_H

#include <unordered_set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class CompanhiaAerea {
public:
    /**
    * Define uma companhia aérea, definida pela sua sigla, nome, callsign e país
    * @brief Constructor.
    * @brief Complexidade O(1)
    *@param sigla
    *@param nome
    *@param callsign
    *@param pais
    */
    CompanhiaAerea(string sigla, string nome, string callsign, string pais);
    /**
     * @brief Obtém a sigla da companhia aérea
     * @brief Complexidade O(1)
     * @return sigla
     */
    string getSigla();
    /**
     * @brief Devolve o nome da companhia aérea
     * @brief Complexidade O(1)
     * @return nome
     */
    string getNome();
    /**
     * @brief Adiciona um novo voo à lista de voos da companhia aérea
     * @brief Complexidade O(1)
     * @param air1 Código do aeroporto de partida
     * @param air2 Código do aeroporto de destino
     */

    void addFlight(const string& air1, const string& air2);
    /**
     * @brief obtém a lista de voos da companhia aérea
     * @brief Complexidade O(1)
     * @return flights
     */
    unordered_multimap<string,string> getFlights();
    /**
    * @brief Define a igualdade de companhias aéreas pela comparação entre as suas siglas
    * @brief Complexidade O(1)
    * @param ca
    * @return sigla_==ca.getSigla()
    */
    bool operator==(CompanhiaAerea ca);
    /**
     * @brief Devolve o país a que a companhia aérea pertence
     * @brief Complexidade O(1)
     * @return pais
     */
    string getPais();
private:
    /**
     * @brief Sigla da companhia aérea
     */
    string sigla_;
    /**
     * @brief Nome da companhia aérea
     */
    string nome_;
    /**
     * @brief Callsign da companhia aérea
     */
    string callsign_;
    /**
     * @brief País da companhia aérea
     */
    string pais_;
    /**
     * @brief Lista de voos da companhia aérea
     */
    unordered_multimap<string, string> flights;
};


#endif //PROJETOAED2_COMPANHIAAEREA_H