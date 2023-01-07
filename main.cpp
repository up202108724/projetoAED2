#include <iostream>
#include <limits>
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

void getAllDestinations(string originAirport, GestaoAeroporto manager){
    vector<pair<Aeroporto,string>> result = manager.getGraph().getAllDestinations(manager.getAirportID(originAirport));
    if (result.empty()) cout << "O aeroporto " << originAirport << " não existe ou não possui voos de destino.\n";
    else {
        cout << "O aeroporto " << originAirport << " tem os seguintes destinos: ";
        for (auto itr = result.begin(); itr!=result.end(); itr++){
            cout << itr->first.getCode() << " operated by " << itr->second << "\n";
            if (itr==result.end()-1) cout << ".\n";
            else cout << ", ";
        }
        cout << endl;
    }
}
void option2(const string& country, const GestaoAeroporto& manager){
    set<string> cities;
    for (Aeroporto a : manager.getAirportsInCountry(country)) {
        cities.insert(a.getCity());
    }
    for (string city : cities) {
        cout << city << endl;
    }
}
void OptionY(GestaoAeroporto manager , string Code){
    unordered_set<string> newset=manager.getGraph().getPaisesfromAeroporto(manager.getAirportID("OPO"));
    for( string a : newset){
        cout << a<< endl;
    }

}
void OptionX(GestaoAeroporto manager, string Code){
    unordered_set<string> newset=manager.getGraph().getCompanhiasAeriasfromAeroporto(manager.getAirportID("OPO"));
    for( string a : newset){
        cout << a<< endl;
    }

}
void OptionZ(GestaoAeroporto manager, string Code){

    unordered_set<string> something= manager.getGraph().reachablecountriesbynflights(manager.getAirportID("LIS"),1);
    for(string a : something){
        cout<< a << endl;
    }
}
void OptionA(GestaoAeroporto manager, string Code){

    unordered_set<string> something= manager.getGraph().reachablecitiesbynflights(manager.getAirportID(Code),1);
    for(string a : something){
        cout<< a << endl;
    }
}
void SeeArticulationPoints(GestaoAeroporto manager){
    manager.getGraph().articulationPoints();
}
void SeeConnectedComponents(GestaoAeroporto manager){
    manager.getGraph().listSCCs();
    cout<< "Fazendo assim: " <<  manager.getGraph().listSCCs().size() << " componentes conexos";
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
        cout << "1 - Ver o melhor precurso entre duas localizações" << endl;
        cout << "2 - Ver todas as cidades de um país com aeroporto" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Selecione uma opção: ";
        selection = inputInt(9);
        if (selection==0) break;
        if (selection==1) {
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
                            vector<vector<int>> result = manager.getGraph().bfs(manager.getAirportID(origin),
                                                                                manager.getAirportID(dest));
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
        if(selection == 2) {
            string country;
            country = inputValidString("Escolha um país: ", manager.getAirportsToCountryMap());
            if (country=="0") break;
            option2(manager, country);
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;
        }


    }
    return 0;

}
