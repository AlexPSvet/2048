#include <vector>
#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

Jeu::Jeu() : plateau(vector<vector<int>>(4, vector<int>(4, 0))), score(0) {}

/** Affiche le score actuel
**/
void Jeu::printScore() {
    cout << "Score actuel: " << score << endl;
}

/** Tourne toutes les lignes en colonnes d'un tableau.
 **/
void Jeu::rotateTable() {
    vector<vector<int>> t2 = plateau;
    for (int i = 0; i < t2.size(); i++) {
        for (int j = 0; j < t2[i].size(); j++) {
            plateau[i][j] = t2[j][i];
        }
    }
}

/** Vérifie si des mouvements horizontales peuvent se faire.
 * @return b booléen : true si au moins un mouvement horizontale est possible, false sinon.
 **/
bool Jeu::canMoveLeft() {
    for (int i = 0; i < plateau.size(); i++) {
        vector<int> t = plateau[i];
        for (int j = 0; j < t.size() - 1; j++) {
            if ((t[j] != 0 || t[j+1] != 0) && (t[j] == t[j+1] || t[j] == 0)) {
                return true;
            }
        }
    }
    return false;
}

/** Vérifie si des mouvements à droite peuvent se faire.
 * @return b booléen : true si au moins un mouvement à droite est possible, false sinon.
 **/
bool Jeu::canMoveRight() {
    for (int i = 0; i < plateau.size(); i++) {
        vector<int> t = plateau[i];
        for (int j = plateau[i].size() - 1; j > 0; j--) {
            if ((t[j] != 0 || t[j-1] != 0) && (t[j] == t[j-1] || t[j] == 0)) {
                return true;
            }
        }
    }
    return false;
}

/** Vérifie si des mouvements en haut peuvent se faire.
 * @return b booléen : true si au moins un mouvement en haut est possible, false sinon.
 **/
bool Jeu::canMoveUp() {
    rotateTable();
    bool b = canMoveLeft();
    rotateTable();
    return b;
}

/** Vérifie si des mouvements en bas peuvent se faire.
 * @return b booléen : true si au moins un mouvement en bas est possible, false sinon.
 **/
bool Jeu::canMoveDown() {
    rotateTable();
    bool b = canMoveRight();
    rotateTable();
    return b;
}

/** Vérifie si des mouvements horizontales ou verticales peuvent se faire.
 * @return b booléen : true si au moins un mouvement horizontale ou verticale est possible, false sinon.
 **/
bool Jeu::canMove() {
    return canMoveLeft() || canMoveRight() || canMoveUp() || canMoveDown();
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclu.
 **/
void Jeu::moveLeftRange(vector<int>& t, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = startIndex; i < endIndex; i++) {
        if (t[i] == 0) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            int value = t[i];
            t[i] = 0;
            t[first0Index] = value;
            first0Index += 1;
        }
    }
}

/** Rajoute vers la gauche les cases avec les memes valeurs.
 * @param t le tableau.
 **/
void Jeu::addLeftValues(vector<int>& t) {
    int i = 0;
    while (i < t.size() - 1) {
        if (t[i] != 0 && t[i+1] == t[i]) {
            int value = t[i] * 2;
            score += value;
            cout << "Updated Score: " << score << endl;                //Mise a jour du score
            t[i+1] = 0;
            t[i] = value;
            moveLeftRange(t, i+1, t.size());
        }
        i++;
    }
}

/** Fait le mouvement de gauche dans la table.
 **/
void Jeu::moveLeft() {
    for (int i = 0; i < plateau.size(); i++) {
        moveLeftRange(plateau[i], 0, plateau[i].size());
        addLeftValues(plateau[i]);
    }
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin.
 **/
void Jeu::moveRightRange(vector<int>& t, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = endIndex - 1; i >= startIndex; i--) {
        if (t[i] == 0) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            int value = t[i];
            t[i] = 0;
            t[first0Index] = value;
            first0Index -= 1;
        }
    }
}

/** Rajoute vers la droite les cases avec les memes valeurs.
 * @param t le tableau.
 **/
void Jeu::addRightValues(vector<int>& t) {
    int i = t.size() - 1;
    while (i > 0) {
        if (t[i] != 0 && t[i-1] == t[i]) {
            int value = t[i] * 2;
            score += value;                 ////Mise a jour du score
            cout << "Updated Score: " << score << endl; 
            t[i-1] = 0;
            t[i] = value;
            moveRightRange(t, 0, i);
        } 
        i--;
    } 
}

/** Fait le mouvement de droite dans la table.
 **/
void Jeu::moveRight() {
    for (int i = 0; i < plateau.size(); i++) {
        moveRightRange(plateau[i], 0, plateau[i].size());
        addRightValues(plateau[i]);
    }
}

/** Fait le mouvement de bas dans la table.
 **/
void Jeu::moveDown() {
    rotateTable();
    moveRight();
    rotateTable();
}

/** Fait le mouvement de haut dans la table.
 **/
void Jeu::moveUp() {
    rotateTable();
    moveLeft();
    rotateTable();
}