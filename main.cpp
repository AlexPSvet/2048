#include <iostream>
#include <string>
#include <vector>
#include "modele.h"
using namespace std;

std::vector<std::vector<int>> table;

/* Fonction pour afficher un tableau d'entiers sur la console.
 * @param un tableau d'entiers
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
 * @param un tableau d'entiers à deux dimensions
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

vector<vector<int>> getEmptySlots() {
    vector<vector<int>> emptySlots = vector<vector<int>>(0);
    for (int i = 0; i < table.size(); i++) {
        vector<int> indexEmptySlots = vector<int>(0);
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == 0) {
                indexEmptySlots.push_back(j);
            }
        }
        emptySlots.push_back(indexEmptySlots);
    }
    return emptySlots;
}

void setRandomElement() {
    vector<int> indexWithValues = vector<int>(0);
    vector<vector<int>> emptySlots = getEmptySlots();
    for (int i = 0; i < emptySlots.size(); i++) {
        if (emptySlots[i].size() != 0) {
            indexWithValues.push_back(i);
        }
    }
    int k = (int) rand() % indexWithValues.size();
    int i = indexWithValues[k];
    int j = emptySlots[i][(int) rand() % emptySlots[i].size()];
    table[k][j] = 2;
}

string getText(string caractere, int max) {
    string texte = caractere;
    for (int i = 0; i < max - caractere.size(); i++) {
        texte += ' ';
    }
    return texte;
}

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
            moveLeft(table);
        } else if (answer == "d") {
            moveRight(table);
        } else if (answer == "h") {
            moveUp(table);
        } else if (answer == "b") {
            moveDown(table);
        } else if (answer == "spawn") {
            setRandomElement();
        } else if (answer == "stop") {
            cout << "Stop game." << endl;
            break;
        }
        setRandomElement();
    }
}

int main() {
    srand(time(0));
    start();
    return 0;
}