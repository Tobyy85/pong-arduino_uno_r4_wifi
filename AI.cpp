#include "AI.h"

AI::AI(int screen_width, int screen_height){
    _screen_width = screen_width;
    _screen_height = screen_height;
}

String AI::where_to_move(int paddle_y, int paddle_height, float ball_y){
    float paddle_middle = paddle_y + paddle_height / 2.0 - 0.5;  // The middle of the paddle
    if (ball_y < paddle_middle){  // If the ball is above the middle of the paddle
        return "UP";
    }else if (ball_y > paddle_middle){  // If the ball is below the middle of the paddle
        return "DOWN";
    }
    
}