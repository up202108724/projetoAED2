
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
        companhias.insert({companhia.getSigla(),companhia});
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
        countries.insert(Country);
        addAirport(novo_aeroporto);
        airportsByCode.insert({novo_aeroporto.getCode(),novo_aeroporto});
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
        companhias.at(Airline).addFlight(Source,Target);
        flightGraph.addEdge(airportIDs.at(Source), airportIDs.at(Target), Airline);
    }
}

void GestaoAeroporto::addAirport(const Aeroporto& a) {
    airportsByCountry[a.getCountry()][a.getCity()].insert({a.getName(), a});
    airportIDs.insert({a.getCode(),airportIDs.size()});
    if (airportIDs.at(a.getCode())==airportIDs.size()-1) flightGraph.addNode(a);
    else cout << "O aeroporto " << a.getCode() << " já se encontra na base de dados." << endl;
}

vector<Aeroporto> GestaoAeroporto::getAirportsInCountry(const string &country) const {
    std::vector<Aeroporto> airports;
    for (const auto& city : airportsByCountry.at(country)) {
        for (const auto& airport : city.second) {
            airports.push_back(airport.second);
        }
    }
    return airports;
}
std::vector<Aeroporto> GestaoAeroporto::getAirportsInCity(const std::string& country, const std::string& city) const {
    std::vector<Aeroporto> airports;
    for (const auto& airport : airportsByCountry.at(country).at(city)) {
        airports.push_back(airport.second);
    }
    return airports;
}

const Aeroporto& GestaoAeroporto::getAirport(const std::string& country, const std::string& city, const std::string& name) const{
    return airportsByCountry.at(country).at(city).at(name);
}

vector<Aeroporto> GestaoAeroporto::getAirportsbyDistanceToPoint(double maxdistance, double x , double y){
    vector<Aeroporto> aeroportospordistancia;
    for(auto it : airportsByCode){
        if (it.second.calculateDistance(x,y)<=maxdistance){
            aeroportospordistancia.push_back(it.second);
        }
    }
    return aeroportospordistancia;
}

Voo GestaoAeroporto::getGraph() {
    return flightGraph;
}

int GestaoAeroporto::getAirportID(const string &airportTag) {
    if (airportIDs.find(airportTag)!=airportIDs.end()) return airportIDs.at(airportTag);
    else return -1;
}

unordered_map<string,CompanhiaAerea> GestaoAeroporto::getCompanhias() {
    return companhias;
}

unordered_map<string, unordered_map<string, unordered_map<string, Aeroporto>>> GestaoAeroporto::getAirportsToCountryMap(){
    return airportsByCountry;
};

unordered_map<string,Aeroporto> GestaoAeroporto::getAirportsToCodeMap(){
    return airportsByCode;
}

unordered_set<string> GestaoAeroporto::getCountriesInOperationCompanhia(const string& companhia){
    unordered_set<string> result;
    for(auto& flight: companhias.at(companhia).getFlights()){
        result.insert(airportsByCode.at(flight.first).getCountry());
        result.insert(airportsByCode.at(flight.second).getCountry());
    }
    return result;
}

unordered_set<string> GestaoAeroporto::getAirportsInOperationCompanhia(const string& companhia){
    unordered_set<string> result;
    for(auto & flight : companhias.at(companhia).getFlights()){
        result.insert(flight.first);
        result.insert(flight.second);
    }
    return result;
}

int GestaoAeroporto::getNumFlights(const string& companhia){
    return companhias.at(companhia).getFlights().size();
}
unordered_set<string> GestaoAeroporto::getcountries() {
    return countries;
}