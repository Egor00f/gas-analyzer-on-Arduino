#ifndef GLOBALS_H
#define GLOBALS_H

#include "config.h"
#include "button.h"


namespace global
{

	//звук
	soundOn    = false;//по умолчанию звук
	bool soundSpeed = false;

	uint16_t DELAY  = SOUNDSPEEDLOW; //переменная 	для сохранения скорости пищания

	unsigned long time;

	bool mute = false;


	uint8_t pinR = LED_PIN_RED;
	uint8_t pinG = LED_PIN_GREEN;
	uint8_t pinB = LED_PIN_BLUE;

	#ifdef LED_PIN_YELLOW
	uint8_t pinY = LED_PIN_YELLOW;
	#endif


	//Управляющие кнопки
	button leftButton(BUTTON_LEFT_PIN);
	button rightButton(BUTTON_RIGHT_PIN);
	button centerButton(BUTTON_CENTER_PIN);


	CONFIG config;	//Экземпляр настроек

}

#endif