//#include <Servo.h>
//Servo myservo; int whitePos = 100;
int colorSensorPins[3] = {9,10,11};  //r,g,b,LDR
int ldrPin = A2; //LDR pin
int rgb[3] = {0,0,0};
int delayTime = 1000;
int maxi,flag = 1, maxv, steps = 2, t = 255;
void setup(){
	//myservo.attach(6);
	Serial.begin(9600);
	for (int i = 0; i < 3; ++i)
	{
		pinMode(colorSensorPins[i], OUTPUT);
	}
	pinMode(ldrPin,INPUT);
}

void loop(){
	autoCalibrate();
	//Serial.print("Done");
}

void manualCalibrate(){
	//myservo.write(whitePos);delay(100);//Rotate to white Patch
	allLow();
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
	Serial.println("Calibration begun");
	//myservo.write(whitePos);delay(100);//Rotate to white Patch


	allLow();Serial.println("allLow");

	for (int i = 0; i < 3; ++i)
		{
			digitalWrite(colorSensorPins[i],HIGH);
			delay(delayTime);
			rgb[i] = analogRead(ldrPin);
			digitalWrite(colorSensorPins[i],LOW);
                        rgbDisplay();
		}

		maxi = rgb[0]>rgb[1]?0:1;
		maxi = rgb[maxi]>rgb[2]?maxi:2;
		maxv = rgb[maxi];

		Serial.print("Maxi and maxv");Serial.println(maxi);																								//Begin 1
			maxi = iplus(maxi);
			digitalWrite(colorSensorPins[maxi], HIGH);delay(delayTime);
      ldrDisp();
			while(1){delay(delayTime);
			 	analogWrite(colorSensorPins[maxi],t);
                                t-= steps;
                                Serial.print("t: ");Serial.println(t);
				delay(delayTime);
				//rgbDisplay();
				ldrDisp();delay(delayTime);
			}
			digitalWrite(maxi, LOW);
			Serial.println("Done 1 Calibration");

	Serial.write("Calibration Done");
	rgbDisplay();
}

void allLow(){																										//Sets the RGB to LOW
	for (int i = 0; i < 3; ++i)
	{
		digitalWrite(colorSensorPins[i],LOW);
	}
}
void rgbDisplay(){															//Displays RGB values
	Serial.print("R: ");
	Serial.print(rgb[0]);
	Serial.print("  G: ");
	Serial.print(rgb[1]);
	Serial.print("  B: ");
	Serial.println(rgb[2]);
}
int iplus(int x){
	x++;
	Serial.println(x);
	if(x>2)
	return 0;
	else
	return x;
}

void ldrDisp(){
	Serial.print(maxv);Serial.print(" > "); Serial.println(analogRead(ldrPin));
}