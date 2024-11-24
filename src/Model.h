#ifndef MODEL_H
#define MODEL_H

#include "Case.h"
#include <vector>
using namespace std;

class Model {
    public:
        // Class constructor
        Model();
        Model(int lines, int columns);

        // Can move methos
        bool compareValues(int i1, int j1, int i2, int j2);
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
        void clear();
        void removeCase(Case& caseObjet);
        // Get methods
        vector<Case>& getCases();
        int getCasesInAnimation();
        Case& getCase(int i, int j);
        bool validCase(int i, int j);
        int getLines();
        int getColumns();
        int getScore();
    private:
        vector<Case> cases;
        int score;
        int lines;
        int columns;
};

#endif