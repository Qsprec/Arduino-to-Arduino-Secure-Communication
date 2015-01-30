//**
//At this code this device will be slave receiver.
//This arduino device will read encrypted data from wire and create the original message with decrypting received data.
//There is a master slave communication between two devices.
//For encryption and decryption AES-128 has been used.
//Created by Qsprec & El2fun
//***


#include <Wire.h>
#include <AESLib.h>

uint8_t key[] = {0,12,2,6,1,8,4,7,11,15,5,3,13,12,10,14};//16 byte key.
char data[]={};
char temp[]={};
String str="";
String str2="";
double blockCount;
int blockSize,num=0;
boolean flag=true;


  void setup()
  {
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
  }

  void loop()
  {
  if(str!=""){
  decryption();

 str="";
}

  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  while(Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
  //  Serial.print(c);
   
  str=str+c;
  
  }

}

void decryption()
{
  int strLength=str.length();
    blockCount=strLength/16;
  if(strLength%16!=0)
    {
      blockCount++;
    }
  
   blockSize=blockCount;
 num=blockSize;
String encrypted[blockSize];
String decrypted[blockSize];

int sCount=0;

     for(int i=0; i<blockSize; i++)
  {
    encrypted[i]=str.substring(sCount,sCount+16);  
     sCount=sCount+16;
 
  }
char finalData[strLength];

for(int i=0;i<num;i++){
Serial.print(encrypted[i]);
}
Serial.println();
for(int t=0;t< num;t++){
encrypted[t].toCharArray(temp,17);
aes128_dec_single(key, temp);
Serial.print(temp);
   delay(400);  
  memset(temp,0,sizeof(temp));
}
}
