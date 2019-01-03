#include "types.h"
#include "input.h"

void enter_mode_1(void) {
  set_pwm();
}

void run_mode_1(void) {
  
  int n = get_value();
  int i = 0;
  while(i < MAX_BARS) {

    if( i < n ) {
      LEDS[i].current = 255;      
    } // if 
    else {
      LEDS[i].current = 0;
    } // else 
    i++;
  }

}
