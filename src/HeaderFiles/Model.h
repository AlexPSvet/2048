#ifndef MODEL_H
#define MODEL_H

#include "Tile.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

enum class GameState {
    Running,
    End
};

class Model {
    public:
        Model(int lines, int columns);

        bool compareValues(int i1, int j1, int i2, int j2);
        bool canMoveLeft();
        bool canMoveRight();
        bool canMoveUp();
        bool canMoveDown();
        bool canMove();

        void moveCase(int i1, int j1, int i2, int j2);
        void moveLeftRange(int i, int startIndex, int endIndex);
        void moveRightRange(int i, int startIndex, int endIndex);
        void moveUpRange(int j, int startIndex, int endIndex);
        void moveDownRange(int j, int startIndex, int endIndex);

        bool addCases(int i1, int j1, int i2, int j2);
        void addLeftValues(int i);
        void addRightValues(int i);
        void addUpValues(int j);
        void addDownValues(int j);

        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        void setRandomElements(int amount);
        std::vector<std::tuple<int, int>> getEmptySlots();

        void printLine(int i);
        void printPlateau();

        void restart();
        void removeTile(Tile& caseObjet);
        bool didPlayerWin();
        GameState getGameState();
        void setGameState(GameState state);
        vector<Tile>& getTiles();
        Tile& getTile(int i, int j);
        int getMaxTileNumber();
        void updateScore();
        bool validTile(int i, int j);
        int getBestScore();
        void setBestScore(int bestScore);
        int getLines();
        int getColumns();
        int getScore();
        void setScore(int score);
    private:
        GameState state;
        vector<Tile> tiles;
        int score = 0;
        int bestScore;
        int lines;
        int columns;
};

#endif