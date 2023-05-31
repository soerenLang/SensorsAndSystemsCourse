#include "rotary_velocity.h"
#include <math.h>

rotary_velocity :: rotary_velocity(float fs){
  this->fs = fs;
  float v_op = 0.08;
  float num_1_1_sec = v_op/(this->wheel_diameter_m*3.14);
  //this->a = v_op*this->ring_array.storage.size()/num_1_1_sec;
  this->a = 0.195;
  Serial.println(this->a);
  Serial.println(this->ring_array.storage.size());
};

float rotary_velocity :: make_velocity(){
  this->mag.make_measurement();

  bool toCompare = this->mag.get_measurement();
  if(toCompare != this->prev_mag &&this->mag.get_measurement_raw() < this->mag.get_limit() ){
    this->update_ring_array(1);

  }
  else {
    this->update_ring_array(0);
  }
  
  this->prev_mag = toCompare;
  float velocity = float(std::accumulate(this->ring_array.storage.begin(), this->ring_array.storage.end(),0))/this->ring_array.storage.size()*this->a;
  //Serial.println(velocity);
  this->velocity = velocity;
  return velocity;
};

float rotary_velocity :: get_velocity(){
  return this->velocity;
};

void rotary_velocity :: update_ring_array(float value){
  this->ring_array.storage[this->ring_array.index] = value;

  this->ring_array.index ++;
  if (this->ring_array.index > this->ring_array.storage.size()){
    this ->ring_array.index = 0;
  }
};