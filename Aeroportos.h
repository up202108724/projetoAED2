//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_AEROPORTOS_H
#define PROJETOAED2_AEROPORTOS_H

#include <string>
using namespace std;
class Aeroportos {
public:
    Aeroportos(string codigo, string nome , string cidade, string pais, float latitude, float longitude);
    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;

private:
    string codigo_;
    string nome_;
    string cidade_;
    string pais_;
    float latitude_;
    float longitude_;
};


#endif //PROJETOAED2_AEROPORTOS_H
