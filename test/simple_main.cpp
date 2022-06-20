#include <Arduino.h>

#define DIR 11
#define STEP 12

void setup() {
  // put your setup code here, to run once:
  pinMode(DIR, OUTPUT);
  pinMode(STEP, OUTPUT);
  digitalWrite(DIR, HIGH);
}

void loop() {
  delayMicroseconds(1);
  digitalWrite(STEP, HIGH);
  delayMicroseconds(1);
  digitalWrite(STEP, LOW);
  // put your main code here, to run repeatedly:
}