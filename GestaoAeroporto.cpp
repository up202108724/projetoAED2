
#include "GestaoAeroporto.h"
#include "Aeroporto.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
GestaoAeroporto::GestaoAeroporto() {
    readFlights();
    readAirlines();
    readAirports();
}
void GestaoAeroporto::readAirlines() {
    ifstream in("../docs/airlines.csv");
    int i=0;
    string line;
    getline(in,line);
    while (getline(in,line)){
        string Code,Name,Callsign,Country;
        istringstream iss(line);
        while(iss.good()){
            string substr;
            getline(iss, substr, ',');
            if (i == 0) Code= substr;
            if (i == 1) Name = substr;
            if (i == 2) Callsign= substr;
            if (i == 3) Country= substr;
            i++;
        }
        CompanhiaAerea companhia= CompanhiaAerea(Code,Name,Callsign,Country);
        i=0;
    }
}
void GestaoAeroporto::readAirports()  {
    ifstream in("../docs/airports.csv");
    int i=0;
    string line;
    getline(in,line);
    while (getline(in,line)){
        string Code,Name,City,Country,Latitude,Longitude;
        istringstream iss(line);
        while(iss.good()){
            string substr;
            getline(iss, substr, ',');
            if (i == 0) Code= substr;
            if (i == 1) Name = substr;
            if (i == 2) City= substr;
            if (i == 3) Country= substr;
            if (i == 4) Latitude= substr;
            if (i == 5) Longitude= substr;
            i++;
        }
        float latitude= stof(Latitude);
        float longitude= stof(Longitude);
        Aeroporto novo_aeroporto= Aeroporto(Code,Name,City,Country,latitude,longitude);
        aeroportos.push_back(novo_aeroporto);
        AddAirport(novo_aeroporto);
        i=0;
    }

}
void GestaoAeroporto::readFlights() {
    ifstream in("../docs/flights.csv");
    int i=0;
    string line;
    getline(in,line);
    while (getline(in,line)){
        string Source,Target,Airline;
        istringstream iss(line);
        while(iss.good()){
            string substr;
            getline(iss, substr, ',');
            if (i == 0)
                Source = substr;
            if (i == 1)
                Target= substr;

            if (i == 2)
                Airline = substr;
            i++;
        }
        i=0;

    }


}

void GestaoAeroporto::AddAirport(const Aeroporto& a) {

    unordered_map<string, Aeroporto> new_map;
    unordered_map<string, unordered_map< string ,Aeroporto>> aux_map ;
    new_map.insert({a.getName(), a});
    aux_map.insert({a.getCity(), new_map});
    airports_by_country_.insert({a.getCountry(), aux_map});
}
vector<Aeroporto> GestaoAeroporto::GetAirportsInCountry(const string &country) const {
    std::vector<Aeroporto> airports;
    for (const auto& city : airports_by_country_.at(country)) {
        for (const auto& airport : city.second) {
            airports.push_back(airport.second);
        }
    }
    return airports;
}
std::vector<Aeroporto> GestaoAeroporto::GetAirportsInCity(const std::string& country, const std::string& city) const {
    std::vector<Aeroporto> airports;
    for (const auto& airport : airports_by_country_.at(country).at(city)) {
        airports.push_back(airport.second);
    }
    return airports;
}
const Aeroporto& GestaoAeroporto::GetAirport(const std::string& country, const std::string& city, const std::string& name) const{
    return airports_by_country_.at(country).at(city).at(name);
}