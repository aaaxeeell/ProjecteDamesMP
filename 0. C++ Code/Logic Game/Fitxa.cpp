#include "Fitxa.hpp"
#include "/Ingenieria Informática/ProjecteDamesMP/0. C++ Code/Logic Game/GraphicManager.h"

void Fitxa::afegeixMovimentValid(const Moviment& M)
{
	bool jaExisteix = false;
	for (int i = 0; i < m_MovimentsValids.size(); i++)
	{
		if (m_MovimentsValids[i].equals(M))
		{
			jaExisteix = true;
		}
	}

	if (!jaExisteix)
	{
		m_MovimentsValids.push_back(M);
	}
}

bool Fitxa::existeixMoviment(Moviment M)
{
    for (int i = 0; i < m_MovimentsValids.size(); i++)
    {
        if (M.getNPosicions() != m_MovimentsValids[i].getNPosicions())
        {
            continue;
        }

        bool igual = true;
        for (int j = 0; j < M.getNPosicions(); j++)
        {
            if (!(M.getPosicio(j) == m_MovimentsValids[i].getPosicio(j)))
            {
                igual = false;
            }
        }

        if (igual)
        {
            return true;
        }
    }

    return false;
}

Moviment Fitxa:: getMovimentValid(int i)
{
    if (i >= 0 && i < m_MovimentsValids.size())
    {
        return m_MovimentsValids[i];
    }
    else
    {
        Moviment buit;
        return buit;
    }
}

void Fitxa::visualitza(int x, int y)
{
    if (esBuida())
    {
        return;
    }

    if (CFitxa == COLOR_BLANC)
    {
        if (TFitxa == TIPUS_DAMA)
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, x, y);
        }
        else
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, x, y);
        }
    }
    else
    {
        if (TFitxa == TIPUS_DAMA)
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, x, y);
        }
        else
        {
            GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, x, y);
        }
    }
}


