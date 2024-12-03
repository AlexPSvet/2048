#include "Case.h"

#include <vector>
using namespace std;

Case::Case() {
    this->i = -1;
    this->j = -1;
    value = -1;
}

/**
 * Constructeur de la classe Case.
 * @param i l'indice de la ligne de la case.
 * @param j l'indice de la colonne de la case.
 */
Case::Case(int i, int j) {
    this->i = i;
    this->j = j;
    value = 0;
}

/**
 * Fonction pour rajouter un mouvement d'une case.
 * Ceci permet de stocker toutes les mouvements précédents
 * jusqu'à arriver au point final dans un tableau.
 * @param event la classe mouvement.
 */
void Case::addAnimation(MoveEvent event) {
    events.push_back(event);
}

/**
 * Fonction pour modifier la liste des événements en rajount tout
 * d'abbord les événements d'une autre case en premier et puis les
 * événements de cette case.
 * Ceci est utile lors d'un mouvement d'addition, pour conserver les mouvements
 * de la case précédente qui s'additionne.
 */
void Case::addAnimations(Case& caseObjet) {
    vector<MoveEvent>& events2 = caseObjet.getEvents();
    for (int i = 0; i < events.size(); i++) {
        events2.push_back(events[i]);
    }
    events = events2;
}

int Case::getValue() {
    return value;
}

void Case::setValue(int value) {
    this->value = value;
}

int Case::getIndexI() {
    return i;
}

int Case::getIndexJ() {
    return j;
}

void Case::setIndexI(int i) {
    this->i = i;
}

void Case::setIndexJ(int j) {
    this->j = j;
}

MoveEvent& Case::getLastAnimation() {
    return events[0];
}

void Case::removeAnimation(int i) {
    events.erase(events.begin() + i);
}

bool Case::hasAnimation() {
    return events.size() != 0;
}

vector<MoveEvent>& Case::getEvents() {
    return events;
}