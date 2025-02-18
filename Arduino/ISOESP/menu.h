#ifndef MENU_H
#define MENU_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI   13
#define OLED_CLK    14
#define OLED_DC     5
#define OLED_CS     15
#define OLED_RESET  4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int currentPage = 0;
int subMenu = 0;
const int totalPages = 3;
const int subMenuLimits[] = {2, 1, 3}; // Number of submenus per menu

int currentMenu = 0;
bool inSettings = false;
int settingsPage = 0;
unsigned long lastUpdate = 0;
const unsigned long slideshowInterval = 3000;

int degree = 20;
int percent = 70;

int intervalON = 15;
int intervalOFF = 10;
int intervalminON = 10;
int intervalsecON = 15;
int intervalminOFF = 10;
int intervalsecOFF = 15;

// Temporary variables for settings editing:
int temp_intervalminON;
int temp_intervalsecON;
int temp_intervalminOFF;
int temp_intervalsecOFF;

void menu_setup() {
    if (!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.display();
    delay(100);
}

void menu_loop() {
    if (!inSettings) {
        if (millis() - lastUpdate > slideshowInterval) {
            currentMenu = (currentMenu + 1) % 3;
            lastUpdate = millis();
            drawSlideshow();
        }
    } else {
        drawSettings();
    }

    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        
        if (command == "next") {
            if (!inSettings) {
                // Enter settings mode and initialize temporary variables:
                inSettings = true;
                settingsPage = 0;
                temp_intervalminON = intervalminON;
                temp_intervalsecON = intervalsecON;
                temp_intervalminOFF = intervalminOFF;
                temp_intervalsecOFF = intervalsecOFF;
                drawSettings();
            } else if (settingsPage < 4) {
                // Move to next settings page:
                settingsPage = settingsPage + 1;
                drawSettings();
            } else { 
                // On the "Saved?" page, save the temporary values to the actual settings:
                intervalminON = temp_intervalminON;
                intervalsecON = temp_intervalsecON;
                intervalminOFF = temp_intervalminOFF;
                intervalsecOFF = temp_intervalsecOFF;
                inSettings = false;
                settingsPage = 0;  // Reset for next entry
                lastUpdate = millis();  // Reset slideshow timer to prevent flickering
                display.clearDisplay();
                drawSlideshow();
                delay(500);  // Short delay to prevent immediate override
            }
        } 
        else if (command == "prev" && inSettings) {
            if (settingsPage > 0){
                settingsPage = settingsPage - 1;
            } else {
                // If already on page 0, exit settings mode
                inSettings = false;
                settingsPage = 0;
                lastUpdate = millis();
                display.clearDisplay();
                drawSlideshow();
                delay(500);
            }
            drawSettings();
        } 
        else if (command == "up" && inSettings) {
            // Increase the corresponding variable (max 60)
            switch(settingsPage) {
                case 0:
                    if (temp_intervalminON < 60)
                        temp_intervalminON++;
                    break;
                case 1:
                    if (temp_intervalsecON < 60)
                        temp_intervalsecON++;
                    break;
                case 2:
                    if (temp_intervalminOFF < 60)
                        temp_intervalminOFF++;
                    break;
                case 3:
                    if (temp_intervalsecOFF < 60)
                        temp_intervalsecOFF++;
                    break;
                default:
                    break;
            }
            drawSettings();
        } 
        else if (command == "down" && inSettings) {
            // Decrease the corresponding variable (min 0)
            switch(settingsPage) {
                case 0:
                    if (temp_intervalminON > 0)
                        temp_intervalminON--;
                    break;
                case 1:
                    if (temp_intervalsecON > 0)
                        temp_intervalsecON--;
                    break;
                case 2:
                    if (temp_intervalminOFF > 0)
                        temp_intervalminOFF--;
                    break;
                case 3:
                    if (temp_intervalsecOFF > 0)
                        temp_intervalsecOFF--;
                    break;
                default:
                    break;
            }
            drawSettings();
        }
    }
}

void drawSlideshow() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 20);
    
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
        display.println("Interval");
        display.setCursor(50, 20);
        display.println("ON");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(intervalminON);
        display.setCursor(40,40);
        display.println(".");
        display.setCursor(48,40);
        display.println(intervalsecON);
        display.setCursor(85,40);
        display.println("M");
    } else if (currentMenu == 2) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("Interval");
        display.setCursor(50, 20);
        display.println("OFF");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(intervalminOFF);
        display.setCursor(40,40);
        display.println(".");
        display.setCursor(48,40);
        display.println(intervalsecOFF);
        display.setCursor(85,40);
        display.println("M");
    }
    display.display();
}

void drawSettings() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Settings Page");
    
    display.setCursor(0, 20);
    if (settingsPage == 0) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("Set Interval");
        display.setCursor(75, 20);
        display.println("ON");
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
        display.println("Set Interval");
        display.setCursor(75, 20);
        display.println("ON");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_intervalsecON);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("s");
    } else if (settingsPage == 2) {
        display.setTextSize(1);
        display.setCursor(0, 20);
        display.println("Set Interval");
        display.setCursor(75, 20);
        display.println("OFF");
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
        display.println("Set Interval");
        display.setCursor(75, 20);
        display.println("OFF");
        display.setTextSize(2);
        display.setCursor(20, 40);
        display.println(temp_intervalsecOFF);
        display.setCursor(40,40);
        display.println(".00");
        display.setCursor(85,40);
        display.println("s");
    } else if (settingsPage == 4) {
        display.setTextSize(2);
        display.setCursor(15, 40);
        display.println("Saved?");
    }
    display.display();
}

#endif
