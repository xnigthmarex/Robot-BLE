
#ifndef _TB6612_H_
#define _TB6612_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class TB6612
{
public:
	TB6612(int direct_pin, int pwm_pin);
	void forward(int speed);
	void backward(int speed);
	void reverseDirec();
	void stop();
private:
	int _dirctPin;
	int _pwmPin;
	bool _direct;
};
#endif