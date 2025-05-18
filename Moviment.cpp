#include "Moviments.hpp"

void Moviment::afegeiexPosicio(const Posicio& P)
{
	if (m_NPosicions < MAX_CAMI)
	{
		m_Cami[m_NPosicions] = P;
		m_NPosicions++;
	}
}

Posicio Moviment::getPosicio(int i) const
{
	if (i >= 0 && i < m_NPosicions)
	{
		return m_Cami[i];
	}
}
