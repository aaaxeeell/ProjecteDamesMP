#include "Tauler.hpp"
#include <sstream> // Concatenar 'couts'.
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
	Tauler(); // Inicialització en buit.

	ifstream FitxerTauler(NomFitxer);
	char FitxaT;
	string PosicioFitxa;

	while (FitxerTauler >> FitxaT >> PosicioFitxa)
	{
		Posicio P(PosicioFitxa);
		TipusFitxa TFitxa;
		ColorFitxa CFitxa;

		switch (FitxaT)
		{
			case 'O':
			{
				TFitxa = TIPUS_NORMAL;
				CFitxa = COLOR_BLANC;
				break;
			}
			case 'D':
			{
				TFitxa = TIPUS_DAMA;
				CFitxa = COLOR_BLANC;
				break;
			}
			case 'X':
			{
				TFitxa = TIPUS_NORMAL;
				CFitxa = COLOR_NEGRE;
				break;
			}
			case 'R':
			{
				TFitxa = TIPUS_DAMA;
				CFitxa = COLOR_NEGRE;
				break;
			}
			default:
			{
				continue; // IGNORAR LO INVÀLID.
			}
		}

		m_Tauler[P.getFila()][P.getColumna()] = Fitxa(TFitxa, CFitxa);
	}

	FitxerTauler.close();
}

string Tauler::ToString() const
{
	stringstream SS;
	
	// Imprimir NFILES:
	for (int i = 0; i < N_FILES; i++)
	{
		SS << (N_FILES - i) << ":";

		for (int j = 0; j < N_COLUMNES; j++)
		{
			const Fitxa& F = m_Tauler[i][j];
			if (F.esBuida())
			{
				SS << "_";
			}
			else
			{
				if (F.getColor() == COLOR_BLANC)
				{
					if (F.esDama())
					{
						SS << "D";
					}
					else
					{
						SS << "O";
					}
				}
				else
				{
					if (F.esDama())
					{
						SS << "R";
					}
					else
					{
						SS << "X";
					}
				}
			}
		}

		SS << endl;
	}

	SS << "  A B C D E F G H";

	return SS.str(); // Obtenim string complet concetenat.
}

void Tauler::actualitzaMovimentsValids()
{
	for (int FILA = 0; FILA < N_FILES; FILA++)
	{
		for (int COLUMNA = 0; COLUMNA < N_COLUMNES; COLUMNA++)
		{
			// ETAPA 1: MOV. DE FITXA NORMAL.
			Fitxa& F = m_Tauler[FILA][COLUMNA];
			if (!F.esBuida() && F.getTipus() == TIPUS_NORMAL)
			{
				F.eliminaMoviments();
				int DIR;
				if (F.getColor() == COLOR_BLANC)
				{
					DIR = -1; // Blanca PUJA;
				}
				else
				{
					DIR = 1; // Negre BAIXA;
				}

				// Comprovem les dues diagonals.
				int novaFila, novaColumna;
				

				// D.Esquerra
				novaFila = FILA + DIR;
				novaColumna = COLUMNA - 1;

				if (novaFila >= 0 && novaFila < N_FILES && novaColumna >= 0 && novaColumna < N_COLUMNES)
				{
					if (m_Tauler[novaFila][novaColumna].esBuida()) // Si la nova casella es buida, ens podem moure.
					{
						// Creem moviment, hi afegim la nova posició (fila, col) i afegim aquest mov. a la llista de movs. vàlids.
						Moviment M;
						M.afegeiexPosicio(Posicio(novaFila, novaColumna));
						F.afegeixMovimentValid(M);
					}
				}

				// D.Dreta
				novaFila = FILA + DIR;
				novaColumna = COLUMNA + 1;
				if (novaFila >= 0 && novaFila < N_FILES && novaColumna >= 0 && novaColumna < N_COLUMNES)
				{
					if (m_Tauler[novaFila][novaColumna].esBuida())
					{
						Moviment M;
						M.afegeiexPosicio(Posicio(novaFila, novaColumna));
						F.afegeixMovimentValid(M);
					}
				}
			}
		}
	}
}