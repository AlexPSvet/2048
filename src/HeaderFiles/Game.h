#ifndef GAME_H
#define GAME_H

#include "Case.h"
#include "Model.h"
#include "Graphics.h"
#include "Console.h"
#include "MoveEvent.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Game {
    public:
        Game(string pathFile);

        void start();

        // Get classes
        Model& getModel();
        Graphics& getGraphics();
        Console& getConsole();
    private:
        // Logic variables
        Model model;
        Graphics graphics;
        Console console;
        
        // Related score
        string pathFile;
        int getBestScoreFile();
        void setBestScoreFile(int bestScore);

        // General variables
        vector<Case> cases;
};

#endif