#include "types.h"
#include "input.h"

const int FLIP = MAX_BARS - 1;
static t_millis last_update = 0;
static int      last_value  = 0;
static byte     status      = 0;

static t_millis start = 0;
static byte     pos   = 0;

void enter_mode_6(void) {
  set_pwm();
  t_millis t = millis() -300;
  int i = 0;
  while(i < MAX_BARS) {
    LED* result = &LEDS[i];
    result->from     = 0xFF;
    result->to       = 0;      
    result->current  = 0;   
    result->duration = 250;
    result->start    = t;
    i++;
  }
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
    result = led->to;
  }
  else {
    f = easeInOutQuad(f);
    result = led->from + (led->to - led->from) * f;    
  } // else
  
  return result;
}


void run_mode_6(void) {
  
  t_millis now = millis();
  int n        = get_value();
  int i        = 0;

  switch(status) {
    case 0: 
      if(n != last_value) {
        status      = 1;
        last_value  = n;
        last_update = now;        
      } // if 
      break;

    case 1:
      if(n != last_value) {      
        last_value  = n;
        last_update = now;   
      }  
      else if(now - last_update > 500) {
        status = 0;
        pos    = n;
        start  = now - 300;
      }
      break;    
  }
  
  if(status == 0) {

    if(now - start > 125) {

      bool hold = false;
      if(pos != 0) {
        pos = pos - 1;
      }
      else {        
        if(now - start > 750) {
          pos = n;          
        }
        else {                                                                          
          hold = true;
        }
      }

      if(!hold) {
        start             = now;
        LED* current      = &LEDS[pos];
        current->from     = 0xFF;
        current->to       = 0                 ;      
        current->duration = 250;
        current->start    = millis();
        current->current  = 0xFF;        
      }
    }

    while(i < MAX_BARS) {
      LED* result = &LEDS[i];
      if( i == n ) {
        result->current = 0xff;
      } // if 
      else {
        result->current = get_brightness(result);
      } // else 
      i++;
    }
  }
  else { // in motion, brightness is constant
    while(i < MAX_BARS) {
      LED* result = &LEDS[i];
      if( i == n ) {
        result->current = 0xff;
      } // if 
      else {
        result->current = 00;
      } // else 
      i++;
    }
  }

}
