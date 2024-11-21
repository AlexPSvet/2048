#include "Case.h"

#include <vector>
using namespace std;

Case::Case() {
    this->i = -1;
    this->j = -1;
    value = -1;
}

Case::Case(int i, int j) {
    this->i = i;
    this->j = j;
    value = 0;
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

void Case::removeLastAnimation() {
    events.erase(events.begin());
}

bool Case::hasAnimation() {
    return events.size() != 0;
}

vector<MoveEvent>& Case::getEvents() {
    return events;
}

void Case::addAnimation(MoveEvent event) {
    events.push_back(event);
}

void Case::addAnimations(Case& caseObjet) {
    vector<MoveEvent>& events2 = caseObjet.getEvents();
    for (int i = 0; i < events.size(); i++) {
        events2.push_back(events[i]);
    }
    events = events2;
}