//kalman filtering for 1d variables
//source: http://interactive-matter.eu/2009/12/filtering-sensor-data-with-a-kalman-filter/

#include "kalman.h"						//we use kalman filter

kalman_state kalman_init(double q, double r, double p, double intial_value)
{
  kalman_state result;
  result.q = q;							//process noise covariance
  result.r = r;							//measurement noise covariance
  result.p = p;							//estimation error covariance
  result.x = intial_value;				//initialize x

  return result;
}

void kalman_update(kalman_state* state, double measurement)
{
  //prediction update
  //omit x = x
  state->p = state->p + state->q;

  //measurement update
  state->k = state->p / (state->p + state->r);
  state->x = state->x + state->k * (measurement - state->x);
  state->p = (1 - state->k) * state->p;
}

