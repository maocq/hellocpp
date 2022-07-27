#ifndef HELLOCPP_PERSONAJE_H
#define HELLOCPP_PERSONAJE_H


#include <string>

class Personaje {
private:
    std::string nombre{};
public:
    Personaje(const std::string_view p_nombre = "")
        : nombre{ p_nombre } {}

    const std::string& getNombre() const { return nombre; }
};


#endif //HELLOCPP_PERSONAJE_H
