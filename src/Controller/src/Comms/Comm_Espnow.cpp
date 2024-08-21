#include "Comms/Comm_Espnow.h"

const uint8_t Comm_Espnow::baseMACAddr[6] = {0x5C, 0xCF, 0x7F, 0x99, 0x9A, 0};

bool Comm_Espnow::Initialize()
{
    WiFi.mode(WIFI_STA);
    
    Serial.println("MAC Address: " + WiFi.macAddress());
    esp_err_t suc = esp_wifi_set_mac(WIFI_IF_STA, (uint8_t*)baseMACAddr);
    Serial.printf("Set MAC: %s (%d)\n", suc == 0 ? "Success" : "Failed", suc);
    Serial.println("Mac Address: " + WiFi.macAddress());

    if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return false;
    }
    
    esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
    esp_now_register_send_cb([](const uint8_t *mac, esp_now_send_status_t status) {
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
    AddPeer(mac);

    uint8_t fullData[len + 1];
    fullData[0] = type;
    memcpy(fullData + 1, data, len);

    esp_err_t stat = esp_now_send(mac, fullData, len + 1);
    Serial.printf("Sent packet %d (Len: %d) to %02X:%02X:%02X:%02X:%02X:%02X [Status: %d]\n", type, len + 1, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], stat);
}

void Comm_Espnow::AddPeer(uint8_t* macAddr)
{
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, macAddr, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    peerInfo.ifidx = wifi_interface_t::WIFI_IF_STA;

    esp_now_add_peer(&peerInfo);
}