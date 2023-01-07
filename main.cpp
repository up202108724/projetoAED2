#include <iostream>
#include <limits>
#include <climits>
#include "GestaoAeroporto.h"

int inputInt(int limit){
    int selection;
    while (!(cin>>selection) or selection>limit or selection<0) {
        cout << "Opção inválida!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Selecione uma opção: ";
    }
    return selection;
}

template <typename T>
string inputValidString(const string& optionText, unordered_map<string,T> validOptions){
    string input;
    cout << optionText;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,input);
    while(true){
        if (input=="0") return input;
        if(cin.fail() or (!cin.fail() and !validOptions.empty() and validOptions.find(input)==validOptions.end())){
            cout << "Opção inválida!" << endl;
            cout<<endl<<optionText;
            cin.clear();
            getline(cin,input);
            continue;
        }
        if(!cin.fail()) break;
    }
    return input;
}

double inputCoords(const string& optionText, double minValue, double maxValue){
    double input;
    cout << optionText;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin >> input;
    while(true){
        if(cin.fail() or input<minValue or input>maxValue){
            cout << "Coordenada inválida!" << endl;
            cout<<endl<<optionText;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cin >> input;
            continue;
        }
        if(!cin.fail()) break;
    }
    return input;
}

void getAllDestinations(const string& originAirport, GestaoAeroporto manager){
    vector<pair<Aeroporto,string>> result = manager.getGraph().getAllDestinations(manager.getAirportID(originAirport));
    cout << endl;
    if (result.empty()) cout << "O aeroporto " << originAirport << " não existe ou não possui voos de destino.\n";
    else {
        cout << "O aeroporto " << originAirport << " tem os seguintes destinos: ";
        for (auto itr = result.begin(); itr!=result.end(); itr++){
            cout << endl << "\t" << itr->first.getCode() << ", " << itr->first.getName() << ", " << itr->first.getCountry() << " operado por " << itr->second;
        }
        cout << endl << "No total, o aeroporto tem " << result.size() << " voos." << endl;
    }
}
void getAllCountryDestinations(const string& originAirport, GestaoAeroporto manager){
    vector<pair<Aeroporto,string>> result = manager.getGraph().getAllDestinations(manager.getAirportID(originAirport));
    unordered_set<string> new_countries;
    cout << endl;
    if (result.empty()) cout << "O aeroporto " << originAirport << " não existe ou não possui voos de destino.\n";
    else {
        cout << "O aeroporto " << originAirport << " tem os seguintes destinos: " << endl;
        for (auto itr = result.begin(); itr!=result.end(); itr++){
            if(new_countries.find(itr->first.getCountry())!=new_countries.end()){
                continue;
            }
            else {
                cout << "\t" << itr->first.getCountry() << "\n";
                new_countries.insert(itr->first.getCountry());
            }
        }
        cout << endl;
    }
}
void getAllAirlines(const string& originAirport, GestaoAeroporto manager){
    vector<pair<Aeroporto,string>> airlines=manager.getGraph().getAllDestinations(manager.getAirportID(originAirport));
    unordered_set<string> new_airlines;
    cout << endl;
    if (airlines.empty()) cout << "Não há companhias a operar no aeroporto " << originAirport << ".\n";
    else {
        cout << "Companhias que operam no aeroporto: " << endl;
        for (auto itr = airlines.begin(); itr!=airlines.end(); itr++){
            if(new_airlines.find(itr->second)!=new_airlines.end()){
                continue;
            }
            else {
                cout << "\t" << itr->second << ", " << manager.getCompanhias().at(itr->second).getNome() << endl;
                new_airlines.insert(itr->second);
            }
        }
        cout << "Existem " << new_airlines.size() << " em operação no aeroporto " << originAirport << "." << endl;
    }
}
void getAirportsByCityInCountry(const string& country, const GestaoAeroporto& manager){
    set<string> cities;
    for (Aeroporto a : manager.getAirportsInCountry(country)) {
        cities.insert(a.getCity());
    }
    for (string city : cities) {
        cout << city << endl;
        for (const Aeroporto& airport : manager.getAirportsInCity(country,city)){
            cout << "\t" << airport.getCode() << ", " << airport.getName() << endl;
        }
    }
}

void nFlightsCountries(GestaoAeroporto manager, const string& Code, int arbitrary){
    unordered_set<string> something= manager.getGraph().nFlightsCountries(manager.getAirportID(Code),arbitrary);
    for(string a : something){
        cout<< a << endl;
    }
}
void nFlightsCities(GestaoAeroporto manager, const string& Code, int arbitrary){
    unordered_set<string> something= manager.getGraph().nFlightsCities(manager.getAirportID(Code),arbitrary);
    for(string a : something){
        cout<< a << endl;
    }
}
void nFlightsAirports(GestaoAeroporto manager, const string& Code, int arbitrary){
    unordered_set<string> something= manager.getGraph().nFlightsAirports(manager.getAirportID(Code),arbitrary);
    for(string a : something){
        cout<< a << endl;
    }
}

