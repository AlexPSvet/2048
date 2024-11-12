#include <vector>
#include "modele.h"

void moveLeftValues() {
    for (int i = 0; i < table.size(); i++) {
        int first0Index = -1;
        for (int j = 0; j < table[i].size(); j++) {
            if (table[i][j] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[i][j];
                table[i][j] = 0;
                table[i][first0Index] = value;
                first0Index += 1;
            }
        }
    }
}

void moveLeft() {
    moveLeftValues();
    for (int i = 0; i < table.size(); i++) {
        for (int j = table[i].size() - 1; j > 0; j--) {
            if (table[i][j] != 0 && table[i][j-1] == table[i][j]) {
                int value = table[i][j] * 2;
                table[i][j] = 0;
                table[i][j-1] = value;
            }
        }
    }
    moveLeftValues();
}

void moveRightValues() {
    for (int i = 0; i < table.size(); i++) {
        int first0Index = -1;
        for (int j = table[i].size() - 1; j >= 0; j--) {
            if (table[i][j] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[i][j];
                table[i][j] = 0;
                table[i][first0Index] = value;
                first0Index -= 1;
            }
        }
    }
}

void moveRight() {
    moveRightValues();
    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table[i].size() - 1; j++) {
            if (table[i][j] != 0 && table[i][j+1] == table[i][j]) {
                int value = table[i][j] * 2;
                table[i][j] = 0;
                table[i][j+1] = value;
            }
        }
    }
    moveRightValues();
}

void moveDownValues() {
    for (int i = 0; i < 4; i++) {
        int first0Index = -1;
        for (int j = 3; j >= 0; j--) {
            if (table[j][i] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[j][i];
                table[j][i] = 0;
                table[first0Index][i] = value;
                first0Index -= 1;
            }
        }
    }   
}

void moveDown() {
    moveDownValues();
    for (int j = 0; j < table[0].size(); j++) {
        for (int i = table.size() - 1; i > 0; i--) {
            if (table[i][j] != 0 && table[i-1][j] == table[i][j]) {
                int value = table[i][j] * 2;
                table[i-1][j] = 0;
                table[i][j] = value;
            }
        }
    }
    moveDownValues();
}

void moveUpValues() {
    for (int i = 0; i < 4; i++) {
        int first0Index = -1;
        for (int j = 0; j < 4; j++) {
            if (table[j][i] == 0) {
                if (first0Index == -1) {
                    first0Index = j;
                }
            } else if (first0Index != -1) {
                int value = table[j][i];
                table[j][i] = 0;
                table[first0Index][i] = value;
                first0Index += 1;
            }
        }
    }
}

void moveUp() {
    moveUpValues();
    for (int j = 0; j < table[0].size(); j++) {
        for (int i = 0; i < table.size() - 1; i++) {
            if (table[i][j] != 0 && table[i+1][j] == table[i][j]) {
                int value = table[i][j] * 2;
                table[i+1][j] = 0;
                table[i][j] = value;
            }
        }
    }
    moveUpValues();
}