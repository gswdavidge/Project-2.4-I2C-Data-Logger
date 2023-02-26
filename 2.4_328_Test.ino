// PROJECT   : PB0-1 Bicolour Blink
// PURPOSE   : Demonstrate that the 328p Works
// COURSE    : ICS3U
// AUTHOR    : G. Davidge
// DATE      : 2023 02 26
// MCU       : 328P
// STATUS    : Working
// REFERENCE : http://darcy.rsgc.on.ca/ACES/TEI3M/2223/Tasks.html#datalogger
#define GREEN        (1 << PB0) | (0 << PB1)
#define RED          (0 << PB0) | (1 << PB1)

void setup() {
  DDRB = GREEN | RED;                              //output
  PORTB = GREEN;                                   //green

  cli();
  MCUSR &= ~(1 << WDRF);                            //disable reset
  WDTCSR |= (1 << WDE) | (1 << WDCE);               //enable change, disable reset
  WDTCSR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1); //1s period
  TIMSK0 = 0;                                       //disable timer0
  sei();
}


void loop() {
}

ISR (WDT_vect) {
  PINB = GREEN | RED;                               //toggle
}
