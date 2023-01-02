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

    vector<Aeroporto> GetAirportsInCountry(const std::string& country) const;
    vector<Aeroporto> GetAirportsInCity(const std::string& country, const std::string& city) const;
    const Aeroporto& GetAirport(const std::string& country, const std::string& city, const std::string& name) const;
private:
    unordered_map<string, unordered_map<string, unordered_map<string, Aeroporto>>> airports_by_country_;
    unordered_map<string, int> airportIDs;
    unordered_map<string, CompanhiaAerea> companhias;
    Voo flightGraph = Voo(true);
};


#endif //PROJETOAED2_GESTAOAEROPORTO_H