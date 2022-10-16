#ifndef HELLOCPP_RECURSO_H
#define HELLOCPP_RECURSO_H


#include <iostream>

class Recurso {
private:
    int m_id{};

public:
    Recurso(int id) : m_id(id) {
        std::cout << "Constructor recurso " << m_id << std::endl;
    }

    ~Recurso() {
        std::cout << "Limpieza recurso " << m_id << std::endl;
    }

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }
};


#endif //HELLOCPP_RECURSO_H
