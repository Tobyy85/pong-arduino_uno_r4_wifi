#include "Paddle.h"


Paddle::Paddle(int x, int y, int screen_height, int paddle_height){
    _original_x = x;
    _original_y = y;
    _x = x;
    _y = y;
    _screen_height = screen_height;
    _PADDLE_HEIGHT = paddle_height;
}


void Paddle::move(String direction){
    if(direction == "UP" && _y > 0){
        _y -= _VEL;
    }
    else if(direction == "DOWN" && _y < _screen_height - _PADDLE_HEIGHT){
        _y += _VEL;
    }
}

void Paddle::reset(){
    _x = _original_x;
    _y = _original_y;
}