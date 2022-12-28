#include "GestaoAeroporto.h"
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
            if (i == 0) {
                Source = substr;
            }
            if (i == 1) {
                Target= substr;

            }
            if (i == 2) {
                Airline = substr;
            }
            i++;

        }
     i=0;

    }


}