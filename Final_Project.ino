#include <WiFi.h>
#include <WebSocketsServer.h>

// WiFi credentials
const char* ssid = "SpectrumSetup-BA";
const char* password = "Hotpoint@1252";

#define NUM_SPOTS 1
#define DISTANCE_THRESHOLD 10
#define OCCUPANCY_TIME_THRESHOLD 5000

const int TRIG_PINS[NUM_SPOTS] = {13};
const int ECHO_PINS[NUM_SPOTS] = {25};
const int LED_RED_PINS[NUM_SPOTS] = {2};
const int LED_GREEN_PINS[NUM_SPOTS] = {16};

bool spotStatus[NUM_SPOTS] = {false};
unsigned long entryTime[NUM_SPOTS] = {0};
unsigned long previousMillis = 0;
const long interval = 100;

WebSocketsServer webSocket = WebSocketsServer(81);

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Smart Parking</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; background-color: #f4f4f9; margin: 0; padding: 0; }
    h1 { margin: 20px 0; color: #333; }
    .container { display: flex; justify-content: center; flex-wrap: wrap; margin-top: 20px; }
    .spot { display: flex; flex-direction: column; align-items: center; justify-content: center; width: 150px; height: 150px; margin: 10px; border: 2px solid #333; border-radius: 10px; text-align: center; font-size: 18px; font-weight: bold; position: relative; }
    .vacant { background-color: #d4edda; color: #155724; }
    .occupied { background-color: #f8d7da; color: #721c24; }
    .vacant::before { content: "\u26F7"; font-size: 50px; color: #155724; position: absolute; top: 20px; }
    .occupied::before { content: "\uD83D\uDE97"; font-size: 50px; color: #721c24; position: absolute; top: 20px; }
    .spot span { margin-top: 80px; }
  </style>
</head>
<body>
  <h1>Smart Parking Status</h1>
  <div id="parking-container" class="container"></div>
  <script>
    const ws = new WebSocket('ws://' + window.location.hostname + ':81/');
    ws.onmessage = (event) => {
      document.getElementById('parking-container').innerHTML = event.data;
    };
  </script>
</body>
</html>
)rawliteral";

String generateSpotHTML() {
  String spots = "";
  for (int i = 0; i < NUM_SPOTS; i++) {
    if (spotStatus[i]) {
      spots += "<div class='spot occupied'><span>Spot " + String(i + 1) + ": Occupied</span></div>";
    } else {
      spots += "<div class='spot vacant'><span>Spot " + String(i + 1) + ": Vacant</span></div>";
    }
  }
  return spots;
}

void handleWebSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
  if (type == WStype_TEXT) {
    if (strcmp((char*)payload, "GET_STATUS") == 0) {
      String htmlContent = generateSpotHTML();
      webSocket.sendTXT(num, htmlContent);
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("IP Address: " + WiFi.localIP().toString());

  webSocket.begin();
  webSocket.onEvent(handleWebSocketEvent);

  for (int i = 0; i < NUM_SPOTS; i++) {
    pinMode(TRIG_PINS[i], OUTPUT);
    pinMode(ECHO_PINS[i], INPUT);
    pinMode(LED_RED_PINS[i], OUTPUT);
    pinMode(LED_GREEN_PINS[i], OUTPUT);

    digitalWrite(LED_RED_PINS[i], LOW);
    digitalWrite(LED_GREEN_PINS[i], HIGH);
    spotStatus[i] = false;
    entryTime[i] = 0;
  }
}

long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 10000);
  if (duration == 0) {
    return -1;
  } else {
    return duration * 0.034 / 2;
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    for (int i = 0; i < NUM_SPOTS; i++) {
      long distance = measureDistance(TRIG_PINS[i], ECHO_PINS[i]);

      if (distance != -1 && distance < DISTANCE_THRESHOLD) {
        if (entryTime[i] == 0) {
          entryTime[i] = currentMillis;
        }
        if (!spotStatus[i] && (currentMillis - entryTime[i] >= OCCUPANCY_TIME_THRESHOLD)) {
          spotStatus[i] = true;
          digitalWrite(LED_RED_PINS[i], HIGH);
          digitalWrite(LED_GREEN_PINS[i], LOW);
          Serial.println("Spot " + String(i + 1) + ": Occupied");
        }
      } else {
        entryTime[i] = 0;
        if (spotStatus[i]) {
          spotStatus[i] = false;
          digitalWrite(LED_RED_PINS[i], LOW);
          digitalWrite(LED_GREEN_PINS[i], HIGH);
          Serial.println("Spot " + String(i + 1) + ": Vacant");
        }
      }
    }

    String htmlContent = generateSpotHTML();
    webSocket.broadcastTXT(htmlContent);
  }

  webSocket.loop();
}