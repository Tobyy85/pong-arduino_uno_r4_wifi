#include "Paddle.h"


/**
 * @brief Constructs a Paddle object with the specified parameters.
 * 
 * @param x The x-coordinate of the paddle's position.
 * @param y The y-coordinate of the paddle's position.
 * @param screen_height The height of the screen.
 * @param paddle_height The height of the paddle.
 */
Paddle::Paddle(int x, int y, int screen_height, int paddle_height){
    _original_x = x;
    _original_y = y;
    _x = x;
    _y = y;
    _screen_height = screen_height;
    _PADDLE_HEIGHT = paddle_height;
}


/**
 * Moves the paddle in the specified direction.
 * 
 * @param direction The direction in which to move the paddle.
 */
void Paddle::move(String direction){
    if (direction == "UP" && _y > 0){  // If the paddle is not at the top of the screen
        _y -= _VEL;  // Move the paddle up
    }
    else if (direction == "DOWN" && _y < _screen_height - _PADDLE_HEIGHT){  // if the paddle is not at the bottom of the screen
        _y += _VEL;  // Move the paddle down
    }
}


/**
 * Resets the paddle to its initial position.
 */
void Paddle::reset(){
    _x = _original_x;
    _y = _original_y;
}