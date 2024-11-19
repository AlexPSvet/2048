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
        int getScore();
    private:
        sf::Font gameFont;
        sf::Texture backgroundText;

        vector<vector<int>> plateau;
        int score;
};

#endif