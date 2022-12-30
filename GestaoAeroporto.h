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

using namespace std;
class GestaoAeroporto {
public:
    GestaoAeroporto();
    void readAirlines();
    void readAirports();
    void readFlights();
    void AddAirport(const Aeroporto& a);
    vector<Aeroporto> GetAirportsInCountry(const std::string& country) const;
    vector<Aeroporto> GetAirportsInCity(const std::string& country, const std::string& city) const;
    const Aeroporto& GetAirport(const std::string& country, const std::string& city, const std::string& name) const;

private:
    vector<CompanhiaAerea> companhiasaereas;
    vector<Aeroporto> aeroportos;
    unordered_map<string, unordered_map<string, unordered_map<string, Aeroporto>>> airports_by_country_;
};



#endif //PROJETOAED2_GESTAOAEROPORTO_H

