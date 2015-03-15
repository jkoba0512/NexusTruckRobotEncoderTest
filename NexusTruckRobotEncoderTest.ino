// Nexus Truck Robot
// Pin 4, 5: encoder for motor 1
// Pin 6, 7: encoder for motor 2

#include <PinChangeInt.h>
const int pinMotor1PWM = 3;
const int pinMotor1Dir = 2;
const int pinMotor2PWM = 11;
const int pinMotor2Dir = 12;

const int pinEncoder1A = 4;
const int pinEncoder1B = 5;
const int pinEncoder2A = 6;
const int pinEncoder2B = 7;

uint32_t counterEnc1 = 0;
uint32_t counterEnc2 = 0;

void setup() {
  // change PWM freq
  TCCR1B=TCCR1B&0xf8|0x01;  // Pin9,Pin10 PWM 31250Hz
  TCCR2B=TCCR2B&0xf8|0x01;  // Pin3,Pin11 PWM 31250Hz
  
  pinMode(pinMotor1PWM, OUTPUT);
  pinMode(pinMotor1Dir, OUTPUT);
  pinMode(pinMotor2PWM, OUTPUT);
  pinMode(pinMotor2Dir, OUTPUT);

  pinMode(pinEncoder1A, INPUT);
  pinMode(pinEncoder1B, INPUT);
  PCintPort::attachPinChangeInterrupt(pinEncoder1A, riseEnc1A, RISING);
  PCintPort::attachPinChangeInterrupt(pinEncoder2A, riseEnc2A, RISING);
  
  Serial.begin(115200);
}

void loop() {
  // motor1
  digitalWrite(pinMotor1Dir, HIGH);
  analogWrite(pinMotor1PWM, 200);

  // motor2
  digitalWrite(pinMotor2Dir, HIGH);
  analogWrite(pinMotor2PWM, 200);

  Serial.println(counterEnc1);
  
  counterEnc1 = 0;
  
  delay(1000);
}

void riseEnc1A() {
  if (digitalRead(pinEncoder1B) == HIGH) {
    counterEnc1++;
  }
  else {
    counterEnc1--;
  }
}

void riseEnc2A() {
  if (digitalRead(pinEncoder2B) == HIGH) {
    counterEnc2++;
  }
  else {
    counterEnc2--;
  }
}

