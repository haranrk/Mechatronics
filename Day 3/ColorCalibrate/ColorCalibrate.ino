//#include <Servo.h>
//Servo myservo; int whitePos = 100;
int delayTime = 1000, steps = 2;																

int colorSensorPins[3] = {9,10,11};  //r,g,b,LDR
int colorSensorValues[3] = {255,255,255};
int ldrPin = A2; //LDR pin
int rgb[3] = {0,0,0}, buff = 0;		//buff is a variable that I use to store values temprorarily across code
int maxi,flag = 1, maxv, t = 255;

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
	
}

int sense(){
	allLow();
	int max = 0;
	return max;
}

void rgbCalc(){
	for (int i = 0; i < 3; ++i)
		{
			digitalWrite(colorSensorPins[i],HIGH);
			delay(delayTime);
			rgb[i] = analogRead(ldrPin);
			digitalWrite(colorSensorPins[i],LOW);
            
		}
	rgbDisplay();
}

void autoCalibrate(){
	Serial.println("<-Calibration begun->");
	//myservo.write(whitePos);delay(100);//Rotate to white Patch
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

void rgbDisplay(){			//Displays RGB values
	Serial.print("R: ");
	Serial.print(rgb[0]);
	Serial.print("  G: ");
	Serial.print(rgb[1]);
	Serial.print("  B: ");
	Serial.println(rgb[2]);
}

int iplus(int x){
	//Serial.println(x);
	x++;
	if(x>2)
	return 0;
	else
	return x;
}

void ldrDisp(){
	Serial.print(maxv);
	Serial.print(" > "); 
	Serial.print(buff); 
	Serial.print(" : "); 
	Serial.println(colorSensorValues[maxi]);
}

int iofmax(int x[]){
	int y = x[0]>x[1]?0:1;
	y = x[y]>x[2]?y:2;
	return y;
}

void manualCalibrate(){
	//myservo.write(whitePos);delay(100);//Rotate to white Patch
	allLow();
	while(!(Serial.read()=='1')){
		rgbCalc();
	}
}

/*

*/