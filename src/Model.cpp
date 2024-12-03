#include "Model.h"
using namespace std;

/**
 * Constructeur de la classe Model pour toutes les fonctions
 * de logique et de mouvement du jeu.
 * 
 * @param lines les lignes du plateau du jeu.
 * @param columns le nombre de colonnes du jeu.
 */
Model::Model(int lines, int columns) {
    this->lines = lines;
    this->columns = columns;
    restart();
}

// FONCTIONS POUR VÉRIFICATION DES MOUVEMENTS

/**
 * Fonction pour comparer deux valeurs proches lors d'un mouvement.
 * On tiendra en compte l'élément 1 en paramètre est avant l'élément 2 selon le mouvement.
 * Le mouvement est valide si le premier et le deuxième élément sont de meme valuer, ou si
 * un espace vide ( premier élément ) se situe avant le deuxième élément.
 * 
 * @param i1 l'indice i du premier élément
 * @param j1 l'indice j du premier élément
 * @param i2 l'indice i du deuxième élément
 * @param j2 l'indice j du deuxième élément
 */
bool Model::compareValues(int i1, int j1, int i2, int j2) {
    if (validCase(i2, j2)) {
        if (validCase(i1, j1)) {
            if (getCase(i1, j1).getValue() == getCase(i2, j2).getValue()) {
                return true;
            }
        } else {
            return true;
        }
    }
    return false;
}

bool Model::canMoveLeftLine(int i, int startIndex, int endIndex) {
    for (int j = startIndex; j < endIndex - 1; j++) {
        if (compareValues(i, j, i, j + 1)) {
            return true;
        }
    }
    return false;
}

bool Model::canMoveRightLine(int i, int startIndex, int endIndex) {
    for (int j = endIndex - 1; j > startIndex; j--) {
        if (compareValues(i, j, i, j - 1)) {
            return true;
        }
    }
    return false;
}

bool Model::canMoveUpLine(int j, int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex - 1; i++) {
        if (compareValues(i, j, i + 1, j)) {
            return true;
        }
    }
    return false;
}

bool Model::canMoveDownLine(int j, int startIndex, int endIndex) {
    for (int i = endIndex - 1; i > startIndex; i--) {
        if (compareValues(i, j, i - 1, j)) {
            return true;
        }
    }
    return false;
}

/**
 * Vérifie pour chaque ligne en comparant deux à deux les nombres
 * pour voir si un mouvement à gauche est possible.
 * On compare les éléments d'indices ( j ) et ( j + 1 ).
 * On vérifie si un espace avec un élément après ( entre 0 et columns - 2 inclus )
 * ou deux éléments égaux près l'un de l'autre ( entre 0 et columns - 1 inclus )
 * 
 * @return true si un mouvement à gauche est possible, false sinon.
 **/
bool Model::canMoveLeft() {
    for (int i = 0; i < lines; i++) {
        if (canMoveLeftLine(i, 0, columns)) {
            return true;
        }
    }
    return false;
}

/**
 * Vérifie pour chaque ligne en comparant deux à deux les nombres
 * pour voir si un mouvement à droite est possible.
 * On compare les éléments d'indices ( j ) et ( j - 1 ).
 * On vérifie si un espace avec un élément après ( entre 1 et columns - 1 inclus )
 * ou deux éléments égaux près l'un de l'autre ( entre 0 et columns - 1 inclus )
 * 
 * @return true si un mouvement à gauche est possible, false sinon.
 **/
bool Model::canMoveRight() {
    for (int i = 0; i < lines; i++) {
        if (canMoveRightLine(i, 0, columns)) {
            return true;
        }
    }
    return false;
}

/**
 * Vérifie pour chaque colonne en comparant deux à deux les nombres
 * pour voir si un mouvement à droite est possible.
 * On compare les éléments d'indices ( i ) et ( i + 1 ).
 * On vérifie si un espace avec un élément après ( entre 0 et lines - 2 inclus )
 * ou deux éléments égaux près l'un de l'autre ( entre 0 et lines - 1 inclus )
 * 
 * @return true si un mouvement à gauche est possible, false sinon.
 **/
