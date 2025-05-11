#pragma once  
#ifndef POSICIO_HPP  
#define POSICIO_HPP  
using namespace std;  
#include <string>  

class Posicio  
{  
public:  
   Posicio() : m_Fila(0), m_Columna(0) {}  
   Posicio(int Fila, int Columna) : m_Fila(Fila), m_Columna(Columna) {}
   
   Posicio (const string& P);



private:  
   int m_Fila;  
   int m_Columna;  
};  

#endif