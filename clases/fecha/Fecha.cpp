#include "Fecha.h"

Fecha::Fecha(int dia, int mes, int anio) {
    setFecha(dia, mes, anio);
}

void Fecha::setFecha(int dia, int mes, int anio) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}