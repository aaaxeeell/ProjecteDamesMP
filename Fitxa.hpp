#pragma once
#ifndef FITXA_HPP
#define FITXA_HPP

#define MAX_POSICIONS_POSSIBLES 10

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
	void ferDama() const { TFitxa == TIPUS_DAMA; }

private:
	TipusFitxa TFitxa;
	ColorFitxa CFitxa;
	
	Posicio m_PosicionsPossibles[MAX_POSICIONS_POSSIBLES]
	
};


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
#endif