bool Model::canMoveUp() {
    for (int j = 0; j < columns; j++) {
        if (canMoveUpLine(j, 0, lines)) {
            return true;
        }
    }
    return false;
}

/**
 * Vérifie pour chaque colonne en comparant deux à deux les nombres
 * pour voir si un mouvement à droite est possible.
 * On compare les éléments d'indices ( i ) et ( i - 1 ).
 * On vérifie si un espace avec un élément après ( entre 1 et lines - 1 inclus )
 * ou deux éléments égaux près l'un de l'autre ( entre 0 et lines - 1 inclus )
 * 
 * @return true si un mouvement à gauche est possible, false sinon.
 **/
bool Model::canMoveDown() {
    for (int j = 0; j < columns; j++) {
        if (canMoveDownLine(j, 0, lines)) {
            return true;
        }
    }
    return false;
}

/** 
 * Vérifie si au moins un mouvement en générale peut se faire en utilisant
 * les 4 fonctions de mouvement.
 * 
 * @return true si au moins un mouvement est possible, false sinon.
 **/
bool Model::canMove() {
    return canMoveLeft() || canMoveRight() || canMoveUp() || canMoveDown();
}

// FONCTIONS DE MOUVEMENT

/**
 * Déplace un case vers une case vide dans le plateau.
 * 
 * @param i1 l'indice i du premier élément
 * @param j1 l'indice j du premier élément
 * @param i2 l'indice i de la case vide
 * @param j2 l'indice j de la case vide
 */
void Model::moveCase(int i1, int j1, int i2, int j2) {
    Case& firstCase = getCase(i1, j1);
    firstCase.setIndexI(i2);
    firstCase.setIndexJ(j2);

    MoveEvent event(firstCase.getValue(), false, i1, j1, i2, j2);
    firstCase.addAnimation(event);
}

/** 
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau
 * vers la gauche. Garde le dernier indice d'une cas vide, et déplace les valeurs différents de 0
 * sur ses indices.
 * 
 * @param i l'indice de la ligne dans le plateau.
 * @param startIndex l'indice de début inclu.
 * @param endIndex l'indice de fin exclu.
 **/
void Model::moveLeftRange(int i, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int j = startIndex; j < endIndex; j++) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = j;
            }
        } else if (first0Index != -1) {
            moveCase(i, j, i, first0Index);
            first0Index += 1;
        }
    }
}

/** 
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau
 * vers la droite. Garde le dernier indice d'une cas vide, et déplace les valeurs différents de 0
 * sur ses indices.
 * 
 * @param i l'indice de la ligne dans le plateau.
 * @param startIndex l'indice de début inclu.
 * @param endIndex l'indice de fin exclu.
 **/
void Model::moveRightRange(int i, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int j = endIndex - 1; j >= startIndex; j--) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = j;
            }
        } else if (first0Index != -1) {
            moveCase(i, j, i, first0Index);
            first0Index -= 1;
        }
    }
}

/** 
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau
 * vers le haut. Garde le dernier indice d'une cas vide, et déplace les valeurs différents de 0
 * sur ses indices.
 * 
 * @param j l'indice de la colonne dans le plateau.
 * @param startIndex l'indice de début inclu.
 * @param endIndex l'indice de fin exclu.
 **/
void Model::moveUpRange(int j, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = startIndex; i < endIndex; i++) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            moveCase(i, j, first0Index, j);
            first0Index += 1;
        }
    }
}

/** 
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les valeurs d'un tableau
 * vers le bas. Garde le dernier indice d'une cas vide, et déplace les valeurs différents de 0
 * sur ses indices.
 * 
 * @param j l'indice de la colonne dans le plateau.
 * @param startIndex l'indice de début inclu.
 * @param endIndex l'indice de fin exclu.
 **/
void Model::moveDownRange(int j, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = endIndex - 1; i >= startIndex; i--) {
        if (!validCase(i, j)) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            moveCase(i, j, first0Index, j);
            first0Index -= 1;
        }
    }
}

// FONCTIONS MOUVEMENT SOMME DES CASES

