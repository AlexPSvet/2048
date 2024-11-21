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
        // Move methods
        bool canMoveGeneral(int i1, int j1, int i2, int j2);
        bool canMoveLeft();
        bool canMoveRight();
        bool canMoveUp();
        bool canMoveDown();
        bool canMove();
        bool addValues(int i1, int j1, int i2, int j2);
        void moveLeftRange(int i, int startIndex, int endIndex);
        void addLeftValues(int i);
        void moveLeft();
        void moveRightRange(int i, int startIndex, int endIndex);
        void addRightValues(int i);
        void moveRight();
        void moveUpRange(int j, int startIndex, int endIndex);
        void addUpValues(int j);
        void moveUp();
        void moveDownRange(int j, int startIndex, int endIndex);
        void addDownValues(int j);
        void moveDown();
        // Util methods
        void clear();
        void removeCase(Case& caseObjet);
        // Cases spawn methods
        void setRandomElements(int amount);
        std::vector<std::tuple<int, int>> getEmptySlots();
        // Debug methods
        void printLine(int i);
        void printPlateau();
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