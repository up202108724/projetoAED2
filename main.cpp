#include <iostream>
#include "GestaoAeroporto.h"

void getAllDestinations(string originAirport, GestaoAeroporto manager){
    vector<Aeroporto> result = manager.getGraph().getAllDestinations(manager.getAirportID(originAirport));
    if (result.empty()) cout << "O aeroporto " << originAirport << " não existe ou não possui voos de destino.\n";
    else {
        cout << "O aeroporto " << originAirport << " tem os seguintes destinos: ";
        for (Aeroporto a: result) {
            cout << a.getCode() << ", ";
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
