#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "modele.h"
#include "graphics.h"
using namespace std;

std::vector<std::vector<int>> table;

/** Fonction pour afficher un tableau d'entiers sur la console.
 * @param line un tableau d'entiers.
 **/
void printLine(const vector<int>& line) {
    cout << "[";
    for (int i = 0; i < table.size(); i++) {
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
void printTable(const vector<vector<int>>& table) {
    cout << "[";
    for (int i = 0; i < table.size(); i++) {
        printLine(table[i]);
        if (i != table.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

/** Fonction qui trouve toutes les indices des tableaux dans lequels des cases sont vides (valeurs égales à 0)
 * @return tableau des uplets : premier valeur l'indice de la ligne et deuxième valeur l'indice dans le tableau de la case vide.
 **/
vector<tuple<int, int>> getEmptySlots() {
    vector<tuple<int, int>> emptySlots;
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == 0) {
                emptySlots.push_back({i, j});
            }
        }
    }
    return emptySlots;
}

/** Fonction qui rajoute un élément de manière aléatoire sur les cases vides de la table.
 */
void setRandomElement() {
    vector<tuple<int, int>> emptySlots = getEmptySlots();
    int k = (int) rand() % emptySlots.size(); /// Choisit un tuple de facon aléatoire
    tuple<int, int> values = emptySlots[k]; // Choisit les indices d'une case vide de ce sous-tableau de facon aléatoire
    int r = rand() % 10; // 90% de Chance d'Ajouter un 2, 10% de Chance d'ajouter un 4.
    table[get<0>(values)][get<1>(values)] = r < 9 ? 2 : 4;
}

/** Retrouve le nombre le plus grand en caractères.
 * @return la plus grande taille des numéros en chaîne de caractères.
 **/
int getMaxTextLenght() {
    int maxValue = 0;
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] > maxValue) {
                maxValue = table[i][j];
            }
        }
    }
    return to_string(k).size(); // Renvoie la longueur de la chaîne de caracteres equvialente a numéro
}

/** Affiche dans la console le tableau à deux dimensions. 
 **/
void printConsole() {
    cout << endl;
    int longMax = getMaxTextLenght();
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            string s = to_string(table[i][j]);
            s.resize(longMax, " ");
            cout << "* " << setw(longMax) << s << " "; //Utilisation setw
        }
        cout << "*" << endl;
    }
    cout << endl;
}

/** Vérifier que la commande est valide à un type de mouvement.
 * @param answer la réponse de l'utilisateur.
 **/
void verifyAnswer(string answer) {
    while (answer != "d" && answer != "g" && answer != "h" && answer != "b") {
        cout << "Votre commande est invalide." << endl;
        cout << "Mouvemant haut : h\nMouvemant bas : b\nMouvemant gauche : g\nMouvemant droite : d\n";
        cout << "Saisir une valeur de mouvement : ";
        cin >> answer;
    }
}

/** Vérifie que la commande de l'utilisateur est un mouvement valide, et réalise le mouvement.
 * @param answer la réponse en string de l'utilisateur en commande.
 **/
void doMovement(string answer) {
    verifyAnswer(answer);
    if (answer == "g") {
       if (canMoveLeft()) {
            moveLeft();
            return;
        }
     } else if (answer == "d") {
        if (canMoveRight()) {
            moveRight();
            return;
        }
    } else if (answer == "h") {
        if (canMoveUp()) {
            moveUp();
            return;
        }
    } else if (answer == "b") {
        if (canMoveDown()) {
            moveDown();
            return;
        }
    }
    cout << "Le mouvement est invalide, saisir un mouvement valide." << endl;
}

/** Commence le jeu en initialisant le tableau, rajoute deux valeurs aléatoires et demande à l'utilisateur les mouvements. 
 **/
void start() {
    table = vector<vector<int>>(4, vector<int>(4, 0));
    for (int i = 0; i < 2; i++) {
        setRandomElement();
    }
    while (true) {
        printConsole();
        string answer;
        cout << "Saisir une valeur de mouvement : ";
        cin >> answer;
        if (canMove()) {
            if (doMovement(answer)) {
                setRandomElement();
            }
        } else {
            cout << "Le jeu est fini! Pas de mouvements possibles.";
            break;
        }
    }
}

int main() {
    srand(time(0));
    start();
    openGame();
    return 0;
}