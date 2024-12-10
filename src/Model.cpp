#include "Model.h"
using namespace std;

/**
 * Constructeur de la classe Model pour toutes les fonctions
 * de logique et de mouvement du jeu.
 * 
 * On retrouvera ici toutes les fonctions de
 * mouvement, de vérification de mouvement et aussi
 * les fonctions pour le score et état du jeu.
 * 
 * @param lines les lignes du plateau du jeu.
 * @param columns le nombre de colonnes du jeu.
 * 
 * Auteur : Alejandro Perez Svetlitsky
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
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
bool Model::compareValues(int i1, int j1, int i2, int j2) {
    if (validTile(i2, j2)) {
        if (validTile(i1, j1)) {
            int value1 = getTile(i1, j1).getValue();
            int value2 = getTile(i2, j2).getValue();
            if (value1 == value2) {
                return true;
            }
        } else {
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
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
bool Model::canMoveLeft() {
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns - 1; j++) {
            if (compareValues(i, j, i, j + 1)) {
                return true;
            }
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
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
bool Model::canMoveRight() {
    for (int i = 0; i < lines; i++) {
        for (int j = columns - 1; j > 0; j--) {
            if (compareValues(i, j, i, j - 1)) {
                return true;
            }
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
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
bool Model::canMoveUp() {
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < lines - 1; i++) {
            if (compareValues(i, j, i + 1, j)) {
                return true;
            }
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
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
bool Model::canMoveDown() {
    for (int j = 0; j < columns; j++) {
        for (int i = lines - 1; i > 0; i--) {
            if (compareValues(i, j, i - 1, j)) {
                return true;
            }
        }
    }
    return false;
}

/** 
 * Vérifie si au moins un mouvement en générale peut se faire en utilisant
 * les 4 fonctions de mouvement.
 * 
 * @return true si au moins un mouvement est possible, false sinon.
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
bool Model::canMove() {
    return canMoveLeft() || canMoveRight() || canMoveUp() || canMoveDown();
}

// FONCTIONS DE MOUVEMENT

/**
 * Déplace un tuile vers une position vide dans le plateau.
 * 
 * @param i1 : l'indice i du premier élément.
 * @param j1 : l'indice j du premier élément.
 * @param i2 : l'indice i de la position vide.
 * @param j2 : l'indice j de la position vide.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Model::moveCase(int i1, int j1, int i2, int j2) {
    Tile& tile = getTile(i1, j1);
    tile.setIndexI(i2);
    tile.setIndexJ(j2);

    MoveEvent event(tile.getValue(), false, i1, j1, i2, j2);
    tile.addAnimation(event);
}

/** 
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les 
 * tuiles de la ligne i vers la gauche. Garde le premier indice d'une 
 * position vide par rapport à la direction du mouvement, et déplace 
 * les tuiles vers les positions vides.
 * 
 * @param i : l'indice de la ligne dans le plateau.
 * @param startIndex : l'indice de début inclu.
 * @param endIndex : l'indice de fin exclu.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Model::moveLeftRange(int i, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int j = startIndex; j < endIndex; j++) {
        if (!validTile(i, j)) {
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
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les 
 * tuiles de la ligne i vers la droite. Garde le premier indice d'une 
 * position vide par rapport à la direction du mouvement, et déplace 
 * les tuiles vers les positions vides.
 * 
 * @param i : l'indice de la ligne dans le plateau.
 * @param startIndex : l'indice de début inclu.
 * @param endIndex : l'indice de fin exclu.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Model::moveRightRange(int i, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int j = endIndex - 1; j >= startIndex; j--) {
        if (!validTile(i, j)) {
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
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les 
 * tuiles de la colonne j vers le haut. Garde le premier indice d'une 
 * position vide par rapport à la direction du mouvement, et déplace 
 * les tuiles vers les positions vides.
 * 
 * @param j : l'indice de la colonne dans le plateau.
 * @param startIndex : l'indice de début inclu.
 * @param endIndex : l'indice de fin exclu.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Model::moveUpRange(int j, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = startIndex; i < endIndex; i++) {
        if (!validTile(i, j)) {
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
 * Décale depuis l'indice startIndex jusqu'à l'indice endIndex exclu les 
 * tuiles de la colonne j vers le bas. Garde le premier indice d'une 
 * position vide par rapport à la direction du mouvement, et déplace 
 * les tuiles vers les positions vides.
 * 
 * @param j : l'indice de la colonne dans le plateau.
 * @param startIndex : l'indice de début inclu.
 * @param endIndex : l'indice de fin exclu.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Model::moveDownRange(int j, int startIndex, int endIndex) {
    int first0Index = -1;
    for (int i = endIndex - 1; i >= startIndex; i--) {
        if (!validTile(i, j)) {
            if (first0Index == -1) {
                first0Index = i;
            }
        } else if (first0Index != -1) {
            moveCase(i, j, first0Index, j);
            first0Index -= 1;
        }
    }
}

// FONCTIONS MOUVEMENT SOMME DES TUILES

/**
 * Vérifie si deux tuiles peuvent s'ajouter, et dans le cas que oui,
 * l'addition de la tuile de départ ( première case ) vers la tuile
 * d'arrivée ( deuxième case ) se réalise.
 * 
 * @param i1 l'indice i de la tuile de départ.
 * @param j1 l'indice j de la tuile de départ.
 * @param i2 l'indice i de la tuile d'arrivé.
 * @param j2 l'indice j de la tuile d'arrivé.
 * @return true si l'addition des tuiles se réalise, false sinon.
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
bool Model::addCases(int i1, int j1, int i2, int j2) {
    if (validTile(i1, j1) && validTile(i2, j2)) {
        Tile& tileStart = getTile(i1, j1);
        Tile& tileEnd = getTile(i2, j2);
        if (tileStart.getValue() == tileEnd.getValue()) {
            int value = tileStart.getValue() * 2;
            tileEnd.setValue(value);
            score += value;

            MoveEvent event(tileEnd.getValue() / 2, true, i1, j1, i2, j2);
            tileEnd.addAnimations(tileStart);
            tileEnd.addAnimation(event);
            removeTile(tileStart);

            return true;
        }
    } 
    return false;
}

/** 
 * Rajoute les tuiles l'un près de l'autres égaux de gauche vers la 
 * droite et décale les tuiles pour enlever les espaces.
 * 
 * @param i : l'indice de la ligne dans le plateau.
 * 
 * Auteur : Alejandro Perez Svetlitsky
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
 * Rajoute les tuiles l'un près de l'autres égaux de droite vers la gauche
 * et décale les tuiles pour enlever les espaces.
 * 
 * @param i : l'indice de la ligne dans le plateau.
 * 
 * Auteur : Alejandro Perez Svetlitsky
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
 * Rajoute les tuiles l'un près de l'autres égaux du haut vers le bas
 * et décale les tuiles pour enlever les espaces.
 * 
 * @param j : l'indice de la colonne dans le plateau.
 * 
 * Auteur : Alejandro Perez Svetlitsky
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

/** 
 * Rajoute les tuiles l'un près de l'autres égaux du bas vers le haut
 * et décale les tuiles pour enlever les espaces.
 * 
 * @param j : l'indice de la colonne dans le plateau.
 * 
 * Auteur : Alejandro Perez Svetlitsky
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
 * @return tableau d'uplets : premier valeur l'indice du tableau et 
 * deuxième valeur l'indice dans le tableau de la case vide.
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
vector<tuple<int, int>> Model::getEmptySlots() {
    vector<tuple<int, int>> emptySlots;
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            if (!validTile(i, j)) {
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
 * @param amount : le nombre de cases vides à mettre aléatoirement dans le plateau.
 * 
 * Auteur : Alejandro Perez Svetlitsky
 **/
