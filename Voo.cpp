//
// Created by andre on 29-12-2022.
//
/*
#include "Voo.h"
Voo::Voo(bool direction) {
    hasDirection=direction;
}

void Voo::addNode(const string& sigla) {
    list<Edge> templist = {};
    Node newnode = {templist, false, sigla};
    nodes.push_back(newnode);

}