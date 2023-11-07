/*
	Датчик газа:  MQ-2
	LCD:          1602
	
	Код расчитан на чип atmega328p
	
*/

//конфиг
#include "config.h"


#include <EEPROM.h>

#include "led.h"
#include "rgbLed.h"
#include "button.h"
#include "lang.h"
#include "settings.h"
#include "display.h"
#include "globals.h"


void setup()
{
	
	LCD_INIT();
	
	//загрузка данных из EEPROM
	EEPROM.get(CONFIG_ADDR, config);
	
	setLang(config.lang, config.otherCharsetLoaded);
	
	//Если используются обычные светодиоды
	if (config.LEDS)
	{
		pinMode(pinR, OUTPUT);
		pinMode(pinG, OUTPUT);
		pinMode(pinY, OUTPUT);
	}
	
	
}

void loop()
{
	
	time = millis();				//Получение времени, нужно для работы звука
	
	int gas = analogRead(MQ2_PIN);	//получение данных с датчика
	
	if(gas < config.MAX_GAS)
	{
		
		print(OK_STR);											//сообщение на дисплее
		ledColor("G", config.LEDS, pinR, pinG, pinB, pinY);		//Светодиод
		soundOn = false;
	}
	else if (gas > config.MIN_GAS and gas < config.MAX_GAS)
	{
		
		print(CONTROL_STR);										//сообщение на дисплее
		ledColor("Y", config.LEDS, pinR, pinG, pinB, pinY);		//Светодиод
		soundOn     = true;				//Включение звука
		soundSpeed  = false;
	}
	else if(gas > config.MAX_GAS)
	{
		
		print(CRITICAL_STR)		//сообщение на дисплее
		ledColor("R", config.LEDS, pinR, pinG, pinB, pinY);		//Светодиод
		soundOn     = true;				//Включение звука
		soundSpeed  = true;
	}
	//Переход в настройка
	if(centerButton.click()) {
		Settings();
	}
	//Вклбючение/выключение звука
	else if(leftButton.click() or rightButton.click()) {
		mute = !mute;
	}
	
	//если беззвучный режим включен, не надо воспроизводить звук
	if (!mute) {
		PlaySound();
	}
}



//Воспроизводит Звук
void PlaySound(){
	
	
	if (time % DELAY) {
		//Если звук включен
		if (soundOn) {
			//Проверка быстриц или медленный писк
			if (soundSpeed) {
				DELAY = SOUNDSPEEDHIGH; //переключение на частый писк
			}
			else {
				DELAY = SOUNDSPEEDLOW; //переключение на редкий писк
			}
			tone(BUZER_PIN, FREQ); //само воспроизведение звука
		}
	}
}
