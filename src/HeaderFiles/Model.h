#ifndef MODEL_H
#define MODEL_H

#include "Case.h"
#include <vector>
using namespace std;

enum class GameState {
    Running,
    End
};

class Model {
    public:
        // Class constructor
        Model(int lines, int columns);

        // Can move methos
        bool compareValues(int i1, int j1, int i2, int j2);

        bool canMoveLeftLine(int i, int startIndex, int endIndex);
        bool canMoveRightLine(int i, int startIndex, int endIndex);
        bool canMoveUpLine(int j, int startIndex, int endIndex);
        bool canMoveDownLine(int j, int startIndex, int endIndex);
        bool canMoveLeft();
        bool canMoveRight();
        bool canMoveUp();
        bool canMoveDown();
        bool canMove();

        // Move methods
        void moveCase(int i1, int j1, int i2, int j2);
        void moveLeftRange(int i, int startIndex, int endIndex);
        void moveRightRange(int i, int startIndex, int endIndex);
        void moveUpRange(int j, int startIndex, int endIndex);
        void moveDownRange(int j, int startIndex, int endIndex);
        // Add cases methods
        bool addCases(int i1, int j1, int i2, int j2);
        void addLeftValues(int i);
        void addRightValues(int i);
        void addUpValues(int j);
        void addDownValues(int j);
        // Move functions
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        // Cases spawn methods
        void setRandomElements(int amount);
        std::vector<std::tuple<int, int>> getEmptySlots();

        // Debug methods
        void printLine(int i);
        void printPlateau();

        // Get methods
        void restart();
        void removeCase(Case& caseObjet);
        bool didPlayerWin();
        GameState getGameState();
        void setGameState(GameState state);
        vector<Case>& getCases();
        Case& getCase(int i, int j);
        int getMaxCaseNumber();
        void updateScore();
        bool validCase(int i, int j);
        int getBestScore();
        void setBestScore(int bestScore);
        int getLines();
        int getColumns();
        int getScore();
        void setScore(int score);
    private:
        GameState state;
        vector<Case> cases;
        int score = 0;
        int bestScore;
        int lines;
        int columns;
};

#endif