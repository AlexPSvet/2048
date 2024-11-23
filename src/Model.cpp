#include <vector>
#include <iostream>
#include <string>
#include "Model.h"
using namespace std;

Model::Model() {
    lines = 0;
    columns = 0;
}

Model::Model(int lines, int columns) {
    this->lines = lines;
    this->columns = columns;
    clear();
}

bool Model::canMoveGeneral(int i1, int j1, int i2, int j2) {
    if (validCase(i1, j1) && validCase(i2, j2)) {
        int value1 = getCase(i1, j1).getValue();
        int value2 = getCase(i2, j2).getValue();
        if (value1 == value2) {
            return true;
        }
    } else if (!validCase(i1, j1)) {
        return true;
    }
    return false;
}

/** Vérifie si des mouvements horizontales peuvent se faire.
 * @return b booléen : true si au moins un mouvement horizontale est possible, false sinon.
 **/
bool Model::canMoveLeft() {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns - 1; j++) {
            if (validCase(i, j) && validCase(i, j + 1)) {
                int value1 = getCase(i, j).getValue();
                int value2 = getCase(i, j + 1).getValue();
                if (value1 == value2) {
                    return true;
                }
            } else if (!validCase(i, j) && validCase(i, j + 1)) {
                return true;
            }
        }
    }
    return false;
}

/** Vérifie si des mouvements à droite peuvent se faire.
 * @return b booléen : true si au moins un mouvement à droite est possible, false sinon.
 **/
bool Model::canMoveRight() {
    for (int i = 0; i < lines; i++) {
        for (int j = columns - 1; j > 0; j--) {
            if (validCase(i, j) && validCase(i, j - 1)) {
                int value1 = getCase(i, j).getValue();
                int value2 = getCase(i, j - 1).getValue();
                if (value1 == value2) {
                    return true;
                }
            } else if (!validCase(i, j) && validCase(i, j - 1)) {
                return true;
            }
        }
    }
    return false;
}

/** Vérifie si des mouvements en haut peuvent se faire.
 * @return b booléen : true si au moins un mouvement en haut est possible, false sinon.
 **/
bool Model::canMoveUp() {
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < lines - 1; i++) {
            if (validCase(i, j) && validCase(i + 1, j)) {
                int value1 = getCase(i, j).getValue();
                int value2 = getCase(i + 1, j).getValue();
                if (value1 == value2) {
                    return true;
                }
            } else if (!validCase(i, j) && validCase(i + 1, j)) {
                return true;
            }
        }
    }
    return false;
}

/** Vérifie si des mouvements en bas peuvent se faire.
 * @return b booléen : true si au moins un mouvement en bas est possible, false sinon.
 **/
bool Model::canMoveDown() {
    for (int j = 0; j < columns; j++) {
        for (int i = lines - 1; i > 0; i--) {
            if (validCase(i, j) && validCase(i - 1, j)) {
                int value1 = getCase(i, j).getValue();
                int value2 = getCase(i - 1, j).getValue();
                if (value1 == value2) {
                    return true;
                }
            } else if (!validCase(i, j) && validCase(i - 1, j)) {
                return true;
            }
        }
    }
    return false;
}

/** Vérifie si des mouvements horizontales ou verticales peuvent se faire.
 * @return b booléen : true si au moins un mouvement horizontale ou verticale est possible, false sinon.
 **/
bool Model::canMove() {
    return canMoveLeft() || canMoveRight() || canMoveUp() || canMoveDown();
}

/*
void Model::moveRangeGeneral(int i1, int j1, int i2, int j2) {
    Case& caseObjet1 = getCase(i1, j1);
    int value = caseObjet1.getValue();
    Case caseObjet0(i2, j2);
    MoveEvent event(value, -1, i1, j1, i2, j2);
    caseObjet1.addAnimation(event);
    caseObjet0.addAnimations(caseObjet1);
    removeCase(caseObjet1);
    caseObjet0.setValue(value);
    cases.push_back(caseObjet0);
}
*/

/*
bool Model::addValues(int i1, int j1, int i2, int j2) {
    if (validCase(i1, j1) && validCase(i2, j2)) {
        Case& caseObjet1 = getCase(i1, j1);
        Case& caseObjet2 = getCase(i2, j2);
        if (caseObjet1.getValue() == caseObjet2.getValue()) {
            int value = caseObjet2.getValue() * 2;
            score += value;
            MoveEvent event(caseObjet2.getValue(), value, i2, j2, i1, j1);
            caseObjet2.addAnimation(event);
            caseObjet1.addAnimations(caseObjet2);
            removeCase(caseObjet2);
            caseObjet1.setValue(value);
            return true;
        }
    }
    return false;
}
*/

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param i l'indice de la ligne dans le tableau
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin exclu.
 **/
void Model::moveLeftRange(int i, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int j = startIndex; j < endIndex; j++) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = j;
            }
        } else {
            if (first0Index != -1) {
                Case& caseObjet1 = getCase(i, j);
                int value = caseObjet1.getValue();
                Case caseObjet0(i, first0Index);
                MoveEvent event(value, -1, i, j, i, first0Index);
                caseObjet1.addAnimation(event);
                caseObjet0.addAnimations(caseObjet1);
                removeCase(caseObjet1);
                caseObjet0.setValue(value);
                cases.push_back(caseObjet0);
                first0Index += 1;
            }
        }
    }
}

