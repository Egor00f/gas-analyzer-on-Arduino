#ifndef SETTINGS_H
#define SETTINGS_H

#include "lang.h"
#include "display.h"
#include "globals.h"

int control(int I, int minValue, int maxValue)
{
    //управление
	if(leftButton.click()) {
		I--;
	}
	else if (rightButton.click()) {
		I++;
	}
    //Проверка на выход за пределы обозначенных значений, тот самый бесконечный список
    if (i < minValue) {
		I = maxValue;
	}
	else if (i > maxValue) {
		I = minValue;
	}
    return I;
}

int setNumber(int number, int minValue, int maxValue)
{
    
    while (true){
        print(number);

        number = control(number, minValue, maxValue);

        if (centerButton.click()) {
            return number;
        }
    }
}

void Settings()
{
	clear();
	print(SETTINGS_STR);
	
	delay(200);

	
	uint8_t i = 0;
	
	#define SETTINGS_LIST_SIZE 4
	
	String names[SETTINGS_LIST_SIZE] = {MIN_GAS_STR, MAX_GAS_STR, SET_LANG_STR, EXIT_STR};
	
	//Выбор параметра
	while(true)
	{
		setCursor(1,1);
		print(names[i]);
		
        i = control(i, 0, SETTINGS_LIST_SIZE - 1);
		
		else if (centerButton.click()) {

			//Выход из настроек
            //EXIT_STR  должен быть в конце
			if (i == SETTINGS_LIST_SIZE - 1) {
				return;
			}
			
			//настройка самого параметра
			uint8_t j;
			
			uint16_t MinValue, MaxValue;
			
			char str;
			
			if (i == 0 or i == 1)//настройка пороговых значений
			{
				j = setNumber();
			}
			else if(i == 2) {
				MinValue = 0;
				MaxValue = 1;
				j = 1;
			}
			
			
			
			while(true)
			{
				setCursor(1,1);
				
				else if(i == 2)
				{
					
					if (j == 0) {
						str = 'E';
					}
					else {
						str = 'R';
					}
					
					if (str == 'E') {
						print("Eng");
                    }
					else if (str == 'R') {
						print("Rus");
                    }
				}
				//управление
				j = control(j, 0, 1)
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
            //Запись новых значений в переменные
			if (i == 0 or i == 1) {
				if (i == 0) {
					config.MIN_GAS = j;
                }
				else {
					config.MAX_GAS = j;
                }
			}
			else if (i == 2) { 
				config.lang = str;
			}
			
		}
		
		
	}
    //Сохранение
	EEPROM.put(CONFIG_ADDR, config);
	
}

#endif