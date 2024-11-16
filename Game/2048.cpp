#include <iostream>
#include <string>
#include <vector>
#include "modele.h"
using namespace std;

std::vector<std::vector<int>> table;

/** Fonction pour afficher un tableau d'entiers sur la console.
 * @param t un tableau d'entiers.
 **/
void printTable(vector<int> table) {
    cout << "[";
    for (int i = 0; i < table.size(); i++) {
        cout << i;
        if (i != table.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

/** Fonction pour afficher un tableau d'entiers à deux dimensions sur la console.
 * @param t un tableau d'entiers à deux dimensions
 **/
void printTable(vector<vector<int>> table) {
    cout << "[";
    for (int i = 0; i < table.size(); i++) {
        printTable(table[i]);
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
    int k = (int) rand() % emptySlots.size();
    tuple<int, int> values = emptySlots[k];
    int r = rand() % 9;
    table[get<0>(values)][get<1>(values)] = r < 9 ? 2 : 4;
}

/** Fonction pour ajuster une chaîne de caracteres d'une taille spécifique.
 * @param caractere la chaîne de caracteres.
 * @param t la taille que la chaîne de caractères doi avoir
 * @return la chaîne de caractères avec la taille.
 **/
string getText(string caractere, int t) {
    string texte = caractere;
    for (int i = 0; i < t - caractere.size(); i++) {
        texte += ' ';
    }
    return texte;
}

/** Retrouve le nombre le plus grand en caractères.
 * @return la plus grande taille des numéros en chaîne de caractères.
 **/
int getMaxTextLenght() {
    int k = 0;
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            if(k < table[i][j]) {
                k = table[i][j];
            }
        }
    }
    return to_string(k).size();
}

/** Affiche dans la console le tableau à deux dimensions. 
 **/
void printConsole() {
    cout << endl;
    int longMax = getMaxTextLenght();
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size(); j++) {
            cout << "* " << getText(to_string(table[i][j]), longMax) << " ";
        }
        cout << "*" << endl;
    }
    cout << endl;
}

/** Vérifie que la commande de l'utilisateur est un mouvement valide, et réalise le mouvement.
 * @param answer la réponse en string de l'utilisateur en commande.
 **/
bool doMovement(string answer) {
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
    } else {
        cout << endl << "Votre commande est invalide." << endl;
        cout << "Mouvemant haut : h" << endl;
        cout << "Mouvemant bas : b" << endl;
        cout << "Mouvemant gauche : g" << endl;
        cout << "Mouvemant droite : d" << endl;
        return false;
    }
    cout << "Le mouvement est invalide, saisir un mouvement valide." << endl;
    return false;
}

/** Commence le jeu en initialisant le tableau, rajoute deux valeurs aléatoires et demande à l'utilisateur les mouvements. 
 **/
void start() {
    table = vector<vector<int>>(4);
    for (int i = 0; i < 4; i++) {
        table[i] = {0, 0, 0, 0};
    }
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
    return 0;
}