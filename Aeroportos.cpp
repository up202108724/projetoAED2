#include "Aeroportos.h"

Aeroportos::Aeroportos(string codigo, string nome, string cidade, string pais, float latitude, float longitude) {
    codigo_=codigo;
    nome_=nome;
    cidade_=cidade;
    pais_=pais;
    latitude_=latitude;
    longitude_=longitude;
}
string Aeroportos::getCode() const{
    return code_;
}
string Aeroportos::getName() const{
    return name_;
}
string Aeroportos::getCity() const{
    return city_;
}
string Aeroportos::getCountry() const{
    return country_;
}
float Aeroportos::getLatitude() const{
    return latitude_;
}
float Aeroportos::getLongitude() const{
    return longitude_;
}
