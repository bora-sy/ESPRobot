#include "Comms/Comm_Espnow.h"

const uint8_t Comm_Espnow::baseMACAddr[6] = {0x5C, 0xCF, 0x7F, 0x99, 0x9A, 1};

bool Comm_Espnow::Initialize()
{
    WiFi.mode(WIFI_STA);
    
    Serial.println("MAC Address: " + WiFi.macAddress());
    bool suc = wifi_set_macaddr(STATION_IF, (uint8_t*)baseMACAddr);
    Serial.printf("Set MAC: %s\n", suc ? "Success" : "Failed");
    Serial.println("Mac Address: " + WiFi.macAddress());

    if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return false;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
    esp_now_register_send_cb([](uint8_t *mac, uint8_t status) {
        Serial.print("Send status: ");
        Serial.println(status);
    });
    return true;
}

void Comm_Espnow::OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
    if(memcmp(mac, baseMACAddr, 5) != 0)
    {
        Serial.println("Received data from unknown device");
        return;
    }

    uint8_t senderDeviceID = mac[5];

    if(len < 1)
    {
        Serial.println("Received data with no type");
        return;
    }

    PacketType type = (PacketType)incomingData[0];
    CommsMain::HandlePacket(senderDeviceID, type, incomingData + 1, len - 1);
}

void Comm_Espnow::GetMACByDeviceID(uint8_t *mac, uint8_t deviceID)
{
    memcpy(mac, baseMACAddr, 6);
    mac[5] = deviceID;
}

void Comm_Espnow::SendPacket(uint8_t receiverDeviceID, PacketType type, const uint8_t *data, int len)
{
    uint8_t mac[6];
    GetMACByDeviceID(mac, receiverDeviceID);

    uint8_t fullData[len + 1];
    fullData[0] = type;
    memcpy(fullData + 1, data, len);

    esp_now_send(mac, fullData, len + 1);
}