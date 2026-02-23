#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x08

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

// Web page
void handleRoot() {
  String html =
    "<!DOCTYPE html><html>"
    "<body>"
    "<h2>ESP32 I2C Master</h2>"
    "<form action='/send'>"
    "Message: <input type='text' name='msg'>"
    "<input type='submit' value='Send'>"
    "</form>"
    "</body></html>";

  server.send(200, "text/html", html);
}

// Send message via I2C
void handleSend() {
  String msg = server.arg("msg");

  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write((uint8_t*)msg.c_str(), msg.length());
  Wire.endTransmission();

  server.send(200, "text/html", "Message Sent: " + msg + "<br><a href='/'>Go Back</a>");
}

void setup() {
  Serial.begin(115200);

  // I2C Master
  Wire.begin();

  // WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Web server routes
  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.begin();
}

void loop() {
  server.handleClient();
}
