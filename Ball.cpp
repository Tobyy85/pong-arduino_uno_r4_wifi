#include "Ball.h"

/**
 * @brief Constructs a new Ball object.
 *
 * @param x The initial x-coordinate of the ball.
 * @param y The initial y-coordinate of the ball.
 * @param screen_width The width of the screen.
 * @param screen_height The height of the screen.
 */
Ball::Ball(float x, float y, int screen_width, int screen_height){
    _original_x = x;
    _original_y = y;
    _x = x;
    _y = y;
    _x_vel = _MAX_VEL;
    _y_vel = 0;
    _screen_width = screen_width;
    _screen_height = screen_height;
}


void Ball::move(Paddle left_paddle, Paddle right_paddle){
    if (_x == 1 && (left_paddle._y <= _y && _y <= left_paddle._y + left_paddle._PADDLE_HEIGHT)){  // If the ball is at the left paddle
        _x_vel *= -1;  // Reverse the x-velocity
        float left_paddle_mid_y = left_paddle._y + left_paddle._PADDLE_HEIGHT / 2.0  - 0.5;  // The y-coordinate of the middle of the left paddle
        float left_y_difference = int(_y) - left_paddle_mid_y;  // The difference between the y-coordinate of the ball and the middle of the left paddle
        _y_vel = (_MAX_VEL / (left_paddle._PADDLE_HEIGHT / 2.0)) * left_y_difference;  // Set the y-velocity based on the difference between the ball's y-coordinate and the middle of the left paddle

    }else if (_x == _screen_width - 2 && (right_paddle._y <= _y && _y <= right_paddle._y + right_paddle._PADDLE_HEIGHT)){  // If the ball is at the right paddle
        _x_vel *= -1;  // Reverse the x-velocity
        float right_paddle_mid_y = right_paddle._y + right_paddle._PADDLE_HEIGHT / 2.0 - 0.5;  // The y-coordinate of the middle of the right paddle
        float right_y_difference = int(_y) - right_paddle_mid_y;  // The difference between the y-coordinate of the ball and the middle of the right paddle
        _y_vel = (_MAX_VEL / (right_paddle._PADDLE_HEIGHT / 2.0)) * right_y_difference;  // Set the y-velocity based on the difference between the ball's y-coordinate and the middle of the right paddle
    }

    if (_y <= 0 || _y >= _screen_height - 1){  // If the ball is at the top or bottom of the screen
        _y_vel *= -1;  // Reverse the y-velocity
    }

    
    _x += _x_vel;
    _y += _y_vel;
    
}

/**
 * Resets the ball to its initial position and velocity.
 */
void Ball::reset(){
    _x = _original_x;
    _y = _original_y;
    _x_vel = _MAX_VEL;
    _y_vel = 0;
}