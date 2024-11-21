#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using namespace std;

class Game {
    public:
        Game();

        // Game screen functions
        void start();
        void clear();
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
        void drawCase(sf::RenderWindow& window, int x_i, int y_i, int i, int j, float xCase, float yCase, int margin);
        bool isCaseInAnimation(int i, int j);
        MoveEvent getMoveEvent(int i, int j);
        void drawAnimation(sf::RenderWindow& window, MoveEvent event, float xCase, float yCase, int margin);
        bool checkMovement(sf::Event event);

        // Model functions
        void rotateTable();
        bool canMoveLeft();
        bool canMoveRight();
        bool canMoveUp();
        bool canMoveDown();
        bool canMove();
        void moveLeftRange(vector<int>& t, int startIndex, int endIndex);
        void addLeftValues(vector<int>& t);
        void moveLeft();
        void moveRightRange(vector<int>& t, int startIndex, int endIndex);
        void addRightValues(vector<int>& t);
        void moveRight();
        void moveDown();
        void moveUp();
        void setRandomElements(int amount);
        vector<tuple<int, int>> getEmptySlots();

        // Debug functions
        void printLine(const vector<int>& line);
        void printTable(const vector<vector<int>>& plateau);

        // Get variables
        vector<vector<int>>& getPlateau();
        vector<vector<int>>& getGraphicsPlateau();
        bool isAnimationLoaded();
        int getScore();
    private:
        // Graphics variables
        sf::Font gameFont;
        sf::Texture backgroundText;
        float xUnit;
        float yUnit;
        vector<MoveEvent> animatedTasks;

        // General variables
        vector<vector<int>> plateau;
        int score;
};

class MoveEvent {
    public:
        MoveEvent(int iStart, int jStart, float xStart, float yStart, float currentX, float currentY, int iEnd, int jEnd);
        int getjStart();
        int getiStart();
        float getStartX();
        float getStartY();
        float getCurrentX();
        float getCurrentY();
        void setCurrentX(float currentX);
        void setCurrentY(float currentY);
        int getiEnd();
        int getjEnd();
    private:
        int iStart;
        int jStart;
        float xStart;
        float yStart;
        float currentX;
        float currentY;
        int iEnd;
        int jEnd;
}

#endif