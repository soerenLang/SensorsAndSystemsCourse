#ifndef MAGNETOMETER_CLASS_H
#define MAGNETOMETER_CLASS_H
#include <Arduino.h>

class magnetometer_class{
  public:
  magnetometer_class();
  bool make_measurement();
  bool get_measurement();
  uint16_t get_measurement_raw();
  uint16_t get_limit();

  private:
  size_t pin {A0};
  uint16_t measurement_raw {0};
  bool measurement {true};
  uint16_t limit {740};
};
#endif