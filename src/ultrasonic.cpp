#include  <Arduino.h>

const int TRIG = 12;
const int ECHO = 13;
long duration;
float distance;


void ultrasonic_setup()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  distance = 0;
}

int get_distance()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
  return (int)distance;
}
