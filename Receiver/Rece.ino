#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
       int b=1;
    
} struct_message;

struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));
    
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(20, 0);
  if(myData.b==1){
    display.clearDisplay();
    display.print("Light Is On");
    //delay(2000);
    }
    if(myData.b==2){
      display.clearDisplay();
    display.print("Light Is Off");
    //delay(2000);
    }

  if(myData.b==3){
   //display.print("System is stable");}
  }
if(myData.b==4){
    display.print("Random Movement is detected");
    delay(2000);}
    display.display();
}

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for recv CB to
    // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);

    // Initialize OLED display
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
    display.display(); // Initialize with the display turned on
    delay(2000);       // Display for 2 seconds
    display.clearDisplay();
}

void loop() {
    // Your receiver-side code (if any) goes here
    delay(100);
}
