#ifndef HELLOCPP_CALCULADORA_H
#define HELLOCPP_CALCULADORA_H


class Calculadora {
private:
    int mvalor{};

public:
    Calculadora& sumar(int valor) { mvalor += valor; return *this; }
    Calculadora& restar(int valor) { mvalor -= valor; return *this; }

    int getValor() const { return mvalor; }
};


#endif //HELLOCPP_CALCULADORA_H
