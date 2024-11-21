#include "Game.h"

MoveEvent::MoveEvent(int iStart, int jStart, float startX, float startY, float currentX, float currentY, int iEnd, int jEnd) : iStart(iStart), jStart(jStart), xStart(xStart), yStart(yStart), currentX(currentX), currentY(currentY), iEnd(iEnd), jEnd(jEnd) {}

float MoveEvent::getStartX() {
    return xStart;
}

float MoveEvent::getStartY() {
    return yStart;
}

int MoveEvent::getjStart() {
    return jStart;
}

int MoveEvent::getiStart() {
    return iStart;
}

float MoveEvent::getCurrentX() {
    return currentX;
}

float MoveEvent::getCurrentY() {
    return currentY;
}

void MoveEvent::setCurrentX(float currentX) {
    this->currentX = currentX;
}

void MoveEvent::setCurrentY(float currentY) {
    this->currentY = currentY;
}

int MoveEvent::getiEnd() {
    return iEnd;
}

int MoveEvent::getjEnd() {
    return jEnd;
}