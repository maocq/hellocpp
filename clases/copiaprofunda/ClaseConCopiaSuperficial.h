#ifndef HELLOCPP_CLASECONCOPIASUPERFICIAL_H
#define HELLOCPP_CLASECONCOPIASUPERFICIAL_H


#include <iostream>

class ClaseConCopiaSuperficial {
private:
    int size{};
    int* array{};
public:
    ClaseConCopiaSuperficial(int size) : size(size) {
        array = new int[size]{};
        std::cout << "Constructor: " << array << std::endl;
    }

    ~ClaseConCopiaSuperficial() {
        std::cout << "Destructor: " << array << std::endl;
        delete[] array;
    }

    void setValor(int indice, int valor) { array[indice] = valor; }
    int getValor(int indice) { return array[indice]; }
    int getSize() { return size; }
};


#endif //HELLOCPP_CLASECONCOPIASUPERFICIAL_H
