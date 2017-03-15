#include <LiquidCrystal.h>
String inp = "", opt;
bool inpComp = false, hold = false;
float num[2];
char c;
int numlength[2];
LiquidCrystal lcd(2,3,4,8,12,13);
int swtch = 3;
float ldr;
int swtchval;

void setup(){
	Serial.begin(9600);
	lcd.begin(16, 2);
	lcd.print("Hello world");
    pinMode(swtch,INPUT);
    pinMode(A1,INPUT);

}

void loop(){	

	if (inpComp)
	{	
		Serial.print("LDR: ");
		Serial.println(num[0]);
		Serial.print("POT: ");
		Serial.println(num[1]);
        lcd.setCursor(0,1);
        lcd.clear();
		lcd.print("LDR:");
		lcd.print(num[0]);
        lcd.setCursor(0,1);
		lcd.print("POT: ");
		lcd.println(num[1]);
        inpComp = false;
	}
    ldr= analogRead(A3);
    swtchval = digitalRead(swtch);
    opt = "a" + String(ldr) + "b" + String(swtchval) + "c";      


}

void serialEvent(){
	while(Serial.available()){
		c = Serial.read();
	}

	if (hold)
	{
		if (c=='b')
		{	
			num[0] = inp.toInt();
			inp = "";
		}
                else if(c=='c')
		{
			num[1] = inp.toInt();
                        inpComp = true;
                        hold = false;
	                inp = "";
		}
		else
		{
	 	inp += c;
		}
	} 
	if (c == 'a')
		hold = true;
	
}



