#include <Servo.h>
Servo myservo; int whitePos = 100;
int colorSensorPins[3] = {13,12,11}  //r,g,b,LDR
int ldrPin = A1; //LDR pin
int rgb[3] = {0,0,0};
int delayTime = 50;
void setup(){
	myservo.attach(6);
	Serial.begin(9600);
	for (int i = 0; i < 3; ++i)
	{
		pinMode(colorSensorPins[i], OUTPUT);
	}
	pinMode(ldrPin,INPUT);
}

void loop(){
	
}

void manualCalibrate(){
	myservo.write(whitePos);delay(100);//Rotate to white Patch

	for (int i = 0; i < 3; ++i)
	{
		digitalWrite(colorSensorPins[i],LOW);
	}

	while(!(Serial.read()=='1')){
		for (int i = 0; i < 3; ++i)
		{
			digitalWrite(colorSensorPins[i],HIGH);
			delay(delayTime);
			rgb[i] = analogRead(ldrPin);
			digitalWrite(colorSensorPins[i],LOW);			
		}
		rgbDisplay();
	}
}

void autoCalibrate(){
	myservo.write(whitePos);delay(100);//Rotate to white Patch

	for (int i = 0; i < 3; ++i)
	{
		digitalWrite(colorSensorPins[i],LOW);
	}

	for (int i = 0; i < 3; ++i)
		{
			digitalWrite(colorSensorPins[i],HIGH);
			delay(delayTime);
			rgb[i] = analogRead(ldrPin);
			digitalWrite(colorSensorPins[i],LOW);			
		}
	rgbDisplay();
}
void rgbDisplay(){															//Displays RGB values
	Serial.print("R: ");
	Serial.print(rgb[0]);
	Serial.print("G: ");
	Serial.print(rgb[1]);
	Serial.print("B: ");	
	Serial.print(rgb[2]);
}