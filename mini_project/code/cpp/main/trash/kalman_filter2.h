#ifndef KALMAN_FILTER2_H
#define KALMAN_FILTER2_H

#include "extra.h"

#include "MatrixMath.h"  
class kalman_filter2{
  
  public:
    kalman_filter2();

    xyz update(float acc, float vel);

  private:
  mtx_type x_pred[3][1] = {0,0,0};
  mtx_type P_pred[3][3] = {1,0,0,0,1,0,0,0,1};
  mtx_type P[3][3] = {1,0,0,0,1,0,0,0,1};
  mtx_type Q[3][3] = {1,0,0,0,1,0,0,0,1};
  mtx_type R[2][2] = {1,0,0,0};

  struct{
    float ts{.1};

    mtx_type A[3][3] = {1,0,0,ts,1,0,0,ts,1};
    mtx_type B[3][1] = {ts,0,0};
    mtx_type C[2][3] = {1,0,0,0,1,0};
  }system;

  mtx_type x[3][1] = {0,0,0};

};

#endif