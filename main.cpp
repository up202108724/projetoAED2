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
void option2(GestaoAeroporto manager, string country){
    set<string> cities;
    for (Aeroporto a : manager.GetAirportsInCountry(country)) {
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

    unordered_set<string> something= manager.getGraph().reachablecitiesbynflights(manager.getAirportID("LIS"),1);
    for(string a : something){
        cout<< a << endl;
    }
}
int main() {
    GestaoAeroporto manager= GestaoAeroporto();


    vector<vector<int>> c = manager.getGraph().bfs(manager.getAirportID("LIS"),manager.getAirportID("OPO"));

    for (vector<int> m : c){
        for(int d : m){
            cout << d << "<-";
        }
        cout << endl;
    }
    for(string country : manager.getCountries()){
        cout << country << endl;
    }
    vector<Aeroporto> novo_aeroporto= manager.GetAirportsInCity("United Kingdom", "London");
    int option;
    int quit;
    while(true) {
        int selection = 0;
        cout << "Gestor de Transportes Aéreos" << endl;
        cout << "Digite 0 a qualquer momento para fechar o programa" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "1 - Ver o melhor trajeto até ao destino" << endl;
        cout << "2 - Ver todas as cidades de um país com aeroporto" << endl;
        cout << "Selecione uma opção: ";
        selection = inputInt(9);
        if (selection==0) break;
        if (selection == 1) {
            cout << "---------------------------------------------------------" << endl;
            cout << "1 - Ver trajeto apartir de determinado aeroporto" << endl;
            cout << "2 - Ver trajeto apartir de determinada cidade" << endl;
            cout << "3 - Ver trajeto apartir de determinada coordenada" << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << "Selecione uma opção: ";
            option = inputInt(3);
            if (option==0) break;
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;

        }
        if(selection == 2) {
            string country;
            set<string> countries = manager.getCountries();
            cout << "---------------------------------------------------------" << endl;
            cout << "Escolha um país: " << endl;
            while (cin>>country and countries.find(country)== countries.end()) {
                if (country=="0") break;
                cout << "Opção inválida!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Escolha um país: ";
            }
            if (country=="0") break;
            option2(manager, country);
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            quit = inputInt(1);
            if (quit==0) break;
        }


    }

    return 0;
}
