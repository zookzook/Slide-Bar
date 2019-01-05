#include "input.h"
#include "types.h"
#include "mode_1.h"
#include "mode_2.h"
#include "mode_3.h"
#include "mode_4.h"

#define MODE_1_MASK (((uint16_t)B00000100)<<8)
#define MODE_2_MASK (((uint16_t)B00001000)<<8)
#define MODE_3_MASK (((uint16_t)B00010000)<<8)
#define MODE_4_MASK (((uint16_t)B00100000)<<8)
#define MODE_5_MASK (((uint16_t)B01000000)<<8)
#define MODE_6_MASK (((uint16_t)B10000000)<<8)

// we are using a filter to smooth the noise on the analog input
static float weight    = 10/100.0;
static float current   = 0;
static float mode_weight    = 10/100.0;
static float mode_current   = 0;
static uint16_t mode_mask   = 0x00;

static uint8_t current_mode = 0xff;

static void (*mode_func_ptr)(void) = NULL; 

const int ANALOG_INPUT = A3;
const int MODE_INPUT   = A2;

int get_value(void) {
  
  int raw    = analogRead(ANALOG_INPUT);
  current    = weight * raw + (1.0 - weight) * current;
  int result = map(current, 0, 1000, 0, MAX_BARS - 1); // durch den Filter erreichen wir keine 100% bzw 1023.
  
  return result;  
}

int get_mode(void) {
  
  int raw      = analogRead(MODE_INPUT);
  mode_current = mode_weight * raw + (1.0 - mode_weight) * mode_current;
  int result   = map(mode_current, 0, 1000, 0, MAX_MODES - 1); // durch den Filter erreichen wir keine 100% bzw 1023.
  
  return result;  
}

uint16_t get_mode_mask(void) {
  return mode_mask;
}

void check_mode(void) {

  int new_mode = get_mode();
  if(current_mode != new_mode) {
    current_mode = new_mode;
    switch(current_mode) {

      case 0: 
        enter_mode_1();
        mode_func_ptr = &run_mode_1;
        mode_mask = MODE_1_MASK;
        break;
        
      case 1:
        enter_mode_2();
        mode_func_ptr = &run_mode_2;
        mode_mask = MODE_2_MASK;
        break;

      case 2:
        enter_mode_3();
        mode_func_ptr = &run_mode_3;
        mode_mask = MODE_3_MASK;
        break;

      case 3:
        enter_mode_4();
        mode_func_ptr = &run_mode_4;
        mode_mask = MODE_4_MASK;
        break;

      default:
        enter_mode_1();
        mode_func_ptr = &run_mode_1;
        mode_mask = MODE_1_MASK;
        break;
    }
  } // if 
  else {
     (*mode_func_ptr)(); 
  } // else
}
