#include "MoveEvent.h"

MoveEvent::MoveEvent(int value, bool isAddAnim, int iStart, int jStart, int iEnd, int jEnd) : value(value), isAddAnim(isAddAnim), iStart(iStart), jStart(jStart), iEnd(iEnd), jEnd(jEnd) {
    currentX = 0;
    currentY = 0;
}

int MoveEvent::getValue() {
    return value;
}

bool MoveEvent::isAddAnimation() {
    return isAddAnim;
}

int MoveEvent::getjStart() {
    return jStart;
}

int MoveEvent::getiStart() {
    return iStart;
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