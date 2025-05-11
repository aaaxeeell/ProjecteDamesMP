#pragma once
#ifndef FITXA_HPP
#define FITXA_HPP


class Fitxa
{
public:


private:
	TipusFitxa TFitxa;
	ColorFitxa CFitxa;
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

