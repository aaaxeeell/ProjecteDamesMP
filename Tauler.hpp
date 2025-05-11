#pragma once
#ifndef TAULER_HPP
#define TAULER_HPP
#define N_FILES 8
#define N_COLUMNES 8

#include "Fitxa.hpp"
#include "Posicio.hpp"

class Tauler
{
public:
	Tauler();

	void inicialitza(const string& NomFitxer);
private:
	Fitxa m_Tauler[N_FILES][N_COLUMNES];
};

#endif