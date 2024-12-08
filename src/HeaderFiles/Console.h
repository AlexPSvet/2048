#ifndef CONSOLE_H
#define CONSOLE_H

#include "Model.h"
#include "ncurses.h"
#include <iostream>
#include <iomanip>
using namespace std;

class Console {
    public:
        Console(Model& game);

        void displayGame();
        bool isValidMove(int key);
        void drawBoard(WINDOW* win, int cellHeight, int cellWidth, int startY, int startX);
        void setupColors();
        int findNumberColor(int value);
    private:
        Model& model;

        int getMaxTextLenght();
};

#endif