#ifndef _LED_H
#define _LED_H
#include <arduino.h>

typedef unsigned long t_millis;

typedef struct {

  t_millis start; // start time
  t_millis duration; // stop - start, gebuffert
  byte from;      // from value
  byte to;        // to value
  byte current;   // current value
} LED;

float easeInOutQuad(float t);
void calc_led_current(int i, float t);
float calc_t(int i, t_millis t);

#endif
