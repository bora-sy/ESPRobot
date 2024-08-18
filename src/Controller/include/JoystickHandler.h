#pragma once
#include <Arduino.h>
#include "Pinout.h"
#include "Comms/CommsMain.h"

class JoystickHandler
{
private:
    static void t_JoystickHandler(void *pvParameters);
public:
    static void Initialize();
};