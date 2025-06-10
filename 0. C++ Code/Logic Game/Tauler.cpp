#include "Tauler.hpp"
#include <sstream> // Concatenar 'couts'.
#include "/Ingenieria Informática/ProjecteDamesMP/0. C++ Code/Logic Game/GraphicManager.h"
#include "/Ingenieria Informática/ProjecteDamesMP/0. C++ Code/Logic Game/info_joc.hpp"

Tauler::Tauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_Tauler[i][j] = nullptr;
		}
	}
}

Tauler::~Tauler()
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			delete m_Tauler[i][j];
			m_Tauler[i][j] = nullptr;
		}
	}
}

Fitxa* Tauler::getFitxa(int fila, int columna)
{
	if (fila >= 0 && fila < N_FILES && columna >= 0 && columna < N_COLUMNES)
	{
		return m_Tauler[fila][columna];
	}
	return NULL;
}

void Tauler::inicialitza(const string& NomFitxer)
{
	// S'ha d'inicialitzar el tauler buit. (No podem cridar el constructor per defecte?)
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			m_Tauler[i][j] = nullptr;
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

		m_Tauler[P.getFila()][P.getColumna()] = new Fitxa(TFitxa, CFitxa);
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
           Fitxa* F = m_Tauler[i][j];  
           if (F == nullptr || F->esBuida())  
           {  
               SS << "_ ";  
           }  
           else  
           {  
               if (F->getColor() == COLOR_BLANC)  
               {  
                   if (F->esDama())  
                   {  
                       SS << "D ";  
                   }  
                   else  
                   {  
                       SS << "O ";  
                   }  
               }  
               else  
               {  
                   if (F->esDama())  
                   {  
                       SS << "R ";  
                   }  
                   else  
                   {  
                       SS << "X ";  
                   }  
               }  
           }  
       }  

       SS << endl;  
   }  

   SS << "  A B C D E F G H";  

   return SS.str(); // Obtenim string complet concatenat.  
}

void Tauler::afegeixCapturesRecursives(const Posicio& origen, Fitxa* fitxa, bool esDama)
{
	bool visitat[N_FILES][N_COLUMNES] = {};
	Moviment cami;
	cami.afegeiexPosicio(origen);
	afegeixCapturesRecursivesA(origen, fitxa, cami, visitat, esDama);
}

void Tauler::afegeixCapturesRecursivesA(const Posicio& actual, Fitxa* fitxa, Moviment camiActual, bool visitat[N_FILES][N_COLUMNES], bool esDama)
{
	bool capturaTrobada = false;
	static const int dirs[4][2] = { {-1,-1}, {-1,1}, {1,-1}, {1,1} };

	for (int i = 0; i < 4; ++i) {
		int df = dirs[i][0];
		int dc = dirs[i][1];

		if (!esDama) {
			int filaMig = actual.getFila() + df;
			int colMig = actual.getColumna() + dc;
			int filaDest = actual.getFila() + 2 * df;
			int colDest = actual.getColumna() + 2 * dc;

			if (filaMig >= 0 && filaMig < N_FILES && colMig >= 0 && colMig < N_COLUMNES
				&& filaDest >= 0 && filaDest < N_FILES && colDest >= 0 && colDest < N_COLUMNES)
			{
				Fitxa* fitxaMig = m_Tauler[filaMig][colMig];
				Fitxa* fitxaDest = m_Tauler[filaDest][colDest];

				if (!fitxaMig->esBuida() && fitxaMig->getColor() != fitxa->getColor() &&
					fitxaDest->esBuida() && !visitat[filaMig][colMig])
				{
					bool visitatNova[N_FILES][N_COLUMNES];
					memcpy(visitatNova, visitat, sizeof(visitatNova));
					visitatNova[filaMig][colMig] = true;

					Moviment nouCami = camiActual;
					nouCami.afegeiexPosicio(Posicio(filaDest, colDest));
					afegeixCapturesRecursivesA(Posicio(filaDest, colDest), fitxa, nouCami, visitatNova, esDama);
					capturaTrobada = true;
				}
			}
		}
		else {
			// Dama movement logic
			int fila = actual.getFila() + df;
			int col = actual.getColumna() + dc;
			bool trobatRival = false;
			int filaRival = -1, colRival = -1;

			while (fila >= 0 && fila < N_FILES && col >= 0 && col < N_COLUMNES) {
				Fitxa* f = m_Tauler[fila][col];
				if (!trobatRival) {
					if (!f->esBuida() && f->getColor() != fitxa->getColor() && !visitat[fila][col]) {
						trobatRival = true;
						filaRival = fila;
						colRival = col;
					}
					else if (!f->esBuida()) {
						break; // Own piece blocks
					}
				}
				else {
					if (f->esBuida()) {
						bool visitatNova[N_FILES][N_COLUMNES];
						memcpy(visitatNova, visitat, sizeof(visitatNova));
						visitatNova[filaRival][colRival] = true;

						Moviment nouCami = camiActual;
						nouCami.afegeiexPosicio(Posicio(fila, col));
						afegeixCapturesRecursivesA(Posicio(fila, col), fitxa, nouCami, visitatNova, esDama);
						capturaTrobada = true;
					}
					else {
						break; // Piece blocks after capture
					}
				}
				fila += df;
				col += dc;
			}
		}
	}

	if (!capturaTrobada && camiActual.getNPosicions() > 1) {
		fitxa->afegeixMovimentValid(camiActual);
	}
}


