/*
	Датчик газа:  MQ-2
	LCD:          1602
	
	Код расчитан на чип atmega328p
	
*/

//конфиг
#include "config.h"

//=================Глобальные переменные ======================================

//звук
bool soundOn    = false;		//по умолчанию звук не воспроизводим
bool soundSpeed = false;
uint16_t DELAY = SOUNDSPEEDLOW; //переменная для сохранения скорости пищания


#define CONFIG_ADDR 0
struct CONFIG{
	//Пороговые значения	
	int16_t MIN_GAS;
	int16_t MAX_GAS;

	bool LEDS;		//Светодиоды
	char lang;		//Язык
	bool otherCharsetLoaded;
};

bool mute = false;

uint8_t pinR = LED_PIN_RED;
uint8_t pinG = LED_PIN_GREEN;
uint8_t pinB = LED_PIN_BLUE;
#ifdef LED_PIN_YELLOW
uint8_t pinY = LED_PIN_YELLOW;
#endif
unsigned long time;
//==============================================================================

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Thread.h>
#include "led.h"
#include "rgbLed.h"
#include "button.h"
#include "lang.h"



//Управляющие кнопки
button leftButton(BUTTON_LEFT_PIN);
button rightButton(BUTTON_RIGHT_PIN);
button centerButton(BUTTON_CENTER_PIN);


//lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);


CONFIG config;	//Экземпляр настроек

void setup()
{
	
	lcd.init();		//Инициализация дисплея
	lcd.backlight();
	
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
		
		lcd.print(OK_STR);				//сообщение на дисплее
		ledColor("G", config.LEDS, pinR, pinG, pinB, pinY);		//Светодиод
		soundOn = false;
	}
	else if (gas > config.MIN_GAS and gas < config.MAX_GAS)
	{
		
		lcd.print(CONTROL_STR);			//сообщение на дисплее
		ledColor("Y", config.LEDS, pinR, pinG, pinB, pinY);		//Светодиод
		soundOn     = true;				//Включение звука
		soundSpeed  = false;
	}
	else if(gas > config.MAX_GAS)
	{
		
		lcd.print(CRITICAL_STR);		//сообщение на дисплее
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


void Settings()
{
	lcd.clear();
	lcd.print(SETTINGS_STR);
	
	delay(200);

	
	uint8_t i = 0;
	
	#define SETTINGS_LIST_SIZE 4
	
	String names[SETTINGS_LIST_SIZE] = {MIN_GAS_STR, MAX_GAS_STR, SET_LANG_STR, EXIT_STR};
	
	//Выбор параметра
	while(true)
	{
		lcd.setCursor(1,1);
		lcd.print(names[i]);
		
		
		//управление
		if(leftButton.click()) {
			i--;
		}
		else if (rightButton.click()) {
			i++;
		}
		else if (centerButton.click()) {

			//Выход из настроек
			if (i == SETTINGS_LIST_SIZE - 1){
				return;
			}
			
			//настройка самого параметра
			uint8_t j;
			
			uint16_t MinValue, MaxValue;
			
			char str;
			
			if (i == 0 or i == 1)
			{
				MinValue = 0;
				MaxValue = 1023;
				if (i == 0)
					j = config.MIN_GAS;
				else
					j = config.MAX_GAS;
			}
			else if(i == 2){
				MinValue = 0;
				MaxValue = 1;
				j = 1;
			}
			
			
			
			while(true)
			{
				lcd.setCursor(1,1);
				if (i == 0 or i == 1){
					lcd.print(j);
				}
				else if(i == 2)
				{
					
					if (j == 0){
						str = 'E';
					}
					else{
						str = 'R';
					}
					
					if (str == 'E')
						lcd.print("Eng");
					else if (str == 'R')
						lcd.print("Rus");
				}
				//управление
				if(leftButton.click()) {
					j--;
				}
				else if (rightButton.click()) {
					j++;
				}
				else if (centerButton.click()) {
					break;
				}
				
				if (j < MinValue) {
					j = MinValue;
				}
				else if (j > MaxValue) {
					j = MaxValue;
				}
			}
			if (i == 0 or i == 1){
				if (i == 0)
					config.MIN_GAS = j;
				else
					config.MAX_GAS = j;
			}
			else if (i == 2){
				config.lang = str;
			}
			
		}
		
		if (i < 0) {
			i = 0;
		}
		else if (i > SETTINGS_LIST_SIZE) {
			i = SETTINGS_LIST_SIZE;
		}
		
		
	}

	lcd.home();		//сохранение настроек
	lcd.print("Saving Settings");
	EEPROM.put(CONFIG_ADDR, config);
	lcd.print(DONE_STR);
}


//Воспроизводит Звук
void PlaySound(){
	
	
	if (time % DELAY) {
		//Если звук включен
		if(soundOn){
			//Проверка быстриц или медленный писк
			if(soundSpeed){
				DELAY = SOUNDSPEEDHIGH; //переключение на частый писк
			}
			else{
				DELAY = SOUNDSPEEDLOW; //переключение на редкий писк
			}
			tone(BUZER_PIN, FREQ); //само воспроизведение звука
		}
	}
}
