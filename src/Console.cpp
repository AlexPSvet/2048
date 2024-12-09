#include "Console.h"
#include <ncurses.h>
using namespace std;

Console::Console(Model& model) : model(model) {}

/** Retrouve le nombre le plus grand en caractères. */
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

/** Configuration des couleurs pour ncurses. */
void Console::setupColors() {
    if (has_colors() && can_change_color()) {
        start_color();
        // Couleurs pour texte normal
        init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
        init_pair(2, COLOR_WHITE, COLOR_RED);
        init_pair(3, COLOR_WHITE, COLOR_MAGENTA);

        // Couleurs pour les tuiles
        use_default_colors(); // Use the terminal's default background
        // Define custom RGB colors (scaled from 0 to 1000)
        init_color(10, 804, 0, 1000);  // Tile 2: RGB(204, 0, 255)
        init_color(11, 529, 55, 651); // Tile 4: RGB(135, 14, 166)
        init_color(12, 741, 35, 576); // Tile 8: RGB(189, 9, 147)
        init_color(13, 463, 43, 365); // Tile 16: RGB(118, 11, 93)
        init_color(14, 337, 35, 627); // Tile 32: RGB(86, 9, 160)
        init_color(15, 63, 35, 627);  // Tile 64: RGB(16, 9, 160)
        init_color(16, 78, 592, 808); // Tile 128: RGB(20, 151, 206)
        init_color(17, 78, 808, 424); // Tile 256: RGB(20, 206, 108)
        init_color(18, 675, 808, 78); // Tile 512: RGB(172, 206, 20)
        init_color(19, 808, 392, 78); // Tile 1024: RGB(206, 100, 20)
        init_color(20, 890, 94, 15);  // Tile 2048: RGB(227, 24, 4)
        init_color(21, 471, 51, 8);   // Default tile: RGB(120, 13, 2)

        // Assign color pairs (foreground: white, background: custom color)
        for (int i = 10; i <= 21; i++) {
            init_pair(i, COLOR_WHITE, i); // White text on a colored background
        }
    }
}

int Console::findNumberColor(int value) {
    int exposant = 0;
    while (value % 2 == 0) {
        value /= 2;
        exposant += 1;
    }
    return exposant;
}

/** Affiche le plateau de jeu en utilisant ncurses. */
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

            wattroff(win, COLOR_PAIR(colorPair));
        }
    }

    wrefresh(win); // Rafraîchir l'affichage
}

bool Console::isValidMove(int key) {
    switch (key) {
        case KEY_UP:
            if (model.canMoveUp()) {
                model.moveUp();
                return true;
            }
            break;
        case KEY_DOWN:
            if (model.canMoveDown()) {
                model.moveDown();
                return true;
            }
            break;
        case KEY_LEFT:
            if (model.canMoveLeft()) {
                model.moveLeft();
                return true;
            }
            break;
        case KEY_RIGHT:
            if (model.canMoveRight()) {
                model.moveRight();
                return true;
            }
            break;
    }
    return false;
}

/** Gestionnaire principal du jeu avec ncurses. */
void Console::displayGame() {
    initscr();               // Initialiser ncurses
    noecho();                // Désactiver l'affichage des touches pressées
    cbreak();                // Désactiver la mise en tampon des entrées
    keypad(stdscr, TRUE);    // Activer les flèches du clavier
    curs_set(0);             // Masquer le curseur

    setupColors();           // Configurer les couleurs

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

        refresh();

        int key = getch();

        if (key == 'q') {
            break;
        }

        if (isValidMove(key)) {
            model.setRandomElements(1);
        }

        if (!model.canMove()) {
            mvprintw(height / 2, (width - 20) / 2, "Jeu terminé !");
            refresh();
            getch();
            model.restart();
        }
    }

    delwin(gameWin);
    endwin();
}