Smart Parking System using ESP32
A real-time smart parking system that uses an ESP32 microcontroller with an ultrasonic sensor to detect the occupancy of a parking spot. The system provides live status updates via a WebSocket server, which can be accessed through a browser-hosted web page.

Features
Ultrasonic Sensor Integration: Detects if a parking spot is occupied based on distance.
LED Indicators:
Red LED: Spot is occupied.
Green LED: Spot is vacant.
Real-Time WebSocket Updates: Provides live updates to connected clients.
Browser-Based Monitoring: Displays parking status dynamically on a user-friendly web interface.
Components Required
ESP32 microcontroller
Ultrasonic Sensor (e.g., HC-SR04)
LEDs:
Red (occupied)
Green (vacant)
Resistors (220Ω)
Jumper wires
Breadboard
Hardware Connections
Component	ESP32 Pin
Ultrasonic Sensor TRIG	GPIO 13
Ultrasonic Sensor ECHO	GPIO 25
Red LED	GPIO 2
Green LED	GPIO 16
Installation and Setup
ESP32 Code
Clone this repository or download the files.
Open the esp32_parking.ino file in the Arduino IDE.
Install the required libraries:
WebSocketsServer: Available in the Arduino Library Manager.
Update the WiFi credentials in the code:
cpp
Copy code
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
Upload the code to your ESP32.
Open the Serial Monitor to get the ESP32’s IP address.
Hosting the Web Page
Option 1: GitHub Pages
Upload the index.html file to a GitHub repository.
Enable GitHub Pages in the repository settings.
Access the hosted page at the provided URL (e.g., https://<your_username>.github.io/SmartParkingESP32/).
Update the WebSocket URL in index.html:
javascript
Copy code
const ws = new WebSocket('ws://<ESP32_IP>:81');
Option 2: Local Hosting
Place index.html in a local folder.
Open a terminal and navigate to the folder.
Run the following command to start a local server:
bash
Copy code
python -m http.server 8000
Open your browser and navigate to:
arduino
Copy code
http://localhost:8000
Usage
Power on the ESP32 and ensure it connects to WiFi.
Access the web page (either via GitHub Pages or locally).
Monitor the real-time status of the parking spot:
Vacant: Green LED is on; status is "Vacant."
Occupied: Red LED is on; status is "Occupied."
Screenshots
Web Interface

Troubleshooting
No WebSocket Connection:
Ensure the ESP32 and the browser are on the same network.
Double-check the WebSocket URL in the index.html file.
LEDs Not Working:
Verify the hardware connections.
Check the LED polarity and resistor values.
License
This project is licensed under the MIT License. See the LICENSE file for details.

