#ifndef HELLOCPP_FRACCION_H
#define HELLOCPP_FRACCION_H

#include <iostream>

class Fraccion {
private:
    int numerador{};
    int denominador{};

public:
    Fraccion(int numerador, int denominador = 1)
        : numerador(numerador), denominador(denominador) {
        std::cout << "Constructor" << std::endl;
    }

    //Contructor por copia
    Fraccion(const Fraccion& fraccion)
        : numerador(fraccion.numerador), denominador(fraccion.denominador) {
        std::cout << "Constructor por copia" << std::endl;
    }

    int getNumerador() const { return numerador; }
    int getDenominador() const { return denominador; }
};


#endif //HELLOCPP_FRACCION_H
