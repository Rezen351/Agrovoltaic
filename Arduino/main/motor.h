#ifndef motor_H
#define motor_H
#include "pin_setup.h"
//extern int RLDR, LLDR;
extern int t;
enum State {UP, DOWN,STOP};
State currentState = STOP;

String readSerial() {
    String inputString = "";
    while (Serial.available()) {
        char receivedChar = Serial.read();
        if (receivedChar == '\n') { // Akhiri saat menemukan newline
            break;
        }
        inputString += receivedChar;
    }
    return inputString;
}

void updateState(String command) {
    if (command == "UP") {
        currentState = UP;
        Serial.println("State berubah menjadi: UP");
        setLED(5, false);
        setLED(4, true);
    } 
    else if (command == "DOWN") {
        currentState = DOWN;
        Serial.println("State berubah menjadi: DOWN");
        setLED(5, true);
        setLED(4, false);
    } 
    else if (command == "STOP") {
        currentState = STOP;
        Serial.println("State berubah menjadi: STOP");
        setLED(5, false);
        setLED(4, false);
    } 
    else {
        Serial.println("Perintah tidak dikenali!");
    }
}


void checkSensor(){


}

void motorAction(){


}

#endif