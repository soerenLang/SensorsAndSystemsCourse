#include <WiFiNINA.h>
#include <WiFiUdp.h>

#include "udp_class.h"
#include "accelerometer_class.h"
#include "magnetometer_class.h"
#include "rotary_velocity.h"

void setup() {

  //Initialize serial and wait for port to open:

  Serial.begin(9600);

  while (!Serial) {

    ; // wait for serial port to connect. Needed for native USB port only

  }

  udp_class udp_transmitter;
  accelerometer_class acc;
  rotary_velocity velSens = rotary_velocity(10);
  udp_transmitter.printWifiStatus();


  while(true)
  {
    acc.make_measurement();
    velSens.make_velocity();

    //Serial.println(velSens.get_velocity());
    
    udp_transmitter.set_acc(acc.get_measurement());
    udp_transmitter.set_mag_out(mag.get_measurement());
    udp_transmitter.set_vel(velSens.get_velocity(), 0,0);

    udp_transmitter.transmit();
    delay(100);
  }
}

void loop() {


}

