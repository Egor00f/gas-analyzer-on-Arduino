/*
	Датчик газа:  MQ-2
	LCD:          1602
*/

//если меньше этого занчения то OK, больше Control
#define MIN_GAS 350
//больше этого значения Critical
#define MAX_GAS 500



#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Thread.h>


//пины
#define LED_PIN_RED   3
#define LED_PIN_YELOW 4
#define LED_PIN_GEEN  5
#define MQ2_PIN       A0
#define BUZER_PIN     6

//Звук
#define SOUNDSPEEDLOW   500
#define SOUNDSPEEDHIGHT 200

bool soundOn    = false;
bool soundSpeed = false;

Thread sound = Thread();

//lcd
LiquidCrystal_I2C lcd(0x27, 16,2);

void setup(){
	lcd.init();
  pinMode(LED_PIN, OUTPUT);
  sound.onRun(PlaySound);
}

void loop(){
  int gas = analogRead(MQ2_PIN);

	if(gas < MIN_GAS){
    lcd.print("OK");
    led(1);
    soundOn = false;
  }
  else if (gas > MIN_GAS and gas < MAX_GAS){
    lcd.print("Control");
    led(2);
    soundOn     = true;
    soundSpeed  = false;
  }
  else if(gas > MAX_GAS){
    lcd.print("Critical");
    led(3);
    soundOn     = true;
    soundSpeed  = true;
  }
}

//Просто переключает светодиоды
bool led(short code){
  if(code == 1){
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_YELOW, LOW);
    digitalWrite(LED_PIN_GREEN, HIGHT);
  }
  else if(code == 2){
    digitalWrite(LED_PIN_RED, LOW);
    digitalWrite(LED_PIN_YELOW, HIGHT);
    digitalWrite(LED_PIN_GREEN, LOW);
  }
  else if(code == 3){
    digitalWrite(LED_PIN_RED, HIGHT);
    digitalWrite(LED_PIN_YELOW, LOW);
    digitalWrite(LED_PIN_GREEN, LOW);
  }
  else{
    return 1;
  }
  return 0;
}

//звук
void PlaySound(){

  short DELAY = SOUNDSPEEDLOW;
  //функция запущена 
  while(true){
    if(soundOn){
      if(soundSpeed){
        DELAY = SOUNDSPEEDHIGHT;
      }
      else{
        DELAY = SOUNDSPEEDLOW;
      }
      tone(BUZER_PIN, 900);
    }
    delay(DELAY);
  }
}

