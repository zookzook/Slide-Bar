#include "types.h"
#include "input.h"

#define DELTA 100

void enter_mode_4(void) {
  set_pwm();
}

static byte get_brightness(LED* led) {

  byte result = 255;
  t_millis now = millis();
  float f = (float)(now - led->start) / led->duration;
  if( f < 0 ) {
    result = led->from;
  } // if 
  else
  if( f > 1.0 ) {
    result = 0;
  }
  else {
    f = easeInOutQuad(f);
    result = led->from + (led->to - led->from) * f;    
  } // else
  
  return result;
}


void run_mode_4(void) {
  
  int n           = get_value();
  int i           = 0;
  
  while(i < MAX_BARS) {

    LED* result = &LEDS[i];

    if(i == n) {
      result->from = 0xFF;
      result->to   = 0x00                 ;      
      result->duration = 1000;
      result->start    = millis();
      result->current = 0xFF;
    }
    else {
      result->current = get_brightness(result);
    }
    i++;
  }

}
