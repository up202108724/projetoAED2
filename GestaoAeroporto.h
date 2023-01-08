//
// Created by andre on 28-12-2022.
//

//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_GESTAOAEROPORTO_H
#define PROJETOAED2_GESTAOAEROPORTO_H


#include "CompanhiaAerea.h"
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "Aeroporto.h"
#include "Voo.h"

using namespace std;
class GestaoAeroporto {
public:
    GestaoAeroporto();
    void readAirlines();
    void readAirports();
    void readFlights();
    void addAirport(const Aeroporto& a);
    int getAirportID(const string& airportTag);
    Voo getGraph();
    vector<Aeroporto> getAirportsInCountry(const std::string& country) const;
    vector<Aeroporto> getAirportsInCity(const std::string& country, const std::string& city) const;
    const Aeroporto& getAirport(const std::string& country, const std::string& city, const std::string& name) const;
    vector<Aeroporto> getAirportsbyDistanceToPoint(double maxdistance, double x , double y);
    unordered_map<string, unordered_map<string, unordered_map<string, Aeroporto>>> getAirportsToCountryMap();
    unordered_map<string,CompanhiaAerea> getCompanhias();
    unordered_map<string,Aeroporto> getAirportsToCodeMap();
    unordered_set<string> getCountriesInOperationCompanhia(const string& companhia);
    unordered_set<string> getAirportsInOperationCompanhia(const string& companhia);
    int getNumFlights(const string& companhia);

private:
    unordered_map<string, unordered_map<string, unordered_map<string, Aeroporto>>> airportsByCountry;
    unordered_map<string, int> airportIDs;
    unordered_map<string, CompanhiaAerea> companhias;
    unordered_map<string, Aeroporto> airportsByCode;
    Voo flightGraph = Voo(true);
};


#endif //PROJETOAED2_GESTAOAEROPORTO_H