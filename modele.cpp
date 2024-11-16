#include <vector>
#include "modele.h"

/** Tourne toutes les lignes en colonnes d'un tableau.
 **/
void rotateTable() {
    std::vector<std::vector<int>> t2 = table;
    for (int i = 0; i < t2.size(); i++) {
        for (int j = 0; j < t2[i].size(); j++) {
            table[i][j] = t2[j][i];
        }
    }
}

/** Vérifie si pour un mouvement à gauche, il y a soit des espaces vides entre les indices 0 et t.size() exclu, ou des elements proches égaux.
 * @param t le tableau représentant la ligne dans la table.
 * @return b booléen : true si un mouvement peut s'effectuer, false sinon.
 **/
bool canMoveLeftLine(std::vector<int> t) {
    bool isEmpty = true;
    for (int i = 0; i < t.size() - 1; i++) {
        if (t[i] != 0 || t[i+1] != 0) {
            isEmpty = false;
            if (t[i] == t[i+1] || t[i] == 0) {
                return true;
            }
        }
    }
    return isEmpty;
}

/** Vérifie si pour un mouvement à droite, il y a soit des espaces vides entre les indices t.size() - 1 et 1 exclu, ou des elements proches égaux.
 * @param t le tableau représentant la ligne dans la table.
 * @return b booléen : true si un mouvement peut s'effectuer, false sinon.
 **/
bool canMoveRightLine(std::vector<int> t) {
    bool isEmpty = true;
    for (int i = t.size() - 1; i > 0; i--) {
        if (t[i] != 0 || t[i-1] != 0) {
            isEmpty = false;
            if (t[i] == t[i-1] || t[i] == 0) {
                return true;
            }
        }
    }
    return isEmpty;
}

/** Vérifie si des mouvements horizontales peuvent se faire.
 * @return b booléen : true si au moins un mouvement horizontale est possible, false sinon.
 **/
bool canMoveLeft() {
    for (int i = 0; i < table.size(); i++) {
        if (canMoveLeftLine(table[i])) {
            return true;
        }
    }
    return false;
}

/** Vérifie si des mouvements à droite peuvent se faire.
 * @return b booléen : true si au moins un mouvement à droite est possible, false sinon.
 **/
bool canMoveRight() {
    for (int i = 0; i < table.size(); i++) {
        if (canMoveRightLine(table[i])) {
            return true;
        }
    }
    return false;
}

/** Vérifie si des mouvements en haut peuvent se faire.
 * @return b booléen : true si au moins un mouvement en haut est possible, false sinon.
 **/
bool canMoveUp() {
    rotateTable();
    bool b = canMoveLeft();
    rotateTable();
    return b;
}

/** Vérifie si des mouvements en bas peuvent se faire.
 * @return b booléen : true si au moins un mouvement en bas est possible, false sinon.
 **/
bool canMoveDown() {
    rotateTable();
    bool b = canMoveRight();
    rotateTable();
    return b;
}

/** Vérifie si des mouvements horizontales ou verticales peuvent se faire.
 * @return b booléen : true si au moins un mouvement horizontale ou verticale est possible, false sinon.
 **/
bool canMove() {
    return canMoveLeft() || canMoveRight() || canMoveUp() || canMoveDown();
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclu.
 **/
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

/** Rajoute vers la gauche les cases avec les memes valeurs.
 * @param t le tableau.
 **/
void addLeftValues(std::vector<int>& t) {
    int i = 1;
    while (i < t.size()) {
        if (t[i] != 0 && t[i-1] == t[i]) {
            int value = t[i] * 2;
            t[i] = 0;
            t[i-1] = value;
            moveLeftRange(t, i, t.size());
            i += 2;
        } else {
            i++;
        }
    }
}

/** Fait le mouvement de gauche dans la table.
 **/
void moveLeft() {
    for (int i = 0; i < table.size(); i++) {
        moveLeftRange(table[i], 0, table[i].size());
        addLeftValues(table[i]);
    }
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin.
 **/
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

/** Rajoute vers la droite les cases avec les memes valeurs.
 * @param t le tableau.
 **/
void addRightValues(std::vector<int>& t) {
    int i = 0;
    while (i < t.size() - 1) {
        if (t[i] != 0 && t[i+1] == t[i]) {
            int value = t[i] * 2;
            t[i] = 0;
            t[i+1] = value;
            moveRightRange(t, 0, i);
            i += 2;
        } else {
            i++;
        }
    } 
}

/** Fait le mouvement de droite dans la table.
 **/
void moveRight() {
    for (int i = 0; i < table.size(); i++) {
        moveRightRange(table[i], 0, table[i].size());
        addRightValues(table[i]);
    }
}

/** Fait le mouvement de bas dans la table.
 **/
void moveDown() {
    rotateTable();
    moveRight();
    rotateTable();
}

/** Fait le mouvement de haut dans la table.
 **/
void moveUp() {
    rotateTable();
    moveLeft();
    rotateTable();
}