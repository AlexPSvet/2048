#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
using namespace std;

class Jeu {
    public:
        Jeu();

        void start();
        void printScore();
        bool validMovement();
        string verifyAnswer();
        void printConsole();
        int getMaxTextLenght();
        void setRandomElements(int amount);
        vector<tuple<int, int>> getEmptySlots();
        void printLine(const vector<int>& line);
        void printTable(const vector<vector<int>>& plateau);

        void rotateTable();
        bool canMoveLeft();
        bool canMoveRight();
        bool canMoveUp();
        bool canMoveDown();
        bool canMove();
        void moveLeftRange(std::vector<int>& t, int startIndex, int endIndex);
        void addLeftValues(std::vector<int>& t);
        void moveLeft();
        void moveRightRange(std::vector<int>& t, int startIndex, int endIndex);
        void addRightValues(std::vector<int>& t);
        void moveRight();
        void moveDown();
        void moveUp();

        vector<vector<int>> getPlateau();
        int getScore();
    private:
        vector<vector<int>> plateau;
        int score;
};

#endif