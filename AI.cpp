#include "AI.h"

AI::AI(Paddle& paddle, Ball& ball, int screen_width, int screen_height)
    : _paddle(paddle), _ball(ball), _screen_width(screen_width), _screen_height(screen_height)
{
    last_y_pos_of_paddle = screen_height;
    last_y_pos_of_ball = screen_height;
}

// TODO if the ball is stuck on the second paddle, then move the paddle
// TODO move the paddle only if the ball is moving towards the paddle
void AI::move(){
    String side;
    if (_paddle._x < _screen_width/2 - 0.5){  // If the paddle is on the left side of the screen
        side = "LEFT";
    }else if (_screen_width/2 - 0.5 < _paddle._x){  // If the paddle is on the right side of the screen
        side = "RIGHT";
    }
    if ((side == "LEFT" && _ball._x_vel < 0) || (side == "RIGHT" && _ball._x_vel > 0)){
        float mid_of_paddle = _paddle._y + _paddle._PADDLE_HEIGHT/2 - 0.5;
        bool ball_hit_paddle;
        if (side == "LEFT"){  // If the paddle is on the left side of the screen
            ball_hit_paddle = _ball._x == _paddle._x + 1;
        }else if (side == "RIGHT"){  // If the paddle is on the right side of the screen
            ball_hit_paddle = _ball._x == _paddle._x - 1;
        }

        if (ball_hit_paddle && last_y_pos_of_paddle == _paddle._y && int(last_y_pos_of_ball) == int(_ball._y)){  // Move the paddle if the ball is stuck
            bool can_move_paddle_down = (_paddle._y < _screen_height - _paddle._PADDLE_HEIGHT) && (_paddle._y != _ball._y);
            bool can_move_paddle_up = (_paddle._y > 0) && (_paddle._y + _paddle._PADDLE_HEIGHT != _ball._y);
            if (can_move_paddle_down && can_move_paddle_up){
                if (_ball._y > mid_of_paddle){
                    _paddle.move("UP");
                }else if (_ball._y < mid_of_paddle){
                    _paddle.move("DOWN");
                }else{
                    // Move the paddle in random direction
                    if (random(0, 2) == 0){
                        _paddle.move("DOWN");
                    }else{
                        _paddle.move("UP");
                    }
                    Serial.println("The paddle can move in both directions so it is moving in random direction");
                }
            }else if (can_move_paddle_down){
                _paddle.move("DOWN");
            }else if (can_move_paddle_up){
                _paddle.move("UP");
            }else{
                Serial.println("The paddle is stuck and cannot move");
            }
        }else{
            if (_ball._y > mid_of_paddle){
                _paddle.move("DOWN");
            }else if (_ball._y < mid_of_paddle){
                _paddle.move("UP");
            }
        }

        if (ball_hit_paddle){
            last_y_pos_of_paddle = _paddle._y;
            last_y_pos_of_ball = _ball._y;
        }
    }
}