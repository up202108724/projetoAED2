//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_COMPANHIAAEREA_H
#define PROJETOAED2_COMPANHIAAEREA_H

#include <unordered_set>
#include <string>
#include <unordered_map>
#include <vector>
#include "Aeroporto.h"

using namespace std;

class CompanhiaAerea {
public:
    CompanhiaAerea(string sigla, string nome, string callsign, string pais);
    string getSigla();
    string getNome();
    void addFlight(const string& air1, const string& air2);
    bool operator==(CompanhiaAerea ca);

private:
    string sigla_;
    string nome_;
    string callsign_;
    string pais_;
    unordered_multimap<string, string> flights;
};


#endif //PROJETOAED2_COMPANHIAAEREA_H
