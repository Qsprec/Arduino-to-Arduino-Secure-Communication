//**
//At this code this device will be master sender.
//This arduino device will write encrypted data and sends to the wire.
//There is a master slave communication between two devices.
//For encryption and decryption AES-128 has been used.
//Created by Qsprec & El2fun
//***

#include <Wire.h>
#include <AESLib.h>

char data[16]; //16 chars == 16 bytes This AES library takes 16 byte data.
uint8_t key[] = {0,12,2,6,1,8,4,7,11,15,5,3,13,12,10,14};//16 bit key
String str;
boolean bl=false;
int strLength, sCount;
double blockCount;

void setup()
{
  Serial.begin(9600);
  Wire.begin(); 
}
void loop()
{
  if(Serial.available() > 0)
    {
        str = Serial.readStringUntil('\n'); //Read all characters at serial monitor.
         delay(1000);

  strLength=str.length();
  blockCount=strLength/16;
  
  if(strLength%16!=0)
    {
      blockCount++;
    }
  
int blockSize=blockCount;
 Serial.println("String: "+str);
 Serial.println(blockSize);
 //After finding the block size for this input
 //We created 2 array. 1 for encryption and the other for encrypted data.
String cipher[blockSize];
String block[blockSize];
sCount=0;
//Fill in the array for encryption
for(int i=0; i<blockSize; i++)
{
  block[i]=str.substring(sCount,sCount+16);  
  sCount= sCount + 16;
}

for(int i=0; i<blockSize; i++)
{
 block[i].toCharArray(data,17);
  Serial.println(block[i]);
 aes128_enc_single(key, data);//Encrypt each elements of array.
 delay(300);
 cipher[i]=data;//Create an encrypted array.
}
//Begin transmission to send data over wire.
Wire.beginTransmission(4);
for(int j=0; j<blockSize; j++)
{
cipher[j].toCharArray(data,17);
Serial.println(j);
Serial.println(data);
//for each element of the cipher array we begin and end the transmission of wire.
if(j%2==0 && j!=0)
{
  Wire.endTransmission();
  Wire.beginTransmission(4);
}
 Wire.write(data);//This will write 16 byte data to the wire. but don't forget wire has max 64 byte capacity! 
}
 Wire.endTransmission();
}
}
