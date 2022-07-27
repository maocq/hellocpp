#ifndef HELLOCPP_CLASECONCOPIAPROFUNDA_H
#define HELLOCPP_CLASECONCOPIAPROFUNDA_H


#include <iostream>

class ClaseConCopiaProfunda {
private:
    int size{};
    int* array{};
public:
    ClaseConCopiaProfunda(int size) : size(size) {
        array = new int[size]{};
        std::cout << "Constructor: " << array << std::endl;
    }
    ClaseConCopiaProfunda(const ClaseConCopiaProfunda& clase)
        : size(clase.size) {
        array = new int[size]{};
        for (int i = 0; i < size; ++i)
            array[i] = clase.array[i];

        std::cout << "Constructor por copia: " << array << std::endl;
    }
    ~ClaseConCopiaProfunda() {
        std::cout << "Destructor: " << array << std::endl;
        delete[] array;
    }

    void setValor(int indice, int valor) { array[indice] = valor; }
    int getValor(int indice) { return array[indice]; }
    int getSize() { return size; }
};


#endif //HELLOCPP_CLASECONCOPIAPROFUNDA_H
