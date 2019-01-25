/**
 * 
 */
#include <tinySPI.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "types.h"
#include "mode_1.h"
#include "mode_2.h"
#include "input.h"

const int LATCH_PIN = 0;
const int DATA_PINPIN = 1;
const int CLOCK_PIN = 2;    

void (*fun_ptr)(void) = NULL; 

LED LEDS[MAX_BARS];

int current_mode = 0;

volatile byte i = 0;

void init_timer_1(void) {
  
  TCCR1 |= (1 << CTC1);     // clear timer on compare match
  TCCR1 |= (1 << CS13) | (1 << CS11) | (1 << CS10); //
  OCR1C = 0;                // compare match value 
  TIMSK |= (1 << OCIE1A);   // enable compare match interrupt
}

void pwm(void) {

  i += 5;
  unsigned int w = 0x0000;
  int          j = 0;
  
  while(j < MAX_BARS) {
    w = w << 1;
    w = w | (LEDS[j].current > i);
    j++;
  }

  w = w | get_mode_mask();
  write_word(w);
  
}

ISR(TIMER1_COMPA_vect) {
  (*fun_ptr)(); 
}

void write_word(int data) {
    
    PORTB &= ~B00000001; // digitalWrite(LATCH_PIN, LOW);
    SPI.transfer(data >> 8);
    SPI.transfer(data); // digitalWrite(LATCH_PIN, HIGH);       
    PORTB |= B00000001;
}

void run_test() {
  write_word(0xffff);  
  delay(3000);
  write_word(0x0000);  
  delay(1000);
}

void set_pwm() {
  fun_ptr = &pwm;
}

void setup() {

  for(int i = 0; i < MAX_BARS; i++ ) {
    LEDS[i].current = 0;
  }
  
  SPI.begin();     

  pinMode(LATCH_PIN, OUTPUT);    // latch pin needs to be set up for hardware or software
  digitalWrite(LATCH_PIN, HIGH);
    
  run_test();
  set_pwm();
  init_timer_1();        // initialize timer registers  
  sei();
}

void loop() {
  check_mode();
}
