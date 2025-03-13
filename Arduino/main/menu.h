#ifndef MENU_H
#define MENU_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "data.h"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int currentMenu = 0;
bool inSettings = false;
int settingsPage = 0;
unsigned long lastUpdate = 0;
const unsigned long slideshowInterval = 2000;
int degree = 20;
int percent = 70;

int intervalminON = 0;
int intervalsecON = 10;
int intervalminOFF = 0;
int intervalsecOFF = 10;

// Variabel untuk menyimpan Start Time dan Stop Time
int startHour = 6, startMinute = 0;
int stopHour = 18, stopMinute = 0;

// Variabel sementara untuk pengaturan
int temp_intervalminON, temp_intervalsecON;
int temp_intervalminOFF, temp_intervalsecOFF;
int temp_startHour, temp_startMinute;
int temp_stopHour, temp_stopMinute;

// Variabel IO
extern int intervalOn, intervalOff;
extern bool isON;

void checkChange() {
    prefs.begin("data", true); // Mode baca

    // Membaca data dari Preferences
    // Memuat interval ON/OFF dalam detik dan mengonversinya kembali ke menit dan detik
    int intervalON = prefs.getInt("pintervalON", 600);
    int intervalOFF = prefs.getInt("pintervalOFF", 600);
    int storedMinON = intervalON / 60;
    int storedSecON = intervalON % 60;
    int storedMinOFF = intervalOFF / 60;
    int storedSecOFF = intervalOFF % 60;
    int storedStartH = prefs.getInt("pstartHour", startHour);
    int storedStartM = prefs.getInt("pstartMinute", startMinute);
    int storedStopH = prefs.getInt("pstopHour", stopHour);
    int storedStopM = prefs.getInt("pstopMinute", stopMinute);

    prefs.end(); // Tutup Preferences setelah membaca

    // Cek apakah ada perubahan dan update nilai jika berbeda
    if (intervalminON != storedMinON) intervalminON = storedMinON;
    if (intervalsecON != storedSecON) intervalsecON = storedSecON;
    if (intervalminOFF != storedMinOFF) intervalminOFF = storedMinOFF;
    if (intervalsecOFF != storedSecOFF) intervalsecOFF = storedSecOFF;
    if (startHour != storedStartH) startHour = storedStartH;
    if (startMinute != storedStartM) startMinute = storedStartM;
    if (stopHour != storedStopH) stopHour = storedStopH;
    if (stopMinute != storedStopM) stopMinute = storedStopM;
}


