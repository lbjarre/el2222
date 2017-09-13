#include<Time.h>

int ledPin = 9;
float pi = 3.14;
float f = 1;
float t;
float val;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  f = f / 1000;
}

void loop() {
  t = millis();
  val = (sin(2.0*pi*f*t) + 1) * 127;
  analogWrite(ledPin, val);
  Serial.println(val);
}