#include "CuaMoviments.hpp"

void CuaMoviments:: afegeixMoviment(Moviment M)
{
	NodeMoviment* NNode = new NodeMoviment;
	NNode->M = M;
	NNode->MNext = nullptr;

	if (m_final == nullptr)
	{
		m_inici = NNode;
		m_final = NNode;
	}
	else
	{
		m_final->MNext = NNode;
		m_final = NNode;
	}
}

Moviment CuaMoviments::primerMoviment()
{
	if (m_inici != nullptr)
	{
		return m_inici->M;
	}

	Moviment BUIT;
	return BUIT;
}

void CuaMoviments::eliminaPrimer()
{
	if (m_inici != nullptr)
	{
		NodeMoviment* aux = m_inici;
		m_inici = m_inici->MNext;
		delete aux;

		if (m_inici == nullptr)
		{
			m_final = nullptr;
		}
	}
}

void CuaMoviments::buida()
{
	while (m_inici != nullptr)
	{
		eliminaPrimer();
	}
}