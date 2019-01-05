#include "types.h"
#include "input.h"

static LED      led;
static t_millis last_update = 0;
static int      last_value  = 0;
static byte     status      = 0;


void enter_mode_3(void) {
  set_pwm();
  led.start    = millis();
  led.duration = 100;
  led.from     = 0;
  led.current  = 0;
  led.to       = 255;
}

static start_pulse(void) {
  led.start    = millis();
  led.duration = 100;
  led.from     = 255;
  led.current  = 255;
  led.to       = 0;
}

static byte get_brightness(int n) {

  byte result = 255;
  t_millis now = millis();
  float f = (float)(now - led.start) / led.duration;
  if( f < 0 ) {
    result = led.from;
  } // if 
  else
  if( f > 4.0 ) {
    byte value   = led.from;
    led.from     = led.to;
    led.to       = value;
    led.start    = now;
    led.duration = 100;
    result       = led.from;
  }
  else
  if( f > 1.0 ) {
    result = led.to;
  } // if 
              else {
    f = easeInOutQuad(f);
    result = led.from + (led.to - led.from) * f;    
  } // else
  
  return result;
}


void run_mode_3(void) {
  
  t_millis now    = millis();
  int n           = get_value();
  int i           = 0;
  byte brightness = 255;

  switch(status) {

    case 0: 
      if(n != last_value) {
        status      = 1;
        last_value  = n;
        last_update = now;        
      } // if 
      else {
        brightness = get_brightness(last_value);
      }
      break;

    case 1:
      if(n != last_value) {      
        last_value  = n;
        last_update = now;   
      }  
      else if(now - last_update > 500) {
        status = 0;
        start_pulse();
      }
      break;    
  }
  
  while(i < MAX_BARS) {

    LED* result = &LEDS[i];
    if( i == n ) {
      result->current = brightness;
    } // if 
    else {
      result->current = 0;
    } // else 
    i++;
  }

}
