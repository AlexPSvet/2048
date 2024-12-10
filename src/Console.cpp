#include "Console.h"
#include <ncurses.h>
using namespace std;

/**
 * Constructeur de la classe Console.
 * Cette classe utilise des fonctionnalités de la classe model
 * en termes des fonctions de mouvement et vérification de mouvement.
 * 
 * @param Model la classe model.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 */
Console::Console(Model& model) : model(model) {}

/** 
 * Retrouve le nombre le plus grand en caractères. 
 * 
 * @return entier représentant le nombre de caractères
 * du plus grand nombre dans le plateau.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
int Console::getMaxTextLenght() {
    int maxValue = 1;
    for (Tile tile : model.getTiles()) {
        int value = tile.getValue();
        if (value > maxValue) {
            maxValue = value;
        }
    }
    return to_string(maxValue).size();
}

/** 
 * Fonction pour initialiser toutes les couleurs pour
 * le text ainsi que les couleurs des tuiles pour la console
 * dans la bibliothéque ncurses.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Console::setupColors() {
    if (has_colors() && can_change_color()) {
        start_color();
        // Couleurs pour texte normal
        init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(2, COLOR_WHITE, COLOR_RED);
        init_pair(3, COLOR_WHITE, COLOR_MAGENTA);

        // Couleurs pour les tuiles
        use_default_colors(); // Use the terminal's default background
        // Couleurs RGB pour les tuiles.
        // On définit une clé ainsi que les trois composantes de la couleur.
        init_color(10, 804, 0, 1000);  // Tuile 2: RGB(204, 0, 255)
        init_color(11, 529, 55, 651); // Tuile 4: RGB(135, 14, 166)
        init_color(12, 741, 35, 576); // Tuile 8: RGB(189, 9, 147)
        init_color(13, 463, 43, 365); // Tuile 16: RGB(118, 11, 93)
        init_color(14, 337, 35, 627); // Tuile 32: RGB(86, 9, 160)
        init_color(15, 63, 35, 627);  // Tuile 64: RGB(16, 9, 160)
        init_color(16, 78, 592, 808); // Tuile 128: RGB(20, 151, 206)
        init_color(17, 78, 808, 424); // Tuile 256: RGB(20, 206, 108)
        init_color(18, 675, 808, 78); // Tuile 512: RGB(172, 206, 20)
        init_color(19, 808, 392, 78); // Tuile 1024: RGB(206, 100, 20)
        init_color(20, 890, 94, 15);  // Tuile 2048: RGB(227, 24, 4)
        init_color(21, 471, 51, 8);   // Tuile >2048: RGB(120, 13, 2)

        // Initialise les paires de couleurs pour ncurses.
        for (int i = 10; i <= 21; i++) {
            init_pair(i, COLOR_WHITE, i); // Couleur blanche pour le texte, et les couleurs de fond.
        }
    }
}

/**
 * Fonction pour retrouver l'exposant d'un nombre 2^k.
 * @param value un entier tel que value = 2^k
 * @return l'exposant k.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 */
int Console::findNumberColor(int value) {
    int exposant = 0;
    while (value % 2 == 0) {
        value /= 2;
        exposant += 1;
    }
    return exposant;
}

/** 
 * Affiche le plateau de jeu en utilisant ncurses dans une sous-fenetre de la terminale.
 * @param win la sous-fenetre du plateau du jeu.
 * @param cellHeight la hauteur de chaque tuile dans le terminale.
 * @param cellWidth la largueur de chaque tuile dans le terminale.
 * @param startY coordonnée y (ligne) de début du plateau.
 * @param coordonnée x (colonne) de début du plateau.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 * */
void Console::drawBoard(WINDOW* win, int cellHeight, int cellWidth, int startY, int startX) {
    box(win, 0, 0);
    for (int i = 0; i < model.getLines(); i++) {
        for (int j = 0; j < model.getColumns(); j++) {
            if (!model.validTile(i, j)) continue;
            int value = model.getTile(i, j).getValue();
            int colorPair = 9 + findNumberColor(value); // Couleur selon la valeur
            colorPair = 0 <= colorPair and colorPair <= 20 ? colorPair : 21;

            // Déterminer les coordonnées pour la case
            int cellStartY = startY + i * cellHeight;
            int cellStartX = startX + j * cellWidth;

            // Dessiner la case
            wattron(win, COLOR_PAIR(colorPair));
            for (int y = 0; y < cellHeight; ++y) {
                mvwprintw(win, cellStartY + y, cellStartX, "%*s", cellWidth, "");
            }

            // Dessiner la valeur centrée dans la case
            mvwprintw(win, cellStartY + cellHeight / 2, cellStartX + (cellWidth - getMaxTextLenght()) / 2, "%d", value);

            wattroff(win, COLOR_PAIR(colorPair)); // Enlever l'utilisation des couleurs de la tuile.
        }
    }

    wrefresh(win); // Rafraîchir l'affichage
}

