#include <iostream>
#include "Commands/GetAllDirectDestinationsCommand.h"
#include "GestaoAeroporto.h"

vector<string> returnAllDestinations(int v ,GestaoAeroporto manager){
    manager.getGraph().dfs(v);

}
int main() {
    GestaoAeroporto aeroporto= GestaoAeroporto();
    vector<Aeroporto> novo_aeroporto= aeroporto.GetAirportsInCity("United Kingdom", "London");
    for(Aeroporto a : novo_aeroporto){
        cout<< a.getName() << '\n';
    }
    return 0;
}
