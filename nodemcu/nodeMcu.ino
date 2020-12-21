#include <SocketIoClient.h>

const char* ssid     = "<wifi_name>";
const char* password = "<wifi_path>";

char host[] = "<wifi_domain>";
int port = 80;
char path[] = "/socket.io/?transport=websocket";

int LEDPin = 16;
int BULBPin = 5;

SocketIoClient webSocket;

void current_status(const char * payload, size_t length) {
  String onState = String(payload);
  Serial.print("Current Status: ");
  Serial.println(payload);
  if (onState.equals("ON")) {
    digitalWrite(BULBPin, HIGH);
  } else {
    digitalWrite(BULBPin, LOW);
  }
}

void setUpWifiConnection() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(LEDPin, OUTPUT);
  pinMode(BULBPin, OUTPUT);

  setUpWifiConnection();

  webSocket.on("status", current_status);
  webSocket.begin(host, port, path);
}
void loop() {
  webSocket.loop();
}
