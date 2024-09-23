/*
one to many transmitter code to send the same message to three receivers
*/

#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH EACH ESP RECEIVER'S MAC ADDRESS
// This example has three receivers and are labelled 
// broadcastAddressX[] where X idents the specific receiver
uint8_t broadcastAddress1[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t broadcastAddress2[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t broadcastAddress3[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct test;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Message to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print("status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
  Serial.begin(115200);
 
  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
   
  // register each receiver from 1 to ...
  // repeat 
  // memcpy(peerInfo.peer_addr, broadcastAddressX, 6);
  // if (esp_now_add_peer(&peerInfo) != ESP_OK){
  //  Serial.println("Failed to add receiver 1");
  //  return;
  // }
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first receiver  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add receiver 1");
    return;
  }
  // register second receiver 
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add receiver 2");
    return;
  }
  /// register third receiver
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add receiver 3");
    return;
  }
}
 // this example creates two random numbers from 0 to 20
 // then sends those numbers 
 // if the send fails to any receiver the MAC fail will be printed
void loop() {
  test.x = random(0,20);
  test.y = random(0,20);
 
  esp_err_t result = esp_now_send(0, (uint8_t *) &test, sizeof(test_struct));
   
  if (result == ESP_OK) {
    Serial.println("Message Sent Successfully");
  }
  else {
    Serial.println("Message NOT Sent");
  }
  delay(2000);
}