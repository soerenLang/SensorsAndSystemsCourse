#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

#include "extra.h"

#include "BasicLinearAlgebra.h"
using namespace BLA;  
class kalman_filter{
  
  public:
    kalman_filter();

    xyz update(float acc, float vel);

  private:
  BLA::Matrix<3> x_pred = {0,0,0};
  BLA::Matrix<3,3> P_pred = {1,0,0,0,1,0,0,0,1};
  BLA::Matrix<3,3> P = {1,0,0,0,1,0,0,0,1};
  BLA::Matrix<3,3> Q = {1,0,0,0,1,0,0,0,1};
  BLA::Matrix<2,2> R = {1,0,0,0};

  struct{
    float ts{.1};

    BLA::Matrix<3,3> A = {1,0,0,ts,1,0,0,ts,1};
    BLA::Matrix<3> B = {ts,0,0};
    BLA::Matrix<2,3> C = {1,0,0,0,1,0};
  }system;

  xyz prev_estimate;

};

#endif