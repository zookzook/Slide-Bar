#include "types.h"
#include "input.h"

void enter_mode_5(void) {
  set_pwm();
}

void run_mode_5(void) {
  
  int n           = get_value();
  int i           = 0;
  
  while(i < MAX_BARS) {

    LED* result = &LEDS[i];

    if(i == n) {
      result->current = 0xFF;
    }
    else {
      result->current = 30;
    }
    i++;
  }

}
