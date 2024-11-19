#include <vector>
#include <iostream>
#include <string>
#include "Game.h"
using namespace std;

Game::Game() : plateau(vector<vector<int>>(4, vector<int>(4, 0))), score(0) {}    

/** Affiche le score actuel
**/
void Game::printScore() {
    cout << "Score actuel: " << score << endl;
}

/** Tourne toutes les lignes en colonnes d'un tableau.
 **/
void Game::rotateTable() {
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
bool Game::canMoveLeft() {
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
bool Game::canMoveRight() {
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
bool Game::canMoveUp() {
    rotateTable();
    bool b = canMoveLeft();
    rotateTable();
    return b;
}

/** Vérifie si des mouvements en bas peuvent se faire.
 * @return b booléen : true si au moins un mouvement en bas est possible, false sinon.
 **/
bool Game::canMoveDown() {
    rotateTable();
    bool b = canMoveRight();
    rotateTable();
    return b;
}

/** Vérifie si des mouvements horizontales ou verticales peuvent se faire.
 * @return b booléen : true si au moins un mouvement horizontale ou verticale est possible, false sinon.
 **/
bool Game::canMove() {
    return canMoveLeft() || canMoveRight() || canMoveUp() || canMoveDown();
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param t tableau représentant la ligne de la table.
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclu.
 **/
void Game::moveLeftRange(vector<int>& t, int startIndex, int endIndex) {
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
void Game::addLeftValues(vector<int>& t) {
    int i = 0;
    while (i < t.size() - 1) {
        if (t[i] != 0 && t[i+1] == t[i]) {
            int value = t[i] * 2;
            score += value;                 //Mise a jour du score
            t[i+1] = 0;
            t[i] = value;
            moveLeftRange(t, i+1, t.size());
        }
        i++;
    }
}

/** Fait le mouvement de gauche dans la table.
 **/
void Game::moveLeft() {
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
void Game::moveRightRange(vector<int>& t, int startIndex, int endIndex) {
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
void Game::addRightValues(vector<int>& t) {
    int i = t.size() - 1;
    while (i > 0) {
        if (t[i] != 0 && t[i-1] == t[i]) {
            int value = t[i] * 2;
            score += value;                 ////Mise a jour du score
            t[i-1] = 0;
            t[i] = value;
            moveRightRange(t, 0, i);
        } 
        i--;
    } 
}

/** Fait le mouvement de droite dans la table.
 **/
void Game::moveRight() {
    for (int i = 0; i < plateau.size(); i++) {
        moveRightRange(plateau[i], 0, plateau[i].size());
        addRightValues(plateau[i]);
    }
}

/** Fait le mouvement de bas dans la table.
 **/
void Game::moveDown() {
    rotateTable();
    moveRight();
    rotateTable();
}

/** Fait le mouvement de haut dans la table.
 **/
void Game::moveUp() {
    rotateTable();
    moveLeft();
    rotateTable();
}

/** Fonction qui identifie les indices des cases vides (valeurs égales à 0) dans un tableau d'uplets.
 * @return tableau des uplets : premier valeur l'indice du tableau et deuxième valeur l'indice dans le tableau de la case vide.
 **/
vector<tuple<int, int>> Game::getEmptySlots() {
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
void Game::setRandomElements(int amount) {
    for (int i = 0; i < amount; i++) {
        vector<tuple<int, int>> emptySlots = getEmptySlots();
        int k = (int) rand() % emptySlots.size(); /// Choisit un tuple de facon aléatoire
        tuple<int, int> values = emptySlots[k]; // Choisit les indices d'une case vide de ce sous-tableau de facon aléatoire
        int r = rand() % 10; // 90% de Chance d'Ajouter un 2, 10% de Chance d'ajouter un 4.
        plateau[get<0>(values)][get<1>(values)] = r < 9 ? 2 : 4;
    }
}