#include <Arduino.h>

const int enA = 6; // right
const int in1 = 7;
const int in2 = 8;
const int enB = 11; // left
const int in4 = 10;
const int in3 = 9;



void old_motor_setup(){
  pinMode(enA, OUTPUT); // left
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT); // right
  pinMode(in4, OUTPUT);
  pinMode(in3, OUTPUT);
}

void right()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void left()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void straight()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backward(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

void enA_speed(int speed){
  analogWrite(enA, speed);
}

void enB_speed(int speed){
  analogWrite(enB, speed);
}

void stop()
{
  enA_speed(0);
  enB_speed(0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
