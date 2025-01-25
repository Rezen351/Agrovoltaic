void writeOutput() {
  digitalWrite(R1, !digitalRead(R1));
  digitalWrite(R2, !digitalRead(R2));
  digitalWrite(RR1, !digitalRead(RR1));
  digitalWrite(RR2, !digitalRead(RR2));
}
