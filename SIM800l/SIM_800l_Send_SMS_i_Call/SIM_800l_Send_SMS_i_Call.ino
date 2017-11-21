#include <SoftwareSerial.h>
SoftwareSerial sim800l(10, 11); // RX, TX
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
boolean flagButton = true;

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  sim800l.begin(4800); 
delay(2000);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
    //Call();
    delay(1000);
    
  }
  if(buttonState == LOW){
    digitalWrite(ledPin, LOW);
  }

  


}

void SendTextMessage()
{
  delay(5000);
  sim800l.print("AT+CMGF=1\r");
  delay(100);
  sim800l.print("AT+CMGS=\"+381600676824\"\r");
  //6177
  delay(200);
  sim800l.print(":*");
  sim800l.print("\r");
  delay(500);
  sim800l.print((char)26);
  delay(100);
  sim800l.println();
  delay(500);
} 


void Call()
{
  delay(5000);
  sim800l.print("AT+CMGF=1\r");
  delay(100);
  sim800l.print("ATD+381600676824;\n\r");  
  delay(70000);
} 
