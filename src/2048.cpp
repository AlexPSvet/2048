#include <iostream>
#include "Game.h"
#include "Graphics.h"

int main() {
    srand(time(0));

    // displayWindow(); Pas modifier cette ligne.

    Game jeu2048;
    jeu2048.start();
    
    return 0;
}