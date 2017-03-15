#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 8, 7, 4, 2);
float val,count = 0,thresh = 200;
unsigned long start,time;

void setup() {
  
  lcd.begin(16, 2);
  pinMode(A3,INPUT);
  Serial.begin(9600);
 start = millis();
  lcd.print("hello, world!");
}

void loop() {
	time = millis();
  	if(time-start < 5000){
	val = analogRead(A3);
	if (val>thresh)
	{
		count++;
	}
	}
	Serial.println(count);
	lcd.clear();
	lcd.print(count);
    delay(500);
}

