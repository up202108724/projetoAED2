//
// Created by jtoma on 28/12/2022.
//

#ifndef PROJETOAED2_MASTER_AEROPORTO_H
#define PROJETOAED2_MASTER_AEROPORTO_H


class Aeroporto {
public:
    Aeroporto(int code,const string& name,const string& city,const string& country,float latitude,float longitude);
    int getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getCode() const;
    float getCode() const;

private:
    int code_;
    string name_;
    string city_;
    string country_;
    float latitude_;
    float longitude_;


};


#endif //PROJETOAED2_MASTER_AEROPORTO_H
