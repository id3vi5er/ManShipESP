#include <ESP8266WiFi.h>
float temps;
float hums;
String request;
String data;
char ssid[] = "WLAN";
char pass[] = "1Qay2Wsx3Edc";
WiFiServer server(80);
IPAddress ip(192, 168, 0, 80);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    if (client.connected()) {
      request = client.readStringUntil('\r');
      hums = request.toFloat();
      client.flush();
      request = client.readStringUntil('\r'); 
      temps = request.toFloat();
      client.flush();
    }
    client.stop();
    NextionData();
  }
}

void NextionData() {
  data = "temps.txt=\"" + String(temps, 1) + "\"";
  Serial.println(temps);
  //Serial.write(0xff);
  //Serial.write(0xff);
  //Serial.write(0xff);
  data = "hums.txt=\"" + String(hums, 1) + "\"";
  Serial.println(hums);
  //Serial.write(0xff);
  //Serial.write(0xff);
  //Serial.write(0xff);
}
