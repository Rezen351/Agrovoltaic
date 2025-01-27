#ifndef OUTPUT_H
#define OUTPUT_H

// Variabel status output
bool out1 = LOW; // Output 1
bool out2 = LOW;
bool out3 = LOW;
bool out4 = LOW;

extern bool isOn; // Variabel global untuk mengontrol kondisi output

// Fungsi untuk mengontrol output digital
void writeOutput() {
  if (isOn) {
    // Jika isOn true, semua output diatur HIGH
    digitalWrite(R1, HIGH);
    digitalWrite(R2, HIGH);
    digitalWrite(RR1, HIGH);
    digitalWrite(RR2, HIGH);

    // Menampilkan status HIGH pada Serial Monitor
    Serial.println("All outputs are set to HIGH (isOn = true)");
  } else {
    // Jika isOn false, output mengikuti status variabel out1, out2, dst.
    digitalWrite(R1, LOW);
    digitalWrite(R2, LOW);
    digitalWrite(RR1, LOW);
    digitalWrite(RR2, LOW);
    Serial.println("All outputs are set to LOW (isOn = false)");
  }
}
#endif
