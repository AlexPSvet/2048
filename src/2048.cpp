#include <iostream>
#include "Game.h"

int main() {
    srand(time(0));

    // Initialiser le jeu avec le fichier de score.txt.
    Game jeu2048("score.txt");
    jeu2048.start();

    return 0;
}