void Tauler::actualitzaMovimentsValids()
{
	for (int FILA = 0; FILA < N_FILES; FILA++)
	{
		for (int COLUMNA = 0; COLUMNA < N_COLUMNES; COLUMNA++)
		{
			
			Fitxa* F = m_Tauler[FILA][COLUMNA];
			F->eliminaMoviments();
			if (!F->esBuida() && F->getTipus() == TIPUS_NORMAL)
			{
				// =========================
				// ETAPA 1: MOVIMENT SENSE MATAR
				// =========================

				F->eliminaMoviments();

				bool teCaptura = false;

				int DIR;
				if (F->getColor() == COLOR_BLANC)
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
					if (m_Tauler[novaFila][novaColumna]->esBuida() && !teCaptura) // Si la nova casella es buida, ens podem moure.
					{
						// Creem moviment, hi afegim la nova posició (fila, col) i afegim aquest mov. a la llista de movs. vàlids.
						Moviment M;
						M.afegeiexPosicio(Posicio(novaFila, novaColumna));
						F->afegeixMovimentValid(M);
					}
				}

				// D.Dreta
				novaFila = FILA + DIR;
				novaColumna = COLUMNA + 1;
				if (novaFila >= 0 && novaFila < N_FILES && novaColumna >= 0 && novaColumna < N_COLUMNES)
				{
					if (m_Tauler[novaFila][novaColumna]->esBuida())
					{
						Moviment M;
						M.afegeiexPosicio(Posicio(novaFila, novaColumna));
						F->afegeixMovimentValid(M);
					}
				}


				// =========================
				// ETAPA 2: MOVIMENT AMB CAPTURA (1 FITXA)
				// =========================

				int filaSalt, columnaSalt;
				int filaMig, columnaMig;

				// D.Esquerra

				filaMig = FILA + DIR;
				columnaMig = COLUMNA - 1;

				filaSalt = FILA + 2 * DIR;
				columnaSalt = COLUMNA - 2;

				if (filaMig >= 0 && filaMig < N_FILES && columnaMig >= 0 && columnaMig < N_COLUMNES && filaSalt >= 0 && filaSalt < N_FILES && columnaSalt >= 0 && columnaSalt < N_COLUMNES)
				{
					Fitxa* FitxaMig = m_Tauler[filaMig][columnaMig];
					Fitxa* FitxaSalt = m_Tauler[filaSalt][columnaSalt];

					if (!FitxaMig->esBuida() && FitxaMig->getColor() != F->getColor() && FitxaSalt->esBuida())
					{
						teCaptura = true;
						Moviment M;
						M.afegeiexPosicio(Posicio(filaSalt, columnaSalt));
						F->afegeixMovimentValid(M);
					}
				}

				// D.Dreta
				filaMig = FILA + DIR;
				columnaMig = COLUMNA + 1;

				filaSalt = FILA + 2 * DIR;
				columnaSalt = COLUMNA + 2;

				if (filaMig >= 0 && filaMig < N_FILES && columnaMig >= 0 && columnaMig < N_COLUMNES && filaSalt >= 0 && filaSalt < N_FILES && columnaSalt >= 0 && columnaSalt < N_COLUMNES)
				{
					Fitxa* FitxaMig = m_Tauler[filaMig][columnaMig];
					Fitxa* FitxaSalt = m_Tauler[filaSalt][columnaSalt];

					if (!FitxaMig->esBuida() && FitxaMig->getColor() != F->getColor() && FitxaSalt->esBuida())
					{
						teCaptura = true;
						Moviment M;
						M.afegeiexPosicio(Posicio(filaSalt, columnaSalt));
						F->afegeixMovimentValid(M);
					}
				}

				Posicio ORIGEN(FILA, COLUMNA);
				afegeixCapturesRecursives(ORIGEN, F, false);
				filtrarMovimentsCaptures(F);
			}

			if (!F->esBuida() && F->getTipus() == TIPUS_DAMA)
			{
				F->eliminaMoviments();

				int fila = FILA;
				int columna = COLUMNA;

				// Direccions diagonals.
				int Direccions[4][2] = { {-1,-1},{-1,+1},{+1,-1},{+1,+1} };
				
				for (int i = 0; i < 4; i++) {
					int df = Direccions[i][0];
					int dc = Direccions[i][1];

					int novaFila = fila + df;
					int novaColumna = columna + dc;
					bool haTrobatRival = false;

					while (novaFila >= 0 && novaFila < N_FILES && novaColumna >= 0 && novaColumna < N_COLUMNES) {
						Fitxa* casella = m_Tauler[novaFila][novaColumna];

						if (casella->esBuida()) {
							if (!haTrobatRival) {
								Moviment M;
								M.afegeiexPosicio(Posicio(novaFila, novaColumna));
								F->afegeixMovimentValid(M);
							}
						}
						else {
							if (!haTrobatRival && casella->getColor() != F->getColor()) {
								haTrobatRival = true;
								// Check space after opponent piece
								int saltFila = novaFila + df;
								int saltCol = novaColumna + dc;
								if (saltFila >= 0 && saltFila < N_FILES && saltCol >= 0 && saltCol < N_COLUMNES &&
									m_Tauler[saltFila][saltCol]->esBuida()) {
									Moviment M;
									M.afegeiexPosicio(Posicio(saltFila, saltCol));
									F->afegeixMovimentValid(M);
								}
								break;
							}
							else {
								break; // Own piece or second opponent piece blocks
							}
						}
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
				Fitxa* Mig = m_Tauler[filaMig][colMig];
				Fitxa* Salt = m_Tauler[filaSalt][colSalt];

				// Si la del mig és rival i la destí està buida
				if (!Mig->esBuida() && Mig->getColor() != C && Salt->esBuida())
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

			while (filaActual >= 0 && filaActual < N_FILES && columnaActual >= 0 && columnaActual < N_COLUMNES)
			{
				Fitxa* Casella = m_Tauler[filaActual][columnaActual];

				if (Casella->esBuida())
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
						if (Casella->getColor() != C)
						{
							trobatRival = true;
						}
						else
						{
							// Fitxa pròpia -> bloqueja el camí.
							break;
						}
					}
				}

				filaActual += df;
				columnaActual += dc;
			}
		}

	}
	return n;

}

