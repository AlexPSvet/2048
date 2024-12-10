#include "Game.h"
using namespace std;

/**
 * Constructeur de la classe Game.
 * Cette classe permet de stocker les classes pour le fonctionnement du jeu, tels
 * que l'interface graphique ou le mode console du terminal, ainsi que pour obtenir
 * le meilleur score du jeu.
 * 
 * @param pathFile : la direction du fichier ou se trouve stockée le meilleur score.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 */
Game::Game(string pathFile) : pathFile(pathFile), model(Model(4, 4)), graphics(Graphics(model)), console(Console(model)) {}

/**
 * Fonction pour chercher dans un fichier le meilleur score.
 * 
 * @param pathFile : la direction du fichier ou se trouve le meilleur score.
 * @return bestScore : le meilleur score du joueur.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 */
int Game::getBestScoreFile(string pathFile) {
    ifstream scoreFile;
    scoreFile.open(pathFile);
    if ( scoreFile ) {
        string text;
        scoreFile >> text;
        scoreFile.close();
        istringstream entier( text );
        int bestScore;
        entier >> bestScore;
        return bestScore;
    } else {
        cerr << "Erreur : fichier non valide ou indisponibe au programme." << endl;
        return 0;
    }
}

/**
 * Fonction pour chercher dans un fichier le meilleur score.
 * 
 * @param bestScore : le meilleur score du joueur.
 * @param pathFile : la direction du fichier ou se trouve le meilleur score.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 */
void Game::setBestScoreFile(int bestScore, string pathFile) {
    ofstream scoreFile;
    scoreFile.open(pathFile);
    if ( scoreFile ) {
        scoreFile << bestScore;
        scoreFile.close();
    } else {
        cerr << "Erreur : fichier non valide ou indisponibe au programme." << endl;
    }
}

/** 
 * Fonction pour commencer le jeu. Demande à l'utilisateur
 * quel mode de jeu utiliser avant de l'initialiser. (Terminale ou console).
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Game::start() {
    model.restart();
    while (true) {
        cout << "Saisir le mode d'interface du jeu (interface, terminale): ";
        model.setBestScore(getBestScoreFile(pathFile));
        string ans;
        cin >> ans;
        if (ans == "interface") {
            // Initialise la bibliothèque SFML ainsi que l'interface graphique.
            graphics.displayGame();
        } else if (ans == "terminale") {
            // Initialise la bibliothèque ncurses ainsi que la terminale du jeu.
            console.displayGame();
        }
        setBestScoreFile(model.getBestScore(), pathFile);
        model.restart();
    }
}

// FONCTIONS GET

Model& Game::getModel() {
    return model;
}

Graphics& Game::getGraphics() {
    return graphics;
}

Console& Game::getConsole() {
    return console;
}