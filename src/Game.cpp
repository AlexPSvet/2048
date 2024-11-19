#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
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

    cout << "Score actuel: " << score << endl;

    string border = "";
    for (int a = 0; a < plateau[0].size(); a++){
        border += string(longMax + 3, '*'); //Ajoute une séquence de (longMax + 4) caracteres '*'
    }

    for (int i = 0; i < plateau.size(); i++) {
        cout << border << '*' << endl;
        for (int j = 0; j < plateau[i].size(); j++) {
            cout << "* " << setw(longMax) << plateau[i][j] << " "; // Utilisation setw
        }
        cout << "*" << endl;
    }
    cout << border << '*' << endl;
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
    if (answer == "g"){
        if (canMoveLeft()){
            moveLeft();
            return true;
        }
    } else if (answer == "d"){
        if (canMoveRight()){
            moveRight();
            return true;
        }
    } else if (answer == "h"){
        if (canMoveUp()){
            moveUp();
            return true;
        }
    } else if (answer == "b"){
        if (canMoveDown()){
            moveDown();
            return true;
        }
    }
    cout << "La mouvement saisi est invalide. Saisir un mouvement valide: ";
    return false;
}

/** Commence le jeu en initialisant le tableau, rajoute deux valeurs aléatoires et demande à l'utilisateur les mouvements. 
 **/
void Game::start() {
    setRandomElements(2);
    printConsole();
    displayWindow();
    /*
    while (true) {
        if (canMove()) {
            if (validMovement()) {
                setRandomElements(1);
                printConsole();
            }
        } else {
            cout << "Le jeu est fini! Pas de mouvements possibles." << endl;
            cout << "Score final: " << score << endl;        //Affiche le score final
            return;
        }
    }
    */
}

vector<vector<int>>& Game::getPlateau() {
    return plateau;
}

int Game::getScore() {
    return score;
}