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

void MotorController::JoystickControl(int16_t rot, int16_t fw)
{
    rot = constrain(rot, -255, 255);
    fw = constrain(fw, -255, 255);

    int16_t leftSpeed = constrain(fw + rot, -255, 255);
    int16_t rightSpeed = constrain(fw - rot, -255, 255);

    Serial.printf("New Speed (L: %d, R: %d)\n", leftSpeed, rightSpeed);

    LCD::PrintCenterRow("L: " + String(leftSpeed),0);
    LCD::PrintCenterRow("R: " + String(rightSpeed),1);

    SetSpeed(M_LEFT, leftSpeed);
    SetSpeed(M_RIGHT, rightSpeed);
}

void MotorController::SetSpeed(Motor motor, int16_t speed)
{
    speed = constrain(speed, -255, 255);

    const uint8_t pinTable[2][2] = {
        {PIN_MOTOR_LEFT_F, PIN_MOTOR_LEFT_B},
        {PIN_MOTOR_RIGHT_F, PIN_MOTOR_RIGHT_B},
    };

    if(speed == 0)
    {
        analogWrite(pinTable[motor][0], 0);
        analogWrite(pinTable[motor][1], 0);
    }
    else if(speed > 0)
    {
        analogWrite(pinTable[motor][0], speed);
        analogWrite(pinTable[motor][1], 0);
    }
    else // speed < 0
    {
        analogWrite(pinTable[motor][0], 0);
        analogWrite(pinTable[motor][1], -speed);
    }
}