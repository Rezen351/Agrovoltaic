
#ifndef SENSOR_H
#define SENSOR_H

#define LDR1 34
#define LDR2 35
#define LS1 32
#define LS1 33

void setupSensor() {
  // Set LDR1, LDR2 as analog inputs
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);

  // Set LS1, LS2 as digital inputs
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  }


void readSensor() {
  int ldr1Value = analogRead(LDR1);  // Baca cahaya dari LDR1
  int ldr2Value = analogRead(LDR2);  // Baca cahaya dari LDR2

  int ls1State = digitalRead(LS1);  // Baca limit switch LS1
  int ls2State = digitalRead(LS2);  // Baca limit switch LS2

  // Cek apakah limit switch aktif
  if (ls1State == HIGH) {
    
    stopMotor();
  } else if (ls2State == HIGH) {
    
    stopMotor();
  } else {
   
    if (ldr1Value > ldr2Value) {
      
      moveUp();
    } else if (ldr2Value > ldr1Value) {
     
      moveDown();
    } else {
    
      stopMotor();
    }
  }
}

#endif 
