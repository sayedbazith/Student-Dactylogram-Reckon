#include<SoftwareSerial.h>
#include<Adafruit_Fingerprint.h>
int mm=0;
SoftwareSerial serial=SoftwareSerial(5,6);
Adafruit_Fingerprint fpo=Adafruit_Fingerprint(&serial);
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  fpo.begin(57600);
   //gsm setup
 
  if(fpo.verifyPassword())
    serial.println("fingerprint found");
  else
    serial.println("not found");
  fpo.getTemplateCount();
  Serial.println("fingerprint count in database");
  Serial.println(fpo.templateCount);
 
  //fingerprint module verification
}

void loop() {
  // put your main code here, to run repeatedly:
  getFingerprintIDez();
  delay(50);
  
}
int getFingerprintIDez() {
  uint8_t p = fpo.getImage();
  if (p != FINGERPRINT_OK) 
    return -1;
  p = fpo.image2Tz();
  if (p != FINGERPRINT_OK) 
    return -1;
  if(p == fpo.fingerFastSearch())
  {
    ++mm;
    Serial.print(mm);
    Serial.println("  success");
  }
  if (p != FINGERPRINT_OK)  
    return -1;
  // found a match!
}
