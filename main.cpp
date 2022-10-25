#include <iostream>
#include <vector>
#include <functional>
#include <cassert>
#include "temas/Temas.h"
#include "sumar/Sumar.h"
#include "namespaces/Uno.h"
#include "namespaces/Dos.h"
#include "constantes/Constantes.h"
#include "constantes/ConstantesInline.h"
#include "estructuras/Vehiculo.h"
#include "clases/fecha/Fecha.h"
#include "clases/fraccion/Fraccion.h"
#include "clases/simple/Simple.h"
#include "clases/calculadora/Calculadora.h"
#include "clases/copiaprofunda/ClaseConCopiaSuperficial.h"
#include "clases/copiaprofunda/ClaseConCopiaProfunda.h"
#include "clases/herencia/Guerrero.h"
#include "clases/MyArray.h"
#include "clases/recurso/Recurso.h"
#include "clases/recurso/RecursoL.h"


int main() {
    parametroFuncionPorReferenciaYRetorno();
    return 0;
}

RecursoL funcionPorReferenciaYRetorno(RecursoL& r) {
    std::cout << "function " << std::endl;
    r.setId(r.getId() + 1);
    return r;
}

void parametroFuncionPorReferenciaYRetorno() {
    RecursoL r1 { 1 };
    RecursoL r3 {funcionPorReferenciaYRetorno(r1) };

    std::cout << "end " << std::endl;
    /*
    Constructor recurso 1 0xe2ad3ff60c
    function
    Constructor copia 2 from: 0xe2ad3ff60c to: 0xe2ad3ff608
    end
    Limpieza recurso 2 0xe2ad3ff608
    Limpieza recurso 2 0xe2ad3ff60c
     */
}

RecursoL funcionPorReferencia(RecursoL& r) {
    std::cout << "function " << std::endl;
    RecursoL recurso { r.getId() + 1 };
    return recurso;
}

void parametroFuncionPorReferencia() {
    RecursoL r1 { 1 };
    RecursoL r3 {funcionPorReferencia(r1) };

    std::cout << "end " << std::endl;
    /*
    Constructor recurso 1 0x13055ffd0c
    function
    Constructor recurso 2 0x13055ffd08
    end
    Limpieza recurso 2 0x13055ffd08
    Limpieza recurso 1 0x13055ffd0c
     */
}

RecursoL funcionPorCopia(RecursoL r) {
    std::cout << "function " << std::endl;
    RecursoL recurso { r.getId() + 1 };
    return recurso;
}

void parametroFuncionPorCopia() {
    RecursoL r1 { 1 };
    RecursoL r3 {funcionPorCopia(r1) };

    std::cout << "end " << std::endl;
    /*
    Constructor recurso 1 0x6a84bff668
    Constructor copia 1 from: 0x6a84bff668 to: 0x6a84bff66c
    function
    Constructor recurso 2 0x6a84bff664
    Limpieza recurso 1 0x6a84bff66c
    end
    Limpieza recurso 2 0x6a84bff664
    Limpieza recurso 1 0x6a84bff668
     */
}

void stdMove() {
    // std::move indica que un objeto puede ser movido en lugar de copiado.

    std::vector<std::string> vector;

    std::string text1 { "Primer texto" };
    std::string text2 { "Segundo texto" };

    vector.push_back(text1);

    std::cout << "t1: " << text1 << std::endl;
    std::cout << "v1:" << vector[0] << std::endl;

    // No se pueden volver a usar los objetos que hayan sido movidos
    vector.push_back(std::move(text2));

    std::cout << "t2: " << text2 << std::endl;
    std::cout << "v2:" << vector[1] << std::endl;
}

/*
template <typename T>
class SmartPtrSoloMov {
    T* m_ptr;

public:
    SmartPtrSoloMov(T* ptr = nullptr) : m_ptr(ptr) {}
    ~SmartPtrSoloMov() { delete m_ptr; }

    // Impide constructor por copia
    SmartPtrSoloMov(const SmartPtrSoloMov& s) = delete;

    // Constructor por movimiento - Transfiere la propiedad s.m_ptr a m_ptr
    SmartPtrSoloMov(SmartPtrSoloMov&& s) noexcept : m_ptr(s.m_ptr) {
        s.m_ptr = nullptr; //Desasignar a s.m_ptr
    }

    // Impide asignación por copia
    SmartPtrSoloMov& operator=(const SmartPtrSoloMov& s) = delete;

    // Asignación por movimiento - Transfiere la propiedad s.m_ptr a m_ptr
    SmartPtrSoloMov& operator=(SmartPtrSoloMov&& s) noexcept {
        if (&s == this)
            return *this;

        delete m_ptr;
        m_ptr = s.m_ptr;
        s.m_ptr = nullptr;
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};
*/

template <typename T>
class SmartPtrCopProfYMov {
    T* m_ptr;

public:
    SmartPtrCopProfYMov(T* ptr = nullptr) : m_ptr(ptr) {}
    ~SmartPtrCopProfYMov() {
        delete m_ptr;
    }

    // Constructor por copia - Hace copia profunda de s.m_ptr a m_ptr
    SmartPtrCopProfYMov(const SmartPtrCopProfYMov& s) {
        m_ptr = new T;
        *m_ptr = *s.m_ptr;
    }

