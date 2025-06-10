#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"

#include </Ingenieria Informática/ProjecteDamesMP/2. Platforms/0. Windows Desktop/extlibs/SDL/include/SDL.h>
#include <iostream>
#include "joc.hpp"
#include "info_joc.hpp"

int main(int argc, const char* argv[])
{
    // Instruccions per inicialitzar SDL
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    // Crear la pantalla gràfica
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    pantalla.show();

    // Crear el joc
    Joc joc;

    // 🟢 TRIA MANUAL DEL MODE (puedes cambiar esto a REPLAY si quieres)
    int mode = MODE_JOC_NORMAL; // O MODE_JOC_REPLAY
    std::string fitxerTauler = "data/tauler.txt";
    std::string fitxerMoviments = "data/moviments.txt";

    // Inicialitzar el joc amb els fitxers
    joc.inicialitza(mode, fitxerTauler, fitxerMoviments);

    bool acabat = false;

    // Bucle principal del joc
    do
    {
        pantalla.processEvents();

        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        bool mouseStatus = Mouse_getBtnLeft();

        acabat = joc.actualitza(mousePosX, mousePosY, mouseStatus);

        pantalla.update();
    } while (!acabat && !Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));

    // Al finalitzar, guardar els moviments si toca
    joc.finalitza();

    // Tancar SDL
    SDL_Quit();

    return 0;
}
