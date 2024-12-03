#include "MoveEvent.h"

MoveEvent::MoveEvent() {}

MoveEvent::MoveEvent(
    int value, 
    bool isAddAnim, 
    bool canEndMoveAfter,
    int iStart, 
    int jStart, 
    int iEnd, 
    int jEnd) : 
    value(value), 
    isAddAnim(isAddAnim), 
    canEndMoveAfter(canEndMoveAfter),
    iStart(iStart), 
    jStart(jStart), 
    iEnd(iEnd), 
    jEnd(jEnd)
{
    xStart = -1;
    yStart = -1;
    currentX = -1;
    currentY = -1;
}

int MoveEvent::getValue() {
    return value;
}

bool MoveEvent::isAddAnimation() {
    return isAddAnim;
}

bool MoveEvent::canMoveAfter() {
    return canEndMoveAfter;
}

int MoveEvent::getjStart() {
    return jStart;
}

int MoveEvent::getiStart() {
    return iStart;
}

float MoveEvent::getStartX() {
    return xStart;
}

float MoveEvent::getStartY() {
    return yStart;
}

void MoveEvent::setStartX(float xStart) {
    this->xStart = xStart;
}

void MoveEvent::setStartY(float yStart) {
    this->yStart = yStart;
}

float MoveEvent::getCurentX() {
    return currentX;
}

float MoveEvent::getCurentY() {
    return currentY;
}

void MoveEvent::setCurentX(float currentX) {
    this->currentX = currentX;
}

void MoveEvent::setCurentY(float currentY) {
    this->currentY = currentY;
}

int MoveEvent::getiEnd() {
    return iEnd;
}

int MoveEvent::getjEnd() {
    return jEnd;
}