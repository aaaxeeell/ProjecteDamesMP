#pragma once
#ifndef FITXA_HPP
#define FITXA_HPP

#include "Moviments.hpp"
const int MAX_POSICIONS_POSSIBLES = 10;

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
	Fitxa() : TFitxa(TIPUS_EMPTY), CFitxa(COLOR_BLANC), m_NMoviments(0) {}
	Fitxa(TipusFitxa T, ColorFitxa C) : TFitxa(T), CFitxa(C), m_NMoviments(0) {}

	// Getters:
	TipusFitxa getTipus() const { return TFitxa; }
	ColorFitxa getColor() const { return CFitxa; }
	
	bool esDama() const { return TFitxa == TIPUS_DAMA; }
	bool esBuida() const { return TFitxa == TIPUS_EMPTY; }
	void ferDama() { TFitxa = TIPUS_DAMA; }

	void afegeixMovimentValid(const Moviment& M);
	int getNMovimentsValids() const { return m_NMoviments; }
	Moviment getMovimentValid(int i) const;
	void eliminaMoviments();

private:
	TipusFitxa TFitxa;
	ColorFitxa CFitxa;
	
	Moviment m_MovimentsValids[MAX_POSICIONS_POSSIBLES];
	int m_NMoviments;
	
};


#endif

