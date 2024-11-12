#include <vector>
#include "modele.h"

/* Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclus.
*/
void moveLeftRange(std::vector<int>& t, int startIndex, int endIndex) {
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

/* Rajoute vers la gauche les cases avec les memes valeurs.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclus.
*/
void addLeftValues(std::vector<int>& t) {
    for (int i = 1; i < t.size(); i++) {
        if (t[i] != 0 && t[i-1] == t[i]) {
            int value = t[i] * 2;
            t[i] = 0;
            t[i-1] = value;
            moveLeftRange(t, i, t.size() - 1);
        }
    }
}

/* Fait le mouvement de gauche dans la table.
*/
void moveLeft() {
    for (int i = 0; i < table.size(); i++) {
        moveLeftRange(table[i], 0, 4);
        addLeftValues(table[i]);
    }
}

/* Décale depuis l'indice startIndex jusqu'à l'indice endIndex les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclus.
*/
void moveRightRange(std::vector<int>& t, int startIndex, int endIndex) {
    int first0Index = -1;
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
        }
    }
}

/* Rajoute vers la droite les cases avec les memes valeurs.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclus.
*/
void addRightValues(std::vector<int>& t) {
    for (int i = 0; i < t.size() - 1; i++) {
        if (t[i] != 0 && t[i+1] == t[i]) {
            int value = t[i] * 2;
            t[i] = 0;
            t[i+1] = value;
            moveRightRange(t, 0, i);
        }
    }
}

/* Fait le mouvement de droite dans la table.
*/
void moveRight() {
    for (int i = 0; i < table.size(); i++) {
        moveRightRange(table[i], 0, 4);
        addRightValues(table[i]);
    }
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
*/
void moveDown() {
    tournerTableau();
    moveRight();
    tournerTableau();
}

/* Fait le mouvement de haut dans la table.
*/
void moveUp() {
    tournerTableau();
    moveLeft();
    tournerTableau();
}