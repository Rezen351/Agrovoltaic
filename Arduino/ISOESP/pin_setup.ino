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
