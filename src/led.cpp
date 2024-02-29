#include <Arduino.h>
#include "led.h"

const int blue_led = 19;
const int red_led = 21;
const int green_led = 20;


void led_setup() {
  pinMode(blue_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
}

void blue_led_on() {
  digitalWrite(blue_led, HIGH);
}

void blue_led_off() {
  digitalWrite(blue_led, LOW);
}

void red_led_on() {
  digitalWrite(red_led, HIGH);
}

void red_led_off() {
  digitalWrite(red_led, LOW);
}

void green_led_on() {
  digitalWrite(green_led, HIGH);
}

void green_led_off() {
  digitalWrite(green_led, LOW);
}

void yellow_led_on() {
  reset_leds();
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, HIGH);
}

void yellow_led_off() {
  reset_leds();
}

void purple_led_on() {
  reset_leds();
  digitalWrite(blue_led, HIGH);
  digitalWrite(red_led, HIGH);
}

void purple_led_off() {
  reset_leds();
}

void cyan_led_on() {
  reset_leds();
  digitalWrite(blue_led, HIGH);
  digitalWrite(green_led, HIGH);
}

void cyan_led_off() {
  reset_leds();
}

void white_led_on() {
  reset_leds();
  digitalWrite(blue_led, HIGH);
  digitalWrite(red_led, HIGH);
  digitalWrite(green_led, HIGH);
}

void white_led_off() {
  reset_leds();
}


void reset_leds() {
  blue_led_off();
  red_led_off();
  green_led_off();
}