#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Arduino.h"

class JoyStick{


public:
    JoyStick(int x_pin, int y_pin, int SW_pin, int normal_x = 512, int normal_y = 512, int deadzone_x = 10, int deadzone_y = 10);
    int get_x();
    int get_y();
    String get_x_direction();
    String get_y_direction();
    String get_direction();
    float get_x_precent();
    float get_y_precent();
    bool get_SW();

private:
    int _x_pin;
    int _y_pin;
    int _SW_pin;
    int _normal_x;
    int _normal_y;
    float _deadzone_x_precent;
    float _deadzone_y_precent;
    float _deadzone_x;
    float _deadzone_y;

}; 









#endif