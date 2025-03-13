#ifndef MOTOR_H
#define MOTOR_H

#include "pin_setup.h"

// Fungsi untuk menggerakkan motor ke kiri (misalnya dengan PWM)
void moveUp() {
  if (t % 5 == 0){
    Serial.println("State berubah menjadi: UP");
   }
  setLED(5, false);
  setLED(4, true);
}

// Fungsi untuk menggerakkan motor ke kanan
void moveDown() {
   if (t % 5 == 0){
    Serial.println("State berubah menjadi: DOWN");
   }
  setLED(5, true);
  setLED(4, false);
}

// Fungsi untuk menghentikan motor
void stopMotor() {
    if (t % 5 == 0){
    Serial.println("State berubah menjadi: STOP");
   }
  setLED(5, false);
  setLED(4, false);
}

#endif
