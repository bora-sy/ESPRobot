#include "MotorController.h"

#define CHANNEL_LEFT 0
#define CHANNEL_RIGHT 1

void MotorController::Initialize()
{
    pinMode(PIN_MOTOR_LEFT_F, OUTPUT);
    pinMode(PIN_MOTOR_LEFT_B, OUTPUT);

    pinMode(PIN_MOTOR_RIGHT_F, OUTPUT);
    pinMode(PIN_MOTOR_RIGHT_B, OUTPUT);
}

void MotorController::JoystickControl(int16_t x, int16_t y)
{
    int16_t speedLeft = 0;
    int16_t speedRight = 0;
    

}

