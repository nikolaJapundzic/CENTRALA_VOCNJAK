//MEMBRAN PAD*******************************************************************************
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
};

byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 9, 8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//MEMBRAN PAD*******************************************************************************
//LCD **************************************************************************************
#include "Wire.h"
#include "LCD.h"
#include "LiquidCrystal_I2C.h"

#define I2C_ADDR 0x3F  // ovo sto pise 0x3F to je adresa displeja, nju promenuti po potrebi.
//znace se koja je kada se pokrene LCD_I2C_scanner fajl i uploaduje u arduino kada je standardno
//nakacen displej po slici koja je data pored fajla ili u blizini na A4 i A5
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
//LCD **************************************************************************************
//SIM800L **********************************************************************************
#include <SoftwareSerial.h>
#include <Sim800l.h>
Sim800l Sim800l;
String text;     // to storage the text of the sms 
uint8_t index;   // to indicate the message to read.
//SoftwareSerial sim800l(10, 11); // RX, TX
const int buttonPin = 3;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
const int ledPin17 =  17;
boolean flagButton = true;

int buttonState = 0;         // variable for reading the pushbutton status
String brojTelefona = "";
boolean flag = true;
boolean flag2 = true;
boolean flag3 = true;
int sensorValue = 0;
boolean flagZICA = true;
boolean flagSHOCH = true;
boolean flagNAPON9 = true;
boolean flagNAPON10 = true;
boolean flagTEMPERATURA = true;
//SIM800L **********************************************************************************

//TEMPERATURE SENSOR ***********************************************************************
#include <OneWire.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// http://milesburton.com/Dallas_Temperature_Control_Library

OneWire  ds(2);  // on pin 2 (a 4.7K resistor is necessary)
float celsius, fahrenheit;
//TEMPERATURE SENSOR ***********************************************************************
//VOLTAGE MESURMENT  ***********************************************************************
int sensorValue2 = 0;
float voltage = 0;
//VOLTAGE MESURMENT  ***********************************************************************
//WIRE MESURMENT  **************************************************************************
int sensorValue3 = 0;
//WIRE MESURMENT  **************************************************************************

//SHOCK MESURMENT  *************************************************************************
int shock = 3; // define the sensor Pin 
int val; // define a numeric variable val 
//SHOCK MESURMENT  *************************************************************************




void setup(){
  //MEMBRAN PAD*******************************************************************************
   //Serial.begin(9600);
   //MEMBRAN PAD*******************************************************************************
   //LCD **************************************************************************************
   pinMode(ledPin17, OUTPUT);
  Sim800l.begin(); // initializate the library. 
  Sim800l.delAllSms();
   lcd.begin (16,2);

// LCD Backlight ON
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);

lcd.home (); // go home on LCD 
lcd.setCursor (2,0); // prvi broj = pozicija u redu, drugi broj broj reda (od nule se broji, znaci 0 = 1)
        lcd.print("Dobro  Dosli");
   //LCD **************************************************************************************
   //SIM800L **********************************************************************************
   pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  //sim800l.begin(4800); 
delay(2000);
lcd.clear();
   //SIM800L **********************************************************************************
   //TEMPERATURE SENSOR ***********************************************************************
   //TEMPERATURE SENSOR ***********************************************************************
   //SHOCK MESURMENT  *************************************************************************
  pinMode (shock, INPUT); // input from KY-002 sensor
