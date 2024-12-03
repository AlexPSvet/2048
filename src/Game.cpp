#include "Game.h"
using namespace std;

// Class constructor
Game::Game(string pathFile) : pathFile(pathFile), model(Model(4, 4)), graphics(Graphics(model)), console(Console(model)) {}

int Game::getBestScoreFile() {
    ifstream scoreFile;
    scoreFile.open(pathFile);
    if ( scoreFile ) {
        string text;
        scoreFile >> text;
        scoreFile.close();
        istringstream entier( text );
        int value;
        entier >> value;
        return value;
    } else {
        cerr << "Erreur: fichier non valide ou indisponible au programme";
        return 0;
    }
}

void Game::setBestScoreFile(int bestScore) {
    ofstream scoreFile;
    scoreFile.open(pathFile);
    if ( scoreFile ) {
        scoreFile << bestScore;
        scoreFile.close();
    } else {
        cerr << "Erreur: fichier non valide ou indisponible au programme";
    }
}

/** Commence le jeu en initialisant le tableau, rajoute deux valeurs 
 * aléatoires et demande à l'utilisateur les mouvements. 
 **/
void Game::start() {
    model.restart();
    while (true) {
        cout << "Game type (screen, console): ";
        model.setBestScore(getBestScoreFile());
        string ans;
        cin >> ans;
        if (ans == "screen") {
            graphics.displayGame();
        } else if (ans == "console") {
            console.displayGame();
        }
        setBestScoreFile(model.getBestScore());
        model.restart();
    }
}

Model& Game::getModel() {
    return model;
}

Graphics& Game::getGraphics() {
    return graphics;
}

Console& Game::getConsole() {
    return console;
}