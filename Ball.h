#ifndef BALL_H
#define BALL_H

#include "Arduino.h"
#include "Paddle.h"



class Ball{
    public:
        Ball(float x, float y, int screen_width, int screen_height);
        void move(Paddle left_paddle, Paddle right_paddle);
        void reset();
        
        float _x;
        float _y;







    private:
        const float _MAX_VEL = 1;
        float _original_x;
        float _original_y;
        float _x_vel;
        float _y_vel;
        int _screen_width;
        int _screen_height;



};








#endif

