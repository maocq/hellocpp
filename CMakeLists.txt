cmake_minimum_required(VERSION 3.21)
project(hellocpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(hellocpp main.cpp sumar/Sumar.cpp sumar/Sumar.h namespaces/Uno.cpp namespaces/Uno.h namespaces/Dos.cpp namespaces/Dos.h constantes/Constantes.cpp constantes/Constantes.h constantes/ConstantesInline.h temas/Temas.h estructuras/Vehiculo.h clases/fecha/Fecha.cpp clases/fecha/Fecha.h clases/fraccion/Fraccion.cpp clases/fraccion/Fraccion.h clases/simple/Simple.cpp clases/simple/Simple.h clases/calculadora/Calculadora.cpp clases/calculadora/Calculadora.h clases/copiaprofunda/ClaseConCopiaSuperficial.cpp clases/copiaprofunda/ClaseConCopiaSuperficial.h clases/copiaprofunda/ClaseConCopiaProfunda.cpp clases/copiaprofunda/ClaseConCopiaProfunda.h clases/herencia/Personaje.cpp clases/herencia/Personaje.h clases/herencia/Guerrero.cpp clases/herencia/Guerrero.h)
