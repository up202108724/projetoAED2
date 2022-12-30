//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_GESTAOAEROPORTO_H
#define PROJETOAED2_GESTAOAEROPORTO_H


#include "CompanhiaAerea.h"
#include <vector>
#include <set>
#include <unordered_set>
#include "Aeroporto.h"

using namespace std;
class GestaoAeroporto {
public:
    GestaoAeroporto();
    void readAirlines();
    void readAirports();
    void readFlights();
private:
    vector<CompanhiaAerea> companhiasaereas;
    vector<Aeroporto> aeroportos;
};


#endif //PROJETOAED2_GESTAOAEROPORTO_H
