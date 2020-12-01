/* Author: N. Rattensperger ------- MQ7 Gassensoren
 *  Beschreibung:
 *  Ein Programm zum Auslesen von 2 MQ7 Gassensoren, Mess-Ausfallsicherheit durch 2 Sensoren,
 *  LCD Anzeige der aktuellen Messwerte und Alarmierung durch LEDs
 *  Features:
 *  -Vergleich der Messwerte, bei Abweichung von mehr als X Prozent --> Alarmierung durch weiß+grüne zeitgleich+LCD
*/

//Initialisieren der Variablen und Bennenung der Nano-Belegung:
int green = 2;
int yellow = 3;
int red = 4;
int white = 5;

int gassensor1 = A0;
int gas1raw = 0;
int gaswert1 = 0;

int gassensor2 = A1;
int gas2raw = 0;
int gaswert2 = 0;

int additiveSumme = 0;

void setup() {
  // Serieller Monitor für Debugging:
  Serial.begin(19200);
  
  // Pinmodi setzen für Ausgänge und Eingänge:
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(white, OUTPUT);
  
  pinMode(gassensor1, INPUT);
  pinMode(gassensor2, INPUT);
}

void loop() {
  // Messung der Spannung des Sensors:
  gas1raw = analogRead(gassensor1);
  gas2raw = analogRead(gassensor2);
  
  // Messewrte von 0-254 auf 0-100 mappen
  gaswert1 = map(gas1raw, 0, 254, 0, 100);
  gaswert2 = map(gas2raw, 0, 254, 0, 100);

  //Messwerte überprüfen
  additiveSumme = (gaswert1+gaswert2)/2;

  //Leds anhand der Werte leuchten lassen <= 25% grün, 50% gelb, 75% rot, >75% weißer ALARM!
  if ((gaswert1 <= 25) && (gaswert2 <=25)){
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
    digitalWrite(white, LOW);
    delay(50);        }
    else if (((gaswert1 >= 25) && (gaswert1 <=50 )) || ((gaswert2 >= 25) && (gaswert2 <=50 ))){
      digitalWrite(green, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, LOW);
      digitalWrite(white, LOW);
      delay(50);      }     
      else if ((gaswert1 >= 50) && (gaswert1 <=75 ) || (gaswert2 >= 50) && (gaswert2 <=75 )){
      digitalWrite(green, HIGH);
      digitalWrite(yellow, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(white, LOW);
      delay(50);      }
      else {
        digitalWrite(green, HIGH);
        digitalWrite(yellow, HIGH);
        digitalWrite(red, HIGH);
        digitalWrite(white, HIGH);   };

      
  Serial.print("1. Gaswert = "); Serial.println(gaswert1);
  Serial.print("2. Gaswert = "); Serial.println(gaswert2);
  Serial.print("Additive Prüfsumme = "); Serial.println(additiveSumme);
}
