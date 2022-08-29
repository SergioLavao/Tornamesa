#include <BPLib.h>

#include <SoftwareSerial.h>

#define RX_PIN 6 // connect to TXD of module
#define TX_PIN 5 // connect to RXD of module (logic level 3.3v!)

int buttonCoolDownDue = 0;

SoftwareSerial swSer(RX_PIN, TX_PIN);

//BPLib BPMod; 

byte get( char BP_STAT[],byte strlen )
{
    char buffer[strlen + 1];
    Serial.write(0x30);
    //while (swSer.available() <= (strlen-1)) {};
    Serial.write(0x31);
    int count = 0;
    while (swSer.available() > 0) {
      buffer[count]=(char)swSer.read();
      count++;
    }//while
    Serial.write(0x32);
    buffer[strlen]=0;
    //Serial.print(buffer);//DEBUG
    if (strcmp(buffer,BP_STAT)==0) {
      return (byte)1;
    }//if
    else {
      return (byte)0;
    }//else

}

int initBT( char BP_Mode[], char BP_Type[] )
{
  swSer.begin(115200);
  swSer.print(BP_MODE_COMMAND);
    if (get(BP_STAT_CMD, (byte)5)!=1) {
      return (byte)0;
    }//if
    
    swSer.print(BP_Mode);
    if (get(BP_STAT_ACK, (byte)5)!=1) {
      return (byte)0;
    }//if
    if(strcmp(BP_Type,BP_SPP_SPP)>0){
    swSer.print(BP_Type);
    if (get(BP_STAT_ACK, (byte)5)!=1) {
      return (byte)0;
    }//if
    }
    swSer.print(BP_REBOOT);
    if (get(BP_STAT_REBOOT, (byte)9)!=1) {
      return (byte)0;
    }//if
    delay(1000); //Delay (Bluetooth boot-up)
  
  return (byte)1;

}

void setup() {
    Serial.begin(115200);
  
    //BPLib BPMod = new BPLib(swSer);

    initBT(BP_MODE_HID,BP_HID_KEYBOARD);
    
    //BPMod.begin(BP_MODE_HID,BP_HID_KEYBOARD);   //Begin HID Mode with HID KEYBOARD AS TYPE
  
}

void loop() 
{
    BPMod->volumeUp();
    delay(100);
    BPMod->keyRelease();
    Serial.write(0x32);
    delay(1000);
    
}
