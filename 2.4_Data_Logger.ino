// PROJECT   : Data Logger
// PURPOSE   : Write temperature data every 6 seconds to 3 24LC56 EEPROMS
// COURSE    : ICS3U
// AUTHOR    : G. Davidge
// DATE      : 2023 02 15
// MCU       : 328P
// STATUS    : Working
// REFERENCE : http://darcy.rsgc.on.ca/ACES/TEI3M/2223/Tasks.html#datalogger
#include <Wire.h>

#define SAMPLINGPERIOD 6
#define MAXIMUMSAMPLES 14400
#define MAXADDRESS     0x7FFF
#define TC74ADDRESS    0x4D
#define RTCADDRESS     0x68
#define EEPROMSTART    0x50

#define SQWREGISTER 7
#define SQWE        4
#define RS0         0
#define RS1         1
#define HZ1         (0 << RS1) | (0 << RS0)

#define SQWPIN        (1 << PD2)
#define FALLINGEDGE   (1 << ISC01) | (0 << ISC00)

#define GREEN        (1 << PB0) | (0 << PB1)
#define RED          (0 << PB0) | (1 << PB1)

//control status varaibles
bool sampling = 1;
volatile uint8_t sqwCount = 0;
uint16_t sampleNum = 0;
uint16_t address = 0;
uint16_t eeprom = EEPROMSTART;

//sample varaibles
int8_t sampleTemp;
uint8_t sampleSecs, sampleMins, sampleHours, sampleDays, sampleMons, sampleYears;

void setup() {
  Wire.begin();
  
  //configure square wave
  Wire.beginTransmission(RTCADDRESS);
  Wire.write(SQWREGISTER);
  Wire.write(1 << SQWE | HZ1);
  Wire.endTransmission();

  DDRD = ~SQWPIN;     //set to input
  DDRB = GREEN | RED; //set to output

  cli();
  EICRA = FALLINGEDGE;    //INT0 mode
  EIMSK |= (1 << INT0);   //enable INT0
  EIFR |= (1 << INTF0);   //clear
  sei();

  PORTB = RED;            //sampling indicator
}

void loop() {
  if (sqwCount == SAMPLINGPERIOD) {
    if (sampling) {
      sqwCount = 0;                 //clear indicator
      sampleTemp = getTempC();
      getTime(sampleSecs, sampleMins, sampleHours, sampleDays, sampleMons, sampleYears);
      eepromWrite(eeprom, address, sampleSecs);   //store data
      if (address == MAXADDRESS) {                //check for adr rollover
        eeprom++;                                 //increment eeprom     
        address = 0;                              //clear adr
      } else {
        address++;
      }
      eepromWrite(eeprom, address, sampleMins);   //store data
      if (address == MAXADDRESS) {                //check for adr rollover
        eeprom++;                                 //increment eeprom
        address = 0;                              //clear adr
      } else {
        address++;
      }
      eepromWrite(eeprom, address, sampleHours);   //store data
      if (address == MAXADDRESS) {                 //check for adr rollover
        eeprom++;                                  //increment eeprom  
        address = 0;                               //clear adr
      } else {
        address++;
      }
      eepromWrite(eeprom, address, sampleDays);   //store data
      if (address == MAXADDRESS) {                //check for adr rollover
        eeprom++;                                 //increment eeprom  
        address = 0;                              //clear adr
      } else {
        address++;
      }
      eepromWrite(eeprom, address, sampleMons);   //store data
      if (address == MAXADDRESS) {                //check for adr rollover
        eeprom++;                                 //increment eeprom  
        address = 0;                              //clear adr
      } else {
        address++;
      }
      eepromWrite(eeprom, address, sampleYears);   //store data
      if (address == MAXADDRESS) {                 //check for adr rollover
        eeprom++;                                  //increment eeprom  
        address = 0;                               //clear adr
      } else {
        address++;
      }

      eepromWrite(eeprom, address, sampleTemp);   //store data
      if (address == MAXADDRESS) {                //check for adr rollover
        eeprom++;                                 //increment eeprom  
        address = 0;                              //clear adr
      } else {
        address++;
      }
    }
    sampleNum++;
    if (sampleNum == MAXIMUMSAMPLES) {            //check samples
      sampling = 0;                               //clear sampling mode
      PORTB = GREEN;                              //complete indicator
    }
  }
}

ISR (INT0_vect) {
  sqwCount++;     //increment count
}

void eepromWrite(uint8_t chip, uint16_t address, uint8_t data) {
  Wire.beginTransmission(chip);   //chip adr
  Wire.write(address >> 8);       //data adr HB
  Wire.write(address & 0xFF);     //data adr LB
  Wire.write(data);               //data
  Wire.endTransmission();
  delay(5);                       //write cycle delay
}

int8_t getTempC() {
  Wire.beginTransmission(TC74ADDRESS);
  Wire.write(0);                          //data adr
  Wire.endTransmission();
  Wire.requestFrom(TC74ADDRESS, 0x1);     //num bytes
  while (!Wire.available());              //wait for transmission
  return Wire.read();
}

void getTime(uint8_t &sec, uint8_t &mi, uint8_t &ho, uint8_t & da, uint8_t &mo, uint8_t &ye) {
  Wire.beginTransmission(RTCADDRESS);
  Wire.write(0);                        //starting data adr
  Wire.endTransmission();
  Wire.requestFrom(RTCADDRESS, 0x7);    //request 7 bytes
  while (!Wire.available());            //hold for data start
  sec = bcd2Dec(Wire.read());
  mi = bcd2Dec(Wire.read());
  ho = bcd2Dec(Wire.read());
  Wire.read();
  da = bcd2Dec(Wire.read());
  mo = bcd2Dec(Wire.read());
  ye = bcd2Dec(Wire.read());
}

uint8_t bcd2Dec(uint8_t bcd) {
  return 10 * (bcd >> 4) + (bcd & 0xF);
}
