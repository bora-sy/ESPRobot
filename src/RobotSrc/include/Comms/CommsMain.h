#pragma once
#include "MotorController.h"

enum PacketType
{
    PING,
    PONG,
    JOYSTICK_CONTROL,
};

#include "Comms/Comm_Espnow.h"
#define DEVICE_ID 1

class CommsMain
{
private:
    static void SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data = nullptr, int len = 0);

    static void pckHandler_JoystickControl(uint8_t senderDeviceID, const uint8_t *data, int len);

public:
    static bool Initialize();
    static void Loop();

    static void HandlePacket(uint8_t senderDeviceID, PacketType type, const uint8_t *data, int len);

    static bool PingReceived;
    static bool PingDevice(uint8_t deviceID, uint timeout = 1000);
};