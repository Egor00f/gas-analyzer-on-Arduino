#include "Arduino.h"
#ifndef BUTTON_H
#define BUTTON_H

class button {
	private:
	uint16_t pin;	//пин кнопки
	uint32_t _tmr;
    bool _flag;
	
	public:
	//Конструктор
	button(uint16_t PIN){
		pin = PIN;
		pinMode(pin, INPUT);
	}
	

	//проверяет нажата ли кнопка + защита от дребезга
	bool click(){
		bool btnState = digitalRead(pin);
		if (!btnState and !_flag and millis() - _tmr >= 100) {
			_flag = true;
			_tmr = millis();
			return true;
		}
		if (!btnState and _flag and millis() - _tmr >= 500) {
			_tmr = millis ();
			return true;
		}
		if (btnState and _flag) {
			_flag = false;
			_tmr = millis();
		}
		return false;
	}
};

#endif