// Nexus Truck Robot
// Pin 4, 5: encoder for motor 1
// Pin 6, 7: encoder for motor 2

#include <PinChangeInt.h>

const int pinEncoder1A = 4;
const int pinEncoder1B = 5;
const int pinEncoder2A = 6;
const int pinEncoder2B = 7;

uint32_t counterEnc1 = 0;
uint32_t counterEnc2 = 0;

void setup() {
//  pinMode(pinEncoder1A, INPUT_PULLUP);
  pinMode(pinEncoder1A, INPUT);
  pinMode(pinEncoder1B, INPUT);
  PCintPort::attachPinChangeInterrupt(pinEncoder1A, riseEnc1A, RISING);
  Serial.begin(115200);
}

void loop() {
}

void riseEnc1A() {
  if (digitalRead(pinEncoder1A) == HIGH) {
  }
  else {
  }
}

