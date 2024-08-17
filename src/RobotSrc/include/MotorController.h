#pragma once
#include <Arduino.h>
#include "Pinout.h"
#include "LCD.h"

enum Motor
{
    M_LEFT = 0,
    M_RIGHT,
};

class MotorController
{
private:
    static void SetSpeed(Motor motor, int16_t speed);
public:
    static void Initialize();

    static void JoystickControl(int16_t x, int16_t y);
};