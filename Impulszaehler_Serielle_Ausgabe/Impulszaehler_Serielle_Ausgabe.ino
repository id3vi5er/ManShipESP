/*
 Impulszaehler
 Gibt die Impulse pro Sekunde des Spannungsignals 
 an Pin X aus wenn Signal auf LOW geht mit INTERNAL_PULLUP
*/
int pin = 7;                          //Anschluss des Impulsgebers (max 5VDC/3,3VDC nach Arduino Modell)
double ILiter = 1800;                 //Angabe des Herstellers für ausgegebene Impulse pro Liter
unsigned long messZeit = 10;          //Messzeit in Sekunden

unsigned long N;                      //Anzahl der Impulse
unsigned long zeitNow;                //Startzeit
unsigned long T = messZeit*1000000;   //Messzeit in µS umwandeln
double durchfluss;                    //Berechneter Durchfluss pro MessZeit
double v; //rechenvariable
double f;

void setup() 
{ Serial.begin(9600);
  pinMode(pin, INPUT_PULLUP);
  
}

void berechneDurchfluss()
{
  v = 1 / ILiter;                     //0.000555;
  durchfluss = v * N;
}


void loop() 
{ N = 0; zeitNow = micros();
  do
    {
      if (pulseIn(pin, LOW)>0) {
        N++; //wenn pulseIn() 
      }
    }
    while( micros() < (zeitNow+T) ); 
  berechneDurchfluss();  
  Serial.print("Anzahl der Impulse: ");  
  Serial.println(N);
  Serial.print("Zeit der Messung in Sekunden: ");
  Serial.println(messZeit);
  Serial.print("Durchfluss: ");
  Serial.print(durchfluss,4);
  Serial.print(" Liter");
  if (durchfluss < 0.1){
    f = durchfluss * 1000;
    Serial.print(" bzw. ");
    Serial.print(f);
    Serial.println("ml");
    } else {
      Serial.println();
      }
  Serial.println();
}
