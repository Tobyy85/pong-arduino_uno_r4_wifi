#ifndef AI_H
#define AI_H

#include "Arduino.h"
#include "Ball.h"
// Paddle.h is not included here because it is included in Ball.h already

class AI {
    public:
        AI(Paddle& paddle, Ball& ball, int screen_width, int screen_height);
        void move();

    private:
        Paddle& _paddle;
        Ball& _ball;
        int _screen_width;
        int _screen_height;
        int last_y_pos_of_paddle;
        float last_y_pos_of_ball;
};






#endif