#include  <Arduino.h>

//encoder variables
const int encoderleft = 15; // connect A0 to GPIO15
const int encoderright = 14; // connect A1 to GPIO14
volatile int leftcount = 0;
volatile int rightcount = 0;
const float encoder_resolution = 21.0;
const float wheel_diameter = 6.9;
const float wheel_circumference = 3.14159 * wheel_diameter;

void leftcount_increment()
{
  leftcount++;
}

void rightcount_increment()
{
  rightcount++;
}


void encoder_setup()
{
//pinMode(encoderleft, INPUT_PULLUP);
  pinMode(encoderright, INPUT_PULLUP);
//attachInterrupt(digitalPinToInterrupt(encoderleft), leftcount_increment, RISING);
  attachInterrupt(digitalPinToInterrupt(encoderright), rightcount_increment, RISING);
}


int get_leftcount()
{
  return leftcount; 
}

int get_rightcount()
{
  return rightcount;
}

int get_target_count(int distance)
{
  return ((float)distance / wheel_circumference) * encoder_resolution;
}

void reset_encoder()
{
  leftcount = 0;
  rightcount = 0;
}
