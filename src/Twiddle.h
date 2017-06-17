#ifndef PID_TWIDDLE_H
#define PID_TWIDDLE_H

class Twiddle {

public:
    Twiddle();

    bool isSatisfied();

    double *getP();

    void UpdateError(double cte, double speed);

    void Decide();

    bool RunCompleted();

    void printBestP();

private:
    double best_err_;
    int steps_;
    int pi_;
    double dp_[3] = {1, 0, 1};
    double p_[3] = {1, 0, 0};
    int current_step_;
    double errors_;
    bool trying_add = true;

    double threshold_;

    void resetPAndCurrentStep();

    void nextIteration();
};


#endif //PID_TWIDDLE_H
