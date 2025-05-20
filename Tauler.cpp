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
	// S'ha d'inicialitzar el tauler buit. (No podem cridar el constructor per defecte?)
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_Tauler[i][j] = Fitxa(TIPUS_EMPTY, COLOR_BLANC);
		}
	}

	ifstream FitxerTauler;
	FitxerTauler.open(NomFitxer); /// Assegurem que hem obert el fitxer.

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
		SS << (N_FILES - i) << ": ";

		for (int j = 0; j < N_COLUMNES; j++)
		{
			const Fitxa& F = m_Tauler[i][j];
			if (F.esBuida())
			{
				SS << "_ ";
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
			
			Fitxa& F = m_Tauler[FILA][COLUMNA];
			if (!F.esBuida() && F.getTipus() == TIPUS_NORMAL)
			{
				// ETAPA 1: MOV. DE FITXA NORMAL.
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

				// ETAPA 2: MATAR FITXA

				int filaSalt, columnaSalt;
				int filaMig, columnaMig;

				// D.Esquerra

				filaMig = FILA + DIR;
				columnaMig = COLUMNA - 1;

				filaSalt = FILA + 2 * DIR;
				columnaSalt = COLUMNA - 2;

				if (filaMig >= 0 && filaMig < N_FILES && columnaMig >= 0 && columnaMig < N_COLUMNES && filaSalt >= 0 && filaSalt < N_FILES && columnaSalt >= 0 && columnaSalt < N_COLUMNES)
				{
					Fitxa& FitxaMig = m_Tauler[filaMig][columnaMig];
					Fitxa& FitxaSalt = m_Tauler[filaSalt][columnaSalt];

					if (!FitxaMig.esBuida() && FitxaMig.getColor() != F.getColor() && FitxaSalt.esBuida())
					{
						Moviment M;
						M.afegeiexPosicio(Posicio(filaSalt, columnaSalt));
						F.afegeixMovimentValid(M);
					}
				}

				// D.Dreta
				filaMig = FILA + DIR;
				columnaMig = COLUMNA + 1;

				filaSalt = FILA + 2 * DIR;
				columnaSalt = COLUMNA + 2;

				if (filaMig >= 0 && filaMig < N_FILES && columnaMig >= 0 && columnaMig < N_COLUMNES && filaSalt >= 0 && filaSalt < N_FILES && columnaSalt >= 0 && columnaSalt < N_COLUMNES)
				{
					Fitxa& FitxaMig = m_Tauler[filaMig][columnaMig];
					Fitxa& FitxaSalt = m_Tauler[filaSalt][columnaSalt];

					if (!FitxaMig.esBuida() && FitxaMig.getColor() != F.getColor() && FitxaSalt.esBuida())
					{
						Moviment M;
						M.afegeiexPosicio(Posicio(filaSalt, columnaSalt));
						F.afegeixMovimentValid(M);
					}
				}

				Posicio ORIGEN(FILA, COLUMNA);
				afegeixCapturesRecursives(ORIGEN, F, false);
				filtrarMovimentsCaptures(F);
			}

			if (!F.esBuida() && F.getTipus() == TIPUS_DAMA)
			{
				F.eliminaMoviments();

				int fila = FILA;
				int columna = COLUMNA;

				// Direccions diagonals.
				int Direccions[4][2] = { {-1,-1},{-1,+1},{+1,-1},{+1,+1} };
				
				for (int i = 0; i < 4; i++)
				{
					int df = Direccions[i][0];
					int dc = Direccions[i][1];

					int novaFila = fila + df;
					int novaColumna = columna + dc;

					// Avancem en diagonal mentre estigui dins i sigui buida.
					while (novaFila >= 0 && novaFila < N_FILES && novaColumna >= 0 && novaColumna < N_COLUMNES && m_Tauler[novaFila][novaColumna].esBuida())
					{
						Moviment M;
						M.afegeiexPosicio(Posicio(novaFila, novaColumna));
						F.afegeixMovimentValid(M);

						novaFila += df;
						novaColumna += dc;
					}
				}

				Posicio ORIGEN(FILA, COLUMNA);
				afegeixCapturesRecursives(ORIGEN, F, true);
				filtrarMovimentsCaptures(F);


			}
		}
	}
}

