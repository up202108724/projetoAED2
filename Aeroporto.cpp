//
// Created by jtoma on 28/12/2022.
//

#include "Aeroporto.h"

Aeroporto::Aeroporto(int code, const string &name, const string &city, const string &country, float latitude, float longitude) {
    code_=code;
    name_=name;
    city_=city;
    country_=country;
    latitude_=latitude;
    longitude_=longitude;

}
int Aeoroporto::getCode() const{
    return code_;
}
string Aeoroporto::getName() const{
    return name_;
}
string Aeoroporto::getCity() const{
    return city_;
}
string Aeoroporto::getCountry() const{
    return country_;
}
float Aeoroporto::getLatitude() const{
    return latitude_;
}
float Aeoroporto::getLongitude() const{
    return longitude_;
}




