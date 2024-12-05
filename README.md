**🚗 Smart Parking System using ESP32
**A real-time Smart Parking System built with an ESP32 microcontroller and ultrasonic sensors to detect parking spot occupancy. The project features a dynamic web interface powered by WebSockets for live status updates.

📖 Table of Contents
Features
Hardware Components
Hardware Setup
Installation and Setup
ESP32 Code
Web Interface Hosting
Usage
Screenshots
Troubleshooting
License
✨ Features
Ultrasonic Sensor Integration: Detects whether a parking spot is occupied or vacant.
LED Indicators:
🟥 Red LED: Spot is Occupied.
🟩 Green LED: Spot is Vacant.
Real-Time WebSocket Communication: Live updates to the web interface.
Browser-Based Monitoring: Simple and visually appealing dashboard for real-time status.
🔧 Hardware Components
Component	ESP32 Pin
Ultrasonic Sensor TRIG	GPIO 13
Ultrasonic Sensor ECHO	GPIO 25
Red LED	GPIO 2
Green LED	GPIO 16
Resistors (220Ω)	N/A
🛠️ Hardware Setup
Ultrasonic Sensor:
Connect TRIG to GPIO 13.
Connect ECHO to GPIO 25.
LEDs:
Red LED to GPIO 2 (with 220Ω resistor).
Green LED to GPIO 16 (with 220Ω resistor).
Use a breadboard and jumper wires for easy assembly.
🚀 Installation and Setup
1️⃣ ESP32 Code
Clone this repository:
bash
Copy code
git clone https://github.com/<your_username>/SmartParkingESP32.git
Open esp32_parking.ino in the Arduino IDE.
Install the required library:
WebSocketsServer (via the Arduino Library Manager).
Update your WiFi credentials:
cpp
Copy code
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
Upload the code to your ESP32.
Open the Serial Monitor to find the ESP32’s IP address.
2️⃣ Web Interface Hosting
Option 1: Host with GitHub Pages
Upload the index.html file to your GitHub repository.
Enable GitHub Pages in Settings > Pages.
Access the hosted page at:
arduino
Copy code
https://<your_username>.github.io/SmartParkingESP32/
Update the WebSocket URL in the index.html file:
javascript
Copy code
const ws = new WebSocket('ws://<ESP32_IP>:81');
Option 2: Host Locally
Save index.html in a folder on your computer.
Open a terminal and navigate to the folder:
bash
Copy code
cd /path/to/folder
Start a local server:
bash
Copy code
python -m http.server 8000
Open your browser and go to:
arduino
Copy code
http://localhost:8000
🕹️ Usage
Power on the ESP32 and ensure it connects to your WiFi network.
Open the hosted web page (either via GitHub Pages or locally).
Observe the parking status in real-time:
Vacant: Green LED is on, and the status shows "Vacant."
Occupied: Red LED is on, and the status shows "Occupied."
📸 Screenshots
Web Dashboard

❓ Troubleshooting
No WebSocket Connection:
Ensure the ESP32 and your browser are on the same network.
Verify the WebSocket URL in index.html points to the correct ESP32 IP address.
LEDs Not Working:
Double-check the hardware connections.
Ensure the LEDs and resistors are properly installed.
📜 License
This project is licensed under the MIT License. See the LICENSE file for more details.

🌟 Contributions
Contributions are welcome! Feel free to:

Fork the repository.
Create a new branch.
Submit a pull request with your improvements.
💡 Future Enhancements
Support for multiple parking spots.
Integration with a database for historical data.
Advanced analytics and remote IoT monitoring.
