#include <Arduino.h>
#include "SunFounder_TB6612_Motor_Driver.h"
#include "led.h"
#include "gyro.h"
#include "ultrasonic.h"
#include "encoder.h"
#include "switch.h"
#include "ble.h"
#include "old_motor.h"
#include <vector>

int left_speed = 191;
int right_speed = 192;
std::vector<int> arrayList;
int command_index = 0;
void rotate(int target_angle, float angle, float angular_velocity);

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  led_setup();
  switch_setup();
  ultrasonic_setup();
  gyro_setup();
  old_motor_setup();
  blue_led_on();
}

void setup1()
{
  encoder_setup();
  ble_setup();
}

void loop1()
{
  ble_loop();
  if (dataAvailable())
  {
    String data = readData();
    data.trim(); //IMP
    Serial.println(data);
    if (data.equals("stop"))
    {
      send_data("DONEDANADONE");
      set_switch_state(false);
      arrayList.clear();
      command_index = 0;
      stop();
    }
    else if (data.equals("start"))
    {
      command_index = 0;
      blue_led_on();
      set_switch_state(true);
    }
    else if (data.equals("del")){
      if (!arrayList.empty()) {
        arrayList.pop_back();
      }
    }
    else
    {
      int num = data.toInt();
      arrayList.push_back(num);
    }
    send_data(arrayList);
  }
}

void loop()
{
  if (get_switch_state())
  {
    if (gyro_ready())
    {
      float angle = get_angle(true);
      float angular_velocity = get_angular_velocity();

      if(command_index > (arrayList.size() - 1)){
        stop();

        return;
      }
      else{
        if(arrayList[command_index] == 0){
          angle = get_angle(false);
        }
        rotate(arrayList[command_index], angle, angular_velocity);
      }
    }
  }
}

void rotate(int target_angle, float angle, float angular_velocity)
{
  Serial.println(target_angle);
  int deltaAngle = round(target_angle - angle);
  int target_angular_velocity;

  if ((abs(deltaAngle) <= 1) && abs(angular_velocity) == 0) // IMPORTANT
  {
    stop();
    command_index++;
    left_speed = 191;
    right_speed = 192;
    delay(1000);
    return;
  }
  else
  {
    if (angle > target_angle)
    {
      left();
    }
    else
    {
      right();
    }
  }

  if (abs(deltaAngle) > 30)
  {
    target_angular_velocity = 35;
  }
  else
  {
    target_angular_velocity = 1.5 * abs(deltaAngle);
  }

  if (round(target_angular_velocity - abs(angular_velocity)) == 0)
  {
    ;
  }
  else if (target_angular_velocity - abs(angular_velocity) > 0)
  {
    left_speed++;
  }
  else
  {
    left_speed--;
  }
  left_speed = constrain(left_speed, 0, 210);
  right_speed = left_speed;
  enA_speed(left_speed);
  enB_speed(right_speed);
}