/** Rajoute vers la gauche les cases avec les memes valeurs.
 * @param i l'indice de la ligne dans le tableau
 **/
void Model::addLeftValues(int i) {
    cout << "----" << endl;
    printPlateau();
    cout << "Left" << endl;
    int j = 0;
    while (j < columns - 1) {
        if (validCase(i, j) && validCase(i, j + 1)) {
            Case& caseObjet1 = getCase(i, j);
            Case& caseObjet2 = getCase(i, j + 1);
            cout << "--" << endl;
            cout << "i: " << i << "; j + 1: " << j + 1 << endl;
            if (caseObjet1.getValue() == caseObjet2.getValue()) {
                cout << "Values ==" << endl;
                int value = caseObjet2.getValue() * 2;
                caseObjet1.setValue(value);
                score += value;
                MoveEvent event(caseObjet2.getValue(), value, i, j + 1, i, j);
                caseObjet2.addAnimation(event);
                caseObjet1.addAnimations(caseObjet2);
                removeCase(caseObjet2);
                moveLeftRange(i, j + 1, columns);
            }
            cout << "--" << endl;
        }      
        j++;
    }
    printPlateau();
    cout << "----" << endl;
}

/** Fait le mouvement de gauche dans la table.
 **/
void Model::moveLeft() {
    for (int i = 0; i < lines; i++) {
        moveLeftRange(i, 0, columns);
        addLeftValues(i);
    }
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param i l'indice de la ligne dans le tableau
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin.
 **/
void Model::moveRightRange(int i, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int j = endIndex - 1; j >= startIndex; j--) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = j;
            }
        } else if (first0Index != -1) {
            Case& caseObjet1 = getCase(i, j);
            int value = caseObjet1.getValue();
            Case caseObjet0(i, first0Index);
            MoveEvent event(value, -1, i, j, i, first0Index);
            caseObjet1.addAnimation(event);
            caseObjet0.addAnimations(caseObjet1);
            removeCase(caseObjet1);
            caseObjet0.setValue(value);
            cases.push_back(caseObjet0);
            first0Index -= 1;
        }
    }
}

/** Rajoute vers la droite les cases avec les memes valeurs.
 * @param i l'indice de la ligne dans le tableau
 **/
void Model::addRightValues(int i) {
    int j = columns - 1;
    while (j > 0) {
        if (validCase(i, j) && validCase(i, j - 1)) {
            Case& caseObjet1 = getCase(i, j);
            Case& caseObjet2 = getCase(i, j - 1);
            if (caseObjet1.getValue() == caseObjet2.getValue()) {
                int value = caseObjet2.getValue() * 2;
                caseObjet1.setValue(value);
                score += value;
                MoveEvent event(caseObjet2.getValue(), value, i, j - 1, i, j);
                caseObjet2.addAnimation(event);
                caseObjet1.addAnimations(caseObjet2);
                removeCase(caseObjet2);
                moveRightRange(i, 0, j - 1);
            }
        }  
        j--;
    } 
}

/** Fait le mouvement de droite dans la table.
 **/
void Model::moveRight() {
    for (int i = 0; i < lines; i++) {
        moveRightRange(i, 0, columns);
        addRightValues(i);
    }
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param i l'indice de la ligne dans le tableau
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin.
 **/
void Model::moveUpRange(int j, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = startIndex; i < endIndex; i++) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            Case& caseObjet1 = getCase(i, j);
            int value = caseObjet1.getValue();
            Case caseObjet0(first0Index, j);
            MoveEvent event(value, -1, i, j, first0Index, j);
            caseObjet1.addAnimation(event);
            caseObjet0.addAnimations(caseObjet1);
            removeCase(caseObjet1);
            caseObjet0.setValue(value);
            cases.push_back(caseObjet0);
            first0Index += 1;
        }
    }
}

/** Rajoute vers la droite les cases avec les memes valeurs.
 * @param i l'indice de la ligne dans le tableau
 * @param t le tableau.
 **/
void Model::addUpValues(int j) {
    int i = 1;
    while (i < lines - 1) {
        if (validCase(i, j) && validCase(i - 1, j)) {
            Case& caseObjet1 = getCase(i - 1, j);
            Case& caseObjet2 = getCase(i, j);
            if (caseObjet1.getValue() == caseObjet2.getValue()) {
                int value = caseObjet2.getValue() * 2;
                caseObjet1.setValue(value);
                score += value;
                MoveEvent event(caseObjet2.getValue(), value, i, j, i - 1, j);
                caseObjet2.addAnimation(event);
                caseObjet1.addAnimations(caseObjet2);
                removeCase(caseObjet2);
                moveUpRange(j, i, lines);
            }
        }  
        i++;
    } 
}

/** Fait le mouvement de bas dans la table.
 **/
void Model::moveUp() {
    for (int j = 0; j < columns; j++) {
        moveUpRange(j, 0, lines);
        addUpValues(j);
    }
}

/** Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau.
 * @param i l'indice de la ligne dans le tableau
 * @param startIndex l'indice de début.
 * @param endIndex l'indice de fin.
 **/
void Model::moveDownRange(int j, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = endIndex - 1; i >= startIndex; i--) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            Case& caseObjet1 = getCase(i, j);
            int value = caseObjet1.getValue();
            Case caseObjet0(first0Index, j);
            MoveEvent event(value, -1, i, j, first0Index, j);
            caseObjet1.addAnimation(event);
            caseObjet0.addAnimations(caseObjet1);
            removeCase(caseObjet1);
            caseObjet0.setValue(value);
            cases.push_back(caseObjet0);
            first0Index -= 1;
        }
    }
}

/** Rajoute vers la droite les cases avec les memes valeurs.
 * @param i l'indice de la ligne dans le tableau
 * @param t le tableau.
 **/
void Model::addDownValues(int j) {
    int i = lines - 1;
    while (i > 0) {
        if (validCase(i, j) && validCase(i - 1, j)) {
            Case& caseObjet1 = getCase(i, j);
            Case& caseObjet2 = getCase(i - 1, j);
            if (caseObjet1.getValue() == caseObjet2.getValue()) {
                int value = caseObjet2.getValue() * 2;
                caseObjet1.setValue(value);
                score += value;
                MoveEvent event(caseObjet2.getValue(), value, i, j, i - 1, j);
                caseObjet2.addAnimation(event);
                caseObjet1.addAnimations(caseObjet2);
                removeCase(caseObjet2);
                moveDownRange(j, 0, i);
            }
        }  
        i--;
    } 
}

/** Fait le mouvement de haut dans la table.
 **/
void Model::moveDown() {
    for (int j = 0; j < columns; j++) {
        moveDownRange(j, 0, lines);
        addDownValues(j);
    }
}

/** Fonction qui identifie les indices des cases vides (valeurs égales à 0) dans un tableau d'uplets.
 * @return tableau des uplets : premier valeur l'indice du tableau et deuxième valeur l'indice dans le tableau de la case vide.
 **/
vector<tuple<int, int>> Model::getEmptySlots() {
    vector<tuple<int, int>> emptySlots;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (!validCase(i, j)) {
                emptySlots.push_back({i, j});
            }
        }
    }
    return emptySlots;
}

/** Fonction qui rajoute un élément de manière aléatoire sur les cases vides de la table.
 */
void Model::setRandomElements(int amount) {
    for (int i = 0; i < amount; i++) {
        vector<tuple<int, int>> emptySlots = getEmptySlots();
        int k = (int) rand() % emptySlots.size(); /// Choisit un tuple de facon aléatoire
        tuple<int, int> values = emptySlots[k]; // Choisit les indices d'une case vide de ce sous-tableau de facon aléatoire
        int r = rand() % 10; // 90% de Chance d'Ajouter un 2, 10% de Chance d'ajouter un 4.
        Case newCase(get<0>(values), get<1>(values));
        newCase.setValue(r < 9 ? 2 : 4);
        cases.push_back(newCase);
    }
}

void Model::clear() {
    cases = {};
    setRandomElements(2);
}

/** Fonction pour afficher une ligne du plateau sous forme de tableau.
 * @param i indice de la ligne dans le plateau.
 **/
void Model::printLine(int i) {
    cout << "[";
    for (int j = 0; j < columns; j++) {
        int value = 0;
        if (validCase(i, j)) {
            value = getCase(i, j).getValue();
        }
        cout << value;
        if (j != columns - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

/** Fonction pour afficher le plateau sous forme de tableau.
 **/
void Model::printPlateau() {
    cout << "[";
    for (int i = 0; i < lines; i++) {
        printLine(i);
        if (i != lines - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

vector<Case>& Model::getCases() {
    return cases;
}

int Model::getScore() {
    return score;
}

bool Model::validCase(int i, int j) {
    for (int k = 0; k < cases.size(); k++) {
        Case& caseObjet = cases[k];
        if (caseObjet.getIndexI() == i && caseObjet.getIndexJ() == j) {
            return true;
        }
    }
    return false;
}

Case& Model::getCase(int i, int j) {
    for (int k = 0; k < cases.size(); k++) {
        Case& caseObjet = cases[k];
        if (caseObjet.getIndexI() == i && caseObjet.getIndexJ() == j) {
            return caseObjet;
        }
    }
    cout << "Case error" << endl;
    return cases[0];
}

int Model::getCasesInAnimation() {
    int n = 0;
    for (Case caseObjet : cases) {
        if (caseObjet.hasAnimation()) {
            n += 1;
        } 
    }
    return n;
}

void Model::removeCase(Case& caseObjet) {
    int i = caseObjet.getIndexI();
    int j = caseObjet.getIndexJ();
    for (auto it = cases.begin(); it != cases.end(); ) {
        if (it->getIndexI() == i && it->getIndexJ() == j) {
            it = cases.erase(it);
            return;
        } else {
            ++it;
        }
    }
}

int Model::getLines() {
    return lines;
}

int Model::getColumns() {
    return columns;
}