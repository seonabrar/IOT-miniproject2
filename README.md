# IOT-Project-2
# Gesture based Wirless Home Automation

This project demonstrates a wireless communication system using two Xiao BLE ESP32-C3 boards. The transmitter board is equipped with an MPU6050 accelerometer, while the receiver board features a 0.96" OLED display. The system is designed to detect movements using the MPU6050 and display corresponding signals on the OLED display and turn on and off the lights.

## Hardware Components

- **Transmitter Board:**
  - Xiao BLE ESP32-C3
  - MPU6050 Accelerometer

- **Receiver Board:**
  - Xiao BLE ESP32-C3
  - 0.96" OLED Display

## Dependencies

- [Edge Impulse](https://www.edgeimpulse.com/): Used for training the MPU6050 data.

- ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/6b46aa26-4a01-46ad-8d11-eeb2181d55a4)

- ESPNOW for wireless Communication 


## Getting Started

1. **Clone the Repository:**
   
https://github.com/aliabidlodhi74/IOT-Project-2

2. **Hardware Setup:**
   
   - **Connect transmitter esp32 board with mpu6050**
     ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/08c7ec3c-fb3e-4739-b31b-32b653e0d787)


   - **Connect Receiver esp32 board with OLED**
   
     ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/251678a5-dd16-4be0-9a75-de70e1ba2914)


3. **Edge Impulse Setup:**

   - Create Account at edge impulse
   - To run edge impulse follow the installation tutorial on the following link
     https://docs.edgeimpulse.com/docs/tools/edge-impulse-cli/cli-installation
   - Upload dataForwarder.ino firmware in the transmitter board with mpu6050 connected
   - Open CMD and run this command
     
4. **edge-impulse-data-forwarder**

     
   - Provide name of 3 axis as aX, aY, aZ and name of the device as shown in the picture below
     
   ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/41be1e86-7e96-4310-a0d6-1b9805dc751b)


    - Now device is connected with edge impulse and project is created

   ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/b1eccd64-10da-407f-94d9-88747f0b67dc)

   ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/b2af4f9a-a3fc-4d9f-9409-d729b786de34)


   - Now click data aqcusition on the top left and capture set for model training
   - Add atleast 15 sample models for each gesture
  
   - ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/6f5dbd1c-7ad7-42b8-b7a9-0b2e90683bcf)
  
   - Now go to Impulse design and add spectral analysis as processing block and Neural Network Classification as learning block, keep the window size upto 1000ms and save impulse
  
   - ![image](https://github.com/aliabidlodhi74/IOT-Project-2/assets/83972129/872a8247-d665-4a39-8943-9d786b61f61a)
  
   - Now go to spectral features and generate features
   - Then go to NN classifier and select esp eye board and tain the model
   - Then go to deployment, select arduino ide and click on build
   - Arduino library will be generated in this way
   - Now open arduino ide go to sketch->include library->add zip file-> select downloaded library from edge impulse
   - model Library is found in this link with name trainingLibarary.zip
    https://github.com/aliabidlodhi74/IOT-Project-2/tree/main/Firmware/Library

   - Now upload firmware in the transmitter and receiver boards
   - Perform up down and left right movements and they will be recognised by transmitter board and sent to receiver
   - The Receiveer board will display Lights are On if left right movement is identified, Lights are off if up down movement is identified
  
5. **Video Demonstration**
   - Youtube link
  
https://www.youtube.com/watch?v=loA9_1b2G0Q

  
# Application

    The main application of this project is wireless home automation