int main() {
    GestaoAeroporto manager= GestaoAeroporto();
    int option;
    int quit;
    while(true) {
        int selection;
        cout << "Gestor de Transportes Aéreos" << endl;
        cout << "Digite 0 a qualquer momento para fechar o programa" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "1 - Ver o melhor percurso entre duas localizações" << endl;
        cout << "2 - Ver todas as cidades de um país com aeroporto" << endl;
        cout << "3 - Ver todos os aeroportos de uma cidade" << endl;
        cout << "4 - Ver informações sobre um aeroporto" << endl;
        cout << "8 - Características da rede" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Selecione uma opção: ";
        selection = inputInt(9);
        if (selection==0) break;
        if (selection==1) {
            string myAirline;
            vector<string> myAirlines;
            while(myAirline!="0"){
                myAirline = inputValidString("Insira companhias aéreas que pretende voar, ou 0 para para parar de adicionar: ", manager.getCompanhias());
                if (myAirline!="0") myAirlines.push_back(myAirline);
            }
            cout << "---------------------------------------------------------" << endl;
            cout << "1 - Selecionar aeroporto como origem" << endl;
            cout << "2 - Selecionar cidade como origem" << endl;
            cout << "3 - Selecionar coordenadas como origem" << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << "Selecione uma opção: ";
            option = inputInt(3);
            vector<string> aero1;
            vector<string> aero2;
            string temp;
            if (option==0) break;
            if (option==1){
                temp = inputValidString("Insira o aeroporto de origem: ", manager.getAirportsToCodeMap());
                if (temp=="0") break;
                aero1.push_back(temp);
            }
            if (option==2){
                string country = inputValidString("Insira o país da cidade: ", manager.getAirportsToCountryMap());
                if (country=="0") break;
                string city = inputValidString("Insira a cidade de origem: ", manager.getAirportsToCountryMap().at(country));
                if (city=="0") break;
                vector<Aeroporto> tempVec = manager.getAirportsInCity(country,city);
                for (const Aeroporto& airport : tempVec){
                    aero1.push_back(airport.getCode());
                }
            }
            if (option==3){
                double lat = inputCoords("Insira a latitude da origem: ", -90, 90);
                if (lat==0) break;
                double lon = inputCoords("Insira a longitude da origem: ", -180, 180);
                if (lon==0) break;
                double maxDist = inputCoords("Insira a distância máxima: ", 0, 20004);
                if (maxDist==0) break;
                vector<Aeroporto> tempVect = manager.getAirportsbyDistanceToPoint(maxDist, lat, lon);
                for (const Aeroporto& airport : tempVect){
                    aero1.push_back(airport.getCode());
                }
            }
            if (option>=1 and option<=3){
                cout << "---------------------------------------------------------" << endl;
                cout << "1 - Selecionar aeroporto como destino" << endl;
                cout << "2 - Selecionar cidade como destino" << endl;
                cout << "3 - Selecionar coordenadas como destino" << endl;
                cout << "---------------------------------------------------------" << endl;
                cout << "Selecione uma opção: ";
                int option2=inputInt(3);
                if (option2==0) break;
                if (option2==1){
                    temp = inputValidString("Insira um aeroporto de destino: ", manager.getAirportsToCodeMap());
                    if (temp=="0") break;
                    aero2.push_back(temp);
                }
                if (option2==2){
                    string country = inputValidString("Insira o país da cidade: ", manager.getAirportsToCountryMap());
                    if (country=="0") break;
                    string city = inputValidString("Insira a cidade de destino: ", manager.getAirportsToCountryMap().at(country));
                    if (city=="0") break;
                    vector<Aeroporto> tempVec = manager.getAirportsInCity(country,city);
                    for (const Aeroporto& airport : tempVec){
                        aero2.push_back(airport.getCode());
                    }
                }
                if (option2==3){
                    double lat = inputCoords("Insira a latitude da origem: ", -90, 90);
                    if (lat==0) break;
                    double lon = inputCoords("Insira a longitude da origem: ", -180, 180);
                    if (lon==0) break;
                    double maxDist = inputCoords("Insira a distância máxima: ", 0, 20004);
                    if (maxDist==0) break;
                    vector<Aeroporto> tempVect = manager.getAirportsbyDistanceToPoint(maxDist, lat, lon);
                    for (const Aeroporto& airport : tempVect){
                        aero1.push_back(airport.getCode());
                    }
                }
                if (option2>=1 and option2<=3) {
                    for(const string& origin : aero1) {
                        for(const string& dest : aero2) {
                            vector<vector<int>> result;
                            if (myAirlines.empty()) {
                                result = manager.getGraph().bfs(manager.getAirportID(origin),
                                                                                    manager.getAirportID(dest));
                            }
                            else{
                                result = manager.getGraph().bfs_airlines(manager.getAirportID(origin),manager.getAirportID(dest),myAirlines);
                            }
                            cout << origin << " to " << dest << ": " << endl;
                            for (const vector<int> &path: result) {
                                cout << "\t";
                                for (int k = path.size() - 1; k >= 0; k--) {
                                    Aeroporto current = manager.getGraph().getAirportFromID(path.at(k));
                                    cout << current.getCode() << "," << current.getCountry() << "," << current.getCity();
                                    if (k!=0) cout << " -> ";
                                }
                                cout << endl;
                            }
                        }
                    }
                }
            }
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;

        }
        if (selection==2) {
            string country;
            country = inputValidString("Insira um país: ", manager.getAirportsToCountryMap());
            if (country=="0") break;
            getAirportsByCityInCountry(country, manager);
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;
        }
        if (selection==3){
            string country;
            string city;
            country = inputValidString("Insira um país: ", manager.getAirportsToCountryMap());
            if (country=="0") break;
            city = inputValidString("Insira uma cidade do país: ", manager.getAirportsToCountryMap().at(country));
            if (city=="0") break;
            vector<Aeroporto> airports = manager.getAirportsInCity(country, city);
            for (const Aeroporto& airport : airports){
                cout << "\t" << airport.getCode() << ", " << airport.getName();
            }
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;
        }
        if (selection==4){
            cout << "---------------------------------------------------------" << endl;
            cout << "1 - Aeroportos de destino e companhias" << endl;
            cout << "2 - Companhias aéreas em operação" << endl;
            cout << "3 - Países de destino" << endl;
            cout << "4 - Aeroportos, países ou cidades alcançáveis até N voos" << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << "Selecione uma opção: ";
            option = inputInt(4);
            string airportCode;
            if (option==0) break;
            if (option==1) {
                airportCode = inputValidString("Insira um aeroporto: ", manager.getAirportsToCodeMap());
                if (airportCode=="0") break;
                getAllDestinations(airportCode, manager);
            }
            if (option==2){
                airportCode = inputValidString("Insira um aeroporto: ", manager.getAirportsToCodeMap());
                if (airportCode=="0") break;
                getAllAirlines(airportCode, manager);
            }
            if (option==3){
                airportCode = inputValidString("Insira um aeroporto: ", manager.getAirportsToCodeMap());
                if (airportCode=="0") break;
                getAllCountryDestinations(airportCode, manager);
            }
            if (option==4){
                cout << "---------------------------------------------------------" << endl;
                cout << "1 - Aeroportos alcançáveis até n voos" << endl;
                cout << "2 - Cidades alcançáveis até n voos"  << endl;
                cout << "3 - Países alcançáveis até n voos"  << endl;
                cout << "---------------------------------------------------------" << endl;
                cout << "Selecione uma opção: ";
                int option2 = inputInt(3);
                int arbitrary;
                if (option2==0) break;
                if (option2==1){
                    airportCode = inputValidString("Insira um aeroporto: ", manager.getAirportsToCodeMap());
                    cout<< "Escolha um número de voos: ";
                    arbitrary=inputInt(INT_MAX);
                    cout << "Com " << arbitrary << " voos , é possível alcançar os seguintes aeroportos: " << endl;
                    nFlightsAirports(manager,airportCode,arbitrary);
                }
                if(option2==2){
                    airportCode = inputValidString("Insira um aeroporto: ", manager.getAirportsToCodeMap());
                    cout<< "Escolha um número de voos: ";
                    arbitrary= inputInt(INT_MAX);
                    cout << "Com " << arbitrary << " voos , é possível alcançar os seguintes países: " << endl;
                    nFlightsCountries(manager, airportCode, arbitrary);
                }
                if(option2==3){
                    airportCode = inputValidString("Insira um aeroporto: ", manager.getAirportsToCodeMap());
                    cout<< "Escolha um número de voos: ";
                    arbitrary= inputInt(INT_MAX);
                    cout << "Com " << arbitrary << " voos , é possível alcançar as seguintes cidades: " << endl;
                    nFlightsCities(manager, airportCode, arbitrary);
                }
            }
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;
        }
        if (selection == 8){
            cout << "---------------------------------------------------------" << endl;
            cout << "1 - Numero máximo de voos encadeados (diâmetro do grafo)" << endl;
            cout << "2 - Pontos de articulação da rede" << endl;
            cout << "3 - Componentes fortemente conexas da rede" << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << "Selecione uma opção: ";
            option=inputInt(3);
            if (option==0) break;
            if (option==1){
                cout << "A maior cadeia de voos possível é " << manager.getGraph().getDiameter() << ".";
            }
            if (option==2){
                cout << "Pontos de articulação: " << endl;
                manager.getGraph().articulationPoints();
            }
            if (option==3){
                cout << "Componentes fortemente conexos: " << endl;
                list<list<int>> componentes = manager.getGraph().listSCCs();
                cout<< "Existem no total " <<  componentes.size() << " componentes fortemente conexos.";
                cout << endl;
            }
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;
        }
    }
    return 0;
}
