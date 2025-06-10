#pragma once  
#ifndef TAULER_HPP  
#define TAULER_HPP  
#define N_FILES 8  
#define N_COLUMNES 8  

#include "Fitxa.hpp"  
#include "Posicio.hpp"  
using namespace std;  

class Tauler  
{  
public:  
	Tauler();  
	~Tauler();  

	void inicialitza(const string& NomFitxer);  
	void actualitzaMovimentsValids();  
	void getPosicionsPosibles(const Posicio& Origen, int& nPosicions, Posicio PosicionsPosibles[]);  

	bool mouFitxa(const Posicio& Origen, const Posicio& Desti);  
	string ToString() const;  
	void afegeixCapturesRecursives(const Posicio& origen, Fitxa* fitxa, bool esDama);  
	void afegeixCapturesRecursivesA(const Posicio& actual, Fitxa* fitxa, Moviment camiActual, bool visitat[N_FILES][N_COLUMNES], bool esDama);  
	int obtenirCaptures(const Posicio& P, ColorFitxa C, bool esDama, Posicio Resultats[]);  
	void filtrarMovimentsCaptures(Fitxa* F);  
	int obtenirMaxCaptures(Posicio& MillorFitxa);  
	Fitxa* getFitxa(int fila, int columna);

	void visualitza(Posicio posSeleccionada, bool fitxaSeleccionada); // Add this declaration to fix the error.

private:  
	Fitxa* m_Tauler[N_FILES][N_COLUMNES];  
};  

#endif