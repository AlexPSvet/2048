#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "modele.h"
using namespace std;

std::vector<std::vector<int>> table;

/* Fonction pour afficher un tableau d'entiers sur la console.
 * @param t un tableau d'entiers
 */
void afficherTableau(vector<int> tableau) {
    cout << "[";
    for (int i = 0; i < tableau.size(); i++) {
        cout << i;
        if (i != tableau.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

/* Fonction pour afficher un tableau d'entiers à deux dimensions sur la console.
 * @param t un tableau d'entiers à deux dimensions
 */
void afficherTableau(vector<vector<int>> tableau) {
    cout << "[";
    for (int i = 0; i < tableau.size(); i++) {
        afficherTableau(tableau[i]);
        if (i != tableau.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

/* Fonction qui trouve toutes les indices des tableaux dans lequels des cases sont vides (valeurs égales à 0)
 * @return map un map avec les indices dans chaque tableau avec des cases vides
 */
map<int, vector<int>> getEmptySlots() {
    map<int, vector<int>> emptySlots;
    for (int i = 0; i < table.size(); i++) {
        vector<int> indexEmptySlots = vector<int>(0);
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == 0) {
                indexEmptySlots.push_back(j);
            }
        }
        if (indexEmptySlots.size() != 0) {
            emptySlots[i] = indexEmptySlots;
        }
    }
    return emptySlots;
}

/* 
 * Fonction qui rajoute un élément de manière aléatoire 
 * sur les cases vides de la table.
 */
void setRandomElement() {
    map<int, vector<int>> emptySlots = getEmptySlots();
    int k = (int) rand() % emptySlots.size();
    int j = emptySlots[k][(int) rand() % emptySlots[k].size()];
    int r = rand() % 9;
    table[k][j] = r < 9 ? 2 : 4;
}

/* Fonction pour ajuster une chaîne de caracteres d'une taille spécifique.
 * @param la chaîne de caracteres.
 * @param taille de la chaîne de caractères.
 * @return la chaîne de caractères avec la taille.
 */
string getText(string caractere, int max) {
    string texte = caractere;
    for (int i = 0; i < max - caractere.size(); i++) {
        texte += ' ';
    }
    return texte;
}

/* Retrouve le nombre le plus grand en caractères.
 * @return la plus grande taille des numéros en chaîne de caractères.
 */
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

/*
 * Affiche dans la console le tableau à deux dimensions.
 */
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

/*
 * Commence le jeu en initialisant le tableau, rajoute deux valeurs
 * aléatoires et demande à l'utilisateur les mouvements.
 */
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
        if (answer == "g") {
            moveLeft();
            setRandomElement();
        } else if (answer == "d") {
            moveRight();
            setRandomElement();
        } else if (answer == "h") {
            moveUp();
            setRandomElement();
        } else if (answer == "b") {
            moveDown();
            setRandomElement();
        } else if (answer == "stop") {
            cout << "Stop game." << endl;
            break;
        } else {
            cout << endl << "Votre commande est invalide." << endl;
            cout << "Mouvemant haut : h" << endl;
            cout << "Mouvemant bas : b" << endl;
            cout << "Mouvemant gauche : g" << endl;
            cout << "Mouvemant droite : d" << endl;
        }  
    }
}

int main() {
    srand(time(0));
    start();
    return 0;
}