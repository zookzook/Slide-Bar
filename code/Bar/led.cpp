#include "types.h"

float easeInOutQuad(float t) { return t<.5 ? 2*t*t : -1+(4-2*t)*t; }

void calc_led_current(LED* result, float t) {
  result->current = result->duration * t + result->start;
}

float calc_t(LED* result, t_millis t) {

  float f = (float)(t - result->start) / result->duration;
  if( f > 1.0 )
    f = 1.0;
  if( f < 0.0 )
    f = 0.0;

  return f;    
}
