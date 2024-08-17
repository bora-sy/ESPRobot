#include "Comms/CommsMain.h"

bool CommsMain::Initialize()
{
    return Comm_Espnow::Initialize();
}


void CommsMain::Loop()
{

}

void CommsMain::HandlePacket(uint8_t senderDeviceID, PacketType type, const uint8_t *data, int len)
{
    
}

void CommsMain::SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data, int len)
{
    Comm_Espnow::SendPacket(receiverDeviceID, type, data, len);
}