#include "Arduino.h"
#include "accelerometer_class.h"


accelerometer_class :: accelerometer_class(){
  IMU.begin();

  this->measurement.x_id = 4;
  this->measurement.y_id = 5;
  this->measurement.z_id = 6;

};

void accelerometer_class :: make_measurement(){
  float temp_x, temp_y, temp_z;

  IMU.readAcceleration(temp_x, temp_y, temp_z);

  float g = 9.82; //gravitational acceleration
  this->measurement.x = temp_x*g;
  this->measurement.y = temp_y*g;
  this->measurement.z = temp_z*g;
};

xyz accelerometer_class :: get_measurement(){
  return this->measurement;
};

void accelerometer_class :: print_measurement() const{
  print_xyz(this->measurement);
};