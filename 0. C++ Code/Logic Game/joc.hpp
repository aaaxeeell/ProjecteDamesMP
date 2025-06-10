#ifndef JOC_H
#define JOC_H

#include <string>
#include "/Ingenieria Informática/ProjecteDamesMP/Tauler.hpp"
#include "info_joc.hpp"
#include "/Ingenieria Informática/ProjecteDamesMP/CuaMoviments.hpp"

class Joc
{
public:
    Joc();

    void inicialitza(int mode, std::string nomFitxerTauler, std::string nomFitxerMoviments);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void finalitza();

private:
    Tauler m_tauler;
    CuaMoviments m_cua;

    int m_mode; // MODE_JOC_NORMAL o MODE_JOC_REPLAY
    std::string m_nomFitxerMoviments;

    bool m_fiPartida;
    int m_jugadorTorn; // 0 = blanc, 1 = negre

    bool m_fitxaSeleccionada;
    Posicio m_posicioSeleccionada;
};

#endif
