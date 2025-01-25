extern int A1, A2, S1, S2, R1, R2, RR1, RR2;

void pinSetup(){
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(RR1, OUTPUT);
  pinMode(RR2, OUTPUT);

  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(RR1, LOW);
  digitalWrite(RR2, LOW);

  Serial.println("Pin Setup is Ready!");
}
