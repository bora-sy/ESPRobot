#pragma once
#include "Comms/Comm_Espnow.h"

enum PacketType
{
    PING,
    PONG
};

class CommsMain
{
private:

public:
    static bool Initialize();
    static void Loop();
};