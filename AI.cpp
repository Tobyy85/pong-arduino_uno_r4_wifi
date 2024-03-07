#include "AI.h"

AI::AI(Paddle& paddle, Ball& ball, int screen_width, int screen_height)
    : _paddle(paddle), _ball(ball), _screen_width(screen_width), _screen_height(screen_height)
{
}

void AI::move(){
    float mid_of_paddle = _paddle._y + _paddle._PADDLE_HEIGHT/2 - 0.5;
    if (_ball._y > mid_of_paddle){
        _paddle.move("DOWN");
    }
    else if (_ball._y < mid_of_paddle){
        _paddle.move("UP");
    }
}