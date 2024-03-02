#include "Ball.h"




Ball::Ball(float x, float y, int screen_width, int screen_height){
    _original_x = x;
    _original_y = y;
    _x = x;
    _y = y;
    randomSeed(analogRead(A4) + analogRead(A5));
    _x_vel = _MAX_VEL;
    _y_vel = 0;
    _screen_width = screen_width;
    _screen_height = screen_height;


}
void Ball::move(Paddle left_paddle, Paddle right_paddle){
    // TODO need to check if it collides with the paddle, if it collides with the wall it will return the side which lost
    if (_x == 1 && (left_paddle._y <= _y && _y <= left_paddle._y + left_paddle._PADDLE_HEIGHT)){
        _x_vel *= -1;
        float left_paddle_mid_y = left_paddle._y + left_paddle._PADDLE_HEIGHT / 2.0  - 0.5;
        Serial.print("left paddle mid y: ");
        Serial.println(left_paddle_mid_y);
        float left_y_difference = int(_y) - left_paddle_mid_y;
        Serial.print("left y difference: ");
        Serial.println(left_y_difference);
        _y_vel = (_MAX_VEL / (left_paddle._PADDLE_HEIGHT / 2.0)) * left_y_difference;
        

    }
    else if (_x == _screen_width - 2 && (right_paddle._y <= _y && _y <= right_paddle._y + right_paddle._PADDLE_HEIGHT)){
        _x_vel *= -1;
        float right_paddle_mid_y = right_paddle._y + right_paddle._PADDLE_HEIGHT / 2.0 - 0.5;
        float right_y_difference = int(_y) - right_paddle_mid_y;
        _y_vel = (_MAX_VEL / (right_paddle._PADDLE_HEIGHT / 2.0)) * right_y_difference;

    }

    if (_y <= 0 || _y >= _screen_height - 1){
        _y_vel *= -1;
    }

    if (-1 < _x && _x < _screen_width && -1 < _y && _y < _screen_height){
        _x += _x_vel;
        _y += _y_vel;
    }
    // else{
    //     move(left_paddle, right_paddle);
    // }



    Serial.print("x vel: ");
    Serial.print(_x_vel);
    Serial.print(", ");
    Serial.print("y vel: ");
    Serial.println(_y_vel);



}

void Ball::reset(){
    _x = _original_x;
    _y = _original_y;
    _x_vel = _MAX_VEL;
    _y_vel = 0;
}