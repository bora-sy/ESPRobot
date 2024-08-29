# ESPRobot
ESPRobot is a mini robot made with ESP32, coded in C++, using PlatformIO. Controller uses the [esp-now](https://github.com/espressif/esp-now) protocol to communicate with the robot.

## Instructions

1- **Clone the Repository:**  
- Clone this repository to your local machine

2- **Install PlatformIO:**  
- Make sure you have PlatformIO installed in your IDE (VS Code recommended). If not, follow the installation guide [here](https://platformio.org/install).

### Robot

2.1- **Open in VS Code:**  
   - Open the [src/RobotSrc](https://github.com/bora-sy/ESPRobot/tree/main/src/RobotSrc) folder in VS Code.
   - PlatformIO will automatically detect the environment.

2.2- **Connect your Board:**  
   Connect an ESP32 Board (or any board with any ESP32 module) to your computer via USB.

2.3- **Select the Environment:**  
   Make sure the correct environment is selected in `platformio.ini`. You can modify this file if needed.

2.4- **Upload the Code:**  
   - Click on the PlatformIO icon in the sidebar.
   - Under "PROJECT TASKS," select your environment.
   - Click on "Upload" to compile and upload the code to your board.

### Controller

3.1- **Open in VS Code:**  
   - Open the [src/Controller](https://github.com/bora-sy/ESPRobot/tree/main/src/Controllerf) folder in VS Code.
   - PlatformIO will automatically detect the environment.

3.2- **Connect your Board:**  
   Connect an ESP32 Board (or any board with any ESP32 module) to your computer via USB.

3.3- **Select the Environment:**  
   Make sure the correct environment is selected in `platformio.ini`. You can modify this file if needed.

3.4- **Upload the Code:**  
   - Click on the PlatformIO icon in the sidebar.
   - Under "PROJECT TASKS," select your environment.
   - Click on "Upload" to compile and upload the code to your board.

## Preview

<img src="https://github.com/user-attachments/assets/b0709aea-4183-4fce-ab9e-c56dfe979041" width="500">
