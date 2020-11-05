#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // gsm module connected here
String textForSMS;
 
int FlameSensor = 4; // Flame Sensor
int Sound = 5; 
int ledred = 6;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(9600);
  SIM900.begin(9600); // original 19200. while enter 9600 for sim900A
  Serial.println(" logging time completed!");
  pinMode(FlameSensor, INPUT); 
  pinMode(Sound, OUTPUT);
  pinMode(ledred, OUTPUT);
  digitalWrite(Sound, LOW); 
  delay(5000); // wait for 5 seconds
}
 
void loop() {
  if ( digitalRead(FlameSensor) == HIGH) // 
  {
    textForSMS =  "\nFire Detected!";  
    digitalWrite(Sound, HIGH);
    digitalWrite(ledred, HIGH); 
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent."); 
    delay(4000);
  }
  else // 
  {  
    Serial.println("No Fire Detected"); 
    digitalWrite(Sound, LOW);
    digitalWrite(ledred, LOW); 
    delay(1000);
  }
}
 
 
void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000); 
  SIM900.println("AT + CMGS = \"+6285155402287\"");  // recipient's mobile number, in international format
  delay(1000);
  SIM900.println(message);                         // message to send
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
  SIM900.println();
  delay(100);                                     // give module time to send SMS
}