/**
 * Vérifie si deux cases peuvent s'ajouter, et dans le cas que oui,
 * l'addition de la case de départ ( première case ) vers la case
 * d'arrivée ( deuxième case ) se réalise.
 * 
 * @param i1 l'indice i de la case de départ.
 * @param j1 l'indice j de la case de départ.
 * @param i2 l'indice i de la case d'arrivé.
 * @param j2 l'indice j de la case d'arrivé.
 * @return true si l'addition des cases se réalise, false sinon.
 */
bool Model::addCases(int i1, int j1, int i2, int j2) {
    if (validCase(i1, j1) && validCase(i2, j2)) {
        Case& caseStart = getCase(i1, j1);
        Case& caseEnd = getCase(i2, j2);
        if (caseStart.getValue() == caseEnd.getValue()) {
            int value = caseStart.getValue() * 2;
            caseEnd.setValue(value);
            score += value;

            MoveEvent event(caseEnd.getValue() / 2, true, i1, j1, i2, j2);
            caseEnd.addAnimations(caseStart);
            caseEnd.addAnimation(event);
            removeCase(caseStart);

            return true;
        }
    } 
    return false;
}

/** 
 * Rajoute les éléments l'un près de l'autres égaux de gauche vers la 
 * droite et décale les éléments pour enlever les espaces.
 * 
 * @param i l'indice de la ligne dans le plateau.
 **/
void Model::addLeftValues(int i) {
    int j = 0;
    while (j < columns - 1) {
        if (addCases(i, j + 1, i, j)) {
            moveLeftRange(i, j + 1, columns);
        }
        j++;
    }
}

/** 
 * Rajoute les éléments l'un près de l'autres égaux de droite vers la gauche
 * et décale les éléments pour enlever les espaces.
 * 
 * @param i l'indice de la ligne dans le plateau.
 **/
void Model::addRightValues(int i) {
    int j = columns - 1;
    while (j > 0) {
        if (addCases(i, j - 1, i, j)) {
            moveRightRange(i, 0, j);
        }
        j--;
    } 
}

/** 
 * Rajoute les éléments l'un près de l'autres égaux du haut vers le bas
 * et décale les éléments pour enlever les espaces.
 * 
 * @param j l'indice de la colonne dans le plateau.
 **/
void Model::addUpValues(int j) {
    int i = 0;
    while (i < lines - 1) {
        if (addCases(i + 1, j, i, j)) {
            moveUpRange(j, i, lines);
        }
        i++;
    } 
}

/** Rajoute vers la droite les cases avec les memes valeurs.
 * @param i l'indice de la ligne dans le tableau
 * @param t le tableau.
 **/
void Model::addDownValues(int j) {
    int i = lines - 1;
    while (i > 0) {
        if (addCases(i - 1, j, i, j)) {
            moveDownRange(j, 0, i);
        }
        i--;
    } 
}

// FONCTIONS DE MOUVEMENT EN GÉNÉRALE

/** 
 * Fait le mouvement de gauche dans le plateau.
 **/
void Model::moveLeft() {
    for (int i = 0; i < lines; i++) {
        moveLeftRange(i, 0, columns);
        addLeftValues(i);
    }
}

/** 
 * Fait le mouvement de droite dans le plateau.
 **/
void Model::moveRight() {
    for (int i = 0; i < lines; i++) {
        moveRightRange(i, 0, columns);
        addRightValues(i);
    }
}

/** 
 * Fait le mouvement de haut dans le plateau.
 **/
void Model::moveUp() {
    for (int j = 0; j < columns; j++) {
        moveUpRange(j, 0, lines);
        addUpValues(j);
    }
}

/** 
 * Fait le mouvement d'en bas dans le plateau.
 **/
void Model::moveDown() {
    for (int j = 0; j < columns; j++) {
        moveDownRange(j, 0, lines);
        addDownValues(j);
    }
}

// LOGIQUE DES CASES ALÉATOIRES

