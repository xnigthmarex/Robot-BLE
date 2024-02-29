#include <Arduino.h>
#include "SoftwareSerial.h"
#include <vector>

SoftwareSerial hc05(1,0); // RX, TX

void ble_setup() {
  hc05.begin(115200);
  delay(1000);
  Serial.println("HC-05 is ready");
}

void ble_loop() {
  if (Serial.available()) {
    char data = Serial.read();
    hc05.print(data);
    Serial.print("Sent via Serial: ");
    Serial.println(data);
  }
}

bool dataAvailable() {
  return hc05.available();
}

String readData() {
  String receivedData = "";
  while (hc05.available()) {
    char data = hc05.read();
    receivedData += data;
    delay(1);
  }
  return receivedData;
}

//get the vector list and send it to the bluetooth module recieve a vector list and add commas and sent it to the robot
void send_data(const std::vector<int>& vec){
    String data = "";
    for (int i = 0; i < vec.size(); i++){
        data += vec[i];
        if (i != vec.size() - 1){
        data += ",";
        }
    }
    hc05.println(data);
    
}

void send_data(String data){
    hc05.println(data);
}