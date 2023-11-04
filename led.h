#ifndef LED_H
#define LED_H

#include "rgbLed.h"

#define RGBLED		false
#define STANDARTLED true


//Просто переключает светодиоды
//Аргументы:     Цвет   Тип Светодиода
void ledColor(char color, bool LEDS, uint8_t pinR, uint8_t pinG, uint8_t pinB, uint8_t pinY) {
	
	
	//Если используется RGBLED то его и преключать надо
	if (!LEDS) {
		rgbLed led(pinR, pinG, pinB, true);
		led.setColor(color);
	}
	//Иначе, просто 3 светодиода
	else { 
		//Да, светодиоды приходится переключать в ручную
		if (color == "R") {
			digitalWrite(pinR, 	HIGH);
			digitalWrite(pinY, LOW);
			digitalWrite(pinG, LOW);
		}
		else if (color == "Y") {
			digitalWrite(pinR,	LOW);
			digitalWrite(pinY, HIGH);
			digitalWrite(pinG, LOW);
		}
		else if (color == "G") {
			digitalWrite(pinR, 	LOW);
			digitalWrite(pinY, LOW);
			digitalWrite(pinG, HIGH);
		}
	}
}

#endif