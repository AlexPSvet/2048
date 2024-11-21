#ifndef MOVEEVENT_H
#define MOVEEVENT_H

class MoveEvent {
    public:
        MoveEvent(int startValue, int endValue, int iStart, int jStart, int iEnd, int jEnd);

        int getStartValue();
        int getEndValue();
        int getjStart();
        int getiStart();
        float getCurentX();
        float getCurentY();
        void setCurentX(float currentX);
        void setCurentY(float currentY);
        int getiEnd();
        int getjEnd();
    private:
        int startValue;
        int endValue;
        int iStart;
        int jStart;
        float currentX;
        float currentY;
        int iEnd;
        int jEnd;
};

#endif