#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MoveEvent.h"
#include "Case.h"
#include "Model.h"
#include "Graphics.h"
#include <string>
#include <vector>
using namespace std;

class Game {
    public:
        Game();

        // Game screen functions
        void start();
        bool validMovement();
        string verifyAnswer();
        void printConsole();
        int getMaxTextLenght();

        // Get classes
        Model getModel();
        Graphics getGraphics();
    private:
        // Logic variables
        Model model;
        Graphics graphics;

        // General variables
        vector<Case> cases;
};

#endif