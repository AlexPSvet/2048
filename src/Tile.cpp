#include "Tile.h"

using namespace std;

Tile::Tile() {
    this->i = -1;
    this->j = -1;
    value = -1;
}

/**
 * Constructeur de la classe Tile (Tuile).
 * @param i l'indice de la ligne de la tuile.
 * @param j l'indice de la colonne de la tuile.
 */
Tile::Tile(int i, int j) {
    this->i = i;
    this->j = j;
    value = 0;
}

/**
 * Fonction pour rajouter un mouvement d'une tuile.
 * Ceci permet de stocker toutes les mouvements précédents
 * jusqu'à arriver au point final dans un tableau.
 * @param event la classe mouvement.
 */
void Tile::addAnimation(MoveEvent event) {
    events.push_back(event);
}

/**
 * Fonction pour modifier la liste des événements en rajount tout
 * d'abbord les événements d'une autre tuile en premier et puis les
 * événements de cette tuile.
 * Ceci est utile lors d'un mouvement d'addition, pour conserver les mouvements
 * de la case précédente qui s'additionne.
 */
void Tile::addAnimations(Tile& tile) {
    vector<MoveEvent>& eventsOtherTile = tile.getEvents();
    for (int i = 0; i < events.size(); i++) {
        eventsOtherTile.push_back(events[i]);
    }
    events = eventsOtherTile;
}

int Tile::getValue() {
    return value;
}

void Tile::setValue(int value) {
    this->value = value;
}

int Tile::getIndexI() {
    return i;
}

int Tile::getIndexJ() {
    return j;
}

void Tile::setIndexI(int i) {
    this->i = i;
}

void Tile::setIndexJ(int j) {
    this->j = j;
}

MoveEvent& Tile::getLastAnimation() {
    return events[0];
}

void Tile::removeAnimation(int i) {
    events.erase(events.begin() + i);
}

bool Tile::hasAnimation() {
    return events.size() != 0;
}

vector<MoveEvent>& Tile::getEvents() {
    return events;
}