void drawSlideshow() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 0);
    display.println("RESUME");
    int count = isON ? intervalOn : intervalOff;
    // Konversi ke menit dan detik
    int minutes = count / 60;
    int seconds = count % 60;
    
    if (currentMenu == 0) {
        display.setTextSize(1);
        display.setCursor(75, 20);
        display.println("17.00");
        display.setCursor(0, 20);
        display.println("Sensor 1");
        display.setTextSize(2);
        display.setCursor(75, 45);
        display.println(percent);
        display.setCursor(100, 45);
        display.println("%");
        display.setTextSize(2);
        display.setCursor(0, 45);
        display.println(degree); 
        display.setCursor(25, 45);
        display.println("C");
    } else if (currentMenu == 1) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println(isON ? "-----Interval ON-----" : "-----Interval OFF----");
        display.setTextSize(2);
        display.setCursor(40, 40);
        display.print(minutes);
        display.print(":");
        if (seconds < 10) display.print("0"); // Tambahkan nol jika <10
        display.println(seconds);
    } else if (currentMenu == 2) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("-----Last Setting----");
        display.setTextSize(1.5);
        display.setCursor(0, 40);
        display.print("Interval ON"); display.setCursor(100, 40); display.print(intervalminON);  display.print(":"); if (intervalsecON < 10) display.print("0"); // Tambahkan nol jika <10
        display.println(intervalsecON);
        display.setCursor(0, 55);
        display.print("Interval OFF"); display.setCursor(100, 55); display.print(intervalminOFF);  display.print(":"); if (intervalsecOFF < 10) display.print("0"); // Tambahkan nol jika <10
        display.println(intervalsecOFF);

       
    }else if (currentMenu == 3) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("Start Time");
        display.setTextSize(2);
        display.setCursor(0, 40);
        if (startHour < 10) display.print("0");
        display.println(startHour);
        display.setCursor(23,40);
        display.println(":");
        display.setCursor(35,40);
        if (startMinute < 10) display.print("0");
        display.println(startMinute);
        display.setCursor(85,40);
        display.println("WIB");
    }
    else if (currentMenu == 4) {
       display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("Stop Time");
        display.setTextSize(2);
        display.setCursor(0, 40);
        if (stopHour < 10) display.print("0");
        display.println(stopHour);
        display.setCursor(23,40);
        display.println(":");
        display.setCursor(35,40);
        if (stopMinute < 10) display.print("0");
        display.println(stopMinute);
        display.setCursor(85,40);
        display.println("WIB");
    }
    display.display();
}
void drawSettings() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 0);
    display.println("SETTING");
    
    display.setCursor(0, 20);
    if (settingsPage == 0) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("----Set Interval ON----");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_intervalminON);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("M");
    } else if (settingsPage == 1) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("----Set Interval ON----");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_intervalsecON);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("S");
    } else if (settingsPage == 2) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("----Set Interval OFF---");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_intervalminOFF);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("M");
    } else if (settingsPage == 3) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("----Set Interval OFF---");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_intervalsecOFF);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("S");
        
    } else if (settingsPage == 4) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("---Set START Time---");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_startHour);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("H");
        
    } else if (settingsPage == 5) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("---Set START Time---");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_startMinute);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("M");
        
    } else if (settingsPage == 6) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("---Set STOP Time---");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_stopHour);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("H");
        
    } else if (settingsPage == 7) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("---Set STOP Time---");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_stopMinute);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("M");
        
    } else if (settingsPage == 8) {
        display.setTextSize(2);
        display.setCursor(30, 40);
        display.println("Saved?");
    }
    display.display();
}
void handleButtonPress() {
    int analogButton = readButton();
    
    if (analogButton > 1500 && analogButton < 2000) { // prev
        if (inSettings && settingsPage > 0) {
            settingsPage--;
        } else if (inSettings && settingsPage == 0) {
            inSettings = false;
            settingsPage = 0;
            lastUpdate = millis();
        }
    } 
    else if (analogButton > 1000 && analogButton <1300) { // down
        if (inSettings) {
            switch(settingsPage) {
                case 0: if (temp_intervalminON > 0) temp_intervalminON--; break;
                case 1: if (temp_intervalsecON > 0) temp_intervalsecON--; break;
                case 2: if (temp_intervalminOFF > 0) temp_intervalminOFF--; break;
                case 3: if (temp_intervalsecOFF > 0) temp_intervalsecOFF--; break;
                case 4: if (temp_startHour > 0) temp_startHour--; break;
                case 5: if (temp_startMinute > 0) temp_startMinute--; break;
                case 6: if (temp_stopHour > 0) temp_stopHour--; break;
                case 7: if (temp_stopMinute > 0) temp_stopMinute--; break;
            }
        }
    } 
    else if (analogButton > 800 && analogButton < 1000) { // up
        if (inSettings) {
            switch(settingsPage) {
                case 0: if (temp_intervalminON < 59) temp_intervalminON++; break;
                case 1: if (temp_intervalsecON < 59) temp_intervalsecON++; break;
                case 2: if (temp_intervalminOFF < 59) temp_intervalminOFF++; break;
                case 3: if (temp_intervalsecOFF < 59) temp_intervalsecOFF++; break;
                case 4: if (temp_startHour < 23) temp_startHour++; break;
                case 5: if (temp_startMinute < 59) temp_startMinute++; break;
                case 6: if (temp_stopHour < 23) temp_stopHour++; break;
                case 7: if (temp_stopMinute < 59) temp_stopMinute++; break;
            }
        }
    } 
    else if (analogButton > 590 && analogButton < 700) { // next
        if (!inSettings) {
            inSettings = true;
            settingsPage = 0;
            temp_intervalminON = intervalminON;
            temp_intervalsecON = intervalsecON;
            temp_intervalminOFF = intervalminOFF;
            temp_intervalsecOFF = intervalsecOFF;
            temp_startHour = startHour ;
            temp_startMinute = startMinute;
            temp_stopHour = stopHour;
            temp_stopMinute = stopMinute;
        } else if (settingsPage < 8) {
            settingsPage++;
        } else {
            intervalminON = temp_intervalminON;
            intervalsecON = temp_intervalsecON;
            intervalminOFF = temp_intervalminOFF;
            intervalsecOFF = temp_intervalsecOFF;
            startHour = temp_startHour;
            startMinute = temp_startMinute;
            stopMinute = temp_stopMinute;
            stopHour = temp_stopHour;
            inSettings = false;
            settingsPage = 0;
            lastUpdate = millis();
            //Simpan semua variabel ke preferense
            saveData();
        }
    }
    delay(200); // Debounce
}

void menu_setup() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.display();
    delay(1000);
    display.clearDisplay();
}

void menu_loop() {
    checkChange();
    handleButtonPress();
    if (!inSettings) {
        if (millis() - lastUpdate > slideshowInterval) {
            currentMenu = (currentMenu + 1) % 5;
            lastUpdate = millis();
            drawSlideshow();
        }
    } else {
        drawSettings();
    }
}


#endif
