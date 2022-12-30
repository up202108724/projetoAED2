//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_AEROPORTO_H
#define PROJETOAED2_AEROPORTO_H

#include <string>
using namespace std;
class Aeroporto {
public:
    Aeroporto(string codigo, string nome , string cidade, string pais, float latitude, float longitude);
    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
    bool operator<(Aeroporto a);
    bool operator==(Aeroporto a);
    double calculateDistance(Aeroporto &a) const;


private:
    string codigo_;
    string nome_;
    string cidade_;
    string pais_;
    float latitude_;
    float longitude_;
};


#endif //PROJETOAED2_AEROPORTO_H
