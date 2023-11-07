#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

template <Type>

void print(Type out){
    lcd.print(out);
}

void setCursor(uint8_t Y, uint8_t X){
    lcd.setCursor(Y, X);
}

void LCD_INIT(){
    lcd.init();		//Инициализация дисплея
	lcd.backlight();
}

void setCursorHome(){
    lcd.home();
}

void clear(){
    lcd.clear();
}

#endif