#include "impl/NotSoBasicLinearAlgebra.h"
#include "ElementStorage.h"
#include "BasicLinearAlgebra.h"
#include "kalman_filter.h"

kalman_filter :: kalman_filter(){

};

xyz kalman_filter :: update(float acc, float vel){
  BLA::Matrix<2> y_meas = {acc,vel};
  
  BLA::Matrix<2> y_pred = {0,0};
  y_pred = this->system.C*this->x_pred;
  
  BLA::Matrix<2> y_error = y_meas - y_pred;

  BLA::Matrix<3,2> C_trans = ~this->system.C;
  BLA::Matrix<2,2> temp = this->system.C*this->P_pred*C_trans + this->R;
  auto temp_inv = temp;
  BLA::Invert(temp, temp_inv);
  BLA::Matrix<3,2> K = this->P_pred*C_trans*temp;
  //BLA::Trans<class MemT>
  
};