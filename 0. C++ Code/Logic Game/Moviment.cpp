#include "Moviments.hpp"

void Moviment::afegeiexPosicio(const Posicio& P)
{
	if (m_NPosicions < MAX_CAMI)
	{
		m_Cami[m_NPosicions] = P;
		m_NPosicions++;
	}
}

bool Moviment::equals(const Moviment& other) const
{
    if (m_NPosicions != other.m_NPosicions)
        return false;

    for (int i = 0; i < m_NPosicions; ++i)
    {
        if (!(m_Cami[i] == other.m_Cami[i]))
            return false;
    }
    return true;
}


Posicio Moviment::getPosicio(int i) const
{
	if (i >= 0 && i < m_NPosicions)
	{
		return m_Cami[i];
	}

	return Posicio();
}

Moviment::Moviment(const Moviment& other)  
{  
   for (int i = 0; i < other.m_NPosicions; ++i)  
   {  
       m_Cami[i] = other.m_Cami[i];  
   }  
   m_NPosicions = other.m_NPosicions;  
}  

Moviment& Moviment::operator=(const Moviment& other)  
{  
   if (this != &other)  
   {  
       for (int i = 0; i < other.m_NPosicions; ++i)  
       {  
           m_Cami[i] = other.m_Cami[i];  
       }  
       m_NPosicions = other.m_NPosicions;  
   }  
   return *this;  
}

