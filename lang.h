#ifndef LANG_H
#define LANG_H



String MIN_GAS_STR	= "";
String MAX_GAS_STR 	= "";

String SET_LANG_STR = "";
String DONE_STR		= "";

String OK_STR		= "";
String CONTROL_STR	= "";
String CRITICAL_STR	= "";
String SETTINGS_STR	= "";
String EXIT_STR		= "";

void setLang(char langCode, bool StringsetLoaded){

	
	//Настройка фраз
	if (langCode == 'R'){
		OK_STR			= "Нормально";
		MIN_GAS_STR 	= "Мин порог газа";
		MIN_GAS_STR 	= "Макс порог газа";
		SET_LANG_STR 	= "Изменить Язык";
		DONE_STR 		= "Готово!";
		CONTROL_STR		= "Контролируемо";
		CRITICAL_STR	= "ОПАСНО!";
		SETTINGS_STR	= "Настройки";
		EXIT_STR		= "Выход";
	}
	else if (langCode == 'E'){
		OK_STR			= "OK";
		MIN_GAS_STR 	= "Min";
		MIN_GAS_STR 	= "Max";
		SET_LANG_STR 	= "Set language";
		DONE_STR 		= "Done!";
		CONTROL_STR		= "Control";
		CRITICAL_STR	= "CRITICAL!";
		SETTINGS_STR	= "Settings";
		EXIT_STR		= "Exit";
	}
}

#endif