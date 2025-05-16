#include "Tauler.hpp"

Tauler::Tauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_Tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC);
		}
	}
}

void Tauler::inicialitza(const string& NomFitxer)
{
	ifstream FitxerTauler(NomFitxer);

}