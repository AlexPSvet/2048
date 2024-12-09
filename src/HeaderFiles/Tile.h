    #ifndef TILE_H
    #define TILE_H

    #include "MoveEvent.h"
    #include <vector>
    using namespace std;

    class Tile {
        public:
            Tile();
            Tile(int i, int j);

            int getValue();
            void setValue(int value);
            int getIndexI();
            int getIndexJ();
            void setIndexI(int i);
            void setIndexJ(int j);

            MoveEvent& getFirstAnimation();
            void removeAnimation(int i);
            bool hasAnimation();
            void addAnimation(MoveEvent event);
            void addAnimations(Tile& caseObjet);
            vector<MoveEvent>& getEvents();
        private:
            int value = 0;
            int i;
            int j;
            vector<MoveEvent> events;
    };

    #endif