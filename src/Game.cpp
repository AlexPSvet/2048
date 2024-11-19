#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Game.h"
using namespace std;

vector<vector<int>> Jeu::getPlateau() {
    return plateau;
}

/** Fonction pour afficher un tableau d'entiers sur la console.
 * @param line un tableau d'entiers.
 **/
void Jeu::printLine(const vector<int>& line) {
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
void Jeu::printTable(const vector<vector<int>>& plateau) {
    cout << "[";
    for (int i = 0; i < plateau.size(); i++) {
        printLine(plateau[i]);
        if (i != plateau.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

/** Fonction qui identifie les indices des cases vides (valeurs égales à 0) dans un tableau d'uplets.
 * @return tableau des uplets : premier valeur l'indice du tableau et deuxième valeur l'indice dans le tableau de la case vide.
 **/
vector<tuple<int, int>> Jeu::getEmptySlots() {
    vector<tuple<int, int>> emptySlots;
    for (int i = 0; i < plateau.size(); i++) {
        for (int j = 0; j < plateau[i].size(); j++) {
            if (plateau[i][j] == 0) {
                emptySlots.push_back({i, j});
            }
        }
    }
    return emptySlots;
}

/** Fonction qui rajoute un élément de manière aléatoire sur les cases vides de la table.
 */
void Jeu::setRandomElements(int amount) {
    for (int i = 0; i < amount; i++) {
        vector<tuple<int, int>> emptySlots = getEmptySlots();
        int k = (int) rand() % emptySlots.size(); /// Choisit un tuple de facon aléatoire
        tuple<int, int> values = emptySlots[k]; // Choisit les indices d'une case vide de ce sous-tableau de facon aléatoire
        int r = rand() % 10; // 90% de Chance d'Ajouter un 2, 10% de Chance d'ajouter un 4.
        plateau[get<0>(values)][get<1>(values)] = r < 9 ? 2 : 4;
    }
}

/** Retrouve le nombre le plus grand en caractères.
 * @return maxValue la plus grande taille des numéros en chaîne de caractères.
 **/
int Jeu::getMaxTextLenght() {
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
void Jeu::printConsole() {
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
string Jeu::verifyAnswer() {
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

/** Vérifie que la commande de l'utilisateur est un mouvement valide, et réalise le mouvement en affichant le score.
**/
bool Jeu::validMovement(){
    string answer = verifyAnswer();
    if (answer == "g"){
        if (canMoveLeft()){
            moveLeft();
            printScore();
            return true;
        }
    } else if (answer == "d"){
        if (canMoveRight()){
            moveRight();
            printScore();
            return true;
        }
    } else if (answer == "h"){
        if (canMoveUp()){
            moveUp();
            printScore();
            return true;
        }
    } else if (answer == "b"){
        if (canMoveDown()){
            moveDown();
            printScore();
            return true;
        }
    } "La mouvement saisi est invalide. Saisir un mouvement valide: ";
    return false;
}

/** Commence le jeu en initialisant le tableau, rajoute deux valeurs aléatoires et demande à l'utilisateur les mouvements. 
 **/
void Jeu::start() {
    setRandomElements(2);
    cout << "Bonjour" << endl;
    printConsole();
    cout << "Coucuu" << endl;
    printScore(); //Affiche le score Initialisé a 0
    cout << "Oke" << endl;
    while (true) {
        printConsole();
        printScore();
        if (canMove()) {
            if (validMovement()) {
                setRandomElements(1);
                printConsole();
                printScore();
            }
        } else {
            cout << "Le jeu est fini! Pas de mouvements possibles." << endl;
            cout << "Score final: " << score << endl;        //Affiche le score final
            return;
        }
    }
}