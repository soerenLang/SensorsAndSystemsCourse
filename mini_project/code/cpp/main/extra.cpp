#include "extra.h"
#include "Arduino.h"

void print_xyz(xyz data){
    Serial.print("x: "); Serial.print(data.x); Serial.print(", id: "); Serial.println(data.x_id);
    Serial.print("y: "); Serial.print(data.y); Serial.print(", id: "); Serial.println(data.y_id);
    Serial.print("z: "); Serial.print(data.z); Serial.print(", id: "); Serial.println(data.z_id);
  };