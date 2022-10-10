/**
 * @file simple-controller-v1.ino
 * @author BG5ABL (sakura@alleysakura.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int initStatus = 0;

void checkClearLcd() {
    if (initStatus == 0) {
        lcd.clear();
        initStatus = 1;
        lcd.setCursor(0, 0);
        lcd.print("AZ:");
        lcd.setCursor(0, 1);
        lcd.print("EL:");
    }
}

void onSerialCall() {
    String serialString;

    while (Serial.available()) {
        serialString = serialString + (char)Serial.read();
    }

    Serial.println(serialString);

    if (serialString.indexOf("AZ") > -1) {
        checkClearLcd();
        lcd.setCursor(0, 0);
        lcd.print(serialString);
        return;
    }

    if (serialString.indexOf("EL") > -1) {
        checkClearLcd();
        lcd.setCursor(0, 1);
        lcd.print(serialString);
        return;
    }
}

void setup() {
    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(1, 0);
    lcd.print("EME Controller");
    lcd.setCursor(0, 1);
    lcd.print("Waiting data...");
}

void loop() {
    if (Serial.available()) {
        onSerialCall();
    }
    delay(100);
}