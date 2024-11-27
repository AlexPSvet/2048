#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MoveEvent.h"
#include "Case.h"
#include "Model.h"
#include "Console.h"
#include "Graphics.h"
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Game {
    public:
        Game(string pathFile);

        void start();
        void restart();

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