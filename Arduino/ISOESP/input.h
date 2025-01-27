#ifndef INPUT_H
#define INPUT_H

#include "pin_setup.h"

// Variabel global untuk menyimpan nilai analog dan digital
int analogValueA1, analogValueA2;
int digitalStateS1, digitalStateS2;
int digitalStateR1, digitalStateR2;
int digitalStateRR1, digitalStateRR2;

void readAnalog() {
  // Membaca nilai analog dari A1 dan A2
  analogValueA1 = analogRead(A1);
  analogValueA2 = analogRead(A2);
}

void readDigital() {
  // Membaca status digital dari S1 dan S2
  digitalStateS1 = digitalRead(S1);
  digitalStateS2 = digitalRead(S2);
  // Membaca status digital dari R1 dan R2
  digitalStateR1 = digitalRead(R1);
  digitalStateR2 = digitalRead(R2);
  // Membaca status digital dari RR1 dan RR2
  digitalStateRR1 = digitalRead(RR1);
  digitalStateRR2 = digitalRead(RR2);
}

void printInput() {
  // Menampilkan semua nilai analog dan digital ke Serial Monitor
  Serial.println("=== Input Values ===");
  Serial.print("Analog A1: "); Serial.println(analogValueA1);
  Serial.print("Analog A2: "); Serial.println(analogValueA2);
  Serial.print("Digital S1: "); Serial.println(digitalStateS1);
  Serial.print("Digital S2: "); Serial.println(digitalStateS2);
  Serial.print("Digital R1: "); Serial.println(digitalStateR1);
  Serial.print("Digital R2: "); Serial.println(digitalStateR2);
  Serial.print("Digital RR1: "); Serial.println(digitalStateRR1);
  Serial.print("Digital RR2: "); Serial.println(digitalStateRR2);
  Serial.println("====================");
}

#endif
