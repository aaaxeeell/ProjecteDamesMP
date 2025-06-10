#include "Posicio.hpp"
#include "Tauler.hpp"
Posicio::Posicio(const string& P)
{
	FromString(P);
}

string Posicio::ToString() const
{
	string P = "a1"; // String de referència per actualitzar el valor.

	P[0] = 'a' + m_Columna;
	P[1] = '1' + (N_FILES - 1 - m_Fila);
	return P;
}

void Posicio::FromString(const string& P)
{
	m_Fila = (N_FILES - 1) - (P[1] - '1');
	m_Columna = P[0] - 'a';

}

// OPERADORS SOBRECARREGATS DE LECTURA I ESCRIPTURA
// Ensenyem al programa com ha de llegir els objectes de la clase 'Posició'.

ifstream& operator>>(ifstream& input, Posicio& P)
{
	string PString; 
	input >> PString; // Posició amb escriptura tipus 'b2'
	P.FromString(PString); // Passem a FILA i COLUMNA.
	return input;
}

ofstream& operator<<(ofstream& output, Posicio& P)
{
	output << P.ToString(); // Converteix de FILA i COLUMNA a 'b2'.
	return output;
}

bool Posicio:: operator==(const Posicio& P) const
{
	bool PIguals = false;

	if (P.m_Fila == m_Fila && P.m_Columna == m_Columna)
	{
		PIguals = true;
	}

	return PIguals;
}