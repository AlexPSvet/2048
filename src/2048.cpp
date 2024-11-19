#include <iostream>
#include "Game.h"

int main() {
    srand(time(0));

    Game jeu2048;
    system("color 1d"); 
    jeu2048.start();

    return 0;
}