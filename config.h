/*
	Сей файл есмь конфиг всего проекта
	define только потому что при компиляции в прошивке не занимает места как константы
*/
#ifndef CONFIG_H
#define CONFIG_H

#include "led.h"


struct CONFIG {
	//Пороговые значения	
	int16_t MIN_GAS;
	int16_t MAX_GAS;

	bool LEDS;		//Светодиоды
	char lang;		//Язык
};
//==============CONFIG===========================

//если меньше этого занчения то OK, больше Control
#define DEFAULT_MIN_GAS 	350

//больше этого значения Critical
#define DEFAULT_MAX_GAS 	500


//ПИНЫ
#define MQ2_PIN				A0
#define BUZER_PIN			6

#define BUTTON_CENTER_PIN	4
#define BUTTON_LEFT_PIN		3
#define BUTTON_RIGHT_PIN	5


//светодиоды

#define RGBLED		false
#define STANDARTLED true
/*
	Можно использовать 3 цветных светодиода(красных, жёлтый и зелёный),
	а можно использовать RGB светодиод
	по умолчанию RGBLED
*/
#define DEFAULT_LED_TYPE  	RGBLED
#define LED_PIN_RED			13
#define LED_PIN_BLUE		11
#define LED_PIN_GREEN		12

#ifdef STANDARTLED
#define LED_PIN_YELLOW		11
#endif


//ЗВУК
//Как часто пищит пищания 
#define SOUNDSPEEDLOW   500
#define SOUNDSPEEDHIGH 200

//частота пищания
#define FREQ	900

//Адресс конфига в EEPROM
#define CONFIG_ADDR 0

//ЯЗЫК
#define DEFAULT_LANG "R"

//====================================================

#endif