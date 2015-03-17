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

inline void setMotorCommand(int num, int dir, int pwm) {
  if (dir == CW) digitalWrite(pinMotorDir[num], HIGH);
  else digitalWrite(pinMotorDir[num], LOW);
  analogWrite(pinMotorPWM[num], pwm);
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
  for (int i = 1; i < 3; i++) {
    setMotorCommand(i, motorDir[i], motorPWM[i]);
  }
  
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'a':
        motorPWM[1] += 10;
        break;
      case 's':
        motorPWM[1] = 0;
        break;
      case 'd':
        motorPWM[1] -= 10;
        break;
      case 'j':
        motorPWM[2] += 10;
        break;
      case 'k':
        motorPWM[2] = 0;
        break;
      case 'l':
        motorPWM[2] -= 10;
        break;
      default:
        ;
    }
  }

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

