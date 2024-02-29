#ifndef BLE_H
#define BLE_H

void ble_setup();
void ble_loop();
bool dataAvailable();
String readData();
void send_data(const std::vector<int>& vec);
void send_data(String data);

#endif