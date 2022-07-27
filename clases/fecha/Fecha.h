#ifndef HELLOCPP_FECHA_H
#define HELLOCPP_FECHA_H

class Fecha {

private:
    int dia{};
    int mes{};
    int anio{};

public:
    Fecha(int dia, int mes, int anio);

    void setFecha(int dia, int mes, int anio);

    int getDia() { return dia; };  // Definición inline
    int getMes() { return mes; };
    int getAnio() { return anio; };
};

#endif //HELLOCPP_FECHA_H
