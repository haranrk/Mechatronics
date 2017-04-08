
#include <Servo.h>
Servo myservo; int whitePos = 180;
int delayTime = 500, steps = 2;																

int colorSensorPins[3] = {9,10,11};  //r,g,b,LDR
int colorSensorValues[3] = {255,255,255};
int ldrPin = A2; //LDR pin
int rgb[3] = {0,0,0}, buff = 0;		//buff is a variable that I use to store values temprorarily across code
int maxi,flag = 1, maxv, t = 255;

void setup(){
	Serial.begin(9600);
	servoMove(whitePos);
	autoCalibrate();
}

void loop(){
	int random = sense();
}

int sense(){				//senses the color and returns the index of the colorPin
	allLow(); 
	rgbCalc();
	maxi = iofmin(rgb);
	colorPrint(maxi);
	return maxi;
}

void colorPrint(int x){  	//prints the color of corresponding color pin
	switch(x){
	case 0: Serial.println("#RED#");break;
	case 1: Serial.println("#GREEN#");break;
	case 2: Serial.println("#BLUE#");break;	
	}	
}

void rgbCalc(){				//calculates the rgb values at this instant
	for (int i = 0; i < 3; ++i)
		{
			analogWrite(colorSensorPins[i],255);
			delay(delayTime);
			rgb[i] = analogRead(ldrPin);
			digitalWrite(colorSensorPins[i],LOW);
            
		}
	rgbDisplay();		
}
void servoMove(int pos){			//Moves the servo to the position specified by value pos 
	Serial.println("Moving Servo....");
	int servoDelay = 2000;
	myservo.attach(5);
	myservo.write(pos);
	delay(servoDelay);
	myservo.detach();
	Serial.println("Servo moved");
}
void autoCalibrate(){
	Serial.println("<-Calibration begun->");
	servoMove(whitePos);								//Rotate to white Patch
	allLow();
	rgbCalc();
	maxi = iofmax(rgb);
	maxv = rgb[maxi];
	
	for (int xyz = 0; xyz < 2; ++xyz)
		{	
			maxi = iplus(maxi);														// maxv - Largest value
			digitalWrite(colorSensorPins[maxi], HIGH);								// maxi - pin index of largest LED value and incremented after that
      	
      		delay(delayTime);
      		buff = 0;
      		ldrDisp();
			while(buff<maxv)
				{
				 	delay(delayTime);
				 	analogWrite(colorSensorPins[maxi],colorSensorValues[maxi]);
            	    colorSensorValues[maxi] -= steps;
            	    delay(delayTime);
            	    buff = analogRead(ldrPin);
					ldrDisp();
				}
			rgb[maxi] = buff;
			digitalWrite(colorSensorPins[maxi], LOW);
			Serial.println("Done a Calibration");
		}

	rgbDisplay();
	Serial.println("<-Calibration Done->");
}

void allLow(){				//LOWs all the LED pins																								//Sets the RGB to LOW
	for (int i = 0; i < 3; ++i)
	{
		digitalWrite(colorSensorPins[i],LOW);
	}
}

void rgbDisplay(){			//displays RGB values
	Serial.print("R: ");
	Serial.print(rgb[0]);
	Serial.print("  G: ");
	Serial.print(rgb[1]);
	Serial.print("  B: ");
	Serial.println(rgb[2]);
}

int iplus(int x){			//increments by 1 in a ciruclar fashion of max 2 (i.e. 2+1 = 0)
	//Serial.println(x);
	x++;
	if(x>2)
	return 0;
	else
	return x;		
}

void ldrDisp(){				//displays the ldrpin value, the max value and the analod value
	Serial.print(maxv);
	Serial.print(" > "); 
	Serial.print(buff); 
	Serial.print(" : "); 
	Serial.println(colorSensorValues[maxi]);
}

int iofmax(int x[]){		//returns the index of the maximum value in the array
	int y = x[0]>x[1]?0:1;
	y = x[y]>x[2]?y:2;
	return y;		
}

int iofmin(int x[]){		//returns the index of the minimum value in the array
	int y = x[0]<x[1]?0:1;
	y = x[y]<x[2]?y:2;
	return y;
}

// void manualCalibrate(){
// 	allLow();
// 	while(!(Serial.read()=='1')){
// 		rgbCalc();
// 	}
// }

/*

*/
