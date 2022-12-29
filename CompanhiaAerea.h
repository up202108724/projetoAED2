//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_COMPANHIAAEREA_H
#define PROJETOAED2_COMPANHIAAEREA_H

#include <unordered_set>
#include <string>
using namespace std;
class CompanhiaAerea {
public:
    CompanhiaAerea( string sigla, string nome, string callsign, string pais);


private:
    string sigla_;
    string nome_;
    string callsign_;
    string pais_;
};


#endif //PROJETOAED2_COMPANHIAAEREA_H
