#include <ESP8266WiFi.h>
#include <math.h>
char ssid[] = "WLAN";
char pass[] = "1Qay2Wsx3Edc";
IPAddress server(192, 168, 0, 80);
WiFiClient client;
float hums;
float temps;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, pass);      
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
    }
}

void loop(){ 
  //hums = mySensor.readFloatHumidity();
  //temps = mySensor.readTempC();
  //Serial.print("Humidity: ");
  //Serial.print(hums, 2);
  //Serial.print(" Temp: ");
  //Serial.print(temps, 2);
  //Serial.println();
  hums = random(0,100);
  temps = random(0,30);
  
  client.connect(server, 80);   
  client.println(hums,2);
  client.flush();
  delay(500);
  client.println(temps,2);
  client.flush();
  delay(2000);
}
