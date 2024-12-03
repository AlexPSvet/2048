#ifndef CASE_H
#define CASE_H

#include "MoveEvent.h"
#include <vector>
using namespace std;

class Case {
    public:
        Case();
        Case(int i, int j);

        int getValue();
        void setValue(int value);
        int getIndexI();
        int getIndexJ();
        void setIndexI(int i);
        void setIndexJ(int j);

        MoveEvent& getLastAnimation();
        void removeAnimation(int i);
        bool hasAnimation();
        void addAnimation(MoveEvent event);
        void addAnimations(Case& caseObjet);
        vector<MoveEvent>& getEvents();
    private:
        int value = 0;
        int i;
        int j;
        vector<MoveEvent> events;
};

#endif