#include <Arduino_LED_Matrix.h>

#include "JoyStick.h"
#include "Ball.h"
#include "Paddle.h"
#include "AI.h"
#include "numbers.h"

ArduinoLEDMatrix matrix;

const int SCREEN_WIDTH = 12;
const int SCREEN_HEIGHT = 8;
const int PADDLE_HEIGHT = 4; // You can change this value to make the paddles taller or shorter

String current_mode = "game";
long last_mode_change_millis = millis();
int mode_change_delay = 1000;

long current_millis = millis();

const int ball_speed = 10;
long ball_last_millis = millis();

const float paddle_speed = ball_speed/(PADDLE_HEIGHT/1.5);
long left_paddle_last_millis = millis();
long right_paddle_last_millis = millis();


Paddle right_paddle(SCREEN_WIDTH -1 , SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2, SCREEN_HEIGHT, PADDLE_HEIGHT);
Paddle left_paddle(0, SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2, SCREEN_HEIGHT, PADDLE_HEIGHT);
Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT);

AI left_paddle_ai = AI(left_paddle, ball, SCREEN_WIDTH, SCREEN_HEIGHT);
AI right_paddle_ai = AI(right_paddle, ball, SCREEN_WIDTH, SCREEN_HEIGHT);
bool is_left_ai = true;
bool is_right_ai = false;

JoyStick left_joystick(A2, A1, A0, 509, 509, 5, 5);
JoyStick right_joystick(A3, A4, A5, 508, 492, 5, 5);
int left_player_score = 0;
int right_player_score = 0;
bool invert_left_joystick = true;
bool invert_right_joystick = false;

int time_to_show_score = 250;  // The time in milliseconds to show the score
bool is_left_pressed = false;
long left_press_millis = millis();
bool is_right_pressed = false;
long right_press_millis = millis();




void setup() {
    matrix.begin();
    Serial.begin(9600);
}

void loop() {
    current_millis = millis();
    if (current_mode == "game"){

        if (current_millis >= ball_last_millis + 1000 / ball_speed){  // If the ball should move
            ball_last_millis = current_millis;
            ball.move(left_paddle, right_paddle);

            if (ball._x < 0){  // If the ball is at the left edge of the screen
                right_player_score++;
                reset();
            }else if(ball._x > SCREEN_WIDTH - 1){  // If the ball is at the right edge of the screen
                left_player_score++;
                reset();
            }
        }
        if (current_millis >= left_paddle_last_millis + 1000 / paddle_speed){  // If the left paddle should move
            left_paddle_last_millis = current_millis;
            if (is_left_ai){
                left_paddle_ai.move();
                if (invert_left_joystick){
                    String direction = left_joystick.get_direction();
                    if (direction == "UP"){
                        left_paddle.move("DOWN");
                    }else if (direction == "DOWN"){
                        left_paddle.move("UP");
                    }
                }else{
                    left_paddle.move(left_joystick.get_direction());
                }
            }
        }
        if (current_millis >= right_paddle_last_millis + 1000 / paddle_speed){  // If the right paddle should move
            right_paddle_last_millis = current_millis;
            if (is_right_ai){
                right_paddle_ai.move();
            }else{
                if (invert_right_joystick){
                    String direction = right_joystick.get_direction();
                    if (direction == "UP"){
                        right_paddle.move("DOWN");
                    }else if (direction == "DOWN"){
                        right_paddle.move("UP");
                    }
                }else{
                    right_paddle.move(right_joystick.get_direction());
                }
            }
        }
        if (left_joystick.get_SW()){
            if (!is_left_pressed){
                is_left_pressed = true;
                left_press_millis = current_millis;
            }
        }else{
            is_left_pressed = false;
        }
        if (right_joystick.get_SW()){
            if (!is_right_pressed){
                is_right_pressed = true;
                right_press_millis = current_millis;
            }
        }else{
            is_right_pressed = false;
        }
        if (is_left_pressed && is_right_pressed && current_millis - mode_change_delay >= last_mode_change_millis){
            if (current_millis - left_press_millis >= time_to_show_score && current_millis - right_press_millis >= time_to_show_score){
                current_mode = "score";
                last_mode_change_millis = current_millis;
            }
        }
        draw_game();

    }else if (current_mode == "score"){
        show_score(left_player_score, right_player_score);
        if (left_joystick.get_SW() && right_joystick.get_SW() && current_millis - mode_change_delay >= last_mode_change_millis){
            current_mode = "game";
            left_press_millis = current_millis;
            right_press_millis = current_millis;
            is_left_pressed = false;
            is_right_pressed = false;
            last_mode_change_millis = millis();
            draw_game();
            delay(1000);
        }
    }
}

void reset(){
    left_paddle.reset();
    right_paddle.reset();
    ball.reset();
}

void draw_game(){

    
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




byte score_on_screen[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};




void show_score(int left_score, int right_score){
    
    for (int y = 0; y < 8; y++){
      for (int x = 0; x < 12; x++){
        score_on_screen[y][x] = 0;
      }
    }

    get_right_number(right_score);
    get_left_number(left_score);
    matrix.renderBitmap(score_on_screen, SCREEN_HEIGHT, SCREEN_WIDTH);

}


void get_right_number(int number){
    int num1 = int(number) / 10;
    int num2 = int(number) % 10;
    int num1_start_x = 5;
    int num1_start_y = 7;

    int num2_start_x = 0;
    int num2_start_y = 7;
    // First number
    for (int screen_y = num1_start_y, number_y = num1*5; screen_y < num1_start_y+5; screen_y++, number_y++){
        for (int screen_x = num1_start_x, number_x = 0; screen_x < num1_start_x+3; screen_x++, number_x++){
            score_on_screen[screen_x][screen_y] = numbers[number_x][number_y];
        }
    }
    // Second number
    for (int screen_y = num2_start_y, number_y = num2*5; screen_y < num2_start_y+5; screen_y++, number_y++){
        for (int screen_x = num2_start_x, number_x = 0; screen_x < num2_start_x+3; screen_x++, number_x++){
            score_on_screen[screen_x][screen_y] = numbers[number_x][number_y];
        }
    }
}

byte rotated_numbers[3][50] = {};// Rotate the numbers array 180 degrees

    
void get_left_number(int number){
    int num1 = int(number) / 10;
    int num2 = int(number) % 10;
    int num1_start_x = 0;
    int num1_start_y = 0;

    int num2_start_x = 5;
    int num2_start_y = 0;

    // Rotate the numbers array 180 degrees
    for (int original_x = 0, rotated_x = 49; original_x < 50; original_x++, rotated_x--){
        for (int original_y = 0, rotated_y = 2; original_y < 3; original_y++, rotated_y--){
            rotated_numbers[rotated_y][rotated_x] = numbers[original_y][original_x];
        }
    }

    // First number
    for (int screen_y = num1_start_y, number_y = (9-num1)*5; screen_y < num1_start_y+5; screen_y++, number_y++){
        for (int screen_x = num1_start_x, number_x = 0; screen_x < num1_start_x+3; screen_x++, number_x++){
            score_on_screen[screen_x][screen_y] = rotated_numbers[number_x][number_y];
        }
    }

    // Second number
    for (int screen_y = num2_start_y, number_y = (9-num2)*5; screen_y < num2_start_y+5; screen_y++, number_y++){
        for (int screen_x = num2_start_x, number_x = 0; screen_x < num2_start_x+3; screen_x++, number_x++){
            score_on_screen[screen_x][screen_y] = rotated_numbers[number_x][number_y];
        }
    }
    

    
  


}