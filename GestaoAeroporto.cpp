
#include "GestaoAeroporto.h"
#include "Aeroporto.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
GestaoAeroporto::GestaoAeroporto() {
    readAirlines();
    readAirports();
    readFlights();
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
        CompanhiaAerea companhia = CompanhiaAerea(Code,Name,Callsign,Country);
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
        addAirportGrouped(novo_aeroporto);
        addAirportID(novo_aeroporto);
        flightGraph.addNode(novo_aeroporto);
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
                Target = substr;
            if (i == 2)
                Airline = substr;
            i++;
        }
        i=0;
        flightGraph.addEdge(airportIDs[Source], airportIDs[Target]);
    }
}

void GestaoAeroporto::addAirportGrouped(const Aeroporto& a) {
    airports_by_country_[a.getCountry()][a.getCity()].insert({a.getName(), a});
}

void GestaoAeroporto::addAirportID(const Aeroporto& a) {
    airportIDs.insert({a.getCode(),airportIDs.size()});
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

Voo GestaoAeroporto::getGraph() {
    return flightGraph;
}

int GestaoAeroporto::getAirportID(const string &airportTag) {
    return airportIDs[airportTag];
}