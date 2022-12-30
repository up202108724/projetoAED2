#include "Aeroporto.h"

Aeroporto::Aeroporto(string codigo, string nome, string cidade, string pais, float latitude, float longitude) {
    codigo_=codigo;
    nome_=nome;
    cidade_=cidade;
    pais_=pais;
    latitude_=latitude;
    longitude_=longitude;
}
string Aeroporto::getCode() const{
    return codigo_;
}
string Aeroporto::getName() const{
    return nome_;
}
string Aeroporto::getCity() const{
    return cidade_;
}
string Aeroporto::getCountry() const{
    return pais_;
}
float Aeroporto::getLatitude() const{
    return latitude_;
}
float Aeroporto::getLongitude() const{
    return longitude_;
}

bool Aeroporto::operator<(Aeroporto a) {
    return codigo_<a.getCode();
}

bool Aeroporto::operator==(Aeroporto a) {
    return codigo_==a.getCode();
}