#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Game.h"
using namespace std;

// Class constructor
Game::Game() : plateau(vector<vector<int>>(4, vector<int>(4, 0))), score(0) {}    

/** Fonction pour afficher un tableau d'entiers sur la console.
 * @param line un tableau d'entiers.
 **/
void Game::printLine(const vector<int>& line) {
    cout << "[";
    for (int i = 0; i < plateau.size(); i++) {
        cout << line[i];
        if (i != line.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

/** Fonction pour afficher un tableau d'entiers à deux dimensions sur la console.
 * @param t un tableau d'entiers à deux dimensions
 **/
void Game::printTable(const vector<vector<int>>& plateau) {
    cout << "[";
    for (int i = 0; i < plateau.size(); i++) {
        printLine(plateau[i]);
        if (i != plateau.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

/** Retrouve le nombre le plus grand en caractères.
 * @return maxValue la plus grande taille des numéros en chaîne de caractères.
 **/
int Game::getMaxTextLenght() {
    int maxValue = 0;
    for (int i = 0; i < plateau.size(); i++) {
        for (int j = 0; j < plateau[i].size(); j++) {
            if (plateau[i][j] > maxValue) {
                maxValue = plateau[i][j];
            }
        }
    }
    return to_string(maxValue).size(); // Renvoie la longueur de la chaîne de caracteres equvialente a numéro
}

/** Affiche dans la console le tableau à deux dimensions. 
 **/
void Game::printConsole() {
    cout << endl;
    int longMax = getMaxTextLenght();
    for (int i = 0; i < plateau.size(); i++) {
        for (int j = 0; j < plateau[i].size(); j++) {
            cout << " * " << setw(longMax) << plateau[i][j] << " "; // Utilisation setw
        }
        cout << "*" << endl;
    }
    cout << endl;
}

/** Vérifier que la commande est valide à un type de mouvement.
 * @return answer la réponse vérifiée de l'utilisateur.
 **/
string Game::verifyAnswer() {
    string answer;
    cout << "Saisir une valeur de mouvement : ";
    cin >> answer;
    while (answer != "d" && answer != "g" && answer != "h" && answer != "b") {
        cout << "Votre commande est invalide." << endl;
        printConsole();
        cout << "Mouvemant haut : h\nMouvemant bas : b\nMouvemant gauche : g\nMouvemant droite : d\n" << endl;
        cout << "Saisir une valeur de mouvement : ";
        cin >> answer;
    }
    return answer;
}

/** Vérifie que la commande de l'utilisateur est un mouvement valide, et réalise le mouvement.
 **/
bool Game::validMovement() {
    string answer = verifyAnswer();
    if (answer == "g") {
       if (canMoveLeft()) {
            moveLeft();
            return true;
        }
    } else if (answer == "d") {
        if (canMoveRight()) {
            moveRight();
            return true;
        }
    } else if (answer == "h") {
        if (canMoveUp()) {
            moveUp();
            return true;
        }
    } else if (answer == "b") {
        if (canMoveDown()) {
            moveDown();
            return true;
        }
    }
    cout << "Le mouvement est invalide, saisir un mouvement valide." << endl;
    return false;
}

/** Commence le jeu en initialisant le tableau, rajoute deux valeurs aléatoires et demande à l'utilisateur les mouvements. 
 **/
void Game::start() {
    setRandomElements(2);
    while (true) {
        printConsole();
        if (canMove()) {
            if (validMovement()) {
                setRandomElements(1);
            }
        } else {
            cout << "Le jeu est fini! Pas de mouvements possibles." << endl;
            return;
        }
    }
}

vector<vector<int>>& Game::getPlateau() {
    return plateau;
}

int Game::getScore() {
    return score;
}