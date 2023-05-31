#include "magnetometer_class.h"

magnetometer_class :: magnetometer_class(){

};


bool magnetometer_class :: make_measurement(){
  int measurement = analogRead(this->pin);
  this->measurement_raw = measurement;
  
  if(measurement < this->limit){
    this->measurement = false;
    return false;
  }
  this->measurement = true;
  return true;
};

bool magnetometer_class :: get_measurement(){
  return this->measurement;
};

uint16_t magnetometer_class :: get_measurement_raw(){
  return this->measurement_raw;
};
uint16_t magnetometer_class :: get_limit(){
  return this->limit;
};