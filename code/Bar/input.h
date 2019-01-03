#ifndef _INPUT_H
#define _INPUT_H
#include <arduino.h>

int get_value(void);
int get_mode(void);
uint16_t get_mode_mask(void);
void check_mode(void);

#define MODE_0 0
#define MODE_1 1
#define MAX_MODES 2

#endif
