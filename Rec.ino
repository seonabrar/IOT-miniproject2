#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define   TouchPin  GPIO_NUM_3
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char a[32];
    int b;
    float c;
    bool d;
} struct_message;
int c=0;
// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
 
  Serial.print("Temp: ");
  Serial.println(myData.b);
  Serial.print("Humidity: ");
  Serial.println(myData.c);
  delay(1000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Temp:");
  display.print(myData.b);
  display.println("C");
  display.setCursor(0, 40);
  display.print("Hum:");
  display.print(myData.c);
  display.println("%");
  display.display();
  c=1;
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(TouchPin,  INPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  delay(200);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Waiting...");
  display.display();
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  esp_deep_sleep_enable_gpio_wakeup(1ULL << 3,ESP_GPIO_WAKEUP_GPIO_HIGH);  
 if(c==1)
 {
  delay(2000);
  display.clearDisplay();
  display.display();
  delay(100);
  esp_deep_sleep_start();}
}