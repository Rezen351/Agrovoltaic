#define A1 32
#define A2 33
#define S1 34
#define S2 35
#define R1 27
#define R2 26
#define RR1 15
#define RR2 2
#define BAUD 9600

void setup() {
  Serial.begin(BAUD);

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

  Serial.println("System Ready!");
}

void loop() {
  // Membaca nilai analog dari A1 dan A2
  int analogValueA1 = analogRead(A1);
  int analogValueA2 = analogRead(A2);

  // Membaca status digital dari S1 dan S2
  int digitalStateS1 = digitalRead(S1);
  int digitalStateS2 = digitalRead(S2);

  // Tampilkan nilai analog dan status digital pada Serial Monitor
  Serial.print("A1: ");
  Serial.print(analogValueA1);
  Serial.print(" | A2: ");
  Serial.print(analogValueA2);
  Serial.print(" | S1: ");
  Serial.print(digitalStateS1);
  Serial.print(" | S2: ");
  Serial.println(digitalStateS2);

  // Mengontrol output digital (contoh: flip status setiap loop)
  digitalWrite(R1, !digitalRead(R1));
  digitalWrite(R2, !digitalRead(R2));
  digitalWrite(RR1, !digitalRead(RR1));
  digitalWrite(RR2, !digitalRead(RR2));

  // Tunggu 1 detik sebelum loop berikutnya
  delay(1000);
}
