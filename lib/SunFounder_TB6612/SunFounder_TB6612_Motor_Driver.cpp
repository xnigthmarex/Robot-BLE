/*
  SunFounder_TB6612_Motor_Driver.cpp - Library for SunFounder TB6612 Motor Driver.
  Created by Dream. SunFounder, 2016-12-17.
  Released into the public domain.
*/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "SunFounder_TB6612_Motor_Driver.h"

TB6612::TB6612(int direct_pin, int pwm_pin)
{
	pinMode(direct_pin, OUTPUT);
	pinMode(pwm_pin, OUTPUT);
	_dirctPin = direct_pin;
	_pwmPin = pwm_pin;
	_direct = 1;
}

void TB6612::forward(int pwm_value)
{
	digitalWrite(_dirctPin, _direct);
	analogWrite(_pwmPin, pwm_value);
}

void TB6612::backward(int pwm_value)
{	
	digitalWrite(_dirctPin, !_direct);
	analogWrite(_pwmPin, pwm_value);
}

void TB6612::stop()
{
	analogWrite(_pwmPin, 0);
}

void TB6612::reverseDirec()
{
	_direct = !_direct;
}