/** 
 * Fonction qui cherche dans le plateau les cases sans 
 * valeurs ( vides ) et en renvoie une liste des indices.
 * 
 * @return tableau des uplets : premier valeur l'indice du tableau et 
 * deuxième valeur l'indice dans le tableau de la case vide.
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

/** 
 * Fonction qui rajoute un élément de manière aléatoire sur les 
 * cases vides de la table. Probabilité des cases : 9/10 pour une 
 * valeur égale à 2 et 1/10 pour une valeur égale à 4.
 * 
 * @param amount le nombre de cases vides à mettre aléatoirement dans le plateau.
 */
void Model::setRandomElements(int amount) {
    for (int i = 0; i < amount; i++) {
        vector<tuple<int, int>> emptySlots = getEmptySlots();
        int k = rand() % emptySlots.size();
        tuple<int, int> values = emptySlots[k];
        int r = rand() % 10;
        Case newCase(get<0>(values), get<1>(values));
        newCase.setValue(r < 9 ? 2 : 4);
        cases.push_back(newCase);
    }
}

// FONCTIONS POUR FAIRE DÉBOGAGE

/** 
 * Fonction pour afficher une ligne du plateau sous forme de tableau.
 * 
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

/** 
 * Fonction pour afficher le plateau sous forme de tableau.
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

// AUTRES MÉTHODES UTILES

/** 
 * Fonction qui vérifie si une case du plateau
 * est non-vide, donc qu'elle existe.
 * 
 * @param i l'indice i de la case à vérifier.
 * @param j l'indice j de la case à vérifier.
 * @return true si la case existe, false sinon.
 **/
bool Model::validCase(int i, int j) {
    for (int k = 0; k < cases.size(); k++) {
        Case& caseObjet = cases[k];
        if (caseObjet.getIndexI() == i && caseObjet.getIndexJ() == j) {
            return true;
        }
    }
    return false;
}

/**
 * Fonction qui renvoie une case du plateau.
 * Renvoie une erreur si la case est invalide.
 * 
 * @param i l'indice i de la case.
 * @param j l'indice j de la case.
 * @return la case d'indices i,j.
 **/
Case& Model::getCase(int i, int j) {
    for (int k = 0; k < cases.size(); k++) {
        Case& caseObjet = cases[k];
        if (caseObjet.getIndexI() == i && caseObjet.getIndexJ() == j) {
            return caseObjet;
        }
    }
    cerr << "Case error : case index i : " << i << "; j : " << j << "; not valid." << endl;
    return cases[0];
}

void Model::updateScore() {
    int bestScore = getBestScore();
    int score = getScore();
    if (score > bestScore) {
        setBestScore(score);
    }
}

/**
 * Fonction pour enlever une case du plateau.
 * 
 * @param caseObjet la case du plateau.
 **/
void Model::removeCase(Case& caseObjet) {
    int i = caseObjet.getIndexI();
    int j = caseObjet.getIndexJ();
    for (auto it = cases.begin(); it != cases.end(); ++it) {
        if (it->getIndexI() == i && it->getIndexJ() == j) {
            cases.erase(it);
            return;
        }
    }
}

/** 
 * Fonction pour enlever toutes les valeurs dans le plateau, rétablir
 * le score et mettre deux valeurs aléatoires. ( Pour redémarrer le jeu ).
 */
void Model::restart() {
    cases = {};
    setRandomElements(2);
    score = 0;
}

// FONCTIONS GET

bool Model::didPlayerWin() {
    return getMaxCaseNumber() >= 2048;
}

GameState Model::getGameState() {
    return state;
}

void Model::setGameState(GameState state) {
    this->state = state;
}

vector<Case>& Model::getCases() {
    return cases;
}

int Model::getMaxCaseNumber() {
    int max = 0;
    for (Case& caseObjet : cases) {
        int value = caseObjet.getValue();
        if (value > max) {
            max = value;
        }
    }
    return max;
}

int Model::getBestScore() {
    return bestScore;
}

void Model::setBestScore(int bestScore) {
    this->bestScore = bestScore;
}

int Model::getScore() {
    return score;
}

void Model::setScore(int score) {
    this->score = score;
}

int Model::getLines() {
    return lines;
}

int Model::getColumns() {
    return columns;
}