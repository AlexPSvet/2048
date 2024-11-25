#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Case.h"
#include "Model.h"
using namespace sf;

class Graphics {
    public:
        Graphics(Model& model);

        void displayWindow();
        void displayScore(RenderWindow& window);
        void displayTitle(RenderWindow& window);
        void displayTable(RenderWindow& window);
        void displayBackground(RenderWindow& window);

        void drawCase(RenderWindow& window, int value, int x, int y, float width, float height);
        bool drawAnimation(RenderWindow& window, Case& caseObjet, float xCase, float yCase, float xStart, float yStart, float margin);
        Color getColor(int caseNumber);

        bool checkMovement(Event event);
    private:
        // Graphics variables
        sf::Font gameFont;
        sf::Texture backgroundText;
        float xUnit;
        float yUnit;
        Model& model;
        // Valid movement
        bool isValidMovement;
};

#endif