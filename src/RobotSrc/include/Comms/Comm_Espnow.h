#pragma once
#include <Arduino.h>
#include <espnow.h>
#include <ESP8266WiFi.h>
#include "Comms/CommsMain.h"

class Comm_Espnow
{
private:
    static const uint8_t baseMACAddr[6];

    static void GetMACByDeviceID(uint8_t *mac, uint8_t deviceID);

    static void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
    
public:

    static bool Initialize();

    static void SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data = nullptr, int len = 0);
};