void Tauler::filtrarMovimentsCaptures(Fitxa* F) 
{
	if (F->esBuida()) return;

	// First find if there are any captures
	bool teCaptures = false;
	for (int i = 0; i < F->getNMovimentsValids(); i++) 
	{
		if (F->getMovimentValid(i).getNPosicions() > 1) 
		{
			teCaptures = true;
			break;
		}
	}

	if (teCaptures) {
		// Remove all non-capture moves
		vector <Moviment> captures ;
		int nCaptures = 0;

		for (int i = 0; i < F->getNMovimentsValids(); i++) 
		{
			if (F->getMovimentValid(i).getNPosicions() > 1) 
			{
				captures.push_back(F->getMovimentValid(i));
			}
		}

		F->eliminaMoviments();

		for (int i = 0; i < nCaptures; i++)
		{
			F->afegeixMovimentValid(captures[i]);
		}
	}
}


void Tauler::getPosicionsPosibles(const Posicio& Origen, int& nPosicions, Posicio PosicionsPossibles[])
{
	int Fila = Origen.getFila();
	int Columna = Origen.getColumna();

	Fitxa* F = m_Tauler[Fila][Columna];

	nPosicions = 0;

	for (int i = 0; i < F->getNMovimentsValids(); i++)
	{
		Moviment M = F->getMovimentValid(i);
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

	Fitxa* fitxaOrigen = m_Tauler[filaOrigen][columnaOrigen];
	Fitxa* fitxaDesti = m_Tauler[filaDesti][columnaDesti];

	if (fitxaOrigen->esBuida() || !fitxaDesti->esBuida())
		return false;

	bool capturaObligada = false;
	int indexMoviment = -1;

	for (int i = 0; i < fitxaOrigen->getNMovimentsValids(); ++i)
	{
		Moviment mov = fitxaOrigen->getMovimentValid(i);
		if (mov.getNPosicions() > 1)
			capturaObligada = true;

		if (mov.getNPosicions() > 0 && mov.getPosicio(mov.getNPosicions() - 1) == Desti)
			indexMoviment = i;
	}

	// Si hi ha captura obligada i no es fa captura, es bufa la fitxa.
	if (capturaObligada && (indexMoviment == -1 || fitxaOrigen->getMovimentValid(indexMoviment).getNPosicions() == 1))
	{
		m_Tauler[filaOrigen][columnaOrigen] =  new Fitxa(TIPUS_EMPTY, COLOR_BLANC);
		return true;
	}

	if (indexMoviment == -1)
		return false;

	Moviment movSeleccionat = fitxaOrigen->getMovimentValid(indexMoviment);

	// Mou la fitxa.
	m_Tauler[filaDesti][columnaDesti] = fitxaOrigen;
	m_Tauler[filaOrigen][columnaOrigen] = new Fitxa(TIPUS_EMPTY, COLOR_BLANC);

	// Captures intermèdies.
	int filaAnterior = filaOrigen;
	int colAnterior = columnaOrigen;

	for (int i = 0; i < movSeleccionat.getNPosicions(); ++i)
	{
		int filaActual = movSeleccionat.getPosicio(i).getFila();
		int colActual = movSeleccionat.getPosicio(i).getColumna();

		int df = (filaActual - filaAnterior) / max(1, abs(filaActual - filaAnterior));
		int dc = (colActual - colAnterior) / max(1, abs(colActual - colAnterior));

		int f = filaAnterior + df;
		int c = colAnterior + dc;

		while (f != filaActual || c != colActual)
		{
			Fitxa* fIntermedia = m_Tauler[f][c];
			if (!fIntermedia->esBuida() && fIntermedia->getColor() != fitxaOrigen->getColor())
			{
				m_Tauler[f][c] = new Fitxa(TIPUS_EMPTY, COLOR_BLANC);
				break;
			}
			f += df;
			c += dc;
		}

		filaAnterior = filaActual;
		colAnterior = colActual;
	}

	// Promoció a dama.
	if ((fitxaOrigen->getColor() == COLOR_BLANC && filaDesti == 0) ||
		(fitxaOrigen->getColor() == COLOR_NEGRE && filaDesti == N_FILES - 1))
	{
		m_Tauler[filaDesti][columnaDesti]->ferDama();
	}

	return true;
}

int Tauler::obtenirMaxCaptures(Posicio& MillorFitxa)
{
	int maxCaptures = 0;

	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			Fitxa* F = m_Tauler[fila][col];

			if (!F->esBuida())
			{
				for (int i = 0; i < F->getNMovimentsValids(); i++)
				{
					Moviment M = F->getMovimentValid(i);
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

void Tauler::visualitza(Posicio posSeleccionada, bool fitxaSeleccionada)
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

	for (int fila = 0; fila < N_FILES; fila++)
	{
		for (int col = 0; col < N_COLUMNES; col++)
		{
			Fitxa* f = m_Tauler[fila][col];
			if (f != NULL && !f->esBuida())
			{
				int x = POS_X_TAULER + CASELLA_INICIAL_X + (col * AMPLADA_CASELLA);
				int y = POS_Y_TAULER + CASELLA_INICIAL_Y + (fila * ALCADA_CASELLA);
				f->visualitza(x, y);
			}
		}
	}

	if (fitxaSeleccionada)
	{
		Fitxa* f = m_Tauler[posSeleccionada.getFila()][posSeleccionada.getColumna()];

		for (int i = 0; i < f->getNMovimentsValids(); i++)
		{
			Moviment m = f->getMovimentValid(i);
			Posicio p = m.getPosicio(m.getNPosicions() - 1);

			int x = POS_X_TAULER + CASELLA_INICIAL_X + (p.getColumna() * AMPLADA_CASELLA);
			int y = POS_Y_TAULER + CASELLA_INICIAL_Y + (p.getFila() * ALCADA_CASELLA);

			GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, x, y);
		}
	}
}
