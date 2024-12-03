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
    private:
        Model& model;

        int getMaxTextLenght();
        void printConsole();
        string verifyAnswer();
        bool validMovement();
};

#endif