#include "JoyStick.h"

//                                                  set the value of the joystick in normal position, and the deadzone precent

/**
 * @brief Constructor for the JoyStick class.
 * 
 * @param x_pin The pin number for the x-axis of the joystick.
 * @param y_pin The pin number for the y-axis of the joystick.
 * @param SW_pin The pin number for the joystick's switch.
 * @param normal_x The normal value for the x-axis of the joystick.
 * @param normal_y The normal value for the y-axis of the joystick.
 * @param deadzone_x The deadzone value for the x-axis of the joystick.
 * @param deadzone_y The deadzone value for the y-axis of the joystick.
 */
JoyStick::JoyStick(int x_pin, int y_pin, int SW_pin, int normal_x, int normal_y, int deadzone_x, int deadzone_y){
    _x_pin = x_pin;
    _y_pin = y_pin;
    _SW_pin = SW_pin;
    _normal_x = normal_x;
    _normal_y = normal_y;
    _deadzone_x_precent = deadzone_x;
    _deadzone_y_precent = deadzone_y;
    // calculate number of deadzones
    _deadzone_x = 1023-normal_x/100 * deadzone_x;
    _deadzone_y = 1023-normal_y/100 * deadzone_y;

    // set pin modes
    pinMode(_x_pin, INPUT);
    pinMode(_y_pin, INPUT);
    pinMode(_SW_pin, INPUT_PULLUP);

    
    
}
/**
 * @brief Get the x-coordinate of the joystick.
 * 
 * @return int The x-coordinate of the joystick.
 */
int JoyStick::get_x(){
    return analogRead(_x_pin);
}
/**
 * Returns the y-axis value of the joystick.
 *
 * @return The y-axis value of the joystick.
 */
int JoyStick::get_y(){
    return analogRead(_y_pin);
}


/**
 * Returns the direction of the joystick in the x-axis.
 * 
 * @return The direction of the joystick in the x-axis as a String.
 */
String JoyStick::get_x_direction(){
    float precent = get_x_precent();
    if(precent < -_deadzone_x_precent){
        return "LEFT";
    }else if(precent > _deadzone_x_precent){
        return "RIGHT";
    }else{
        return "CENTER";
    }
}


/**
 * Returns the direction of the joystick in the y-axis.
 * 
 * @return The direction of the joystick in the y-axis as a String.
 */
String JoyStick::get_y_direction(){
    float precent = get_y_precent();
    if(precent < -_deadzone_y_precent){
        return "UP";
    }else if(precent > _deadzone_y_precent){
        return "DOWN";
    }else{
        return "CENTER";
    }
}


/**
 * @brief Get the direction based on the joystick input.
 * 
 * This function determines the direction based on the joystick input.
 * It compares the x and y directions and their corresponding percentages
 * to determine the dominant direction. If both directions are equal,
 * it returns the corresponding direction. If the x direction is dominant,
 * it returns "LEFT" or "RIGHT" based on the sign of the x percentage.
 * If the y direction is dominant, it returns "UP" or "DOWN" based on the
 * sign of the y percentage. If no dominant direction is found, it returns
 * "CENTER".
 * 
 * @return The direction based on the joystick input.
 */
String JoyStick::get_direction(){

    String x_direction = get_x_direction();
    String y_direction = get_y_direction();
    int x_precent = get_x_precent();
    int y_precent = get_y_precent();
    if(x_direction == "RIGHT" && y_direction == "UP"){
        if(abs(x_precent) > abs(y_precent)){
            return "RIGHT";
        }else{
            return "UP";
        }
    }else if(x_direction == "RIGHT" && y_direction == "DOWN"){
        if(abs(x_precent) > abs(y_precent)){
            return "RIGHT";
        }else{
            return "DOWN";
        }
    }else if(x_direction == "LEFT" && y_direction == "DOWN"){
        if(abs(x_precent) > abs(y_precent)){
            return "LEFT";
        }else{
            return "DOWN";
        }
    }else if(x_direction == "LEFT" && y_direction == "UP"){
        if(abs(x_precent) > abs(y_precent)){
            return "LEFT";
        }else{
            return "UP";
        }
    }else{
        if (x_direction == "LEFT"){
            return "LEFT";
        }else if(x_direction == "RIGHT"){
            return "RIGHT";
        }else if(y_direction == "UP"){
            return "UP";
        }else if(y_direction == "DOWN"){
            return "DOWN";
        }else{
            return "CENTER";
        }
    }
    
}


/**
 * Calculates the percentage value of the x-axis position of the joystick.
 * 
 * @return The percentage value of the x-axis position.
 */
float JoyStick::get_x_precent(){
    
    int x = get_x();
    if (x > _normal_x){
        float one = 100.0/(1023.0 - float(_normal_x));
        return ((float(x) - float(_normal_x)) * one);
    }else if(x < _normal_x){
        float one = 100.0/float(_normal_x);
        return ((float(x) - float(_normal_x)) * one);
    }else{
        return 0;
    }
}


/**
 * Returns the percentage value of the y-axis position of the joystick.
 *
 * @return The percentage value of the y-axis position.
 */
float JoyStick::get_y_precent(){
    int y = get_y();
    if (y > _normal_y){
        float one = 100.0/(1023.0 - float(_normal_y));
        return ((float(y) - float(_normal_y)) * one);
    }else if(y < _normal_y){
        float one = 100.0/float(_normal_y);
        return ((float(y) - float(_normal_y)) * one);
    } else{
        return 0;
    }
}


/**
 * @brief Gets the state of the joystick's switch.
 * 
 * @return true if the switch is pressed, false otherwise.
 */
bool JoyStick::get_SW(){
    return digitalRead(_SW_pin) == LOW;
}
