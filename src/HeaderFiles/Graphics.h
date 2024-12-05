#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Model.h"
#include <iostream>
#include <vector>
using namespace sf;

class Graphics {
    public:
        Graphics(Model& game);

        void drawText(
            RenderWindow& window, 
            std::string text, 
            float width, float height, 
            int x, int y, 
            float marginWidth, float marginHeight, 
            float outline,
            Color fillColor, Color outlineColor, Color textColor);

        void displayGame();
        void updateUnits(RenderWindow& window);

        void drawRestartMenu(RenderWindow& window);
        void checkButtons(RenderWindow& window);

        void updateGame(RenderWindow& window);

        void displayTable(RenderWindow& window);
        void displayInfo(RenderWindow& window);
        void displayBackground(RenderWindow& window);

        bool endAnimation(Tile& tile, int i, float xEnd, float yEnd);
        void checkAnimation(RenderWindow& window, Tile& tile, float timeElapsed);
        void drawAnimation(RenderWindow& window, Tile& tile, float x, float y);
        void drawAnimations(RenderWindow& window, float timeElapsed);
        
        sf::Color getColor(int caseNumber);
        bool checkMovement(Event event);

        bool isCasesInAnimation();
    private:
        Model& model;
        // Graphics variables
        Font gameFont;
        Texture backgroundText;
        float unit;
        float xRectangle;
        float yRectangle;
        float rectangleLenght;
        float caseLenght;
        float caseMargin;
        // Animation
        Clock clock;
        // Valid movement
        bool isValidMovement;
};

#endif