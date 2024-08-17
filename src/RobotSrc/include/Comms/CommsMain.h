#pragma once
#include "Comms/Comm_Espnow.h"

#define DEVICE_ID 1

enum PacketType
{
    PING,
    PONG
};

class CommsMain
{
private:
    static void SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data = nullptr, int len = 0);

public:
    static bool Initialize();
    static void Loop();

    static void HandlePacket(uint8_t senderDeviceID, PacketType type, const uint8_t *data, int len);
};