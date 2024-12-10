#include "MoveEvent.h"

MoveEvent::MoveEvent() {}

/**
 * Constructeur de la classe MoveEvent.
 * Cette classe permet de pouvoir registrer un mouvement
 * réalisée dans le plateau pour ainsi pouvoir après le dessiner
 * dans l'interface graphique pour les animations.
 * 
 * @param value : la valeur de la tuile au moment du mouvement.
 * @param isAddAnim : booléen pour dire si le mouvement est pour
 * faire l'addition de deux cases.
 * @param iStart : ligne de départ du mouvement.
 * @param jStart : colonne de départ du mouvement.
 * @param iEnd : ligne de fin du mouvement.
 * @param jEnd : colonne de fin du mouvement.
 * 
 * Auteur : Alejandro Perez Svetlitsky
 */
MoveEvent::MoveEvent(
    int value, 
    bool isAddAnim, 
    int iStart, 
    int jStart, 
    int iEnd, 
    int jEnd) : 
    value(value), 
    isAddAnim(isAddAnim), 
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

// FONCTIONS GET/SET

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