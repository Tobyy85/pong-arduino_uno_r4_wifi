#include "AI.h"

AI::AI(Paddle paddle, Ball ball, int screen_width, int screen_height): _paddle(paddle), _ball(ball){
    _screen_width = screen_width;
    _screen_height = screen_height;
}

bool AI::should_move(){
    bool r_should_move = _ball._x_vel > 0 && _paddle._x > _screen_width/2;  // If the paddle is on right side of the screen and the ball is moving to the right
    bool l_should_move = _ball._x_vel < 0 && _paddle._x < _screen_width/2;  // If the paddle is on the left side of the screen and the ball is moving to the left
    return r_should_move || l_should_move;
}

void AI::move(){
    if (should_move()){
        if (_ball._y < _paddle._y + _paddle._PADDLE_HEIGHT / 2.0 - 0.5){  // If the ball is above the middle of the paddle
            _paddle.move("UP");
        }else if (_ball._y > _paddle._y + _paddle._PADDLE_HEIGHT / 2.0 - 0.5){  // If the ball is below the middle of the paddle
            _paddle.move("DOWN");
        }
    }
}