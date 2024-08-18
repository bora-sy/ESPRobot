#include "JoystickHandler.h"


void JoystickHandler::Initialize()
{
    pinMode(PIN_JOYSTICK_X, INPUT);
    pinMode(PIN_JOYSTICK_Y, INPUT);

    xTaskCreate(t_JoystickHandler, "JoystickHandler", 4096, NULL, 1, NULL);
}

void JoystickHandler::t_JoystickHandler(void *pvParameters)
{
    const uint8_t TargetDeviceID = 1;
    const uint16_t deadzone = 10;

    while (true)
    {
        uint16_t x = analogRead(PIN_JOYSTICK_X);
        uint16_t y = analogRead(PIN_JOYSTICK_Y);
        Serial.printf("X: %d, Y: %d\n", x, y);

        int16_t x16 = map(x, 0, 4095, -255, 255);
        int16_t y16 = map(y, 0, 4095, -255, 255);

        x16 = x16 < deadzone && x16 > -deadzone ? 0 : x16; // Deadzone

        

        CommsMain::SendJoystickControl(TargetDeviceID, x16, y16);
        
        delay(5);

    }

    Serial.println("JoystickHandler task ended unexpectedly");
    vTaskDelete(NULL);
    delay(0);
}