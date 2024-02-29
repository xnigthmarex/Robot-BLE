/*************************************************** 
  This is an example for our Sunfounder TB6612 Motor driver
  speed and direction test - this will drive 2 motors, speed increase and then decrese

 ****************************************************/

#include <SunFounder_TB6612_Motor_Driver.h>

TB6612 motorA (5,6);
TB6612 motorB(9,10);

void setup() {
  Serial.begin(9600);
  Serial.println("TB6612 Motor test!");
}

void loop() {
  for(int pwm_value=0; pwm_value<256; pwm_value++){
      motorA.forward(pwm_value);
      motorB.forward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  Serial.println();
  for(int pwm_value=255; pwm_value>0; pwm_value--){
      motorA.forward(pwm_value);
      motorB.forward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  for(int pwm_value=0; pwm_value<256; pwm_value++){
      motorA.backward(pwm_value);
      motorB.backward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  Serial.println();
  for(int pwm_value=255; pwm_value>0; pwm_value--){
      motorA.backward(pwm_value);
      motorB.backward(pwm_value);
      Serial.print("pwm_value:");Serial.println(pwm_value);
      delay(50);
  }
  Serial.println();
  motorA.reverseDirec();
  motorB.reverseDirec();
}
