#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MoveEvent.h"
#include "Case.h"
#include "Model.h"
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

        // Graphics functions
        void displayWindow();
        void displayBackground(sf::RenderWindow& window);
        void displayTitle(sf::RenderWindow& window);
        void displayTable(sf::RenderWindow& window);
        void displayScore(sf::RenderWindow& window);
        sf::Color getColor(int caseNumber);
        void drawCase(sf::RenderWindow& window, int value, int x, int y, float xCase, float yCase);
        bool drawAnimation(sf::RenderWindow& window, Case& caseObjet, float xCase, float yCase, float xStart, float yStart, float margin);
        bool checkMovement(sf::Event event);

        // Get classes
        Model getModel();
    private:
        // Graphics variables
        sf::Font gameFont;
        sf::Texture backgroundText;
        float xUnit;
        float yUnit;
        vector<MoveEvent> animatedTasks;

        // Logic variables
        Model model;

        // General variables
        vector<Case> cases;
};

#endif