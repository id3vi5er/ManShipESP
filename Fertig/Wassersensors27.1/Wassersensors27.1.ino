#include <WiFi.h>
#include <PubSubClient.h>

#define Threshold 5 /* Greater the value, more the sensitivity */
#define alarm 1

RTC_DATA_ATTR int bootCount = 0;
touch_pad_t touchPin;

//const char* ssid = "JL21";
//const char* password = "Wangerooge";
//const char* mqtt_server = "192.168.2.100";

const char* ssid = "WLAN";
const char* password = "1Qay2Wsx3Edc";
const char* mqtt_server = "192.168.0.10";


WiFiClient espClient;
PubSubClient client(espClient);

/*void print_wakeup_touchpad(){
  touchPin = esp_sleep_get_touchpad_wakeup_status();

  switch(touchPin)
  {
    case 0  : Serial.println("Touch detected on GPIO 4"); break;
    case 1  : Serial.println("Touch detected on GPIO 0"); break;
    case 2  : Serial.println("Touch detected on GPIO 2"); break;
    case 3  : Serial.println("Touch detected on GPIO 15"); break;
    case 4  : Serial.println("Touch detected on GPIO 13"); break;
    case 5  : Serial.println("Touch detected on GPIO 12"); break;
    case 6  : Serial.println("Touch detected on GPIO 14"); break;
    case 7  : Serial.println("Touch detected on GPIO 27"); break;
    case 8  : Serial.println("Touch detected on GPIO 33"); break;
    case 9  : Serial.println("Touch detected on GPIO 32"); break;
    default : Serial.println("Wakeup not by touchpad"); break;
  }
}
*/

void callbackAlarm(){
}

void setup_wifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "Wassersensor1";
    //clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
      }
    }
}

void setup(){
  delay(750);
  Serial.begin(115200);
  delay(200);
  ++bootCount;
  setup_wifi();
  delay(500);

  delay(150);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  if (!client.connected()) {
  reconnect(); }
  Serial.println("MQTT Verbunden!");
  client.loop();
  
  char bootString[50];
  dtostrf(bootCount, 50, 1, bootString);
  
  
  client.publish("/alarm/Wassersensors1/", bootString);
  delay(200);
  Serial.println("MQTT Gesendet!");
  Serial.println(bootCount);
  /* 
  //Print the wakeup reason for ESP32 and touchpad too
  print_wakeup_reason();
  print_wakeup_touchpad();
  */
  
  //Setup interrupt on Touch Pad 3 (GPIO15)
  touchAttachInterrupt(T3, callbackAlarm, Threshold);
  //Serial.println(bootCount);
  esp_sleep_enable_touchpad_wakeup();
  Serial.println("ESP goes to Deepsleep");
  esp_deep_sleep_start();
}

void loop(){
  //This will never be reached
}
