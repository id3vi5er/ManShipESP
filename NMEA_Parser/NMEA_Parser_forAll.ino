/*
 * NMEAParser für Windgeschwindigkeit und Richtung
 * Wenn Nachricht reinkommt wird sie über den Seriellen Monitor ausgegeben
 * 
 * 
 */
#include <NMEAParser.h>

/* A parser is declared with 2 handlers at most */
NMEAParser<1> parser;

//"MWV,x.x,a,x.x,a*hh<CR><LF>"

void errorHandler()
{
  Serial.print("*** Error : ");
  Serial.println(parser.error()); 
}


void firstHandler()
{
  Serial.print("Got $MWV with ");
  Serial.print(parser.argCount());
  Serial.println(" arguments");
  float WindAngle;
  char Reference;
  float WindSpeed;
  char WindUnit;
  char Status;
  if (parser.getArg(0,WindAngle)) Serial.println(WindAngle);
  if (parser.getArg(1,Reference)) Serial.println(Reference);
  if (parser.getArg(2,WindSpeed)) Serial.println(WindSpeed);
  if (parser.getArg(3,WindUnit)) Serial.println(WindUnit);
  if (parser.getArg(4,Status)) Serial.println(Status);
}

void secondHandler()
{
  Serial.print("Got $XDR with ");
  Serial.print(parser.argCount());
  Serial.println(" arguments");
  char TransducerType[10];
  float Measurement;
  char Unit;
  char TransducerName[10];
  if (parser.getArg(0,TransducerType)) Serial.println(TransducerType);
  if (parser.getArg(1,Measurement)) Serial.println(Measurement);
  if (parser.getArg(2,Unit)) Serial.println(Unit);
  if (parser.getArg(3,TransducerName)) Serial.println(TransducerName);
}

void setup()
{
  Serial.begin(115200);

  parser.setErrorHandler(errorHandler);
  parser.addHandler("MWV", firstHandler);
  parser.addHandler("XDR", secondHandler);
  
  
  
  //Serial.print("Parsing : ");
  //Serial.print(firstSentence);
  //for (uint8_t i = 0; i < strlen(firstSentence); i++) {
  //  parser << firstSentence[i];
  //}

  //Serial.print("Parsing : ");
  //Serial.print(secondSentence);
  //for (uint8_t i = 0; i < strlen(secondSentence); i++) {
  //  parser << secondSentence[i];
 
}

void loop()
{
}