int Tauler::obtenirCaptures(const Posicio& P, ColorFitxa C, bool esDama, Posicio Resultats[])
{
	int fila = P.getFila();
	int col = P.getColumna();
	int n = 0;  // Comptador de captures trobades
	
	// Direccions diagonals: {deltaFila, deltaColumna}
	
	int direccions[4][2] = {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}};

	for (int i = 0; i < 4; i++)
	{
		int df = direccions[i][0];
		int dc = direccions[i][1];

		if (!esDama)
		{
			int filaMig = fila + df;
			int colMig = col + dc;
			int filaSalt = fila + 2 * df;
			int colSalt = col + 2 * dc;

			// Comprovem que totes dues posicions estan dins del tauler
			if (filaMig >= 0 && filaMig < N_FILES && colMig >= 0 && colMig < N_COLUMNES && filaSalt >= 0 && filaSalt < N_FILES && colSalt >= 0 && colSalt < N_COLUMNES)
			{
				Fitxa& Mig = m_Tauler[filaMig][colMig];
				Fitxa& Salt = m_Tauler[filaSalt][colSalt];

				// Si la del mig és rival i la destí està buida
				if (!Mig.esBuida() && Mig.getColor() != C && Salt.esBuida())
				{
					Resultats[n] = Posicio(filaSalt, colSalt);
					n++;
				}
			}
		}

		else
		{
			int filaActual = fila + df;
			int columnaActual = col + dc;
			bool trobatRival = false;
			int filaRival = -1;
			int colRival = -1;

			while (filaActual >= 0 && filaActual < N_FILES && columnaActual >= 0 && columnaActual < N_COLUMNES)
			{
				Fitxa& Casella = m_Tauler[filaActual][columnaActual];

				if (Casella.esBuida())
				{
					if (trobatRival)
					{
						Resultats[n] = Posicio(filaActual, columnaActual);
						n++;
						break; // Només un salt per direcció.
					}
					// Si no hi ha rival, seguim avançant.

					else
					{
						if (trobatRival)
						{
							// Ja havia una fitxa -> no podem saltar més d'una.
						}
					}

					if (Casella.getColor() != C)
					{
						// Trobat primer rival.
						trobatRival = true;
						filaRival = filaActual;
						colRival = columnaActual;

					}
					else
					{
						// Fitxa pròpia -> bloqueja el camí.
						break;
					}
				}

				filaActual += df;
				columnaActual += dc;
			}
		}

	}
	return n;

}
void Tauler::afegeixCapturesRecursives(const Posicio& Origen, Fitxa& F, bool esDama)
{
	Moviment MPendents[100];
	int nPendents = 0;

	// Inicialitzem el primer moviment amb la posició d'origen.
	Moviment M;
	M.afegeiexPosicio(Origen);
	MPendents[nPendents] = M;
	nPendents++;

	while (nPendents > 0)
	{
		// Treiem el primer mov. pendent.
		Moviment MActual = MPendents[0];
		
		// Desplaçem cap a l'esquerra.
		for (int i = 1; i < nPendents; i++)
		{
			MPendents[i - 1] = MPendents[i];
		}
		nPendents--;

		// Última posició del moviment actual.
		Posicio PFinal = MActual.getPosicio(MActual.getNPosicions() - 1);

		// Busquem captrues des d'aquesta posicio.
		Posicio Noves[10];
		int nNoves = obtenirCaptures(PFinal, F.getColor(), esDama, Noves);

		if (nNoves == 0)
		{
			// No hi ha més captures --> MOVIMENT VÀLID.
			if (MActual.getNPosicions() > 1)
			{
				F.afegeixMovimentValid(MActual);
			}
		}
		else
		{
			for (int i = 0; i < nNoves; i++)
			{
				Moviment COPIA = MActual;
				COPIA.afegeiexPosicio(Noves[i]);
				MPendents[nPendents] = COPIA;
				nPendents++;
			}
		}
	}
}

void Tauler::filtrarMovimentsCaptures(Fitxa& F)
{
	const int MAX = 10;
	Moviment Captures[MAX];
	int nCaptures = 0;

	int maxLongitud = 1;

	// PAS 1: TROBEM NOMÉS ELS MOVIMENTS AMB CAPTURA.
	for (int i = 0; i < F.getNMovimentsValids(); i++)
	{
		Moviment M = F.getMovimentValid(i);
		if (M.getNPosicions() > 1)
		{
			if (M.getNPosicions() > maxLongitud)
			{
				maxLongitud = M.getNPosicions();
				nCaptures = 0;
				Captures[nCaptures++] = M;
			}
			else
			{
				if (M.getNPosicions() == maxLongitud)
				{
					Captures[nCaptures++] = M;
				}
			}
		}
	}

	// PAS 2: ESBORREM ELS MOVIMENTS DE LA FITXA.
	F.eliminaMoviments();

	// PAS 3: Afegim només els millors captures trobats.
	for (int i = 0; i < nCaptures; i++)
	{
		F.afegeixMovimentValid(Captures[i]);
	}

}


