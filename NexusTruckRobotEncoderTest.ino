// Nexus Truck Robot
//
// Gear ratio: 64:1
// Resolution of encoder: 12CPR
//
// Pin 4, 5: encoder for motor 1
// Pin 6, 7: encoder for motor 2

#include <PinChangeInt.h>

const int CW = 0;
const int CCW = 1;

const int pinMotorPWM[3] = {100, 3, 11};
const int pinMotorDir[3] = {100, 2, 12};

const int pinEncoder1A = 4;
const int pinEncoder1B = 5;
const int pinEncoder2A = 6;
const int pinEncoder2B = 7;

int encCounter[3] = {0, 0, 0};

int motorDir[3] = {CW, CW, CW};
int motorPWM[3] = {0, 0, 0}; 

void setMotorCommand(int num, int dir, int pwm) {
}

void setup() {
  // change PWM freq
  TCCR1B=TCCR1B&0xf8|0x01;  // Pin9,Pin10 PWM 31250Hz
  TCCR2B=TCCR2B&0xf8|0x01;  // Pin3,Pin11 PWM 31250Hz
  
  for (int i = 1; i < 3; i++) {
    pinMode(pinMotorPWM[i], OUTPUT);
    pinMode(pinMotorDir[i], OUTPUT);
  }

  pinMode(pinEncoder1A, INPUT);
  pinMode(pinEncoder1B, INPUT);
  PCintPort::attachPinChangeInterrupt(pinEncoder1A, riseEnc1A, RISING);
  PCintPort::attachPinChangeInterrupt(pinEncoder2A, riseEnc2A, RISING);
  
  Serial.begin(115200);
}

void loop() {
  // motor1
  digitalWrite(pinMotorDir[1], HIGH);
  analogWrite(pinMotorPWM[1], 200);

  // motor2
  digitalWrite(pinMotorDir[2], HIGH);
  analogWrite(pinMotorPWM[2], 200);

  Serial.print(encCounter[1]);
  Serial.print(", ");
  Serial.println(encCounter[2]);
  
  encCounter[1] = encCounter[2] = 0;
  
  delay(1000);
}

void riseEnc1A() {
  if (digitalRead(pinEncoder1B) == HIGH) encCounter[1]++;
  else encCounter[1]--;
}

void riseEnc2A() {
  if (digitalRead(pinEncoder2B) == HIGH) encCounter[2]++;
  else encCounter[2]--;
}

