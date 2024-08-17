#include "Comms/CommsMain.h"

bool CommsMain::Initialize()
{
    return Comm_Espnow::Initialize();
}


void CommsMain::Loop()
{
    LCD::PrintCenter("Pinging...");
    bool suc = PingDevice(0, 1000);
    LCD::PrintCenter(suc ? "1" : "0");
    delay(1000);
}

void CommsMain::HandlePacket(uint8_t senderDeviceID, PacketType type, const uint8_t *data, int len)
{
    Serial.printf("Received packet (%d)\n", type);

    switch (type)
    {

    case PING:
        SendPacket(senderDeviceID, PONG);
        break;

    case PONG:
        PingReceived = true;
        break;

    case JOYSTICK_CONTROL: pckHandler_JoystickControl(senderDeviceID, data, len); break;
    
    default: Serial.printf("Unknown packet received (%d)\n", type);  break;
    }
}

void CommsMain::SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data, int len)
{
    Comm_Espnow::SendPacket(receiverDeviceID, type, data, len);
}


bool CommsMain::PingReceived = false;
bool CommsMain::PingDevice(uint8_t deviceID, uint timeout)
{
    PingReceived = false;
    SendPacket(deviceID, PING);
    ulong start = millis();
    while (!PingReceived && millis() - start < timeout)
    {
        delay(10);
    }

    return PingReceived;
}


//----------------------------------------------

void CommsMain::pckHandler_JoystickControl(uint8_t senderDeviceID, const uint8_t *data, int len)
{
    if(len != 4)
    {
        Serial.printf("Invalid data length for SET_SPEED packet (%d)\n", len);
        return;
    }
    
    int16_t x = *((int16_t*)data);
    int16_t y = *((int16_t*)(data + 2));

    Serial.printf("Joystick control received: %d, %d\n", x, y);

    MotorController::JoystickControl(x,y);
}