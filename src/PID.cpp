#include <string>
#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kd = Kd;
  this->Ki = Ki;
  this->Kp = Kp;

  d_error = 0;
  p_error = 0;
  i_error = 0;
  initialized = false;
  cout << "Now using (" << Kp << "," << Ki << "," << Kd << ")" << endl;
}

void PID::UpdateError(double cte) {
  if (!initialized) {
    p_error = cte;
    initialized = true;
  }
  d_error = cte - p_error;
  p_error = cte;
  i_error += p_error;
}

double PID::TotalError() {
  return -Kp * p_error - Ki * i_error - Kd * d_error;
}

