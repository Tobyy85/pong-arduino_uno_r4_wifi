#ifndef AI_H
#define AI_H

#include "Arduino.h"
#include "Ball.h"
// Paddle.h is not included here because it is included in Ball.h


class AI{
    public:
        AI(int screen_width, int screen_height);
        String where_to_move(int paddle_y, int paddle_height, float ball_y);
        


    private:
        int _screen_width;
        int _screen_height;

        
};











#endif