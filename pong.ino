#include <Arduino_LED_Matrix.h>

#include "JoyStick.h"
#include "Ball.h"
#include "Paddle.h"

ArduinoLEDMatrix matrix;

const int SCREEN_WIDTH = 12;
const int SCREEN_HEIGHT = 8;
const int PADDLE_HEIGHT = 3;

long current_millis = millis();

const int ball_speed = 3;
long ball_last_millis = millis();


Paddle right_paddle(SCREEN_WIDTH -1 , SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2, SCREEN_HEIGHT, PADDLE_HEIGHT);
Paddle left_paddle(0, SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2, SCREEN_HEIGHT, PADDLE_HEIGHT);
Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT);

JoyStick left_joystick(A2, A1, A0, 509, 507, 5, 5);
JoyStick right_joystick(A3, A4, A5, 509, 507, 5, 5);


void setup() {
    matrix.begin();
    Serial.begin(9600);
}

void loop() {
  current_millis = millis();

  if (current_millis >= ball_last_millis + 1000 / ball_speed){  // If the ball should move
    ball_last_millis = current_millis;
    ball.move(left_paddle, right_paddle);

    if (ball._x < 0 || ball._x > SCREEN_WIDTH - 1){  // If the ball is off the screen
        ball.reset();
        left_paddle.reset();
        right_paddle.reset();
    } 
  }

  draw();
}



void draw(){
    byte on_screen[8][12] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    for (int i = left_paddle._y; i < left_paddle._y + left_paddle._PADDLE_HEIGHT; i++){
        on_screen[i][left_paddle._x] = 1;
    }
    for (int i = right_paddle._y; i < right_paddle._y + right_paddle._PADDLE_HEIGHT; i++){
        on_screen[i][right_paddle._x] = 1;
    }
    on_screen[int (ball._y)][int (ball._x)] = 1;

    matrix.renderBitmap(on_screen, SCREEN_HEIGHT, SCREEN_WIDTH);

}
