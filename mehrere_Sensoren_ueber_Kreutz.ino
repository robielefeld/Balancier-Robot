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

#include <SPI.h>
#include <SD.h>

#include <Wire.h>
//#include <EEPROM.h>

  File myFile;

  void sensorauslesen (int adress){
  
  int reading = 0;


  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(adress); // transmit to device #adress (0x71)
  // the address specified in the datasheet is  (0xE2)
  // but i2c adressing uses the high 7 bits so it's adress
  Wire.write(byte(0x00));      // sets register pointer to the command register (0x00)
  Wire.write(byte(0x51));      // command sensor to measure in "inches" (0x50)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  delay(70);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(adress); // transmit to device #adress
  Wire.write(byte(0x02));      // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(adress, 2);    // request 2 bytes from slave device #adress

  // step 5: receive reading from sensor
  if (2 <= Wire.available()) { // if two bytes were received
    reading = Wire.read();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.read(); // receive low byte as lower 8 bits
    
    Serial.print("DATA,");
    Serial.print(adress);
    Serial.print(",");
    Serial.print(adress);
    Serial.print(",");
    Serial.println(reading);   // print the reading
     
  }

  //delay(130);                  // wait a bit since people have to read the output :)
}

void setup() {
  Wire.begin();                // join i2c bus (address optional for master)
  Serial.begin(9600);          // start serial communication at 9600bps
  Serial.print("LABEL,Adress,:,Wert");
  //myFile = SD.open("accX.txt", FILE_WRITE);
  //myFile.close();
 
            
}

void loop() {

  // Start Sensor 112 erst gegenüber Sensor (adress = adress + 5), dann gegenUhrzeigersinn 90° (adress = adress + 3)
  
  int adress = 112 ; // Startadresse Auslieferungszustand 
  while(1){
  int reading;      
    
                 
    sensorauslesen(112);         // Sensor E0 default Adresse (minus LSB = 0x70 bzw 112 dezimal), nächste Adressen sind in hexadezimal:
                                 // E2,E4,E6,E8,EA,EC,EE,F0,F2 bzw. minus LSB 71,72,73,74,75,76,77,78,79 in dezimal 113,114,115,116,117,118,119,120,121
    sensorauslesen(117);
    sensorauslesen(120);
    sensorauslesen(115);
    sensorauslesen(118);
    sensorauslesen(113);
    sensorauslesen(116);
    sensorauslesen(121);
    sensorauslesen(114);
    sensorauslesen(119);
                                 
                              
                
  

    
    
   
   
    

    //EEPROM.write(adress, reading);
    //EEPROM.write(adress, adress);
  }
  
  
  
  
}




/*

// The following code changes the address of a Devantech Ultrasonic Range Finder (SRF10 or SRF08)
// usage: changeAddress(0x70, 0xE6);

void changeAddress(byte oldAddress, byte newAddress)
{
  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA0));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xAA));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(byte(0xA5));
  Wire.endTransmission();

  Wire.beginTransmission(oldAddress);
  Wire.write(byte(0x00));
  Wire.write(newAddress);
  Wire.endTransmission();

  at 0xE0 (the default shipped address) to 0xF2, write the following to address 0xE0; (0xA0, 0xAA, 0xA5, 0xF2 ). 
}

*/
