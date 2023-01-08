//
// Created by andre on 28-12-2022.
//

#ifndef PROJETOAED2_AEROPORTO_H
#define PROJETOAED2_AEROPORTO_H

#include <string>
using namespace std;
class Aeroporto {
public:
    /**
   * Cria um aeroporto, definido pelo seu código, nome, cidade, país, latitude e longitude
   * @brief Constructor.
   * @brief Complexidade O(1)
   *@param codigo
   *@param nome
   *@param cidade
   *@param pais
   *@param latitude
   *@param longitude
   */
    Aeroporto(string codigo, string nome , string cidade, string pais, float latitude, float longitude);
    /**
     * @brief Obtém o código do aeroporto
     * @brief Complexidade O(1)
     * @return codigo
     */
    string getCode() const;
    /**
     * @brief Devolve o nome do aeroporto
     * @brief Complexidade O(1)
     * @return nome
     */
    string getName() const;
    /**
     * @brief Devolve a cidade do aeroporto
     * @brief Complexidade O(1)
     * @return cidade
     */
    string getCity() const;
    /**
     * @brief Devolve o país do aeroporto
     * @brief Complexidade O(1)
     * @return pais
     */
    string getCountry() const;
    /**
     * @brief Obtém a latitude do aeroporto
     * @brief Complexidade O(1)
     * @return latitude
     */
    float getLatitude() const;
    /**
     * @brief Obtém a longitude do aeroporto
     * @brief Complexidade O(1)
     * @return longitude
     */
    float getLongitude() const;
    /**
     * @brief Relaciona os aeroportos pela comparação entre os seus códigos
     * @brief Complexidade O(1)
     * @param a
     * @return codigo_<a.getCode()
     */
    bool operator<(Aeroporto a);
    /**
    * @brief Define a igualdade de aeroportos pela comparação entre os seus códigos
    * @brief Complexidade O(1)
    * @param a
    * @return codigo_==a.getCode()
    */
    bool operator==(Aeroporto a);
    /**
     * @brief Calcula a distância entre um aeroporto e outro ponto espacial usando as coordenadas de latitude e longitude
     * @brief Complexidade O(1)
     * @param x Latitude de um ponto
     * @param y Longitude de um ponto
     * @return A distância em quilômetros
     */

    double calculateDistance(double x, double y) const;


private:
    /**
     * @brief Código do aeroporto
     */
    string codigo_;
    /**
     * @brief Nome do aeroporto
     */
    string nome_;
    /**
     * @brief Cidade do aeroporto
     */
    string cidade_;
    /**
     * @brief País do aeroporto
     */
    string pais_;
    /**
     * @brief Latitude do aeroporto
     */
    float latitude_;
    /**
     * @brief Longitude do aeroporto
     */
    float longitude_;
};


#endif //PROJETOAED2_AEROPORTO_H
