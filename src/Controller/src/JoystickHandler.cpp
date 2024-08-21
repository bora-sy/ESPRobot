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

    while (true)
    {
        uint16_t x = analogRead(PIN_JOYSTICK_X);
        uint16_t y = analogRead(PIN_JOYSTICK_Y);

        #if AXIS_X_REVERSED
        x = 4095 - x;
        #endif

        #if AXIS_Y_REVERSED
        y = 4095 - y;
        #endif

        //Serial.printf("X: %d, Y: %d\n", x, y);

        int16_t x16 = map(x, 0, 4095, -255, 255);
        int16_t y16 = map(y, 0, 4095, -255, 255);

        if(AXIS_X_DEADZONE < 0) x16 = x16 < -AXIS_X_DEADZONE && x16 > AXIS_X_DEADZONE ? 0 : x16;
        else x16 = x16 < AXIS_X_DEADZONE && x16 > -AXIS_X_DEADZONE ? 0 : x16;

        if(AXIS_Y_DEADZONE < 0) y16 = y16 < -AXIS_Y_DEADZONE && y16 > AXIS_Y_DEADZONE ? 0 : y16;
        else y16 = y16 < AXIS_Y_DEADZONE && y16 > -AXIS_Y_DEADZONE ? 0 : y16;

       Serial.printf("(Mapped) X: %d, Y: %d\n", x16, y16);

        

        CommsMain::SendJoystickControl(TargetDeviceID, x16, y16);
        
        delay(5);

    }

    Serial.println("JoystickHandler task ended unexpectedly");
    vTaskDelete(NULL);
    delay(0);
}