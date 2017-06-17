#include <limits>
#include <iostream>
#include <cmath>
#include "Twiddle.h"

using namespace std;


Twiddle::Twiddle() {
  best_err_ = std::numeric_limits<double>::max();
  steps_ = 4000;
  threshold_ = 0.05;
  pi_ = 0;
  current_step_ = 0;
}

bool Twiddle::isSatisfied() {
  return dp_[0] + dp_[1] + dp_[2] < threshold_;
}

double *Twiddle::getP() {
  return p_;
}

void Twiddle::UpdateError(double cte, double speed) {
  current_step_++;
  errors_ += cte * cte;
}

void Twiddle::Decide() {
  if (current_step_ == steps_ && errors_ < best_err_) {
    cout << "best error: " << best_err_ << " ----> current error: " << errors_ << endl;
  } else if (current_step_ < steps_) {
    cout << "best error: " << best_err_ << " ..... current error: " << errors_ << " current_step: " << current_step_
         << endl;
  } else {
    cout << "best error: " << best_err_ << " ..... current error: " << errors_ << endl;
  }

  if (trying_add) {
    if (errors_ < best_err_) {
      best_err_ = errors_;
      dp_[pi_] *= 1.1;
      nextIteration();
    } else {
      p_[pi_] -= 2 * dp_[pi_];
      trying_add = false;
      resetPAndCurrentStep();
    }
  } else {
    if (errors_ < best_err_) {
      best_err_ = errors_;
      dp_[pi_] *= 1.1;
    } else {
      p_[pi_] += dp_[pi_];
      dp_[pi_] *= 0.9;
    }
    nextIteration();
  }
}

void Twiddle::nextIteration() {
  pi_ = (++pi_) % 3;
  if(pi_ == 1)
    pi_ = 2;
  p_[pi_] += dp_[pi_];
  trying_add = true;
  resetPAndCurrentStep();
}


void Twiddle::resetPAndCurrentStep() {
  cout << "dp is (" << dp_[0] << "," << dp_[1] << "," << dp_[2] << ")" << " index: " << pi_ << endl;
//  cout << "change p to (" << p_[0] << "," << p_[1] << "," << p_[2] << ")" << endl;
  current_step_ = 0;
  errors_ = 0;
}

bool Twiddle::RunCompleted() {
  return current_step_ >= steps_ || errors_ > best_err_;
}

void Twiddle::printBestP() {
  std::cout << "The best p is (" << p_[0] << "," << p_[1] << "," << p_[2] << ")" << endl;
}
