//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"


Joc::Joc()
{
	m_mode = MODE_JOC_NONE;
	m_fiPartida = false;
	m_jugadorTorn = 0;
	m_fitxaSeleccionada = false;
}

void Joc::inicialitza(int mode, std::string nomFitxerTauler, std::string nomFitxerMoviments)
{
    m_mode = mode;
    m_nomFitxerMoviments = nomFitxerMoviments;

    m_tauler.inicialitza(nomFitxerTauler);
    m_tauler.actualitzaMovimentsValids();

    if (mode == MODE_JOC_REPLAY)
    {
        std::ifstream fitxer(nomFitxerMoviments.c_str());
        std::string orig, desti;

        while (fitxer >> orig >> desti)
        {
            Moviment m;
            m.afegeiexPosicio(Posicio(orig));
            m.afegeiexPosicio(Posicio(desti));
            m_cua.afegeixMoviment(m);
        }

        fitxer.close();
    }
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    // Dibuixar el tauler i fitxes
    m_tauler.visualitza(m_posicioSeleccionada, m_fitxaSeleccionada);

    // Coordenades del text
    int posTextX = POS_X_TAULER;
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;

    // Mostrar el mode
    std::string msgMode;
    if (m_mode == MODE_JOC_NORMAL)
        msgMode = "Mode: JOC NORMAL";
    else if (m_mode == MODE_JOC_REPLAY)
        msgMode = "Mode: REPLAY";
    else
        msgMode = "Mode: NONE";

    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8f, msgMode);

    // Mostrar jugador del torn
    std::string msgTorn = "Torn: ";
    if (m_jugadorTorn == 0)
        msgTorn += "BLANC";
    else
        msgTorn += "NEGRE";

    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 30, 0.8f, msgTorn);

    // Mostrar posició del ratolí
    std::string posMouse = "Mouse: X=" + std::to_string(mousePosX) + " Y=" + std::to_string(mousePosY);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY + 60, 0.8f, posMouse);

    // Detectar clic
    static bool clicAnterior = false;
    bool clicDetectat = mouseStatus && !clicAnterior;
    clicAnterior = mouseStatus;

    // Convertir posició del ratolí a (fila, col)
    bool dinsTauler = mousePosX >= POS_X_TAULER + CASELLA_INICIAL_X &&
        mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y &&
        mousePosX < POS_X_TAULER + CASELLA_INICIAL_X + NUM_COLS_TAULER * AMPLADA_CASELLA &&
        mousePosY < POS_Y_TAULER + CASELLA_INICIAL_Y + NUM_FILES_TAULER * ALCADA_CASELLA;

    int fila = -1;
    int col = -1;

    if (dinsTauler)
    {
        col = (mousePosX - POS_X_TAULER - CASELLA_INICIAL_X) / AMPLADA_CASELLA;
        fila = (mousePosY - POS_Y_TAULER - CASELLA_INICIAL_Y) / ALCADA_CASELLA;
    }

    // === MODE NORMAL ===
    if (m_mode == MODE_JOC_NORMAL)
    {
        if (clicDetectat && dinsTauler)
        {
            Fitxa* f = m_tauler.getFitxa(fila, col);

            if (!m_fitxaSeleccionada)
            {
                if (!f->esBuida() && f->getColor() == m_jugadorTorn)
                {
                    m_fitxaSeleccionada = true;
                    m_posicioSeleccionada = Posicio(fila, col);
                }
            }
            else
            {
                // Provar de moure
                bool movimentFet = m_tauler.mouFitxa(m_posicioSeleccionada, Posicio(fila, col));
                if (movimentFet)
                {
                    // Guardar moviment
                    Moviment m;
                    m.afegeiexPosicio(m_posicioSeleccionada);
                    m.afegeiexPosicio(Posicio(fila, col));
                    m_cua.afegeixMoviment(m);

                    // Actualitzar
                    m_tauler.actualitzaMovimentsValids();
                    m_fitxaSeleccionada = false;

                    // Comprovar si ha acabat
                    Posicio p;
                    int captures = m_tauler.obtenirMaxCaptures(p);
                    if (captures == 0)
                    {
                        m_fiPartida = true;
                        std::string guanyador = (m_jugadorTorn == 0) ? "BLANC" : "NEGRE";
                        std::string missatge = "Ha guanyat el jugador " + guanyador;
                        GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER, posTextY + 100, 1.0f, missatge);
                        return true;
                    }

                    // Canviar torn
                    m_jugadorTorn = 1 - m_jugadorTorn;
                }
                else
                {
                    // Clic invalid → desseleccionar
                    m_fitxaSeleccionada = false;
                }
            }
        }
    }

    // === MODE REPLAY ===
    else if (m_mode == MODE_JOC_REPLAY)
    {
        if (clicDetectat && dinsTauler)
        {
            if (m_cua.teMoviments())
            {
                Moviment m = m_cua.primerMoviment();
                m_cua.eliminaPrimer();
                m_tauler.mouFitxa(m.getPosicio(0), m.getPosicio(m.getNPosicions() - 1));
                m_tauler.actualitzaMovimentsValids();
                m_jugadorTorn = 1 - m_jugadorTorn;
            }
            else
            {
                GraphicManager::getInstance()->drawFont(FONT_RED_30, POS_X_TAULER, posTextY + 100, 1.0f, "Ja no queden moviments!");
                return true;
            }
        }
    }

    // === PARTIDA ACABADA ===
    if (m_fiPartida)
    {
        return true;
    }

    return false;
}



void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL)
    {
        std::ofstream fitxer(m_nomFitxerMoviments.c_str());

        while (m_cua.teMoviments())
        {
            Moviment m = m_cua.primerMoviment();
            if (m.getNPosicions() >= 2)
            {
                fitxer << m.getPosicio(0).ToString() << " " << m.getPosicio(m.getNPosicions() - 1).ToString() << std::endl;
            }
            m_cua.eliminaPrimer();
        }

        fitxer.close();
    }
}



