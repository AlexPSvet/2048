#ifndef GAME_H
#define GAME_H

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
        vector<vector<int>> plateau;
        int score;
};

#endif