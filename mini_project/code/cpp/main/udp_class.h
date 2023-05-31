#ifndef UDP_CLASS_H
#define UDP_CLASS_H

#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include "extra.h"
#include <array>

class udp_class{
  public:
  udp_class();

  void printWifiStatus() const;
  void set_udpPort(size_t port);

  void transmit();
  
  void set_acc(float x, float y, float z);
  void set_acc(xyz data);
  void set_vel(float x, float y, float z);
  void set_pos(float x, float y, float z);
  void set_mag_out(uint16_t value);

  private:
  char ssid[9]  = "Lang net";        // your network SSID (name)
  char pass[11]  = {"mfool89030"};    // your network password (use for WPA, or use as key for WEP)  
  int status = WL_IDLE_STATUS;

  struct{
    xyz acc;
    xyz vel;
    xyz pos;
    uint32_t time {0};

    struct{
      uint16_t val{0};
      size_t id{13};
    } mag_out;
  } transmission_message_struct;

  void assignToTransmission(uint8_t id, float value, char* the_array, size_t* index);

  WiFiUDP Udp;
  const unsigned int localPort {25000};  
  
};

#endif