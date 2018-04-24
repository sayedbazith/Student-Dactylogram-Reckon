//master uno
#include <Wire.h>
#include <UbidotsArduinoGPRS.h>
#include <SoftwareSerial.h> 
#define APN "internet" // Assign the APN 
#define USER "Put_the_APN_user_herer"  // If your apn doesnt have username just put ""
#define PASS "Put_the_APN_pwd_here"  // If your apn doesnt have password just put ""
#define TOKEN "A1E-p1KwUMldK0SkoVAJx45kOCoDPa16Qq"  // Replace it with your Ubidots token
#define VARIABLE_LABEL "5a9f89677625422a53ddbbb8" // Assign the variable label 
Ubidots client(TOKEN);
SoftwareSerial gprs= SoftwareSerial(3,2);
SoftwareSerial *GPRSSerial = &gprs;

void setup() 
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  GPRSSerial->begin(9600);
  if (! client.init(*GPRSSerial)) 
  {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  } 
  client.setApn(APN,USER,PASS);
}
void loop() 
{
  String phrase;
  int value=0;
  Wire.requestFrom(8, 3);    // request 6 byZZtes from slave device #8
  while (Wire.available()) 
  { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    phrase=String(phrase+c);
  }
  value=phrase.toInt();
  delay(500);
  client.add(VARIABLE_LABEL, value);  
  client.sendAll();
}
