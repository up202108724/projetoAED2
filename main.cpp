#include <iostream>
#include <limits>
#include "GestaoAeroporto.h"

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

int main() {
    GestaoAeroporto manager= GestaoAeroporto();
    vector<Aeroporto> novo_aeroporto= manager.GetAirportsInCity("United Kingdom", "London");
    int option;
    int quit;
    while(true) {
        int selection = 0;
        cout << "Gestor de Transportes Aéreos" << endl;
        cout << "Digite 0 a qualquer momento para fechar o programa" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "1 - Ver o melhor trajeto até ao destino" << endl;
        cout << "Selecione uma opção: ";
        while (!(cin>>selection) or selection>9 or selection<0) {
            cout << "Opção inválida!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Selecione uma opção: ";

        }
        if (selection==0) break;
        if (selection == 1) {
            cout << "---------------------------------------------------------" << endl;
            cout << "1 - Ver trajeto apartir de determinado aeroporto" << endl;
            cout << "2 - Ver trajeto apartir de determinada cidade" << endl;
            cout << "3 - Ver trajeto apartir de determinada coordenada" << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << "Escolha uma opção: ";
            while (!(cin>>option) or option<0 or option>3){
                if (option==0) break;
                cout << "Opção inválida!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Escolha uma opção: ";
            }
            if (option==0) break;
            cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            while (!(cin >> quit) or (quit != 0 and quit != 1)) {
                cout << "Opção inválida!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << endl << "Insira 0 para sair do programa ou 1 para voltar ao menu principal: ";
            }
            if (quit==0) break;

        }

    }


    for(Aeroporto a : novo_aeroporto){
        cout<< a.getName() << '\n';
    }
    getAllDestinations("PDL", manager);
    vector<Aeroporto> aeroportos= manager.GetAirportsbyDistanceToPoint(5, 48.725278,2.359444);

    for (Aeroporto e: aeroportos){
        cout<< e.getName() << endl;
    }
    return 0;
}
