#ifndef HELLOCPP_RECURSOL_H
#define HELLOCPP_RECURSOL_H


#include <iostream>

class RecursoL {
private:
    int m_id{};

public:
    RecursoL(int id = 0) : m_id(id) {
        std::cout << "Constructor recurso " << m_id  << " " << this << std::endl;
    }

    // Constructor por copia
    RecursoL(const RecursoL& r) : m_id(r.m_id) {
        std::cout << "Constructor copia " << m_id << " from: " << &r << " to: " << this << std::endl;
    }

    // Constructor por movimiento
    RecursoL(RecursoL&& r) noexcept : m_id(r.m_id) {
        std::cout << "Constructor movimiento " << m_id << " from: " << &r << " to: " << this << std::endl;
    }

    // Asignación por copia
    RecursoL& operator=(const RecursoL& r) {
        std::cout << "Asignación por copia " << m_id << " from: " << &r << " to: " << this << std::endl;
        if (&r == this)
            return *this;

        m_id = r.m_id;
        return *this;
    }

    // Asignación por movimiento
    RecursoL& operator=(RecursoL&& r) noexcept {
        std::cout << "Asignación por movimiento " << m_id << " from: " << &r << " to: " << this << std::endl;
        if (&r == this)
            return *this;

        m_id = r.m_id;
        return *this;
    }


    ~RecursoL() {
        std::cout << "Limpieza recurso " << m_id << " " << this << std::endl;
    }

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }
};

#endif //HELLOCPP_RECURSOL_H
