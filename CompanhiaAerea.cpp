//
// Created by andre on 28-12-2022.
//

#include "CompanhiaAerea.h"

CompanhiaAerea::CompanhiaAerea(string sigla, string nome, string callsign, string pais) {
    sigla_=sigla;
    nome_=nome;
    callsign_=callsign;
    pais_=pais;
}

string CompanhiaAerea::getNome() {
    return nome_;
}

string CompanhiaAerea::getSigla() {
    return sigla_;
}

bool CompanhiaAerea::operator==(CompanhiaAerea ca){
    return ca.getSigla()==sigla_;
}