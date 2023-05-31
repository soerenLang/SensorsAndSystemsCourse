#include "USB/USBAPI.h"
#include "api/IPAddress.h"
#include "WiFi.h"
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "Arduino.h"
#include "udp_class.h"
#include <cstdlib>
#include <array>


udp_class::udp_class()
{
  this->transmission_message_struct.acc.x_id = 4;
  this->transmission_message_struct.acc.y_id = 5;
  this->transmission_message_struct.acc.z_id = 6;

  this->transmission_message_struct.vel.x_id = 7;
  this->transmission_message_struct.vel.y_id = 8;
  this->transmission_message_struct.vel.z_id = 9;

  this->transmission_message_struct.pos.x_id = 10;
  this->transmission_message_struct.pos.y_id = 11;
  this->transmission_message_struct.pos.z_id = 12;


  if (WiFi.status() == WL_NO_MODULE) 
  {

    Serial.println("Communication with WiFi module failed!");

    // don't continue

    while (true);

  }

  String fv = WiFi.firmwareVersion();

  if (fv < WIFI_FIRMWARE_LATEST_VERSION) 
  {

    Serial.println("Please upgrade the firmware");

  }

  // attempt to connect to Wifi network:

  while (WiFi.status() != WL_CONNECTED) 
  {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(this->ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:

    this->status = WiFi.begin(this->ssid, this->pass);

    // wait 10 seconds for connection:

    delay(10000);

  }
  
  Serial.println("Connected to wifi");
  this->Udp.begin(this->localPort);
};

void udp_class::printWifiStatus()const
{
     // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your board's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
};

void udp_class::transmit()
{
    IPAddress ip(***,***,***,***);

    std::array <char, 50> ReplyBuffer;
    
    size_t ReplyBuffer_index = 0;

    this->assignToTransmission(this->transmission_message_struct.acc.x_id,this->transmission_message_struct.acc.x, &ReplyBuffer[0], &ReplyBuffer_index);
    this->assignToTransmission(this->transmission_message_struct.acc.y_id,this->transmission_message_struct.acc.y, &ReplyBuffer[0], &ReplyBuffer_index);    
    this->assignToTransmission(this->transmission_message_struct.acc.z_id,this->transmission_message_struct.acc.z, &ReplyBuffer[0], &ReplyBuffer_index);

    this->assignToTransmission(this->transmission_message_struct.vel.x_id,this->transmission_message_struct.vel.x, &ReplyBuffer[0], &ReplyBuffer_index);
    this->assignToTransmission(this->transmission_message_struct.vel.y_id,this->transmission_message_struct.vel.y, &ReplyBuffer[0], &ReplyBuffer_index);    
    this->assignToTransmission(this->transmission_message_struct.vel.z_id,this->transmission_message_struct.vel.z, &ReplyBuffer[0], &ReplyBuffer_index);

    this->assignToTransmission(this->transmission_message_struct.pos.x_id,this->transmission_message_struct.pos.x, &ReplyBuffer[0], &ReplyBuffer_index);
    this->assignToTransmission(this->transmission_message_struct.pos.y_id,this->transmission_message_struct.pos.y, &ReplyBuffer[0], &ReplyBuffer_index);    
    this->assignToTransmission(this->transmission_message_struct.pos.z_id,this->transmission_message_struct.pos.z, &ReplyBuffer[0], &ReplyBuffer_index);
    
    this->assignToTransmission(this->transmission_message_struct.mag_out.id,this->transmission_message_struct.mag_out.val, &ReplyBuffer[0], &ReplyBuffer_index);

    this->Udp.beginPacket(ip, this->localPort);
    this->Udp.write(ReplyBuffer.data(), ReplyBuffer.size());

    this->Udp.endPacket();
};

void udp_class::assignToTransmission(uint8_t id, float value, char* the_array, size_t* index){
  uint8_t *temp_array;
  size_t index_start = (*index)*5;
  the_array[index_start] = id;
  temp_array = (uint8_t*)(&value);
  the_array[index_start + 1] = temp_array[0]; the_array[index_start + 2] = temp_array[1]; the_array[index_start + 3] = temp_array[2]; the_array[index_start + 4] = temp_array[3];
  (*index)++;
};

void udp_class::set_acc(float x, float y, float z)
{
  this->transmission_message_struct.acc.x = x;
  this->transmission_message_struct.acc.y = y;
  this->transmission_message_struct.acc.z = z;
};

void udp_class :: set_acc(xyz data){
  this->transmission_message_struct.acc = data;
}

void udp_class :: set_mag_out(uint16_t value){
  this->transmission_message_struct.mag_out.val = value;
};

void udp_class::set_vel(float x, float y, float z)
{
  this->transmission_message_struct.vel.x = x;
  this->transmission_message_struct.vel.y = y;
  this->transmission_message_struct.vel.z = z;
};

void udp_class::set_pos(float x, float y, float z)
{
  this->transmission_message_struct.pos.x = x;
  this->transmission_message_struct.pos.y = y;
  this->transmission_message_struct.pos.z = z;
};