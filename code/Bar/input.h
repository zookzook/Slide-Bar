#ifndef _INPUT_H
#define _INPUT_H
#include <arduino.h>

int get_value(void);
int get_mode(void);
uint16_t get_mode_mask(void);
void check_mode(void);

#define MODE_1 0
#define MODE_2 1
#define MODE_3 2
#define MODE_3 3
#define MAX_MODES 4

#endif
