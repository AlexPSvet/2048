#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Model.h"
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

        void displayTable(RenderWindow& window, float timeElapsed);
        void displayInfo(RenderWindow& window);
        void displayBackground(RenderWindow& window);

        bool endAnimation(Case& caseObjet, int i, float xEnd, float yEnd);
        void checkAnimation(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float timeElapsed);
        void drawAnimation(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float x, float y);
        
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