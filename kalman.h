#ifndef KALMAN_H_INCLUDED
#define KALMAN_H_INCLUDED

//kalman filtering for 1d variables
//source: http://interactive-matter.eu/2009/12/filtering-sensor-data-with-a-kalman-filter/

typedef struct {
  double q; //process noise covariance
  double r; //measurement noise covariance
  double x; //value
  double p; //estimation error covariance
  double k; //kalman gain
} kalman_state;

//initialize the kalman filter
kalman_state kalman_init(double q, double r, double p, double intial_value);

void kalman_update(kalman_state* state, double measurement);

#endif // KALMAN_H_INCLUDED
