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

	void inicialitza(const string& NomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPosibles(const Posicio& Origen, int& nPosicions, Posicio PosicionsPosibles[]);
	bool mouFitxa(const Posicio& Origen, const Posicio& Desti);
	string ToString() const;

private:
	Fitxa m_Tauler[N_FILES][N_COLUMNES];
};

#endif