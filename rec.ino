#include <SPI.h>
#include <LoRa.h>

#define PIN_LORA_COPI   23
#define PIN_LORA_CIPO   19
#define PIN_LORA_SCK    18
#define PIN_LORA_CS     5
#define PIN_LORA_RST    2
#define PIN_LORA_DIO0   4

#define LORA_FREQUENCY  433E6

void setup() {
  pinMode(16, OUTPUT);
  Serial.begin (115200);
  while (!Serial);
  delay (1500);
  Serial.println ("LoRa Receiver");

  LoRa.setPins (PIN_LORA_CS, PIN_LORA_RST, PIN_LORA_DIO0);
  LoRa.setSPIFrequency (20000000);

  if (!LoRa.begin (LORA_FREQUENCY)) {
    Serial.println ("Starting LoRa failed!");
    while (1);
  }
  else {
    Serial.print ("LoRa initialized with frequency ");
    Serial.println (LORA_FREQUENCY);
  }
}

void loop() {
  String a = "a";
  String result;
  bool x;
  int packetSize = LoRa.parsePacket();
  
  if (packetSize) {
    while (LoRa.available()) {
      result += (char)LoRa.read();
      if (a.equals(result)) {
       Serial.println("onn");
       digitalWrite(16, HIGH);
      } else {
         Serial.println("off");
         digitalWrite(16, LOW);
      }
    }
  }
}
