#pragma once
#ifndef CUAMOVIMENTS_HPP
#define CUAMOVIMENTS_HPP

#include "Moviments.hpp"

struct NodeMoviment
{
	Moviment M;
	NodeMoviment* MNext;
};

class CuaMoviments
{
public:
	CuaMoviments() : m_inici(nullptr), m_final(nullptr) {}
	~CuaMoviments() { buida(); }

	void afegeixMoviment(Moviment M);
	bool teMoviments() { return m_inici != nullptr; }
	Moviment primerMoviment();
	void eliminaPrimer();
	void buida();

private:
	NodeMoviment* m_inici;
	NodeMoviment* m_final;
};
	
#endif