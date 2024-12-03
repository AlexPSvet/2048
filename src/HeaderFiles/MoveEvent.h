#ifndef MOVEEVENT_H
#define MOVEEVENT_H

class MoveEvent {
    public:
        MoveEvent();
        MoveEvent(int value, bool isAddAnim, bool canEndMoveAfter, int iStart, int jStart, int iEnd, int jEnd);

        int getValue();
        int getjStart();
        int getiStart();
        int getiEnd();
        int getjEnd();

        bool isAddAnimation();
        bool canMoveAfter();
        float getCurentX();
        float getCurentY();
        float getStartX();
        float getStartY();
        void setStartX(float startX);
        void setStartY(float startY);
        void setCurentX(float currentX);
        void setCurentY(float currentY);
    private:
        int value;
        bool isAddAnim;
        bool canEndMoveAfter;
        int iStart;
        int jStart;
        float xStart;
        float yStart;
        float currentX;
        float currentY;
        int iEnd;
        int jEnd;
};

#endif