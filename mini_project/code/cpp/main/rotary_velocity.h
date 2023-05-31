#ifndef ROTARY_VELOCITY_H
#define ROTARY_VELOCITY_H

#include "Arduino.h"
#include "magnetometer_class.h"
#include "array"
#include <numeric>
#include <math.h>

class rotary_velocity{
  public:
  rotary_velocity(float fs);

  float make_velocity();
  float get_velocity();

  private:
  void update_ring_array(float value);

  struct{
    std::array <float, 10> storage;
    size_t index{0};
  } ring_array;
  
  float a;
  float fs;
  size_t num_mags {4};
  float wheel_diameter_m {0.025};
  float velocity {0};
  bool prev_mag {true};
  magnetometer_class mag;
};

#endif