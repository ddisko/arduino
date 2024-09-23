// Asmbly Dust Collector Early Warning System ADCEWS using ESP Now

#include <esp_now.h>
#include <WiFi.h>

// Variables for test data
int int_value;
float float_value;
bool bool_value = true;

// MAC Address for all warning devices NOTE you need to insert the correct addresses for all receivers
uint8_t broadcastAddress1[] = {0x24, 0x6F, 0x28, 0x7A, 0xAE, 0x7C};
uint8_t broadcastAddress2[] = {0x24, 0x6F, 0x28, 0x7A, 0xAE, 0x7C};
uint8_t broadcastAddress3[] = {0x24, 0x6F, 0x28, 0x7A, 0xAE, 0x7C};

// Define a data structure for a test message using characters, integers, float, and boolean data types
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Create the message
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent to test if message is successful
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
 
  // Set ESP32 as a Wi-Fi Station / Transmitter
  WiFi.mode(WIFI_STA);

  // Initilize ESP-NOW 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register all Receivers and set them to the same channel
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, broadcastAddress3, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add Receivers     
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

  // Create test data message

  // Generate a random integer
  int_value = random(1,20);

  // Use above integer to make a new float
  float_value = 1.3 * int_value;

  // Invert the current boolean value
  bool_value = !bool_value;
  
  // Format message
  strcpy(myData.a, "Welcome to the Asmbly Dust Collection Early Warning System ADCEWS!");
  myData.b = int_value;
  myData.c = float_value;
  myData.d = bool_value;
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress1, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(2000);
}