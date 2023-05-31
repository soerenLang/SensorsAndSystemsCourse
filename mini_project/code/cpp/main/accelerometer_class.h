#ifndef ACCELEROMETER_CLASS_H
#define ACCELEROMETER_CLASS_H

#include <Arduino.h>
#include "extra.h"
#include "LSM6DS3.h"

class accelerometer_class{
  public:
    accelerometer_class();

    void make_measurement();

    xyz get_measurement();

    void print_measurement() const;

  private:
    xyz measurement;
};

#endif