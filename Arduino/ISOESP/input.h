#ifndef INPUT_H
#define INPUT_H

int analogValueA1,analogValueA2,
digitalStateS1,digitalStateS2,
digitalStateR1,digitalStateR2,
digitalStateRR1,digitalStateRR2;

void readAnalog(){
    // Membaca nilai analog dari A1 dan A2
  int analogValueA1 = analogRead(A1);
  int analogValueA2 = analogRead(A2);
}
void readDigital(){
  // Membaca status digital dari S1 dan S2
  int digitalStateS1 = digitalRead(S1);
  int digitalStateS2 = digitalRead(S2);
  // Membaca status digital dari R1 dan R2
  int digitalStateR1 = digitalRead(R1);
  int digitalStateR2 = digitalRead(R2);
  // Membaca status digital dari RR1 dan RR2
  int digitalStateRR1 = digitalRead(RR1);
  int digitalStateRR2 = digitalRead(RR2);
}
#endif 