void Tauler::getPosicionsPosibles(const Posicio& Origen, int& nPosicions, Posicio PosicionsPossibles[])
{
	int Fila = Origen.getFila();
	int Columna = Origen.getColumna();

	Fitxa& F = m_Tauler[Fila][Columna];

	nPosicions = 0;

	for (int i = 0; i < F.getNMovimentsValids(); i++)
	{
		Moviment M = F.getMovimentValid(i);
		if (M.getNPosicions() > 0)
		{
			Posicio P = M.getPosicio(M.getNPosicions() - 1);
			PosicionsPossibles[nPosicions] = P;
			nPosicions++;
		}
	}
}

bool Tauler::mouFitxa(const Posicio& Origen, const Posicio& Desti)
{
	int filaOrigen = Origen.getFila();
	int columnaOrigen = Origen.getColumna();

	int filaDesti = Desti.getFila();
	int columnaDesti = Desti.getColumna();

	bool mouFitxa = true;

	Posicio millorFitxa;
	int maxCaptures = obtenirMaxCaptures(millorFitxa);

	Fitxa& F = m_Tauler[filaOrigen][columnaOrigen];

	if (F.esBuida())
	{
		mouFitxa = false;
	}

	bool movimentTrobat = false;
	Moviment MSeleccionat;

	for (int i = 0; i < F.getNMovimentsValids(); i++)
	{
		Moviment M = F.getMovimentValid(i);
		if (M.getNPosicions() > 0)
		{
			Posicio FINAL = M.getPosicio(M.getNPosicions() - 1);
			if (FINAL == Desti)
			{
				movimentTrobat = true;
				MSeleccionat = M;
				break;
			}
		}
	}

	m_Tauler[filaDesti][columnaDesti] = F;
	m_Tauler[filaOrigen][columnaOrigen] = Fitxa(); // TIPUS_EMPTY


	// ETAPA 2: ELIMINAR FITXES CAPTURADES
	if (MSeleccionat.getNPosicions() > 1)
	{
		for (int i = 0; i < MSeleccionat.getNPosicions() - 1; i++)
		{
			Posicio P1 = MSeleccionat.getPosicio(i);
			Posicio P2 = MSeleccionat.getPosicio(i + 1);

			int filaCaptura = (P1.getFila() + P2.getFila()) / 2;
			int columnaCaptura = (P1.getColumna() + P2.getColumna()) / 2;

			m_Tauler[filaCaptura][columnaCaptura] = Fitxa();
		}
	}

	// ETAPA 3: CONVERSIÓ A DAMA

	Fitxa& DEST = m_Tauler[filaDesti][columnaDesti];
	if (DEST.getTipus() == TIPUS_NORMAL)
	{
		if ((DEST.getColor() == COLOR_BLANC && filaDesti == 0) || (DEST.getColor() == COLOR_NEGRE && filaDesti == N_FILES - 1))
		{
			DEST.ferDama();
		}
	}
	// ETAPA 4: BUFAR PEÇA

	int capturesRealitzedes = MSeleccionat.getNPosicions() - 1;
	if (capturesRealitzedes < maxCaptures)
	{
		int filaBufada = millorFitxa.getFila();
		int columnaBufada = millorFitxa.getColumna();

		m_Tauler[filaBufada][columnaBufada] = Fitxa();
	}


	return mouFitxa;
}

int Tauler::obtenirMaxCaptures(Posicio& MillorFitxa)
{
	int maxCaptures = 0;

	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			Fitxa& F = m_Tauler[fila][col];

			if (!F.esBuida())
			{
				for (int i = 0; i < F.getNMovimentsValids(); i++)
				{
					Moviment M = F.getMovimentValid(i);
					int Captures = M.getNPosicions() - 1;

					if (Captures > maxCaptures)
					{
						maxCaptures = Captures;
						MillorFitxa = Posicio(fila, col);
					}
 				}
			}
		}
	}

	return maxCaptures;
}