#pragma once
#ifndef FITXA_HPP
#define FITXA_HPP

#define MAX_POSICIONS_POSSIBLES 10

class Fitxa
{
public:
	Fitxa() : TFitxa(TIPUS_EMPTY), CFitxa(COLOR_BLANC) {}
	Fitxa(TipusFitxa T, ColorFitxa C) : TFitxa(T), CFitxa(C) {}

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

