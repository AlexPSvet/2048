#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Case.h"
#include "Model.h"
using namespace sf;

class Graphics {
    public:
        Graphics(Model& model);

        void drawText(
            RenderWindow& window, 
            std::string text, 
            float width, float height, 
            int x, int y, 
            float marginWidth, float marginHeight, 
            float outline,
            Color fillColor, Color outlineColor, Color textColor);

        void displayWindow();
        void displayTable(RenderWindow& window);
        void displayInfo(RenderWindow& window);
        void displayBackground(RenderWindow& window);

        void drawAnimLeftDown(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float xRemove, float yRemove);
        void drawAnimRightUp(RenderWindow& window, Case& caseObjet, float caseLenght, float margin, float xAdd, float yAdd);
        void drawAnimation(RenderWindow& window, Case& caseObjet, float caseLenght, float margin);
        
        Color getColor(int caseNumber);
        bool checkMovement(Event event);
    private:
        // Graphics variables
        Font gameFont;
        Texture backgroundText;
        float unit;
        Model& model;
        // Valid movement
        bool isValidMovement;
};

#endif