    // Constructor por movimiento - Transfiere la propiedad s.m_ptr a m_ptr
    SmartPtrCopProfYMov(SmartPtrCopProfYMov&& s) noexcept : m_ptr(s.m_ptr) {
        s.m_ptr = nullptr; //Desasignar a s.m_ptr
    }

    // Asignación por copia - Hace copia profunda de s.m_ptr a m_ptr
    SmartPtrCopProfYMov& operator=(const SmartPtrCopProfYMov& s) {
        if (&s == this)
            return *this;

        delete m_ptr;
        m_ptr = new T;
        *m_ptr = *s.m_ptr;
        return *this;
    }

    // Asignación por movimiento - Transfiere la propiedad s.m_ptr a m_ptr
    SmartPtrCopProfYMov& operator=(SmartPtrCopProfYMov&& s) noexcept {
        // Detección de autoasignación
        if (&s == this)
            return *this;

        delete m_ptr;
        m_ptr = s.m_ptr;
        s.m_ptr = nullptr;
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

SmartPtrCopProfYMov<Recurso> generarRecurso() {
    SmartPtrCopProfYMov<Recurso> recurso { new Recurso(9) };
    return recurso;
    // Algunos compiladores en este punto pueden llamar el Constructor por movimiento.
}

void constYAsigCopiaProfundaYMovimiento() {
    SmartPtrCopProfYMov<Recurso> r;
    r = generarRecurso(); // Despues de ejecutar generarRecurso() llama a la sobreescritura de asignación por movimiento (r-value)

    /*
    SmartPtrCopProfYMov<Recurso> r2 = generarRecurso(); // De esta forma el 'return recurso' se asigna directamente a r2
    */
    std::cout << "..." << std::endl;
}


template <typename T>
class SmartPtrCopiaProf {
    T* m_ptr;

public:
    SmartPtrCopiaProf(T* ptr = nullptr) : m_ptr(ptr) {}
    ~SmartPtrCopiaProf() {
        delete m_ptr;
    }

    // Constructor por copia - Hace copia profunda de s.m_ptr a m_ptr
    SmartPtrCopiaProf(const SmartPtrCopiaProf& s) {
        m_ptr = new T;
        *m_ptr = *s.m_ptr;
    }

    // Asignación por copia - Hace copia profunda de s.m_ptr a m_ptr
    SmartPtrCopiaProf& operator=(const SmartPtrCopiaProf& s) {
        if (&s == this)
            return *this;

        delete m_ptr;
        m_ptr = new T;
        *m_ptr = *s.m_ptr;
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

SmartPtrCopiaProf<Recurso> crearRecurso() {
    SmartPtrCopiaProf<Recurso> recurso { new Recurso(9) };
    return recurso;
}

void constYAsigCopiaProfunda() {
    /*
    {
        SmartPtrCopiaProf<Recurso> r = crearRecurso(); // Solo llamaria una vez el constructor y el destructor de Recurso
    }
    */

    // Ver el siguiente código en el depurador. Llama dos veces el contructor y dos veces el destructor de Recurso
    SmartPtrCopiaProf<Recurso> r;    // Llama el constructor de SmartPtrCopiaProf con valor por defecto (nullptr)
    r = crearRecurso();
    std::cout << "..." << std::endl;
    std::cout << r->getId() << std::endl;
}


void compare(const int& lref) {
    std::cout << "Referencia l-value " << lref << std::endl;
}

void compare(int&& rref) {
    std::cout << "Referencia r-value " << rref << std::endl;
}

/*
 * Las referencias l-value = referencias clasicas hasta C++11
 */
void referenciaLValueYRValue() {
    int x { 5 };
    int& lref { x };     // Referencia l-value inicializada con el valor l-value x
    int&& rref { 5 };    // Referencia r-value inicializada con el r-value 5 (valor literal)
                         // Las referencias r-values extienden la vida util del objeto con que se inicializan

    auto&& rref2 { Simple(1) };
    std::cout << rref2.getId() << std::endl;

    int&& rref3 { 5 };
    rref3 = 10;
    std::cout << rref3 << std::endl; // 10

    int y { 5 };
    compare(y); // l-value
    compare(6); // r-value

    int &&rref4 { 7 };
    compare(rref4); // Llama la función l-value, ya que despues de creada rref4 pasa a ser l-value
                        // Los objetos que tienen nombre son siempre l-value y los anonimos son r-value

    //No usar r-value como valores de retorno (o cualquier referencia), terminaran devolviendo una referencia colgante.
}

/**
 RAII: El recurso esta vinculado a la vida útil del objeto que adquirió ese recurso.
 Semántica de movimiento: Transfiere la propiedad de un objeto a otro
 */

/*
    Equivalente a std::auto_ptr de C++ 98 y eliminado en C++17 por problemas en diferencias entre copiar y mover,
    ejemplo al pasar auto_ptr por valor a una función, al salir de la función se elimina con su valor interno

    Diferencia entre semantica de copia y semantica de movimiento a partir de C++11 (moderno). (Ver arriba)
*/
template <typename T>
class SmartPtrSemMov {
    T* m_ptr;

public:
    SmartPtrSemMov(T* ptr = nullptr) : m_ptr(ptr) {}
    ~SmartPtrSemMov() {
        delete m_ptr;
    }

    // Constructor por copia con semántica de movimiento
    SmartPtrSemMov(SmartPtrSemMov& s) {
        m_ptr = s.m_ptr;
        s.m_ptr = nullptr;
    }

    // Operador de asignación con semántica de movimiento
    SmartPtrSemMov& operator=(SmartPtrSemMov& s) {
        if (&s == this)
            return *this;

        delete m_ptr;
        m_ptr = s.m_ptr;
        s.m_ptr = nullptr;
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

void semanticaMovimiento() {
    SmartPtrSemMov<Recurso> recurso ( new Recurso(9) );
    std::cout << recurso->getId() << std::endl; // 9

    //SmartPtrSemMov<Recurso> copia ( recurso ); // Llama constructor por copia
    SmartPtrSemMov<Recurso> copia;                   // Inicia con nullptr por valor por default en nuestro constructor
    copia = recurso;                             // Llama sobre-escritura del operador asignación

    //recurso->getId() = nullptr
    std::cout << copia->getId() << std::endl;   // 9
}

template <typename T>
class MySmartPtr {
    T* m_ptr;

public:
    MySmartPtr(T* ptr = nullptr) : m_ptr(ptr) {}
    ~MySmartPtr() {
        delete m_ptr;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};

void punterosInteligentes() {
    /*
    Recurso* recurso = new Recurso(1);
    delete recurso;
    */

    MySmartPtr<Recurso> recurso ( new Recurso(9) );
    std::cout << recurso->getId() << std::endl;

    /*
    // Error si se usa constructor por copia
    MySmartPtr<Recurso> copia ( recurso );
    // Ver semantica del movimiento
    */
}

void exceptionesReThrowing() {
    try {
        throw -1;
    } catch (int exception) {
        std::cerr << "Error " << std::endl;
        throw 'z';

        //throw exception; Relanzar la misma excepción genera una inicialización por copia
        //Relanzar una excepción capturada desde su tipo padre corta el objeto a solo su tipo padre
        //Lo anterior se soluciona de la siguiente forma:

        //throw;
    }
}

class MyException : public std::exception {
private:
    std::string m_error{};
public:
    MyException(const std::string_view error) : m_error(error) {}

    const char* what() const noexcept override {
        return m_error.c_str();
    }
    //const std::string& getError() const { return m_error; }
};

void myException() {
    try {
        throw MyException("Bummm!");
    } catch (const MyException& exception) {
        std::cerr << "Error " << exception.what() << std::endl;
    } catch (const std::exception& exception) {
        std::cerr << "Error general" << exception.what() << std::endl;
    }
}

void clasesException() {
    try {
        // https://en.cppreference.com/w/cpp/error/exception
        throw std::runtime_error("Bummm!");
    } catch (const std::exception& exception) {
        std::cerr << "Error " << exception.what() << std::endl;
    }
}

void excepcionesCatchAll() {
    try {
        throw -1;
    } catch (...) {
        std::cerr << "Error" << std::endl;
    }
}

int myFunct(int number) {
    if (number < 0)
        throw "Numero menor";
    return number + 1;
}

void excepcionesEnFunciones() {
    try {
        myFunct(-1);
    } catch (const char* exception) {
        std::cerr << "Error " << exception << std::endl;
    }
}

void erroresExcepciones() {
    int value = 9;
    try {
        if (value == 9)
            throw std::string("Bumm!!!");
            //throw -1;

        std::cout << "Ok" << std::endl;
    } catch (int n) {
        std::cerr << "Error " << n << std::endl; // cerr no se almacena en el buffer, ejecución inmediata
    } catch (const std::string& error) {
        std::cerr << "Error " << error << std::endl;
    }

    std::cout << "end." << std::endl;
    // 'throw' salta al bloque envolvente 'try' mas cercano. try transmitira la excepción a los catch (busca un catch compatible)
}

/*
Operadores Bitwise (Operadores bit a bit)
    & AND bit a bit
    | OR bit a bit
    ^ XOR bit a bit
    ~ Complemento bit a bit
    << Desplazamiento a la izquierda bit a bit
    >> Desplazamiento a la izquierda OR bit a bit
 */

template <typename T>
class Wrapper8 {
private:
    T m_array[8]{};
public:
    void set(int index, const T& value) {
        m_array[index] = value;
    }

    const T& get(int index) const {
        return m_array[index];
    }
};

// Especialización clase Wrapper8
template<>
class Wrapper8<bool> {
private:
    unsigned char m_data{};
public:
    void set(int index, bool value) {
        auto mask{ 1 << index };
        if (value)
            m_data |= mask;
        else
            m_data &= ~mask;
    }

    //Podemos usar otros nombres de funciones sin problema ya que se trata de dos clases diferentes
    bool get(int index) {
        auto mask{ 1 << index };
        return (m_data & mask);
    }
};

void especializacionPlantillasDeClases() {
    Wrapper8<int> intWrapper{};
    intWrapper.set(6, 9);
    std::cout << intWrapper.get(6) << std::endl;

    Wrapper8<bool > boolWrapper{};
    boolWrapper.set(6, true);
    std::cout << std::boolalpha;
    std::cout << boolWrapper.get(6) << "-" << boolWrapper.get(7) << std::endl;
}

template <typename T>
class WrapperT {
private:
    T m_value{};
public:
    WrapperT(T value) : m_value(value) {}
    ~WrapperT() {}; //Necesario para definir destructor especializado

    void print() {
        std::cout << m_value << std::endl;
    }
};

// Especialización de constructor para realizar copia profunda
template<>
WrapperT<char*>::WrapperT(char* value) {
    if (!value) return;

    int size{ 0 };
    while (value[size] != '\0')
        ++size;
    ++size;  // +1 - This array includes the same sequence of characters that make up the value of the string object plus an additional terminating null-character ('\0') at the end.

    m_value = new char[size];

    for (int i = 0; i < size; ++i)
        m_value[i] = value[i];
}

// Destructor especializado
template<>
WrapperT<char*>::~WrapperT() {
    delete[] m_value;
}

// Especialización de función para double
template<>
void WrapperT<double>::print() {
    std::cout << std::scientific << m_value << std::endl;
}

void especializacionConstructorYDestructor() {
    std::string  name;
    std::cout << "Ingrese nombre:";
    std::cin >> name;

    WrapperT<char*> wrapper(name.data());
    wrapper.print();

    name.clear();
    wrapper.print();
}

void especializacionPlantillas() {
    WrapperT<int> intValue{ 9 };
    WrapperT<double> doubleValue{ 9.5 };

    intValue.print();
    doubleValue.print();
}

template <typename T, int size>
class ArrayEstatico {
private:
    T m_array[size]{};
public:
    T* getArray();

    T& operator[](int index) {
        return m_array[index];
    }
};

template<typename T, int size>
T *ArrayEstatico<T, size>::getArray() {
    return m_array;
}

void templatesNoTipo() {
    constexpr auto size = 3;
    ArrayEstatico<double, size> doubleArray;
    std::cout << doubleArray.getArray() << std::endl;

    for (int i{ 0 }; i < size; ++i)
        doubleArray[i] = 0.1 * i;

    for (int i{ 0 }; i < size; ++i)
        std::cout << doubleArray[i] << std::endl;
}

void templateClases() {
    MyArray<int> intArray{9};
    MyArray<double> intDouble{9};
    for (int i{ 0 }; i < intArray.getSize(); ++i)
        intArray[i] = i * 2;

    for (int i{ intArray.getSize() - 1 }; i >= 0; --i)
        std::cout << intArray[i] << std::endl;
}

class PadreFVPura {
public:
    virtual int getValorM() const = 0;
};

//Implementación predeterminada
int PadreFVPura::getValorM() const { return 1; }

class DerivadaFVPura: public PadreFVPura {
public:
    int getValorM() const override {
        //return PadreFVPura::getValorM(); //Si queremos usar la implementación predeterminada
        return 9;
    }
};

void funcionesVirtualesPuras() {
    //PadreFVPura padre; Error compilación, es una clase abstracta
    DerivadaFVPura derivada;
    PadreFVPura& padre { derivada };

    std::cout << padre.getValorM() << std::endl; // 9
}

class Padre {
public:
    virtual std::string_view getNombre() const { return "Padre"; }
};

class Derivada: public Padre {
public:
    std::string_view getNombre() const override { return "Derivada"; }
};

void funcionesVirtuales() {
    //Resuelve a la versión mas derivada que exista de la función
    Derivada derivada;
    Padre& padre { derivada };

    std::cout << padre.getNombre() << std::endl;
}

void referenceWrapper() {
    Padre padre {};
    Derivada derivada {};

    //std::vector<Padre&> vecr{}; // (Error compilación) Las referencias no pueden reasignarse, solo inicializarse
    std::vector<std::reference_wrapper<Padre>> vector{};
    vector.push_back(padre);
    vector.push_back(derivada);

    for (const auto& i : vector)
        std::cout << i.get().getNombre() << std::endl;
}

void punteroClasePadre() {
    Guerrero guerrero{ "Name", 10 };
    Personaje& personajeRef { guerrero };
    Personaje* personaje { &guerrero };

    std::cout << guerrero.getNombre() << std::endl;
}

void herencia() {
    Guerrero guerrero{ "Name", 10 };
    std::cout << guerrero.getNombre() << std::endl;

    /*
     Internamente la herencia se implementa mediante composición.
     guerrero
        Personaje
            nombre
        puntos
     */
}

ClaseConCopiaProfunda funcionCopiaProfunda(ClaseConCopiaProfunda clase) {
    return clase;
}

void claseConCopiaProfunda() {
    ClaseConCopiaProfunda clase{4};
    clase.setValor(0, 1);
    clase.setValor(1, 2);

    auto copia = funcionCopiaProfunda(clase);
    copia.setValor(1, 5);

    std::cout << clase.getValor(1) << std::endl; // 5
};

ClaseConCopiaSuperficial funcionCopiaSuperficial(ClaseConCopiaSuperficial clase) {
    return clase;
}

void claseConCopiaSuperficial() {
    ClaseConCopiaSuperficial clase{4};
    clase.setValor(0, 1);
    clase.setValor(1, 2);

    //Internamente solo se copia la dirección del array
    auto copia {funcionCopiaSuperficial(clase) };
    copia.setValor(1, 5);

    std::cout << clase.getValor(1) << std::endl; // 5
}

void claseConCopiaSuperficialError() {
    ClaseConCopiaSuperficial clase{4};
    clase.setValor(0, 1);
    {
        auto copia{ clase };
    } //Ya que internamente solo se copia la dirección del array,
      // al llamar al destructor se elimina la memoria para ambos dejando un puntero colgante
    std::cout << clase.getValor(0) << std::endl;
}

void calculadoraBuilder() {
    Calculadora calculadora{};
    auto resultado = calculadora.sumar(3).restar(1).getValor();

    std::cout << resultado << std::endl;
}

void punteroOcultoThis() {
    Simple simple{1};
    simple.setId(3);
    /*
     El compilador convierte 'simple.setId(3)' en:

     setId(&simple, 3);

     void setId(Simple* const this, int nid) {
        this->id = nid;
     }
     */

    std::cout << "-> " << simple.getId() << std::endl;
}

// Se llama 2 veces el constructor por copia, al pasar y al retornar el valor
Fraccion pasoYRetorno(Fraccion fraccion) {
    std::cout << "-> " << fraccion.getNumerador() << std::endl;
    return fraccion;
}

void pasoYRetornoPorValor() {
    Fraccion fraccion{3, 2};
    Fraccion resultado = pasoYRetorno(fraccion);
}

void constructorPorCopia() {
    Fraccion fraccion1 {5};                     //Inicialización uniforme
    Fraccion fraccion2 { fraccion1 };                     //Llama el constructor por copia
    std::cout << fraccion1.getNumerador() << std::endl;
}

void claseFecha() {
    Fecha fecha(10, 9, 2008);
    std::cout << " - " << fecha.getAnio() << std::endl;
}

class ClaseConDestructor {
private:
    int* array{};
    int size{};

public:
    ClaseConDestructor(int size) : size(size) {
        assert(size > 0);
        array = new int[static_cast<std::size_t>(size)]{};
    }

    ~ClaseConDestructor() {
        delete[] array;
    }

    void serValor(int indice, int valor) { array[indice] = valor; }
    int getValor(int indice) { return array[indice]; }
    int getSize() { return size; }
};


void destructoresClases() {
    ClaseConDestructor clase(5);
    clase.serValor(3, 9);

    std::cout << "-> " << clase.getValor(3) << std::endl;
}

class C {
    int valor{};
public:
    C(int valor = -1) : valor(valor) {}

    void imprimir() {
        std::cout << "-> " << valor << std::endl;
    }

    void reset() {
        *this = C(0);
    }
};

void clasesMiembrosNoStatic() {
    C c1{};
    c1.imprimir();

    C c2{ 9 };
    c2.imprimir();
    c2.reset();
    c2.imprimir();
}


class B {
    const int bValue{};
public:
    B(const int y = 0) : bValue{ y } { std::cout << "B " << y << std::endl; }
};

class A {
    const B bClass{};
public:
    A(const int x) : bClass { x - 1 } { std::cout << "A " << x << std::endl; }
};



class ClaseA {
private:
    const int numero{};
    const int otro{};

public:
    ClaseA(int numero, int otro = 0) : numero(numero), otro(otro) {}

    void imprimir() {
        std::cout << numero << " - " << otro << std::endl;
    }
};

void inicializacionClases() {
    ClaseA claseA{9};
    claseA.imprimir();

    A a{ 5 };
    std::cout << "end"<< std::endl;
}

class VehiculoC {

public:
    int id {};
    std::string nombre {};
    int velocidad { 100 };

    void imprimir() {
        std::cout << nombre << ": " << id << std::endl;
    }
};

void clases() {
    VehiculoC vehiculo { 1, "xxx", 120 };
    vehiculo.imprimir();
}

void lambdasClausulaCaptura() {
    int buscar { 4 };
    auto x { [buscar](int n) { return n == buscar; } }; //Crea una variable clonada con el mismo valor
    auto y { [buscar](int n) mutable { return n == ++buscar; } }; //No modifica la variable original
    auto z { [&buscar](int n) { return n == ++buscar; } }; //Modifica la variable original

    //Capturas predeterminadas
    auto u { [=](int n) { return n == buscar; } }; //Captura por copia (=)
    auto w { [&](int n) { return n == buscar; } }; //Captura por referencia (&)
    // [&]  [=, &x]   [&, =x]

    std::vector<int> v {7, 2, 1, 4, 5};
    auto res1 { std::find_if(v.begin(), v.end(), [&buscar](const auto& n) { return n == buscar; }) };
    int r1 { res1 == v.end() ? 0 : *res1 };

    auto res2 { std::find_if(v.begin(), v.end(), [&](auto n) { return n == buscar; }) };
    int r2 { res1 == v.end() ? 0 : *res1 };

    std::cout << "end!" << std::endl;
}

void lambdas() {
    auto x = []() {};
    auto y { [](int n) -> bool { return n == 4; } };  //El compilador genera un tipo unico para ella
    std::function z { [](int n) { return n == 4; } };  //Se puede almacenar en std::function

    std::vector<int> v {7, 2, 1, 4, 5};
    auto res1 { std::find_if(v.begin(), v.end(), [](int n) { return n == 4; }) };
    int r1 { res1 == v.end() ? 0 : *res1 };

    std::cout << "end!" << std::endl;
}

bool primeroMayor(int x, int y) {
    return x > y;
}

void stdFunction() {
    std::function<bool(int, int)> ptrFunction1 { primeroMayor };
    bool resultado1 { ptrFunction1(2, 1) };

    auto ptrFunction2 { primeroMayor };
    bool resultado2 { ptrFunction1(2, 1) };

    std::cout << resultado1 << " " << resultado2 << std::endl;
}

bool funcionComoArgumento(bool (*fn)(int, int)) {
    return fn(2, 3);
}

void funcionesComoArgumentos() {
    bool resultado { funcionComoArgumento(primeroMayor) };
    std::cout << resultado << std::endl;
}

int funcionEjemplo(int x) {
    return x + 1;
}

int *funcionEjemplo2();  //Declaración anticipada de una función

void punterosDeFunciones() {
    int res1 { (*funcionEjemplo)(2) }; //Ejecutar función por medio de su dirección en memoria

    int (*ptrFuncion)(int) { &funcionEjemplo };  //Puntero a función
    int res2 { ptrFuncion(3) };

    int (*ptrFuncionNula)(int) { nullptr };

    std::cout << "end!" << std::endl;
}

void busquedas() {
    std::vector<int> v {7, 2, 1, 4, 5};

    auto existe { std::find(v.begin(), v.end(), 4) };
    std::string r1 { existe == v.end() ? "error" : "ok" };

    auto noexiste { std::find(v.begin(), v.end(), 10) };
    std::string r2 { noexiste == v.end() ? "error" : "ok" };

    std::cout << "end!" << std::endl;
}

void vectorMap() {
    std::vector<int> v {1, 2, 3, 4, 5};
    std::vector<int> n;

    transform(
            v.begin(),
            v.end(),
            back_inserter(n),
            [] (int i) { return i * 2; }
    );
}

void vectorFilter() {
    std::vector<int> v {1, 2, 3, 4, 5};
    std::vector<int> n;
    copy_if(
            v.begin(),
            v.end(),
            back_inserter(n),
            [] (int i) { return i % 2 == 0; }
    );
    std::cout << n.size() << std::endl;
}

//Vector se autolimpia cuando sale de alcance
void stdVector() {
    std::vector<int> miVector {3, 2, 4};
    miVector[2];   //No comprueba limites
    miVector.at(2); //Comprueba limites

    miVector.size();

    miVector.resize(5);

    miVector.begin();
    miVector.end();

    vectorMap();
    vectorFilter();
}

//Arrays fijos
void stdArray() {
    std::array miArray {3, 2, 4};
    std::cout << miArray.at(1) << std::endl;

    std::sort(miArray.begin(), miArray.end());
    for (auto n : miArray)
        std::cout << n << std::endl;
}

void punterosVoid() {
    int valor { 5 };
    void* voidPtr { &valor };

    int* intPrt { static_cast<int*>(voidPtr) };
    std::cout << *intPrt << std::endl;
}

void loopForEach() {
    const std::string textos[] {"aaa", "bbb", "ccc", "ddd"};
    for (const auto& texto : textos) {
        std::cout << texto << std::endl;
    }
}

void asignacionDinamicaArrays() {
    int size {};
    std::cout << "Numero...";
    std::cin >> size;

    int* array { new int[size]{} };
    delete[] array;
    std::cout << "end" << std::endl;
}

void asignacionDinamicaMemoria() {
    int* x { new int };
    std::cout << x << std::endl; //0x562ff18e7eb0
    *x = 9;
    std::cout << *x << std::endl;

    delete x;
    std::cout << x << std::endl; //0x562ff18e7eb0
    x = nullptr;
    std::cout << x << std::endl; //0
}

void arimeticaDePunteros() {
    int array[]{ 7, 8, 9};
    std::cout << &array[0] << std::endl; //0x7ffc092a5dbc
    std::cout << &array[1] << std::endl; //0x7ffc092a5dc0
    std::cout << &array[2] << std::endl; //0x7ffc092a5dc4

    std::cout << "---" << std::endl;
    std::cout << array << std::endl;     //0x7ffc092a5dbc
    std::cout << array + 1 << std::endl; //0x7ffc092a5dc0
    std::cout << array + 2 << std::endl; //0x7ffc092a5dc4
    std::cout << "---" << std::endl;
    std::cout << std::begin(array) << std::endl; //0x7ffc092a5dbc
    std::cout << std::end(array) << std::endl;   //0x7ffc092a5dc8

    std::cout << array[2] << std::endl;     //9
    std::cout << *(array + 2) << std::endl; //9

    int length { static_cast<int>(std::size(array)) };
    for (int* ptr{ array }; ptr != (array + length) ; ++ptr) {
        std::cout << *ptr << std::endl;
    }
}

struct Usuario {
    int id {};
    std::string nombre {};
};

void seleccionDeMiembros() {
    Usuario usuario {1, "mmm"};

    Usuario* ptr { &usuario };

    std::cout << ptr->nombre << std::endl;
    std::cout << (*ptr).nombre << std::endl;
}

void imprimirUsuario(Usuario& usuario) {
    std::cout << usuario.id << " " << usuario.nombre << std::endl;
}

void estructuras() {
    Usuario usuarioCero;
    Usuario usuario {1, "mmm"};

    Vehiculo vehiculo {2, "yyy"};

    std::cout << usuario.nombre << std::endl;
    imprimirUsuario(usuario);
}

const std::string& menorPorReferencia(const std::string& x, const std::string& y) {
    return x < y ? x : y;
}

void retornoPorReferencia() {
    const std::string x { "c" };
    const std::string y { "b" };
    auto& z = menorPorReferencia(x, y);
    std::cout << z << std::endl;
}

void anularInvalido(int* ptr) {
    ptr = nullptr; // Modifica a que apunta el puntero
}

void anularValido(int*& ptr) { //Referencia a un puntero
    ptr = nullptr;
}

void pasoPunteroPorRef() {
    int x { 9 };
    int* ptr { &x };
    std::cout << (ptr ? *ptr : 0)  << std::endl;
    //anularInvalido(ptr);
    anularValido(ptr);
    std::cout << (ptr ? *ptr : 0)  << std::endl;
}

void imprimirRefYPuntero(const std::string& x, const std::string* y) {
    std::cout << "Direcc.referencia " << &x << std::endl; //0x7ffe7b2a9a40
    std::cout << "Dirección puntero " << y << std::endl;  //0x7ffe7b2a9a40
    std::cout << "Dir mem del punt. " << &y << std::endl; //0x7ffe7b2a9a10
}

void pasoPorRefYDirecc() {
    std::string texto { "mmm" };
    std::cout << "Dirección memoria " << &texto << std::endl; //0x7ffe7b2a9a40

    imprimirRefYPuntero(texto, &texto);
}

//Paso por copia del puntero
void imprimirPorDireccion(const std::string* ptr) {
    // Validar que el puntero no sea nulo
    std::cout << *ptr << std::endl;
}

void pasoPorDireccion() {
    std::string texto { "Hello" };
    imprimirPorDireccion(&texto);
}

void punterosColgantes() {
    int* ptr{ };
    {
        int x { 5 };
        ptr = &x;
    }
    std::cout << *ptr << std::endl;
}

void punterosNulos() {
    int* ptr {};
    std::cout << ptr << std::endl;

    int x { 3 };
    ptr = &x;
    std::cout << *ptr << std::endl;

    int* ptrNull { nullptr };
    //std::cout << *ptrNull << std::endl;   ->   (Comportamiento indefinido)

    if (ptrNull)
        std::cout << *ptrNull << std::endl;

    int res { ptrNull ? *ptrNull : 0 };

    std::cout << "end!!!" << std::endl;
}

struct S {
    double x, y, z;
};

#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))
void evaluarCostoPasoPorReferencia() {
    std::cout << std::boolalpha;
    std::cout << isSmall(int) << " " << sizeof(int) << std::endl;
    std::cout << isSmall(double) << " " << sizeof(double) << std::endl;
    std::cout << isSmall(S) << " " << sizeof(S) << std::endl;
    std::cout << isSmall(std::string) << " " << sizeof(std::string) << std::endl;
}

void imprimirTextoPorRef(const std::string& t) {
    std::cout << t << std::endl;
}

void pasoPorValor(int x) {
    ++x;
}

void pasoPorReferencia(int& x) {
    ++x;
}

void pasoPorReferenciaYValor() {
    int x { 5 };
    pasoPorValor(x);
    std::cout << "x: " << x << std::endl;

    pasoPorReferencia(x);
    std::cout << "x: " << x << std::endl;

    std::string name = "mmm";
    imprimirTextoPorRef(name);
}

void punteros() {
    int x { 1 };

    //Operador de dirección & -> Retorna direccíon en memoria (El 1er byte que ocupa)
    int* puntero { &x };
    std::cout << "Dirección: " << puntero << std::endl;

    //Operador de indirección *
    int valor { *puntero };
    std::cout << "Valor: " << valor << std::endl;

    int w = *(&x);

    //Referencias int&   (alias para un objeto)
    int& ref = x;
    x = 3;
    std::cout << "Valor: " << ref << std::endl; //3

    // Favorecer las referencia sobre los punteros
}

void funcionArray(int* array) {
    std::cout << "Dirección: " << array << std::endl;
    std::cout << "1er valor: " << *array << std::endl;
}

void decaimientoAPuntero() {
    int numeros[] {9, 8, 7};

    funcionArray(numeros);

    std::cout << "Dirección: " << numeros << std::endl;
    std::cout << "1er valor: " << *numeros << std::endl;
}

void arrayMultidimencional() {
    int array[][2] {
            {1,2},
            {3,4},
    };
}

void swapStd() {
    auto x { 5 };
    auto y { 2 };
    std::swap(x, y);
    std::cout << x << " " << y << std::endl;
}

enum Estado {
    Activo,     // 0
    Suspendido, // 1
    Inactivo,   // 2
    maximo      // 3
};

void enums() {
    std::cout << Estado::Inactivo << std::endl;
}

void arrays() {
    int numeros[10] {9, 8, 7};
    int numeros3[] {9, 8, 7};

    std::cout << "Size: " << std::size(numeros3) << std::endl;
    for (int i { 0 }; i < std::size(numeros3); ++i) {
        std::cout << numeros3[i] << std::endl;
    }
}

template <typename T>
T mayor(T x, T y) {
    return (x > y) ? x : y;
}

template <typename T, typename U>
T mayorv2(T x, U y) {
    return (x > y) ? x : y;
}

template <typename T, typename U>
auto mayorv3(T x, U y) {
    return (x > y) ? x : y;
}

auto mayorv4(auto x, auto y) {
    return (x > y) ? x : y;
}

void templatesFunciones() {
    // Hace uso de sobrecarga de funciones en tiempo de compilación
    auto x { mayor(2.1, 2.05) };
    auto y { mayor<int>(3.5, 3) };
    auto z { mayor<>(5, 3) };

    auto w { mayorv4(5.0, 3) };

    std::cout << x << y << std::endl;
}

int sumaPredeterminado(int x, int y = 0) {
    return x + y;
}

void argumentoPredeterminado() {
    std::cout << sumaPredeterminado(5) << std::endl;
}

int sumaSobrecargada(int x, int y) {
    return x + y;
}

double sumaSobrecargada(double x, double y) {
    return x + y;
}

void sobrecargaFunciones() {
    auto r { sumaSobrecargada(1.0, 2.0) };
}

// auto autoSuma(int x, auto y) -> int {
auto autoSuma(int x, int y) {
    return x + y;
}

void infereciaTipos() {
    // Eliminara const de los tipos inferidos
    const int x { 5 };
    auto y { x };
    const auto z { x };

    // Eliminara las referencias de los tipos inferidos
    int a { 5 };
    int& ra { a };
    auto b { ra };   // int
    auto& c { ra };   // int&

    using namespace std::literals;
    auto nombre { "Mauricio"s };

    auto w { autoSuma(1, 2) };

    std::cout << "end!" << std::endl;
}


void conversionesExplicitas() {
    int x { 10 };
    int y { 4 };

    double a { (double) x / y };
    double b { double (x) / y };

    //static_cast: Verificación de tipos en tiempo de compilación
    double c { static_cast<double>(x) / y };

    std::cout << "end!" << std::endl;
}

void usoGoto() {
    int numero{};
    deNuevo:
    std::cout << numero << std::endl;
    if (numero < 5) {
        ++numero;
        goto deNuevo;
    }
}

void excepciones() {
    try {
        throw 9;
    } catch (int n) {
        std::cout << "Error " << n << std::endl;
    }
}

void variablesInline() {
    // Variables constantes compartidas
    std::cout << constantes::pi << std::endl;
    std::cout << constantesinline::pi << std::endl;
}

// Variable global (Alcance de archivo) Pueden ser inicializadas después si no son const
constexpr int g_global { 9 };
extern constexpr int g_global_externa { 11 };

void vinculacion() {
    /*
      Variables globales no const tienen vinculación externa pero podemos darles vinculación interna con la palabra clave static.
      Variables globales constantes tiene vinculación interna, podemos darles vinculación externa con la palabra clave extern.
    */
    std::cout << g_global_externa << std::endl;
}

void variablesGlobales() {
    std::cout << g_global << std::endl;
}

void namespaces() {
    // :: Operador de resolución de alcance
    std::cout << uno::algo(4, 2) << std::endl;
    std::cout << dos::algo(4, 2) << std::endl;
}

void constantesTiempoCompilacion() {
    constexpr int suma { 1 + 2 };
    std::cout << suma << std::endl;
}

void variablesConstantes(const int x) {
    //x = 1; Error
    const int y { 9 };
}

void cadenas() {
    std::string nombre { "Mauricio" };
    std::cout << nombre << " " << nombre.length() << std::endl;
}

void conversionTipos() {
    double x { 5.5 };
    int y = static_cast<int>(x);
    std::cout << "Numero: " << y << std::endl;

    int a = (int) x;
    std::cout << "Numero: " << a << std::endl;
}


void tiposFundamentales() {
    std::cout << "bool: \t\t" << sizeof(bool) << "bytes\n";
    std::cout << "char: \t\t" << sizeof(char) << "bytes\n";
    std::cout << "wchar_t: \t" << sizeof(wchar_t) << "bytes\n";
    std::cout << "char16_t: \t" << sizeof(char16_t) << "bytes\n";
    std::cout << "char32_t: \t" << sizeof(char32_t) << "bytes\n";
    std::cout << "short: \t\t" << sizeof(short) << "bytes\n";
    std::cout << "int: \t\t" << sizeof(int) << "bytes\n";
    std::cout << "long: \t\t" << sizeof(long) << "bytes\n";
    std::cout << "long long: \t" << sizeof(long long) << "bytes\n";
    std::cout << "float: \t\t" << sizeof(float) << "bytes\n";
    std::cout << "double: \t" << sizeof(double) << "bytes\n";
    std::cout << "long double: " << sizeof(long double) << "bytes\n";
}

void headers() {
    auto resultado { sumar(1, 2) };
    std::cout << ":" << resultado << std::endl;
}

void asignacion() {
    int a;               // Sin inicializador
    int b = 8;           // Inicialización por copia
    int c ( 6 );         // Inicialización directa
    int d = { 9 };       // Inicialización uniforme (El compilador nos avisa de posibles errores)
    int e = {};          // Inicialización de valor  // 0
    std::cout << "Inicialización" << std::endl;
}