# IOT-Mini-project-2

This project demonstrates a simple communication setup between two ESP32 devices using the ESP-NOW protocol. ESP-NOW allows for peer-to-peer communication between ESP32 modules, enabling efficient and direct data transmission without the need for a traditional Wi-Fi connection. Unlike the wifi, it has large range upto 500 in open space, with antenna. 

## ESP-NOW Overview:

### ESP-NOW Protocol: 
ESP-NOW is a communication protocol developed by Espressif Systems specifically for ESP8266 and ESP32 devices. It enables fast, low-power communication between ESP devices, making it ideal for scenarios where a dedicated Wi-Fi network is not required.

### Peer-to-Peer Communication: 

In this project, the sender and receiver ESP32 devices act as peers. The sender collects data from a DHT11 sensor and transmits it to the receiver using ESP-NOW. The receiver, in turn, displays the received data on an OLED display.

## Sender Sketch (`sender.ino`)

The sender sketch is responsible for reading data from a DHT11 sensor and transmitting it using the ESP-NOW protocol. After successfully broadcasting the data, the sender enters deep sleep mode to minimize power consumption. The sender board wake up for 50mS and go to sleep for 10s. It consumes 40uA in deep sleep state and 100mA in wake up state.

### Components:
	Seed Studio XIAO ESP32 C3 -> 2 boards
	DHT11 ->    1 unit
	0.96” OLED -> 1 Unit

### Hardware Setup:

1.	Connect the DHT11 sensor to pin D10 on the ESP32.
2.	. Connect the DHT11 sensor to pin D10 on the ESP32.
2. Ensure the ESP32 is powered and connected appropriately.

### How to Use:

1. Upload the `sender.ino` sketch to the ESP32 device.
2. Open the Serial Monitor (Tools > Serial Monitor) to monitor debugging information.
3. The device will read temperature and humidity data, broadcast it via ESP-NOW, and then enter deep sleep.

## Receiver Sketch (`receiver.ino`)

The receiver sketch initializes the ESP-NOW communication and waits for data from the sender. Upon receiving data, it displays temperature and humidity on an OLED display. The receiver also supports deep sleep when not actively receiving data.

### Hardware Setup:

1. Connect the OLED display to the appropriate pins on the ESP32.
2. Ensure the ESP32 is powered and connected appropriately.

### How to Use:

1. Upload the `receiver.ino` sketch to the ESP32 device.
2. Open the Serial Monitor (Tools > Serial Monitor) to monitor debugging information.
3. The device will wait for data from the sender and display it on the OLED screen.
4. If data is received, the receiver will enter deep sleep after a brief display.
5. To Read data again press reset button on esp32 it will wait for few 2nd and display temperature and humidity values

### Benefits:

1. **Energy-Efficient Monitoring:**
   - Deep sleep functionality ensures minimal power consumption, suitable for battery-powered applications.

2. **Real-Time Climate Data:**
   - Users can access up-to-date temperature and humidity information, aiding in decision-making for climate control adjustments.

3. **Integration with Smart Home Systems:**
   - The system can be extended to integrate with other smart home devices, creating a comprehensive climate control solution.

4. **User-Friendly Interface:**
   - The OLED display provides an intuitive and user-friendly interface for viewing environmental data.

5. **Cost-Effective Solution:**
   - ESP32 devices are affordable and the ESP-NOW protocol eliminates the need for a dedicated Wi-Fi network, reducing infrastructure costs.

By employing this ESP-NOW based smart home climate control system, users can enhance their living environment, optimize energy usage, and contribute to a more comfortable and efficient home.


