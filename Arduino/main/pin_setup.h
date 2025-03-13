
#ifndef PIN_SETUP_H
#define PIN_SETUP_H

//IO
//Shift Register

#define clockReg 5
#define latchReg 18
#define dataReg 19

//Multiplexer
//#define s0 13
//#define s1 12
//#define s2 14
//#define s3 27
//#define sig 26

//BUTTON
#define BUTTON 2
//MOSI, MISO, 23, 19
#define MOSI 23
//#define MISO 19
//SCL, SDA, 22, 21
#define SCL 22
#define SDA 21
//RX0,TX0, 3, 1,
#define RX0 3
#define TX0 1
//RX2.TX2, 16, 17
#define RX0 16
#define TX0 17
byte ledState = 0; // Variabel untuk menyimpan status LED

void pinSetup(){
  //Register
  pinMode(latchReg, OUTPUT);
  pinMode(clockReg, OUTPUT);
  pinMode(dataReg, OUTPUT);
  //Multiplexer
//  pinMode(s0, OUTPUT);
//  pinMode(s1, OUTPUT);
//  pinMode(s2, OUTPUT);
//  pinMode(s3, OUTPUT);
  pinMode(BUTTON, INPUT);
 }


void setLED(int pin, bool state) {
  if (state) {
    ledState |= (1 << pin); // Menyalakan LED tertentu
  } else {
    ledState &= ~(1 << pin); // Mematikan LED tertentu
  }
  digitalWrite(latchReg, LOW);
  shiftOut(dataReg, clockReg, MSBFIRST, ledState);
  digitalWrite(latchReg, HIGH);
}


#endif 
