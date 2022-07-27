#ifndef HELLOCPP_GUERRERO_H
#define HELLOCPP_GUERRERO_H


#include "Personaje.h"

class Guerrero : public Personaje {
private:
    int puntos{};
public:
    Guerrero(const std::string_view p_nombre = "", int p_puntos = 0)
        : Personaje{p_nombre}, puntos{ p_puntos } {}

    int getPuntos() const { return puntos; }
};

#endif //HELLOCPP_GUERRERO_H
