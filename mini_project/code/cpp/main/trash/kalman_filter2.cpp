#include "MatrixMath.h"
#include "kalman_filter2.h"

kalman_filter2 :: kalman_filter2(){

};

xyz kalman_filter2 :: update(float acc, float vel){
  mtx_type y_meas[2][1] = {acc,vel};
  
  mtx_type y_pred[2][1] = {0,0};

  //predict output
  Matrix.Multiply((mtx_type*)this->system.C, (mtx_type*)this->x_pred, 2, 3, 2, (mtx_type*)y_pred); 
  
  //Find prediction error
  mtx_type y_error[2][1];
  Matrix.Subtract((mtx_type*)y_meas, (mtx_type*)y_pred, 2, 1, (mtx_type*)y_error);

  //Calculate kalman gain
  mtx_type C_transpose[3][2]; Matrix.Transpose((mtx_type*)this->system.C, 2, 3, (mtx_type*)C_transpose);
  mtx_type temp[2][3];// = this->system.C*this->P_pred C_trans + this->R;
  Matrix.Multiply((mtx_type*)this->system.C, (mtx_type*)this->P_pred, 2, 3, 3, (mtx_type*)temp);
  
  mtx_type temp2[2][2];
  Matrix.Multiply((mtx_type*)temp, (mtx_type*)C_transpose, 2, 3, 2, (mtx_type*)temp2);
  Matrix.Add((mtx_type*)temp2, (mtx_type*)this->R, 2, 2, (mtx_type*)temp2);
  Matrix.Invert((mtx_type*)temp2, 2);

  mtx_type temp3[3][2];
  Matrix.Multiply((mtx_type*)C_transpose, (mtx_type*)temp2, 3, 2, 2, (mtx_type*)temp3);

  mtx_type k[3][2];
  Matrix.Multiply((mtx_type*)this->P_pred, (mtx_type*)temp3, 3, 3, 2, (mtx_type*)k);

  //Find state estimate
  mtx_type pred_error[3][1];
  Matrix.Multiply((mtx_type*)k, (mtx_type*)y_error, 3, 2, 1, (mtx_type*)pred_error);

  Matrix.Add((mtx_type*)this->x, (mtx_type*)pred_error, 3, 1, (mtx_type*)this->x);

  //Find estimate covariance
  mtx_type temp[3][3] = {1,0,0,0,1,0,0,0,1};
  mtx_type temp2[3][3]; Matrix.Multiply((mtx_type*)k, (mtx_type*)this->system.C, 3, 2, 3, (mtx_type*)temp2);

  Matrix.Subtract((mtx_type*)temp, (mtx_type*)temp2, 3, 3, (mtx_type*)temp);

  mtx_type temp2[3][3]; Matrix.Multiply((mtx_type*)temp, (mtx_type*)temp2, 3, 3, 3, (mtx_type*)temp2);
  Matrix.Transpose(temp, 3, 3, temp);
  Matrix.Multiply(temp2, temp, 3, 3, 3, double *C)

  
};