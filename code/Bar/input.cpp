#include "input.h"
#include "types.h"

static float weight  = 10/100.0;
static float current = 0;
const int ANALOG_INPUT = A3;

int get_value() {
  
  int raw    = analogRead(ANALOG_INPUT);
  current    = weight * raw + (1.0 - weight) * current;
  int result = map(current, 0, 1000, 0, MAX_BARS); // durch den Filter erreichen wir keine 100% bzw 1023.
  
  return result;  
}
