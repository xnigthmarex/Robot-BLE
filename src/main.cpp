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
unsigned long start_time;
const unsigned long target_time = 10 * 1000;
bool volatile state_back_and_forth = false;
void rotate(int target_angle, float angle, float angular_velocity);
void travel(float angle, float angular_velocity, int target_count, int right_count);
void travel_with_ultrasonic(float angle, float angular_velocity, int target_distance, int current_distance);
int target_angle = 0;
const int PRE_STOP_DIS = 26;//12cm + 9cm

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
    data.trim(); // IMP
    Serial.println(data);
    if (data.equals("s"))
    {
      send_data("DONEDANADONE");
      set_switch_state(false);
      blue_led_off();
      arrayList.clear();
      command_index = 0;
      stop();
    }
    else if (data.equals("start"))
    {
      command_index = 0;
      blue_led_on();
      start_time = millis();
      set_switch_state(true);
    }
    else if (data.equals("del"))
    {
      if (!arrayList.empty())
      {
        arrayList.pop_back();
      }
    }
    else
    {
      int int_data = data.toInt();
      if (int_data % 90 == 0)
      {

        arrayList.push_back(int_data);
      }
      else if(int_data >= 1000){
        arrayList.push_back(int_data);
      }
      else
      {
        arrayList.push_back(get_target_count(int_data));
      }
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

      if (command_index > (arrayList.size() - 1))
      {
        stop();
        unsigned long stop_time = millis();
        send_data(String(stop_time - start_time));
        if((state_back_and_forth == false) && (stop_time - start_time > target_time)){
            send_data("TIMEOUT");
            set_switch_state(false);
        }else{
          if(state_back_and_forth){
            backward();
            enA_speed(80);
            enB_speed(80);
            delay(100);
            stop();
            delay(700);
            state_back_and_forth = false;
          }else{
            straight();
            enA_speed(80);
            enB_speed(80);
            delay(100);
            stop();
            delay(700);
            state_back_and_forth = true;
          }
        }
        return;
      }
      else
      {
        
        if (target_angle == 0 || arrayList[command_index] == 0)
        {
          angle = get_angle(false);
        }
        if (arrayList[command_index] % 90 == 0)
        {
          target_angle = arrayList[command_index];
          rotate(arrayList[command_index], angle, angular_velocity);
        }

        else if(arrayList[command_index] >= 1000){
          int target_distance = arrayList[command_index] - 1000;
          if(target_distance == 0){
            target_distance = PRE_STOP_DIS;
          }else{
            target_distance = target_distance + PRE_STOP_DIS;
          }
          Serial.println(target_distance);

          travel_with_ultrasonic(angle, angular_velocity, target_distance,get_distance());
        }
        else{
            travel(angle, angular_velocity, arrayList[command_index], get_rightcount());
        }
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
    right_speed = 192; //add delay(500);
    delay(200);
    reset_encoder();
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
    target_angular_velocity = 30;
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
  enA_speed(left_speed-60);
  enB_speed(right_speed-60);
  delay(10);
}

void travel(float angle, float angular_velocity, int target_count, int right_count)
{
  straight();

  if (target_count <= right_count)
  {
    stop();
    command_index++;
    left_speed = 191;
    right_speed = 192;
    delay(500);
    reset_encoder();
    return;
  }
  else
  {
    int delta_angle = round(target_angle - angle);
    int target_angular_velocity;

    if (delta_angle > 30)
    {
      target_angular_velocity = 60;
    }
    else if (delta_angle < -30)
    {
      target_angular_velocity = -60;
    }
    else
    {
      target_angular_velocity = 3 * delta_angle;
    }
    angular_velocity = -1 * angular_velocity; // gyro data and accelerometer data are opposite
    if (round(target_angular_velocity - angular_velocity) == 0)
    {
      ;
    }
    else if (target_angular_velocity > angular_velocity)
    {
      left_speed++;
    }
    else
    {
      left_speed--;
    }

    left_speed = constrain(left_speed, 0, 210);
    right_speed = 192;
    enA_speed(left_speed);
    enB_speed(right_speed);
    delay(10);
  }
}

void travel_with_ultrasonic(float angle, float angular_velocity, int target_distance, int current_distance)
{
  straight();
  if (target_distance > current_distance)
  {
    stop();
    command_index++;
    left_speed = 191;
    right_speed = 192;
    delay(500);
    reset_encoder();
    return;
  }
  else
  {
    int delta_angle = round(target_angle - angle);
    int target_angular_velocity;

    if (delta_angle > 30)
    {
      target_angular_velocity = 60;
    }
    else if (delta_angle < -30)
    {
      target_angular_velocity = -60;
    }
    else
    {
      target_angular_velocity = 2 * delta_angle;
    }
    angular_velocity = -1 * angular_velocity; // gyro data and accelerometer data are opposite
    if (round(target_angular_velocity - angular_velocity) == 0)
    {
      ;
    }
    else if (target_angular_velocity > angular_velocity)
    {
      left_speed++;
    }
    else
    {
      left_speed--;
    }

    left_speed = constrain(left_speed, 0, 203);
    right_speed = 192;
    enA_speed(left_speed);
    enB_speed(right_speed);
    delay(10);
  }
}