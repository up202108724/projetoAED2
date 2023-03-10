#include "Aeroporto.h"
#include "math.h"
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
double Aeroporto::calculateDistance(double x, double y) const{
    double dLat = (x - latitude_) * M_PI / 180.0;
    double dLon = (y- longitude_) * M_PI / 180.0;
    double lat1 = (latitude_) * M_PI / 180.0;
    double lat2 = x * M_PI / 180.0;
    double result = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(result));
    return rad * c;
}
