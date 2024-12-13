#define A1 32
#define A2 33
#define S1 34
#define S2 35
#define R1 27
#define R2 26
#define RR1 15
#define RR2 2
#define BAUD 9600
#define Tpin 25

//MOSI, MISO, 23, 19
//SCL, SDA, 22, 21
//RX0,TX0, 3, 1, 
//RX2.TX2, 16, 17 

void setup() {
  Serial.begin(BAUD);
  pinSetup();
 
}

void loop() {
  readAnalog();

  readDigital();

  printInput();

  writeOutput();

  // Tunggu 1 detik sebelum loop berikutnya
  delay(1000);
}
