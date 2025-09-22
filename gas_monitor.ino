#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// WiFi Configuration
#define WIFI_SSID "YOUR_WIFI_SSID"       // Ganti dengan SSID WiFi Anda
#define WIFI_PASS "YOUR_WIFI_PASSWORD"   // Ganti dengan password WiFi Anda

// Antares Configuration
const char* host = "platform.antares.id";
const int httpsPort = 8443;
const char* accessKey = "YOUR_ACCESS_KEY"; // Ganti dengan AccessKey Antares Anda
const char* projectName = "YOUR_PROJECT_NAME"; // Ganti dengan nama project Antares
const char* deviceName = "YOUR_DEVICE_NAME"; // Ganti dengan nama device Antares

// Pin Configuration
const int analogPin = A0; // Output analog MQ-135
const int digitalPin = D0; // Output digital MQ-135 (threshold alarm)

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(digitalPin, INPUT);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  // For testing purposes (ignore SSL certificate)
  client.setInsecure();
}

void loop() {
  // Read sensor values
  int analogValue = analogRead(analogPin);
  int digitalValue = digitalRead(digitalPin);

  Serial.print("MQ135 Analog Value: ");
  Serial.println(analogValue);
  Serial.print("MQ135 Digital Value: ");
  Serial.println(digitalValue);

  // Create JSON payload
  String conData = String("{\"sensorValue\":") + analogValue +
                   String(",\"digitalValue\":") + digitalValue + String("}");

  // Prepare HTTP POST payload
  String payload = String("{\"m2m:cin\":{\"con\":\"") + conData + "\"}}";

  // Construct URL
  String url = "/~/antares-cse/antares-id/" + String(projectName) + "/" + String(deviceName);

  // Connect to Antares
  if (!client.connect(host, httpsPort)) {
    Serial.println("Connection failed");
    delay(10000);
    return;
  }

  // Send HTTP POST request
  client.println("POST " + url + " HTTP/1.1");
  client.println("Host: " + String(host));
  client.println("X-M2M-Origin: " + String(accessKey));
  client.println("Content-Type: application/json;ty=4");
  client.print("Content-Length: ");
  client.println(payload.length());
  client.println();
  client.println(payload);

  // Read server response
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") break;
  }
  String response = "";
  while (client.available()) {
    response += client.readString();
  }
  Serial.println("Response: " + response);

  client.stop();

  // Send data every 30 seconds
  delay(30000);
}
