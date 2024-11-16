#ifndef MODELE_H
#define MODELE_H

#include <vector>
extern std::vector<std::vector<int>> table;

bool canMoveRight();
bool canMoveLeft();
bool canMoveUp();
bool canMoveDown();
bool canMove();
void moveLeft();
void moveRight();
void moveUp();
void moveDown();

#endif