#include "MoveEvent.h"

MoveEvent::MoveEvent(int startValue, int endValue, int iStart, int jStart, int iEnd, int jEnd) : startValue(startValue), endValue(endValue), iStart(iStart), jStart(jStart), iEnd(iEnd), jEnd(jEnd) {
    currentX = 0;
    currentY = 0;
}

int MoveEvent::getStartValue() {
    return startValue;
}

int MoveEvent::getEndValue() {
    return endValue;
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