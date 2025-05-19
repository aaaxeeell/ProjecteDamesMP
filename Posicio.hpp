#pragma once  
#ifndef POSICIO_HPP  
#define POSICIO_HPP  
using namespace std;  
#include <string>  
#include <fstream>  

class Posicio  
{  
public:  
  Posicio() : m_Fila(0), m_Columna(0) {}  
  Posicio(int Fila, int Columna) : m_Fila(Fila), m_Columna(Columna) {}  
  Posicio(const string& P);  

  string ToString() const; // De coordenades a string tipus 'A1'.  
  void FromString(const string& P);  

  int getFila() const { return m_Fila; }  
  int getColumna() const { return m_Columna; }  

  bool operator==(const Posicio& P) const;  

  // Sobrecarga del operador '<<' para permitir la impresión de objetos Posicio  
  friend ostream& operator<<(ostream& os, const Posicio& pos)  
  {  
      os << pos.ToString();  
      return os;  
  }  

private:  
  int m_Fila;  
  int m_Columna;  
};  

#endif