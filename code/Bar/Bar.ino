#include <tinySPI.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const int LATCH_PIN = 0;
const int DATA_PINPIN = 1;
const int CLOCK_PIN = 2;    
const int ANALOG_INPUT = A3;

const byte MAX_BARS  = 10;
const int MASKS[]    = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000f, 0x001f, 0x003f, 0x007f, 0x00ff, 0x01ff, 0x03ff };
const int DIVISOR    = 1023 / MAX_BARS;
      int last_value = -1;

byte LEDS[MAX_BARS];
byte START[MAX_BARS];
byte STOP[MAX_BARS];

typedef struct {

  unsigned long t;
  byte source;
  byte dest;
  byte current;
} LED;

int current_mode = 0;

volatile byte i = 0;
volatile int t = 0;

// 1/(16*10^6/(8192*2))*100

byte get_value() {
  
  int result = analogRead(ANALOG_INPUT) / DIVISOR;
  if(result < 0)
    result = 0;
  if(result > MAX_BARS)
    result = MAX_BARS - 1;
  
  return result;  
}

float easeInOutQuad(float t) { return t<.5 ? 2*t*t : -1+(4-2*t)*t; }

void calc(float t) {
  int i = 0;
  LEDS[i] = (STOP[i] - START[i])*t + START[i];
}


void initTimer1(void) {
  
  TCCR1 |= (1 << CTC1);  // clear timer on compare match
  TCCR1 |= (1 << CS13) | (1 << CS11) | (1 << CS10); //
  OCR1C = 0; // compare match value 
  TIMSK |= (1 << OCIE1A); // enable compare match interrupt
}

void counter_isr() {
  if(t < 5 ) {
    t += 1;
  }
  else {
    int max_value = MASKS[get_value()];
    if(i < max_value) {
      i++;
      write_word(i);
    }
    t = 0;
  }  
}

ISR(TIMER1_COMPA_vect) {

  i += 5;
  unsigned int w = 0x0000;
  int          j = MAX_BARS - 1;
  
  while(j >= 0) {
    w = w << 1;
    w = w | (LEDS[j] > i);
    j--;
  }
  
  write_word(w);
}

void write_word(int data) {
    
    PORTB &= ~B00000001; // digitalWrite(LATCH_PIN, LOW);
    SPI.transfer(data >> 8);
    SPI.transfer(data); // digitalWrite(LATCH_PIN, HIGH);       
    PORTB |= B00000001;
}

void test() {
  write_word(0xffff);  
  delay(3000);
  write_word(0x0000);  
  delay(1000);
}
void setup() {

  for(int i = 0; i < MAX_BARS; i++ ) {
    LEDS[i] = 0;
  }
  
  SPI.begin();     

  pinMode(LATCH_PIN, OUTPUT);    // latch pin needs to be set up for hardware or software
  digitalWrite(LATCH_PIN, HIGH);
    
  test();

  initTimer1();        // initialize timer registers
  sei();
}

void loop() {

  int value = analogRead(ANALOG_INPUT) / 4;
  if( last_value != value ) {
    last_value = value;
    for(int i = 0; i < MAX_BARS; i++ ) {
      LEDS[i] = last_value;
    }

  } // if 
}
