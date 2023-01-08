//
// Created by andre on 28-12-2022.
//

//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_GESTAOAEROPORTO_H
#define PROJETOAED2_GESTAOAEROPORTO_H


#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "CompanhiaAerea.h"
#include "Aeroporto.h"
#include "Voo.h"

using namespace std;
class GestaoAeroporto {
public:
    /**
     * Cria um gestor dos aeroportos e voos da rede, chamando os leitores de dados
     * @brief Constructor.
     * @brief Complexidade O(n)
     */
    GestaoAeroporto();
    /**
     * Lê os dados do ficheiro airlines.csv, transformando-lhes em objetos da classe CompanhiaAerea e inserindo-lhes no unordered_map companhias
     * @brief Lê e trata os dados do ficheiro airlines.csv
     * @brief Complexidade O(n)
     */
    void readAirlines();
    /**
     * Lê os dados do ficheiro airports.csv, transformando-lhes nodes do grafo flightGraph, e inserindo-lhes nos unordered_maps airportsByCountry, airportsByCode e airportIDs
     * @brief Lê e trata os dados do ficheiro airports.csv
     * @brief Complexidade O(n)
     */
    void readAirports();
    /**
     * Lê os dados do ficheiro flights.csv, inserindo-lhes no flightGraph como edges que conectam os aeroportos e no unordered_multimap da airline respetiva
     * @brief Lê os e trata os dados do ficheiro flights.csv
     * @brief Complexidade O(n)
     */
    void readFlights();
    /**
     * @brief Adiciona um aeroporto ao grafo, airportIDs, airportsByCode e airportsByCountry
     * @brief Complexidade O(1)
     * @param a
     */
    void addAirport(const Aeroporto& a);
    /**
     * @brief Obtém o ID do aeroporto, ou seja, o indíce do aeroporto no grafo
     * @brief Complexidade O(1)
     * @param airportTag
     * @return airportIDs.at(airportTag);
     */
    int getAirportID(const string& airportTag);
    /**
     * @brief Devolve uma referência ao grafo flightGraph
     * @brief Complexidade O(1)
     * @return flightGraph;
     */
    Voo getGraph();
    /**
     * @brief Devolve um vetor com os aeroportos todos de um país
     * @param country
     * @return vetor com os aeroportos de um país
     */
    vector<Aeroporto> getAirportsInCountry(const std::string& country) const;
    /**
     * @brief Devolve um vetor com os aeroportos todos de uma cidade
     * @brief Complexidade O(n)
     * @param country
     * @param city
     * @return vetor com os aeroportos de uma cidade
     */
    vector<Aeroporto> getAirportsInCity(const std::string& country, const std::string& city) const;
    /**
     * @brief Obtém uma referência a um aeroporto a partir do seu país, cidade e código
     * @brief Complexidade O(1)
     * @param country
     * @param city
     * @param name
     * @return airportsByCountry.at(country).at(city).at(name)
     */
    const Aeroporto& getAirport(const std::string& country, const std::string& city, const std::string& name) const;
    /**
     * @brief Obtém os aeroportos até uma maxdistance de uma coordenada
     * @brief Complexidade O(n)
     * @param maxdistance
     * @param x
     * @param y
     * @return os aeroportos a uma maxdistance da coordenada (x,y)
     */
    vector<Aeroporto> getAirportsbyDistanceToPoint(double maxdistance, double x , double y);
    /**
     * @brief Obtém o unordered_map airportsByCountry
     * @brief Complexidade O(1)
     * @return airportsByCountry
     */
    unordered_map<string, unordered_map<string, unordered_map<string, Aeroporto>>> getAirportsToCountryMap();
    /**
     * @brief Obtém o unordered_map companhias
     * @brief Complexidade O(1)
     * @return companhias
     */
    unordered_map<string,CompanhiaAerea> getCompanhias();
    /**
     * @brief Obtém o unordered_map airportIDs
     * @brief Complexidade O(1)
     * @return airportIDs
     */
    unordered_map<string,Aeroporto> getAirportsToCodeMap();
    /**
     * @brief Obtém os países em que uma companhia aérea está presente
     * @brief Complexidade O(n)
     * @param companhia
     * @return unordered_set com os países únicos em que a companhia aérea opera
     */
    unordered_set<string> getCountriesInOperationCompanhia(const string& companhia);
    /**
     * @brief Obtém os aeroportos em que uma companhia aérea está presente
     * @brief Complexidade O(n)
     * @param companhia
     * @return unordered_set com os códigos dos aeroportos únicos em que a companhia aérea opera
     */
    unordered_set<string> getAirportsInOperationCompanhia(const string& companhia);
    /**
     * @brief Obtém os voos pelo qual a companhia aérea é responsável
     * @brief Complexidade O(1)
     * @param companhia
     * @return Tamanho do unordered_multimap flights da companhia
     */
    int getNumFlights(const string& companhia);
    /**
     * @brief Devolve o unordered_set countries
     * @brief Complexidade O(1)
     * @return countries
     */
    unordered_set<string> getcountries();

private:
    /**
     * @brief Unordered_map que associa um aeroporto ao seu código, à sua cidade e ao seu país
     */
    unordered_map<string, unordered_map<string, unordered_map<string, Aeroporto>>> airportsByCountry;
    /**
     * @brief Unordered_map que associa um aeroport ao seu ID, ou seja, o seu indíce no flightGraph
     */
    unordered_map<string, int> airportIDs;
    /**
     * @brief Unordered_map que associa uma companhia aérea ao seu callsign
     */
    unordered_map<string, CompanhiaAerea> companhias;
    /**
     * @brief Unordered_map que associa um aeroporto ao seu código
     */
    unordered_map<string, Aeroporto> airportsByCode;
    /**
     * @brief Grafo que associa os aeroportos entre si pelos seus voos
     */
    Voo flightGraph = Voo(true);
    /**
     * @brief Unordered_set que guarda os países únicos
     */
    unordered_set<string> countries;
};


#endif //PROJETOAED2_GESTAOAEROPORTO_H