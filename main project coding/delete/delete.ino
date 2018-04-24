#include<SoftwareSerial.h> //communication between ardunio and system
#include <Adafruit_Fingerprint.h> //fingerprint library
SoftwareSerial serial(2,3); //2 pin is for IN and 3 pin is for OUT
Adafruit_Fingerprint fop = Adafruit_Fingerprint(&serial); //creating fingerprint object
uint8_t id = 0,p1=0; // user input variable
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600); //baudrate of communicataion
  Serial.println("for fingerprint delete");
  fop.begin(57600); //fingerprint baudrate 
  if(fop.verifyPassword()) //check for the password
    Serial.println("found modulo");
  else
    Serial.println("not found device");
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("Ready to delete");
  Serial.println("enter a number from 1 to 127");
  p1=id;
  id=temp(); //getting input from user for id
  if ((id<=0) && (id>=128)) //input id checking 
  {
    Serial.println("enter valid id");
    return ;
  }
  Serial.print("Deleting ID #");
  Serial.println(id);
  delfing(id); //deleting fingerprint function with given inout id
}
//user input function
uint8_t temp(void)
{
  uint8_t temp1 = 0;
  while ((temp1 == 0) &&(!Serial.available())) 
    temp1 = Serial.parseInt();
  return temp1;
}
//deleting the fingerprint function
uint8_t delfing(uint8_t id)
{
  uint8_t p =-1;
  p = fop.deleteModel(id); //calling deleting function with geive id
 
  if (p ==FINGERPRINT_OK) //if deletion successfull then fingerprint ok returns
    Serial.println("Deleted!");
  else if (p ==FINGERPRINT_PACKETRECIEVEERR) //error in the packet delivery 
  {
    Serial.println("Communication error");
    return p;
  }
  else if (p ==FINGERPRINT_BADLOCATION) // storage error
  {
    Serial.println("Cannot delete");
    return p;
  } 
  else if (p ==FINGERPRINT_FLASHERR) //data contains garbage values
  {
    Serial.println("Error writing");
    return p;
  }
  else
  {
    Serial.print("Unknown error"); 
    return p;
  }
  if(id == p1)
    Serial.println("Fingerprint Already Deleted!");  
}
