void readAnalog(){
    // Membaca nilai analog dari A1 dan A2
  int analogValueA1 = analogRead(A1);
  int analogValueA2 = analogRead(A2);
}
void readDigital(){
  // Membaca status digital dari S1 dan S2
  int digitalStateS1 = digitalRead(S1);
  int digitalStateS2 = digitalRead(S2);
}

void printInput(){
  // Tampilkan nilai analog dan status digital pada Serial Monitor
  Serial.print("A1: ");
  Serial.print(analogValueA1);
  Serial.print(" | A2: ");
  Serial.print(analogValueA2);
  Serial.print(" | S1: ");
  Serial.print(digitalStateS1);
  Serial.print(" | S2: ");
  Serial.println(digitalStateS2);
}