//SHOCK MESURMENT  *************************************************************************
}






  
void loop(){
  //SHOCK MESURMENT  *************************************************************************
  val = digitalRead (shock); // read the value from KY-002
  //SHOCK MESURMENT  *************************************************************************
  //MEMBRAN PAD*******************************************************************************
  char key = keypad.getKey();
  sensorValue = analogRead(A0);
  //VOLTAGE MESURMENT  ***********************************************************************
  sensorValue2 = analogRead(A1);
  
//VOLTAGE MESURMENT  ***********************************************************************
//WIRE MESURMENT  **************************************************************************
sensorValue3 = analogRead(A2);
//WIRE MESURMENT  **************************************************************************
  
  //MEMBRAN PAD*******************************************************************************
  //LCD **************************************************************************************
  //i++;
  //LCD **************************************************************************************
  //SIM800L **********************************************************************************
  if(flag2){
    if(brojTelefona.length() < 10){
    flag = true;
  }else{
    flag = false;
  }
    if(flag){
      lcd.setCursor (0,0); // prvi broj = pozicija u redu, drugi broj broj reda (od nule se broji, znaci 0 = 1)
        lcd.print("Unesite broj: ");
    }
    if (key){
      if(flag){
        lcd.setCursor (0,1);
        if(key == '1' || key == '2' || key == '3' || key == '4'  || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0'){
          brojTelefona = brojTelefona + key;
          //lcd.clear();
          lcd.print(brojTelefona);
        }      
      }
      if(key == 'A' && brojTelefona.length() != 0){
          String pomoc = "";
          for(int i = 0; i < brojTelefona.length()-1; i++){
            pomoc = pomoc + brojTelefona[i];
          }
          brojTelefona = pomoc;
          lcd.clear();
          lcd.print("Unesite broj: ");
          lcd.setCursor (0,1);
          lcd.print(brojTelefona);
          pomoc = "";
        }
      if(key == 'B' && (brojTelefona.length() == 10 || brojTelefona.length() == 9)){
        flag2 = false;
      }
    }
  }else{
    if(flag3){
      lcd.clear();
      lcd.setCursor (0,0);
      lcd.print("Uspesno ste");
      lcd.setCursor (0,1);
      lcd.print("uneli broj.");
      delay(2000);
      lcd.clear();
      flag3 = false;
    }
    //lcd.clear();
    lcd.setCursor (0,0);
    lcd.print("t=");


    
    lcd.setCursor (7,0);
    lcd.print("Z=");
    lcd.setCursor(9,0);
    lcd.print("     ");
    lcd.setCursor(9,0);
    float tempZ = sensorValue * (60.0 / 1023.0);
    tempZ = tempZ - 10;
    lcd.print(tempZ,1);
    



    
    lcd.setCursor (0,1);
    lcd.print(brojTelefona);


    
    voltage = (sensorValue2 * (5.0 / 1024.0) * 10)+0.4;
    lcd.setCursor (10,1);
    lcd.print("V=");
    lcd.setCursor (12,1);
    lcd.print(voltage);

    float wire = (sensorValue3 * (5.0 / 1024.0) * 10)+0.4;
    /*
    lcd.setCursor (10,1);
    lcd.print("V=");
    lcd.setCursor (12,1);
    lcd.print(wire);*/

    //TEMPERATURE SENSOR ***********************************************************************
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
    ds.reset_search();
    delay(250);
    return;
  }


  if (OneWire::crc8(addr, 7) != addr[7]) {
      return;
  }
  switch (addr[0]) {
    case 0x10:
      type_s = 1;
      break;
    case 0x28:
      type_s = 0;
      break;
    case 0x22:
      type_s = 0;
      break;
    default:
      return;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44);        // start conversion, use ds.write(0x44,1) with parasite power on at the end

  //delay(1000);     // maybe 750ms is enough, maybe not
  // we might do a ds.depower() here, but the reset will take care of it.

  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad

  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
  }
  celsius = (float)raw / 16.0;
  lcd.setCursor (2,0);
  lcd.print(celsius, 1);
  //lcd.print(" Celsius");
  //TEMPERATURE SENSOR ***********************************************************************

    if(flagTEMPERATURA){
      if(celsius < tempZ){
      //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      String brojBRE = "+381";
      for(int i = 1; i < brojTelefona.length(); i++){
        brojBRE = brojBRE + brojTelefona[i];
      }
      int duzinaNiza = brojBRE.length() +1;
      char brojTelefoncica [duzinaNiza];
      brojBRE.toCharArray(brojTelefoncica, duzinaNiza);      
      Sim800l.sendSms(brojTelefoncica ,"Temperatura je niza od podesene!");
      //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      flagTEMPERATURA = false;
    }
    }
        
    if(flagZICA){
      if(wire < 3){
      lcd.setCursor (15,0);
      lcd.print("X");//presecena zica
      
      //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      String brojBRE = "+381";
      for(int i = 1; i < brojTelefona.length(); i++){
        brojBRE = brojBRE + brojTelefona[i];
      }
      int duzinaNiza = brojBRE.length() +1;
      char brojTelefoncica [duzinaNiza];
      brojBRE.toCharArray(brojTelefoncica, duzinaNiza);      
      Sim800l.sendSms(brojTelefoncica ,"Zica je presecena!");
      //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM


      //Sim800l.callNumber(brojTelefoncica);
      
      flagZICA = false;
      }
      if(wire >= 3){
        lcd.setCursor (15,0);
        lcd.print("O");
      }
    }

    if(flagSHOCH){
      if (val == LOW ) {
        lcd.setCursor (14,0);
        lcd.print("M");
      }
      if (val == HIGH ) {// Neko drma uredjaj
        lcd.setCursor (14,0);
        lcd.print("S");

        //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      String brojBRE = "+381";
      for(int i = 1; i < brojTelefona.length(); i++){
        brojBRE = brojBRE + brojTelefona[i];
      }
      int duzinaNiza = brojBRE.length() +1;
      char brojTelefoncica [duzinaNiza];
      brojBRE.toCharArray(brojTelefoncica, duzinaNiza);      
      Sim800l.sendSms(brojTelefoncica ,"Uredjaj je potresen!");
      //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM

        
        flagSHOCH = false;
        delay(1000);
      }
    }


    if(flagNAPON10){
      if(voltage < 10){
        //SendTextMessage("Napon u akumulatoru je pao ispod 10 [V]!");
        flagNAPON10 = false;
        //Call();
      }
    }
    if(flagNAPON9){
      if(voltage < 9){
        flagNAPON9 = false;
        String brojBRE = "+381";
      for(int i = 1; i < brojTelefona.length(); i++){
        brojBRE = brojBRE + brojTelefona[i];
      }
      int duzinaNiza = brojBRE.length() +1;
      char brojTelefoncica [duzinaNiza];
      brojBRE.toCharArray(brojTelefoncica, duzinaNiza);      
      Sim800l.sendSms(brojTelefoncica ,"Napon u akumulatoru je pao ispod 9 [V]!");
        //SendTextMessage("Napon u akumulatoru je pao ispod 9 [V]!");
        //Call();
      }
    }
    
    
    index=1; // first position in the prefered memory storage. 
    text=Sim800l.readSms(index);
  
    if(text.indexOf("OK") > 0){ // Provera da li je doslo do greske 
      if(text.indexOf("STANJA") > 0){  // Provera dali poruka sadrzi u sebi kljucnu rec
        String stanja = "";
        stanja = stanja + "Temperatura iznosi: ";
        stanja = stanja + celsius;
        stanja = stanja + "\n";
        stanja = stanja + "Napon iznosi: ";
        stanja = stanja + voltage;
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Zica: ";
        if(flagZICA){
          stanja = stanja + "OK";
        }
        if(!flagZICA){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Napon: ";
        if(flagNAPON9){
          stanja = stanja + "OK";
        }
        if(!flagNAPON9){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Stres: ";
        if(flagSHOCH){
          stanja = stanja + "OK";
        }
        if(!flagSHOCH){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Temperatura: ";
        if(flagTEMPERATURA){
          stanja = stanja + "OK";
        }
        if(!flagTEMPERATURA){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------

        // Define 
        String str = stanja; 
        
        // Length (with one extra character for the null terminator)
        int str_len = str.length() + 1; 
        
        // Prepare the character array (the buffer) 
        char char_array[str_len];
        
        // Copy it over 
        str.toCharArray(char_array, str_len);
        
        //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      String brojBRE = "+381";
      for(int i = 1; i < brojTelefona.length(); i++){
        brojBRE = brojBRE + brojTelefona[i];
      }
      int duzinaNiza = brojBRE.length() +1;
      char brojTelefoncica [duzinaNiza];
      brojBRE.toCharArray(brojTelefoncica, duzinaNiza);      
      Sim800l.sendSms(brojTelefoncica ,char_array);
      //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      }

      if(text.indexOf("VRATI") > 0){  // Provera dali poruka sadrzi u sebi kljucnu rec
        flagZICA = true;
        flagSHOCH = true;
        flagNAPON9 = true;
        flagNAPON10 = true;
        flagTEMPERATURA = true;

        String stanja = "";
        stanja = stanja + "Temperatura iznosi: ";
        stanja = stanja + celsius;
        stanja = stanja + "\n";
        stanja = stanja + "Napon iznosi: ";
        stanja = stanja + voltage;
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Zica: ";
        if(flagZICA){
          stanja = stanja + "OK";
        }
        if(!flagZICA){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Napon: ";
        if(flagNAPON9){
          stanja = stanja + "OK";
        }
        if(!flagNAPON9){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Stres: ";
        if(flagSHOCH){
          stanja = stanja + "OK";
        }
        if(!flagSHOCH){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------
        stanja = stanja + "\n";
        stanja = stanja + "Temperatura: ";
        if(flagTEMPERATURA){
          stanja = stanja + "OK";
        }
        if(!flagTEMPERATURA){
          stanja = stanja + "NIJE OK";
        }
        //--------------------------------------------------------------


        // Define 
        String str = stanja; 
        
        // Length (with one extra character for the null terminator)
        int str_len = str.length() + 1; 
        
        // Prepare the character array (the buffer) 
        char char_array[str_len];
        
        // Copy it over 
        str.toCharArray(char_array, str_len);
        
        //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      String brojBRE = "+381";
      for(int i = 1; i < brojTelefona.length(); i++){
        brojBRE = brojBRE + brojTelefona[i];
      }
      int duzinaNiza = brojBRE.length() +1;
      char brojTelefoncica [duzinaNiza];
      brojBRE.toCharArray(brojTelefoncica, duzinaNiza);      
      Sim800l.sendSms(brojTelefoncica ,char_array);
      //ZA SLANJE PORUKE PARCE KODA RADI SA SIM0l BIBLIOTEKOM
      }
      
       Sim800l.delAllSms();
    }
    digitalWrite(ledPin17, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(ledPin17, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  }
  

  
  //SIM800L **********************************************************************************
  
  
}



