#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <WiFi.h>
#include <PubSubClient.h>

HardwareSerial uart(2);
TinyGPSPlus gps;



//const char* ssid = "JL21";
//const char* password = "Wangerooge";
//const char* mqtt_server = "192.168.2.100";

const char* ssid = "WLAN";
const char* password = "1Qay2Wsx3Edc";
const char* mqtt_server = "192.168.0.10";

WiFiClient espClient;
PubSubClient client(espClient);
//long lastMsg = 0;

void setup_wifi() {

  delay(10);
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
    String clientId = "GPS_Modul";
    clientId += String(random(0xffff), HEX);
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


void setup() {
  uart.begin(9600, SERIAL_8N1, 17, 16);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{

  if (!client.connected()) {
    reconnect();
  }
    float latitude = 0;
    float longitude = 0;
    double groundspeed = 0;
    double coursedegree = -1;


  // This sketch displays information every time a new sentence is correctly encoded.
  while (uart.available() > 0)
    if (gps.encode(uart.read())){
      if (gps.location.isValid()){
        latitude = gps.location.lat(); //flaot
        Serial.println(latitude, 8);
        longitude = gps.location.lng(); //float
        Serial.println(longitude, 8);
        groundspeed = gps.speed.kmph();  //double
        Serial.println(groundspeed);
        coursedegree = gps.course.deg();

       
        char latitudeString[11];
        dtostrf(latitude, 11, 8, latitudeString);
        client.publish("/nav/latitude", latitudeString);
        delay(200);
        char longitudeString[10];
        dtostrf(longitude, 10, 8, longitudeString);
        client.publish("/nav/longitude", longitudeString);
        delay(200);
        char groundspeedString[8];
        dtostrf(groundspeed, 2, 1, groundspeedString);
        client.publish("/nav/groundspeed", groundspeedString);
        delay(200);
        char coursedegreeString[8];
        dtostrf(coursedegree, 3, 0, coursedegreeString);
        //Serial.println(coursedegreeString);
        client.publish("/nav/coursedegree", coursedegreeString);
        delay(200);

     }

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while (true);
  }
}
}

/*void displayInfo(){
  if (gps.location.isValid())
  {
    //Serial.print(gps.location.lat(), 6);
    //Serial.print(F(","));
    //Serial.print(gps.location.lng(), 6);
    Serial.print("Speed in kmp/h: ");
    Serial.println(gps.speed.kmph()); // Speed in kilometers per hour (double)

  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
      Serial.print(gps.date.month());
      Serial.print(F("/"));
      Serial.print(gps.date.day());
      Serial.print(F("/"));
      Serial.print(gps.date.year());
      Serial.print(" Speed over Ground: ");
      Serial.print(gps.speed());
      Serial.println(gps.course.deg()); // Course in degrees (double)

    //Serial.print("Latitude: ");
    //Serial.println(gps.location.lat(), 6); // Latitude in degrees (double)
    //Serial.print("Longitude: ");
    //Serial.println(gps.location.lng(), 6); // Longitude in degrees (double)
    //Serial.print(gps.location.rawLat().negative ? "-" : "+");
    //Serial.println(gps.location.rawLat().deg); // Raw latitude in whole degrees
    //Serial.println(gps.location.rawLat().billionths);// ... and billionths (u16/u32)
    //Serial.print(gps.location.rawLng().negative ? "-" : "+");
    //Serial.println(gps.location.rawLng().deg); // Raw longitude in whole degrees
    //Serial.println(gps.location.rawLng().billionths);// ... and billionths (u16/u32)
    //Serial.println(gps.date.value()); // Raw date in DDMMYY format (u32)
    //Serial.println(gps.date.year()); // Year (2000+) (u16)
    //Serial.println(gps.date.month()); // Month (1-12) (u8)
    //Serial.println(gps.date.day()); // Day (1-31) (u8)
    //Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
    //Serial.println(gps.time.hour()); // Hour (0-23) (u8)
    //Serial.println(gps.time.minute()); // Minute (0-59) (u8)
    //Serial.println(gps.time.second()); // Second (0-59) (u8)
    //Serial.println(gps.time.centisecond()); // 100ths of a second (0-99) (u8)
    //Serial.println(gps.speed.value()); // Raw speed in 100ths of a knot (i32)
    //Serial.println(gps.speed.knots()); // Speed in knots (double)
    //Serial.println(gps.speed.mph()); // Speed in miles per hour (double)
    //Serial.println(gps.speed.mps()); // Speed in meters per second (double)

    //Serial.println(gps.course.value()); // Raw course in 100ths of a degree (i32)
    //Serial.println(gps.altitude.value()); // Raw altitude in centimeters (i32)
    //Serial.println(gps.altitude.meters()); // Altitude in meters (double)
    //Serial.println(gps.altitude.miles()); // Altitude in miles (double)
    //Serial.println(gps.altitude.kilometers()); // Altitude in kilometers (double)
    //Serial.println(gps.altitude.feet()); // Altitude in feet (double)
    Serial.print("Satellites in View: ");
    Serial.println(gps.satellites.value());

    Serial.print("Horizontale Precision: ");// Number of satellites in use (u32)
    Serial.println(gps.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
    delay(5000);
*/
