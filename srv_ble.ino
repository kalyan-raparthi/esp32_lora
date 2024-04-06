#include <SPI.h>
#include <LoRa.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define PIN_LORA_COPI   23
#define PIN_LORA_CIPO   19
#define PIN_LORA_SCK    18
#define PIN_LORA_CS     5
#define PIN_LORA_RST    2
#define PIN_LORA_DIO0   4
#define LORA_FREQUENCY  433E6

char state = 'a';

void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1500);
  Serial.println ("transmitter");
  
  SerialBT.begin("transmitter"); 
  Serial.println("pair it with bluetooth");

  LoRa.setPins (PIN_LORA_CS, PIN_LORA_RST, PIN_LORA_DIO0);
  LoRa.setSPIFrequency (20000000);
  LoRa.setTxPower (20);

  if (!LoRa.begin (LORA_FREQUENCY)) {
    Serial.println ("error while starting");
    while (1);
  }
  else {
    Serial.print ("LoRa initialized with frequency ");
    Serial.println (LORA_FREQUENCY);
  }
}

void loop() {
  char receivedChar =(char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  
  }
  if (SerialBT.available()) {
    
    SerialBT.print("Received:");
    SerialBT.println(receivedChar);
    Serial.print ("Received:");
    Serial.println(receivedChar);

    if(receivedChar == 'a')
    {
      state = 'a';       
    }
    if(receivedChar == 'b')
    {
      state = 'b';
    }    
     
  }

  Serial.print ("state: ");
  Serial.println (state);

  LoRa.beginPacket();
  LoRa.print (state);
  LoRa.endPacket();

  delay (1000);
}