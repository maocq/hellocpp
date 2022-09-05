#ifndef HELLOCPP_MYARRAY_H
#define HELLOCPP_MYARRAY_H

#include <cassert>

template <typename T>
class MyArray {
private:
    int m_size{};
    T* m_data{};

public:
    MyArray(int size) {
        assert(size > 0);
        m_data = new T[size]{};
        m_size = size;
    }

    MyArray(const MyArray&) = delete;
    MyArray& operator=(const MyArray&) = delete;

    ~MyArray() {
        delete[] m_data;
    }

    void clean() {
        delete[] m_data;
        m_data = nullptr;
        m_size = 0;
    }

    T& operator[](int index) {
        assert(index >= 0 && index < m_size);
        return m_data[index];
    }

    int getSize() const;
};

//Para esta parte tambien podemos usar archivos inline
template <typename T>
int MyArray<T>::getSize() const {
    return m_size;
}

#endif //HELLOCPP_MYARRAY_H
