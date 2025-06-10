#pragma once
#ifndef MOVIMENT_HPP
#define MOVIMENTS_HPP

#include "Posicio.hpp"
#define MAX_CAMI 10

class Moviment
{
public:
	Moviment() : m_NPosicions(0) {}
	Moviment(const Moviment& other);
	bool equals(const Moviment& other) const;
	Moviment& operator=(const Moviment& other);
	void afegeiexPosicio(const Posicio& P); // Afegim una posicio al camí.
	int getNPosicions() const { return m_NPosicions; } // Retorna quantes posicions hi ha al camí.
	Posicio getPosicio(int i) const; // Retorna la posició 'i' del camí.

private:

	Posicio m_Cami[MAX_CAMI]; // Camí de posicions.
	int m_NPosicions; // Quantes posicions porta el moviment.

};

#endif