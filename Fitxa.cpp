#include "Fitxa.hpp"

void Fitxa::afegeixMovimentValid(const Moviment& M)
{
	if (m_NMoviments < MAX_POSICIONS_POSSIBLES)
	{
		m_MovimentsValids[m_NMoviments] = M;
		m_NMoviments++;
	}
}

Moviment Fitxa::getMovimentValid(int i) const
{
	if (i >= 0 && i < m_NMoviments)
	{
		return m_MovimentsValids[i];
	}
}

void Fitxa::eliminaMoviments()
{
	m_NMoviments = 0;
}