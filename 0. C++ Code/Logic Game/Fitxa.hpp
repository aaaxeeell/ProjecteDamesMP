#pragma once
#ifndef FITXA_HPP
#define FITXA_HPP

#include "Moviments.hpp"
#include <vector>
using namespace std;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_EMPTY,
	TIPUS_DAMA

}TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC

}ColorFitxa;


class Fitxa 
{
public:
	Fitxa() : TFitxa(TIPUS_EMPTY), CFitxa(COLOR_BLANC) {}
	Fitxa(TipusFitxa T, ColorFitxa C) : TFitxa(T), CFitxa(C) {}

	// Getters:
	TipusFitxa getTipus() const { return TFitxa; }
	ColorFitxa getColor() const { return CFitxa; }
	
	bool esDama() const { return TFitxa == TIPUS_DAMA; }
	bool esBuida() const { return TFitxa == TIPUS_EMPTY; }
	void ferDama() { TFitxa = TIPUS_DAMA; }

	void afegeixMovimentValid(const Moviment& M);
	bool existeixMoviment(Moviment M);
	int getNMovimentsValids() { return m_MovimentsValids.size(); }
	Moviment getMovimentValid(int i);
	void eliminaMoviments() { m_MovimentsValids.clear(); }

	void visualitza(int x, int y);


private:
	TipusFitxa TFitxa;
	ColorFitxa CFitxa;
	
	vector <Moviment> m_MovimentsValids;
	
};


#endif

