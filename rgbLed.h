/*
	Класс для удобной работы с rgb светодиодом
	Предпологается что светодиод подключен к цифровым пинам
*/
#ifndef RGBLED_HPP
#define RGBLED_HPP

#include <Arduino.h>

class rgbLed{
	private:
	
	uint8_t pinR, pinG, pinB;				//Пины к которым подключен светодиод
	
	bool r, g, b;						//Цвета
	
	bool on = true; 					//Состояние светодиода (ВКЛ/ВЫКЛ)
	
	//Обновление состояния светодиода
	//Вызывается для применения любых изменений
	void update() { 
		if (on) {					//Если по настройкам включен
			digitalWrite(pinR, r);
			digitalWrite(pinG, g);
			digitalWrite(pinB, b);
		}
		else {						//Если по настройкам выключен, выключить
			digitalWrite(pinR, LOW);
			digitalWrite(pinG, LOW);
			digitalWrite(pinB, LOW);
		}
	}
	
	
	public:
	//Конструктор класса
	//  пины: красного         зелёного         синего   цветов. Включен ли светодиод по умолчанию
	rgbLed(uint8_t pinR = 0, uint8_t pinG = 0, uint8_t pinB = 0, bool Status = true){
		if (pinR == pinG and pinG == pinB) {
			pinMode(pinR, OUTPUT);
			pinMode(pinG, OUTPUT);
			pinMode(pinB, OUTPUT);
			on = Status;
		}
		update();
	}
	
	//Включение/выключение светодиода
	void Switch(){ //Инвертировать
		on = !on;
		update();
	}
	
	void Switch(bool newSatatus){ //Указать конкретное значение
		on = newSatatus;
		update();
	}
	
	//Изменить цвет RGB светодиода
	void setRGB(bool R, bool G, bool B){
		r = R;
		g = G;
		b = B;
		update();
	}
	
	/*
	функция переключает цвет по символьному коду
	Коды цветов:
	R - красный
	G - Зелёный
	B - синий
	Y - Жёлтый
	P - Фиолетовый
	W - Белый
	
	*/
	void setColor(char color) {
		if (color == "R") {
			setRGB(true, false, false);
		}
		else if (color == "G") {
			setRGB(false, true, false);
		}
		else if (color == "B") {
			setRGB(false, false, true);
		}
		else if (color == "Y") {
			setRGB(true, true, false);
		}
		else if (color == "P") {
			setRGB(true, false, true);
		}
		else if (color == "W") {
			setRGB(true, true, true);
		}
	}
	
};

#endif