void Model::setRandomElements(int amount) {
    for (int i = 0; i < amount; i++) {
        vector<tuple<int, int>> emptySlots = getEmptySlots();
        int k = rand() % emptySlots.size();
        tuple<int, int> values = emptySlots[k];
        Tile newTile(get<0>(values), get<1>(values));
        int r = rand() % 10;
        newTile.setValue(r < 9 ? 2 : 4);
        tiles.push_back(newTile);
    }
}

// FONCTIONS POUR FAIRE DÉBOGAGE

/** 
 * Fonction pour afficher une ligne du 
 * plateau sous forme de tableau.
 * 
 * @param i : indice de la ligne dans le plateau.
 **/
void Model::printLine(int i) {
    cout << "[";
    for (int j = 0; j < columns; j++) {
        int value = 0;
        if (validTile(i, j)) {
            value = getTile(i, j).getValue();
        }
        cout << value;
        if (j != columns - 1) {
            cout << ", ";
        }
    }
    cout << "]";
}

/** 
 * Fonction pour afficher le plateau sous
 * forme de tableau dans la terminale.
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
 * Fonction qui vérifie si une tuile du plateau
 * est non-vide, donc qu'elle existe.
 * 
 * @param i : l'indice i de la tuile à vérifier.
 * @param j : l'indice j de la tuile à vérifier.
 * @return true si la tuile existe, false sinon.
 **/
