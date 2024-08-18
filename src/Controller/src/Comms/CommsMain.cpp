#include "Comms/CommsMain.h"

bool CommsMain::Initialize()
{
    return Comm_Espnow::Initialize();
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
    
    default: Serial.printf("Unknown packet received (%d)\n", type);  break;
    }
}

void CommsMain::SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data, int len)
{
    Comm_Espnow::SendPacket(receiverDeviceID, type, data, len);
}

//---------------------------------------------

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

void CommsMain::SendJoystickControl(uint8_t deviceID, int16_t x, int16_t y)
{
    uint8_t data[4];
    data[0] = x & 0xFF;
    data[1] = x >> 8;
    data[2] = y & 0xFF;
    data[3] = y >> 8;

    SendPacket(deviceID, JOYSTICK_CONTROL, data, 4);
}


//---------------------------------------------