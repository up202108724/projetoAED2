//
// Created by antonio on 31/12/22.
//

#ifndef PROJETOAED2_GETALLDIRECTDESTINATIONSCOMMAND_H
#define PROJETOAED2_GETALLDIRECTDESTINATIONSCOMMAND_H


#include "CommandInterface.h"

class GetAllDirectDestinationsCommand : public CommandInterface{
private:
    string origin;
    GestaoAeroporto manager;
public:
    explicit GetAllDirectDestinationsCommand(string origin_, GestaoAeroporto manager_){
        origin=origin_;
        manager=manager_;
    }
    void execute() const{
        cout << "Working...";
    }
};


#endif //PROJETOAED2_GETALLDIRECTDESTINATIONSCOMMAND_H
