//slave nano
#include <Wire.h>
#include<SoftwareSerial.h>
#include<Adafruit_Fingerprint.h>
int mm,temp=0;
int a[100];
char b[3];
String str;
SoftwareSerial serial=SoftwareSerial(3,4);
Adafruit_Fingerprint fpo=Adafruit_Fingerprint(&serial);
void setup() 
{
  Wire.begin(8);  
  Serial.begin(9600); // join i2c bus with address #8
  fpo.begin(57600);
  if(fpo.verifyPassword())
    serial.println("fingerprint found");
  else
    serial.println("not found");
  fpo.getTemplateCount();
  Serial.println("fingerprint count in database");
  Serial.println(fpo.templateCount);
  Wire.onRequest(requestEvent); // register event
  for(int i=1;i<=100;i++)
  {
    a[i]=0;
  }
}
void loop()
{
  delay(100);
  //Serial.println("hai this is slave");
  getFingerprintIDez();
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
  str=String(mm);
  str.toCharArray(b,3);
  Wire.write(b,3); // respond with message of 6 bytes
  // as expected by master
}
int getFingerprintIDez()
{
  uint8_t p = fpo.getImage();
  if (p != FINGERPRINT_OK) 
    return -1;
  p = fpo.image2Tz();
  if (p != FINGERPRINT_OK)    return -1;
  if(p != fpo.fingerFastSearch()) return -1;
  if (p != FINGERPRINT_OK)  return -1;
  temp=fpo.fingerID;
  if(a[temp]==0)
  {
    ++mm;
    a[temp]=1;
    Serial.print(mm);
    Serial.println("  success");
  }
}
