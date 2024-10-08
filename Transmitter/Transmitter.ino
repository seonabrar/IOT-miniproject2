
#include <gesture2_inferencing.h>  
#include <Adafruit_MPU6050.h>  
#include <Adafruit_Sensor.h>  
#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>
/* Constant defines -------------------------------------------------------- */
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#define MAX_ACCEPTED_RANGE  2.0f        
float scale = 0.08;
Adafruit_MPU6050 mpu;
typedef struct struct_message {
    int b;
  } struct_message;
struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
/* Private variables ------------------------------------------------------- */
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal


void setup()
{

  Serial.begin(115200);
  //while (!Serial)
    delay(10); // wait for serial port

  Serial.println("Movement detector");
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  if (!mpu.begin()) {
    ei_printf("Error MPU6050!\r\n");
  }
  else {
    ei_printf("MPU6050 found\r\n");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);

  if (EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME != 3) {
    ei_printf("ERR: EI_CLASSIFIER_RAW_SAMPLES_PER_FRAME should be equal to 3 (the 3 sensor axes)\n");
    return;
  }
}

/**
 * @brief Return the sign of the number
 * 
 * @param number 
 * @return int 1 if positive (or 0) -1 if negative
 */
float ei_get_sign(float number) {
  return (number >= 0.0) ? 1.0 : -1.0;
}

/**
* @brief      Get data and run inferencing
*
* @param[in]  debug  Get debug info if true
*/
void loop()
{
  ei_printf("\nStarting inferencing in 2 seconds...\n");

  //delay(2000);
esp();
  ei_printf("Sampling...\n");

  // Allocate a buffer here for the values we'll read from the IMU
  float buffer[EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE] = { 0 };

  for (size_t ix = 0; ix < EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE; ix += 3) {
    // Determine the next tick (and then sleep later)
    uint64_t next_tick = micros() + (EI_CLASSIFIER_INTERVAL_MS * 1000);

    /* Gather sensor data */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    buffer[ix] = (a.acceleration.x)*scale;
    buffer[ix + 1] = (a.acceleration.y)*scale;
    buffer[ix + 2] = (a.acceleration.z)*scale;

    delayMicroseconds(next_tick - micros());
  }

  // Turn the raw buffer in a signal which we can the classify
  signal_t signal;
  int err = numpy::signal_from_buffer(buffer, EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, &signal);
  if (err != 0) {
    ei_printf("Failed to create signal from buffer (%d)\n", err);
    return;
  }

  // Run the classifier
  ei_impulse_result_t result = { 0 };

  err = run_classifier(&signal, &result, debug_nn);
  if (err != EI_IMPULSE_OK) {
    ei_printf("ERR: Failed to run classifier (%d)\n", err);
    return;
  }
// ...

// print the predictions
ei_printf("Predictions ");
ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
          result.timing.dsp, result.timing.classification, result.timing.anomaly);
ei_printf(": \n");
for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
    ei_printf("    %s: %.5f\n", result.classification[ix].label, result.classification[ix].value);
}

// Classify between LR (Low Risk) and UP (Unknown Purpose) categories
if (result.classification[0].value >= 0.8) {
    ei_printf("Left Right movement is detected\r\n");
    myData.b=1;
} else if (result.classification[1].value >= 0.8) {
    ei_printf("Up Downt movement is detected\r\n");
    myData.b=2;
}
 else if (result.classification[4].value >= 0.4) {
    ei_printf("Device is Stable\r\n");
    myData.b=3;
}
 else if (result.classification[5].value >= 0.4) {
    ei_printf("Random Movement is detected\r\n");
    myData.b=4;
}
#if EI_CLASSIFIER_HAS_ANOMALY == 1
ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif


}