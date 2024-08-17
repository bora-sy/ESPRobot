#pragma once
#include <Arduino.h>
#include "Pinout.h"


enum Motor
{
    M_LEFT = 0,
    M_RIGHT,
};

class MotorController
{
private:
public:
    static void Initialize();

    static void JoystickControl(int16_t x, int16_t y);
};