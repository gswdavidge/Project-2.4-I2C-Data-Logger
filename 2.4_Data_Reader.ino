// PROJECT   : Data Reader
// PURPOSE   : Read data from 24LC256 and print to serial
// COURSE    : ICS3U
// AUTHOR    : G. Davidge
// DATE      : 2023 02 20
// MCU       : 328P(Nano)
// STATUS    : Working
// REFERENCE : http://darcy.rsgc.on.ca/ACES/TEI3M/2223/Tasks.html#datalogger
#include <Wire.h>

#define MAXIMUMSAMPLES 14400
#define MAXADDRESS     0x7FFF
#define EEPROMSTART    0x50
#define TC74ADDRESS    0x4D

//control vars
uint16_t sampleNum = 0;
uint16_t address = 6;   //first temp adr
uint16_t eeprom = EEPROMSTART;

//samples vars
int8_t sampleTemp;
uint8_t startSecs, startMins, startHours, startDays, startMons, startYears;

void setup() {
  Wire.begin();

  pinMode(LED_BUILTIN, 1);
  digitalWrite(LED_BUILTIN, 0);

  Serial.begin(9600);
  while(!Serial);

  delay(2000); //to allow for processing to start

  //read and send start time
  startSecs = eepromRead(EEPROMSTART, 0);
  startMins = eepromRead(EEPROMSTART, 1);
  startHours = eepromRead(EEPROMSTART, 2);
  startDays = eepromRead(EEPROMSTART, 3);
  startMons = eepromRead(EEPROMSTART, 4);
  startYears = eepromRead(EEPROMSTART, 5);
  Serial.println(startSecs);
  Serial.println(startMins);
  Serial.println(startHours);
  Serial.println(startDays);
  Serial.println(startMons);
  Serial.println(startYears);

  //print out all samples
  for (uint16_t samplesRead = 0; samplesRead < MAXIMUMSAMPLES; samplesRead++) {
    sampleTemp = eepromRead(eeprom, address);
    address+= 7;
    if (address > MAXADDRESS) { //check for adr rollover
      address -= MAXADDRESS;    //calculate new adr
      eeprom++;                 //increment eeprom
    }
    Serial.println(sampleTemp);
  }
  digitalWrite(LED_BUILTIN, 1);
}

void loop() {
}

uint8_t eepromRead(uint8_t chip, uint16_t address) {
  Wire.beginTransmission(chip);       //chip adr
  Wire.write(address >> 8);           //HB
  Wire.write(address & 0xFF);         //LB
  Wire.endTransmission();
  Wire.requestFrom(chip, 0x1);        //1 byte
  while (!Wire.available());          //hold for data
  return Wire.read();
}
