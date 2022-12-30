#include <iostream>
#include "GestaoAeroporto.h"

int main() {
    GestaoAeroporto aeroporto= GestaoAeroporto();
    vector<Aeroporto> novo_aeroporto= aeroporto.GetAirportsInCity("United Kingdom", "London");
    for(Aeroporto a : novo_aeroporto){
        cout<< a.getName() << '\n';
    }
    return 0;
}