bool Model::validTile(int i, int j) {
    for (int k = 0; k < tiles.size(); k++) {
        Tile& tile = tiles[k];
        if (tile.getIndexI() == i && tile.getIndexJ() == j) {
            return true;
        }
    }
    return false;
}

/**
 * Fonction qui renvoie une tuile du plateau.
 * Renvoie une erreur si la tuile est invalide.
 * 
 * @param i : l'indice i de la tuile.
 * @param j : l'indice j de la tuile.
 * @return tile : la tuile d'indices i,j.
 **/
Tile& Model::getTile(int i, int j) {
    for (int k = 0; k < tiles.size(); k++) {
        Tile& tile = tiles[k];
        if (tile.getIndexI() == i && tile.getIndexJ() == j) {
            return tile;
        }
    }
    cerr << "Case error : case index i : " << i << "; j : " << j << "; not valid." << endl;
    return tiles[0];
}

/**
 * Fonction qui compare le score avec le
 * meilleur score, et si le meilleur score est
 * plus petit que le score actuel, il
 * change le meilleur score.
 **/
void Model::updateScore() {
    int bestScore = getBestScore();
    int score = getScore();
    if (score > bestScore) {
        setBestScore(score);
    }
}

/**
 * Fonction pour enlever une tuile du plateau.
 * 
 * @param tile : la tuile du plateau.
 **/
void Model::removeTile(Tile& tile) {
    int i = tile.getIndexI();
    int j = tile.getIndexJ();
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        if (it->getIndexI() == i && it->getIndexJ() == j) {
            tiles.erase(it);
            return;
        }
    }
}

/** 
 * Fonction pour enlever toutes les valeurs dans le plateau, rétablir
 * le score et mettre deux valeurs aléatoires. ( Pour redémarrer le jeu ).
 */
void Model::restart() {
    tiles = {};
    setRandomElements(2);
    score = 0;
}

// FONCTIONS GET

/** 
 * Vérifie si le joueur a gagné la partie
 * @return true si la tuile de plus grande valeur est supérieur
 * à 2048, false sinon.
 */
bool Model::didPlayerWin() {
    return getMaxTileNumber() >= 2048;
}

GameState Model::getGameState() {
    return state;
}

void Model::setGameState(GameState state) {
    this->state = state;
}

vector<Tile>& Model::getTiles() {
    return tiles;
}

/** 
 * Fonction pour retrouver la tuile avec la plus
 * grande valeur.
 * @return max la tuile avec le plus grand nombre.
 **/
int Model::getMaxTileNumber() {
    int max = 0;
    for (Tile& caseObjet : tiles) {
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