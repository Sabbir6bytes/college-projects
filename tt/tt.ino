#include <SPI.h>  
#include <nRF24L01.h>
#include <RF24.h>

#define  CE_PIN 9
#define  CSN_PIN 8

const byte Address[5] = {'N','e','s','s','y'};

RF24 radio(CE_PIN,CSN_PIN);
String username = "";
String dataInput;
char dataToSend[32];
char dataReceived[32];

void setup(){



  Serial.begin(9600);
  Serial.println("Enter userrname :-");


  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(3,5);
  radio.openWritingPipe(Address);
  radio.openReadingPipe(1,Address);
}

void loop(){
  
  while(username ==""){
    if (Serial.available()){
    username = Serial.readStringUntil('\n');
    Serial.print("welcome! ");
    Serial.print(username);
}  
 } 
 radio.startListening();
 if( radio.available()){
  radio.read(&dataReceived,sizeof(dataReceived));
  Serial.print(dataReceived);
 }
 if(Serial.available()){

  radio.stopListening();
  dataInput = "["+username + "]" + Serial.readStringUntil('\n');
  Serial.println(dataInput);
  dataInput.toCharArray(dataToSend,32);
   radio.write(&dataToSend, sizeof(dataToSend));
  }
  }
