#include <Arduino.h>

const int switch_pin = 16;
volatile bool switch_state = false;


void switch_interrupt() {
  switch_state = !switch_state;
}

bool get_switch_state() {
  return switch_state;
}

void set_switch_state(bool state) {
  switch_state = state;
}

void switch_setup() {
  pinMode(switch_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(switch_pin), switch_interrupt, RISING);
  set_switch_state(false);
}


