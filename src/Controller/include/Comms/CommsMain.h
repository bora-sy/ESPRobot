#pragma once

enum PacketType
{
    PING,
    PONG,
    JOYSTICK_CONTROL,
};

#include "Comms/Comm_Espnow.h"
#define CURRENT_DEVICE_ID 1

class CommsMain
{
private:
    static void SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data = nullptr, int len = 0);

    static void pckHandler_JoystickControl(uint8_t senderDeviceID, const uint8_t *data, int len);

public:
    static bool Initialize();

    static void HandlePacket(uint8_t senderDeviceID, PacketType type, const uint8_t *data, int len);

    static bool PingReceived;
    static bool PingDevice(uint8_t deviceID, uint timeout = 1000);


    static void SendJoystickControl(uint8_t deviceID, int16_t x, int16_t y);
};