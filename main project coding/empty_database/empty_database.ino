#include<SoftwareSerial.h>//communication library for communication b/w ardunio,sensor and system
#include<Adafruit_Fingerprint.h>//fingerprint library
SoftwareSerial serial(2,3);//pin for IN and OUT 
Adafruit_Fingerprint fpo= Adafruit_Fingerprint(&serial);//creating object to the adafruit_fingerprint
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);//serial baudrate
  Serial.println("deleting all the fingerprints");
  fpo.begin(57600);//fingerprint sensor baudrate
  if(fpo.verifyPassword())//checking password 
    Serial.println("modulo found");
  else
    Serial.println("not found ");
  Serial.println("enter D to delete the database");
  delay(3000);
  
}

void loop() 
{
  // put your main code here, to run repeatedly:
  fpo.getTemplateCount();
  Serial.print("Sensor contains "); 
  Serial.println(fpo.templateCount); 
  if(Serial.read()== 'D')
  {
    fpo.emptyDatabase();//deleting entire database
    Serial.println("done");
    delay(5000);
  }
}
