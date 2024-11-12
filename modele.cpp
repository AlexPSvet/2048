#include <vector>
#include "modele.h"

/* Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclu.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool moveLeftRange(std::vector<int>& t, int startIndex, int endIndex) {
    int first0Index = -1;
    bool isMoved = false;
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
            isMoved = true;
        }
    }
    return isMoved;
}

/* Rajoute vers la gauche les cases avec les memes valeurs.
 * @param t le tableau.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool addLeftValues(std::vector<int>& t) {
    bool isMoved = false;
    int i = 1;
    while (i < t.size()) {
        if (t[i] != 0 && t[i-1] == t[i]) {
            int value = t[i] * 2;
            t[i] = 0;
            t[i-1] = value;
            isMoved = true;
            moveLeftRange(t, i, t.size());
            i += 2;
        } else {
            i++;
        }
    }
    return isMoved;
}

/* Fait le mouvement de gauche dans la table.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool moveLeft() {
    bool isMoved = false;
    for (int i = 0; i < table.size(); i++) {
        bool b1 = moveLeftRange(table[i], 0, table[i].size());
        bool b2 = addLeftValues(table[i]);
        isMoved = b1 || b2;  
    }
    return isMoved;
}

/* Décale depuis l'indice startIndex jusqu'à l'indice endIndex les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool moveRightRange(std::vector<int>& t, int startIndex, int endIndex) {
    int first0Index = -1;
    bool isMoved = false;
    for (int i = endIndex; i >= startIndex; i--) {
        if (t[i] == 0) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            int value = t[i];
            t[i] = 0;
            t[first0Index] = value;
            first0Index -= 1;
            isMoved = true;
        }
    }
    return isMoved;
}

/* Rajoute vers la droite les cases avec les memes valeurs.
 * @param t le tableau.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool addRightValues(std::vector<int>& t) {
    bool isMoved = false;
    int i = 0;
    while (i < t.size() - 1) {
        if (t[i] != 0 && t[i+1] == t[i]) {
            int value = t[i] * 2;
            t[i] = 0;
            t[i+1] = value;
            isMoved = true;
            moveRightRange(t, 0, i);
            i += 2;
        } else {
            i++;
        }
    } 
    return isMoved;
}

/* Fait le mouvement de droite dans la table.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool moveRight() {
    bool isMoved = false;
    for (int i = 0; i < table.size(); i++) {
        bool b1 = moveRightRange(table[i], 0, table[i].size() - 1);
        bool b2 = addRightValues(table[i]);
        isMoved =  b1 || b2;
    }
    return isMoved;
}

/* Tourne toutes les lignes en colonnes d'un tableau.
 */
void tournerTableau() {
    std::vector<std::vector<int>> t2 = table;
    for (int i = 0; i < t2.size(); i++) {
        for (int j = 0; j < t2[i].size(); j++) {
            table[i][j] = t2[j][i];
        }
    }
}

/* Fait le mouvement de bas dans la table.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool moveDown() {
    tournerTableau();
    bool b = moveRight();
    tournerTableau();
    return b;
}

/* Fait le mouvement de haut dans la table.
 * @return true si un mouvement est réalisée, false sinon.
 */
bool moveUp() {
    tournerTableau();
    bool b = moveLeft();
    tournerTableau();
    return b;
}