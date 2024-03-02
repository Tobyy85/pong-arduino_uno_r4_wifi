#ifndef PADDLE_H
#define PADDLE_H

#include "Arduino.h"


class Paddle{
    public:
        Paddle(int x, int y, int screen_height, int paddle_height);
        void move(String direction);
        void reset();

        int _x;
        int _y;
        int _PADDLE_HEIGHT;


    private:
        const int _VEL = 1.2;
        int _original_x;
        int _original_y;
        int _screen_height;
};

#endif