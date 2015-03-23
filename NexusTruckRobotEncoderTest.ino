// Nexus Truck Robot
//
// Gear ratio: 64:1
// Resolution of encoder: 12CPR
//
// Pin 4, 5: encoder for motor 1
// Pin 6, 7: encoder for motor 2

#include <PinChangeInt.h>

const int pinMotorPWM[3] = {100, 3, 11};
const int pinMotorDir[3] = {100, 2, 12};

const int pinEncoder1A = 4;
const int pinEncoder1B = 5;
const int pinEncoder2A = 6;
const int pinEncoder2B = 7;

int encCounter[3] = {0, 0, 0};

int motorCommand[3] = {0, 0, 0};  // CCW if it's negative

const int Ts = 100000;  // sampling period in usec
long int startTime, endTime;

inline void setMotorCommand(int num, int com) {
  if (com < 0) digitalWrite(pinMotorDir[num], LOW);
  else digitalWrite(pinMotorDir[num], HIGH);
  analogWrite(pinMotorPWM[num], abs(com));
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
  startTime = micros();
  
  for (int i = 1; i < 3; i++) {
    setMotorCommand(i, motorCommand[i]);
  }
  
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'a':
        motorCommand[1] += 30;
        break;
      case 's':
        motorCommand[1] = 0;
        break;
      case 'd':
        motorCommand[1] -= 30;
        break;
      case 'j':
        motorCommand[2] += 30;
        break;
      case 'k':
        motorCommand[2] = 0;
        break;
      case 'l':
        motorCommand[2] -= 30;
        break;
      default:
        ;
    }
  }

  Serial.print(encCounter[1]);
  Serial.print(", ");
  Serial.print(encCounter[2]);
  Serial.print(", ");
  Serial.print(motorCommand[1]);
  Serial.print(", ");
  Serial.println(motorCommand[2]);
  
  encCounter[1] = encCounter[2] = 0;
  
  endTime = micros();
  delayMicroseconds(max(0, startTime+Ts-endTime));
}

void riseEnc1A() {
  if (digitalRead(pinEncoder1B) == HIGH) encCounter[1]++;
  else encCounter[1]--;
}

void riseEnc2A() {
  if (digitalRead(pinEncoder2B) == HIGH) encCounter[2]++;
  else encCounter[2]--;
}

