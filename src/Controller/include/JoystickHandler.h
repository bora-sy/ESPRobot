#pragma once
#include <Arduino.h>
#include "Pinout.h"
#include "Comms/CommsMain.h"

#define AXIS_Y_REVERSED true
#define AXIS_X_REVERSED false

#define AXIS_X_DEADZONE 100
#define AXIS_Y_DEADZONE -90

class JoystickHandler
{
private:
    static void t_JoystickHandler(void *pvParameters);
public:
    static void Initialize();
};