#include <iostream>
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
    for(Aeroporto a : novo_aeroporto){
        cout<< a.getName() << '\n';
    }
    getAllDestinations("PDL", manager);
    return 0;
}
