// I2C SRF10 or SRF08 Devantech Ultrasonic Ranger Finder
////////////////////////////////////
// basierend auf:
///////////////////////////////////
// Nicholas Zambetti <http://www.zambetti.com>
// and James Tichenor <http://www.jamestichenor.net>

// Demonstrates use of the Wire library reading data from the
// Devantech Utrasonic Rangers SFR08 and SFR10

// Created 29 April 2006
// This example code is in the public domain.
///////////////////////////////////

#include <Wire.h>

// The following code changes the address of a Devantech Ultrasonic Range Finder (SRF10 or SRF08)
// usage: changeAddress(0x70, 0xE6);

void changeAddress(byte oldAddress, byte newAddress)
{
  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA0));
  Wire.endTransmission();
  delay(50);

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xAA));
  Wire.endTransmission();
  delay(50);

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA5));
  Wire.endTransmission();
  delay(50);

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(newAddress);
  Wire.endTransmission();


}
void setup() {
  Wire.begin();
  changeAddress(0x70,0xF2);       // anzusprechende Adresse minus LSB, zu schreibende Adresse ganze 8 Bit! 

}

void loop() {
  
}


  //at 0xE0 (the default shipped address) to 0xF2, write the following to address 0xE0; (0xA0, 0xAA, 0xA5, 0xF2 ). 


