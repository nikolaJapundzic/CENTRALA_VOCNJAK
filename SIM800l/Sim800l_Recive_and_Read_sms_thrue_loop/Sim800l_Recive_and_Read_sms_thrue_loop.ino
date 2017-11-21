#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library
SoftwareSerial sim800l(10, 11); // RX, TX
String text;     // to storage the text of the sms
uint8_t index;   // to indicate the message to read.


void setup(){
  Serial.begin(9600); // only for debug the results . 
  Sim800l.begin(); // initializate the library. 
  SoftwareSerial.print("AT+CMGF=1\r");
  delay(100);
  SoftwareSerial.print("ATD+381600676824;\n\r");
  

}

void loop(){
 
}