/**
 * Fonction pour vérifier si le mouvement saisit est valide, et
 * si c'est le cas, réalise le mouvmenet dans le plateau.
 * 
 * @param key : le code numérique de la touche pressée.
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 */
bool Console::isValidMove(int key) {
    switch (key) {
        // Mouvement haut.
        case KEY_UP:
            if (model.canMoveUp()) {
                model.moveUp();
                return true;
            }
            break;
        // Mouvement bas.
        case KEY_DOWN:
            if (model.canMoveDown()) {
                model.moveDown();
                return true;
            }
            break;
        // Mouvement gauche.
        case KEY_LEFT:
            if (model.canMoveLeft()) {
                model.moveLeft();
                return true;
            }
            break;
        // Mouvement droite.
        case KEY_RIGHT:
            if (model.canMoveRight()) {
                model.moveRight();
                return true;
            }
            break;
    }
    return false;
}

/** 
 * Gestionnaire principal du jeu avec ncurses.
 * Initialise toutes les variables, et montre le jeu
 * dans le terminale avec le score et le meilleur score.
 * Vérifie à chaque tour de boucle les mouvmenets réalisées. 
 * 
 * Auteur : Andres Felipe Sanchez Salcedo
 **/
void Console::displayGame() {
    initscr(); // Initialiser la bibliothèque ncurses
    noecho(); // Désactiver l'affichage des touches pressées
    cbreak(); // Désactiver la mise en tampon des entrées
    keypad(stdscr, TRUE); // Activer les touches du clavier
    curs_set(0); // Masquer le curseur

    setupColors(); // Initialiser liste des couleurs

    // Récupérer les dimensions du terminal
    int height, width;
    getmaxyx(stdscr, height, width);

    // Calculer les dimensions du plateau
    int boardHeight = height * 2 / 3; // 2/3 de la hauteur du terminal
    int boardWidth = width * 2 / 3;   // 2/3 de la largeur du terminal
    int cellHeight = boardHeight / model.getLines();  // Hauteur des cases
    int cellWidth = boardWidth / model.getColumns();  // Largeur des cases

    // Calculer la position centrale
    int startY = (height - boardHeight) / 2;
    int startX = (width - boardWidth) / 2;

    // Créer une fenêtre pour le plateau
    WINDOW* gameWin = newwin(boardHeight, boardWidth, startY, startX);

    while (true) {
        werase(gameWin);

        // Dessiner le titre du jeu
        attron(COLOR_PAIR(1));
        mvprintw(startY - 2, (width - 8) / 2, " 2048 ");
        attroff(COLOR_PAIR(1));

        // Dessiner le plateau
        drawBoard(gameWin, cellHeight, cellWidth, 0, 0);
        
        // Dessiner le score
        attron(COLOR_PAIR(2));
        string score = "Score: " + to_string(model.getScore());
        mvprintw(startY + boardHeight + 1, (width - score.size()) / 2, "%s", score.c_str());
        attroff(COLOR_PAIR(2));

        // Dessiner le meilleur score
        attron(COLOR_PAIR(3));
        string bestScore = "Meilleur score: " + to_string(model.getBestScore());
        mvprintw(startY + boardHeight + 2, (width - bestScore.size()) / 2, "%s", bestScore.c_str());
        attroff(COLOR_PAIR(3));

        refresh(); // Faire l'affichage.

        int key = getch();

        // q pour sortir de l'interface terminal du jeu.
        if (key == 'q') {
            break;
        }

        if (isValidMove(key)) {
            model.setRandomElements(1);
        }

        if (!model.canMove()) {
            mvprintw(height / 2, (width - 20) / 2, "Jeu terminé ! (r : réinitialiser)");
            refresh();
            int r = getch();
            // r pour réinitialiser le jeu
            if (r == 'r') model.restart();
        }
    }

    delwin(gameWin);
    endwin();
}