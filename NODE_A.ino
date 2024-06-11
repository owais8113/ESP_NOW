#include <esp_now.h>
#include <WiFi.h>

// MAC Address of the peer (ESP32 Device 1)
uint8_t peerAddress[] = {0x80, 0x64, 0x6F, 0x3C, 0x03, 0x58}; // Replace with your Device 1's MAC address

// Structure to send data
typedef struct struct_message {
    char a[32];
} struct_message;

struct_message myData;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Received message: ");
    Serial.println(myData.a);
}

void setup() {
    Serial.begin(115200);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register the send and receive callbacks
    esp_now_register_send_cb(OnDataSent);
    esp_now_register_recv_cb(OnDataRecv);

    // Register peer
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, peerAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    if (Serial.available() > 0) {
        String msg = Serial.readString();
        msg.toCharArray(myData.a, 32);
        esp_now_send(peerAddress, (uint8_t *) &myData, sizeof(myData));
    }
}
