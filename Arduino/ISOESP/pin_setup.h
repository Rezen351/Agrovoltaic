#ifndef PIN_SETUP_H
#define PIN_SETUP_H

#define A1 32
#define A2 33
#define S1 34
#define S2 35
#define R1 27
#define R2 26
#define RR1 15
#define RR2 2
#define Tpin 25
//MOSI, MISO, 23, 19
//SCL, SDA, 22, 21
//RX0,TX0, 3, 1, 
//RX2.TX2, 16, 17 

void pinSetup(){
 // Konfigurasi pin sebagai input atau output
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(RR1, OUTPUT);
  pinMode(RR2, OUTPUT);

  // Inisialisasi output digital dalam keadaan LOW
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(RR1, LOW);
  digitalWrite(RR2, LOW);

  Serial.println("Pin Setup is Ready!");
 }
#endif 