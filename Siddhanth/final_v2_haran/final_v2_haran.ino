
#include <Servo.h>
#include <LiquidCrystal.h>
Servo pickservo; int pick_pin =  6,angoffset = 40, prox = A1, gripper = 7, grip_delay=5000, prox_thresh=1022, angdrop = 90;
LiquidCrystal lcd(2, 3, 4, 8, 12, 13);
//--------------------------------
Servo myservo; int whitePos = 180, servoSteps = -10, servoPos = 180;  //Big Servo
int delayTime = 500, steps = 2, senseThreshold = 69;																

int location[2];
int colorSensorPins[3] = {9,10,11};  //r,g,b,LDR
int colorSensorValues[3] = {255,255,255};  //230,175,255
int ldrPin = A2; //LDR pin
int rgb[3] = {0,0,0}, buff = 0;		//buff is a variable that I use to store values temprorarily across code
int maxi,flag = 1, maxv, t = 255;

void servoMove(int pos,int servoDelay=2000){			//Moves the servo to the position specified by value pos 
	Serial.println("Moving Servo....");
	//int servoDelay = 2000;
	myservo.attach(5);
	myservo.write(pos);servoPos = pos;
	delay(servoDelay);
	myservo.detach();
	Serial.println("Servo moved");
}
void setup(){
	Serial.begin(9600);
	pinMode(gripper, OUTPUT);
	lcd.begin(16, 2);
	//servoMove(whitePos);
}

void loop(){
  arm_rotate(0);
  calib_option();
	col_option();
	if(detectColor(location[0]))
	{
		Serial.print("------------At the Pickup location------");colorPrint(location[0]);
   pick();
	}
	if(detectColor(location[1]))
	{
		Serial.print("------------At the Drop location------");colorPrint(location[1]);
   drop();
	}
	
}

void arm_rotate(int position)
{
  int delay_time=500;
  
  pickservo.attach(pick_pin);
  pickservo.write(position);
  delay(delayTime);
  pickservo.detach();
}

void pick()
{
		
  servoMove(servoPos-angoffset);
  

  for(int angpick=0;;angpick+=2)
  {
    arm_rotate(angpick);

    if(analogRead(prox)>=prox_thresh)
    {
      digitalWrite(gripper, HIGH);
      delay(grip_delay);
      break;
    }

    if(angpick==120) angpick=0;
  }

  arm_rotate(0);
}
void drop()
{
  servoMove(servoPos-angoffset);
  
  arm_rotate(angdrop);
  
  digitalWrite(gripper, LOW);
  delay(grip_delay);

  arm_rotate(0);
}

void lcd_display(String text, int x=0, int y=0)
{
  if((x==0)&&(y==0))
  {
    lcd.clear();
  }

  lcd.setCursor(x, y);
  lcd.print(text);
}

int detectColor(int colorCode){				//keeps moving until it reaches the specified color
	while(colorCode != sense()){
	servoPos += servoSteps;
	if (servoPos<=0)
	{
		servoPos = 180;
	}
	servoMove(servoPos,1000);
	}
	return 1;
}

int sense(){				//senses the color and returns the index of the colorPin
	allLow(); 
	rgbCalc();
	maxi = iofmin(rgb);
	if (rgb[iplus(maxi)]-rgb[maxi]>=senseThreshold)
	{
		colorPrint(maxi);
		return maxi;
	}
	else
	{
		colorPrint(-1);
		return -1;
	}
}

void calib_option()
{
  char opt;
  
  Serial.print("\n\n\nHow would you like to calibrate?");
  Serial.print("\n\n1.Manual");
  Serial.print("\n2.Auto");
  Serial.print("\n3.Skip calibration");
  Serial.println("\n\nEnter your choice");

  lcd_display("1.Manual");
  lcd_display("2.Auto", 10, 0);
  lcd_display("3.Skip", 0, 1);

  while(true)
  {
    opt=Serial.read();

    if(opt=='1')
    {
      Serial.println("\nManual Calibration");
      lcd_display("Manual");
      lcd_display("Calibration", 0, 1);
      
      manualCalibrate();
      break;
    }
    else if(opt=='2')
    {
      potAdjust();
      
      Serial.println("\nAuto Calibration");
      lcd_display("Auto");
      lcd_display("Calibration", 0, 1);

      autoCalibrate();
      break;
    }
    else if(opt=='3')
    {
      Serial.println("\nCalibration skipped");
      lcd_display("Calibration");
      lcd_display("skipped", 0, 1);

      delay(2000);
      
      break;
    }
  }
}

void col_option()
{
  bool valid=false;
  char pick_col, drop_col;
  
  Serial.println("\n\nEnter pickup colour (r/g/b)");
  lcd_display("Enter pickup");
  lcd_display("colour (r/g/b)", 0, 1);

  while(!valid)
  {
    pick_col=Serial.read();

    switch(pick_col)
    {
      case 'r':
      case 'R':
      location[0]=0;
      valid=true;
      break;
      
      case 'g':
      case 'G':
      location[0]=1;
      valid=true;
      break;
      
      case 'b':
      case 'B':
      location[0]=2;
      valid=true;
    }
  }

  Serial.println("\nEnter drop colour (r/g/b)");
  lcd_display("Enter drop");
  lcd_display("colour (r/g/b)", 0, 1);
  
  valid=false;

  while(!valid)
  {
    drop_col=Serial.read();

    switch(drop_col)
    {
      case 'r':
      case 'R':
      location[1]=0;
      valid=true;
      break;
      
      case 'g':
      case 'G':
      location[1]=1;
      valid=true;
      break;
      
      case 'b':
      case 'B':
      location[1]=2;
      valid=true;
    }
  }

  displayColors();
}

void displayColors()
{
  Serial.print("\nPickup colour: ");
  lcd_display("Pickup:");
  
  switch(location[0])
  {
    case 0:
    Serial.println("Red");
    lcd_display("Red", 8, 0);
    break;
    
    case 1:
    Serial.println("Green");
    lcd_display("Green", 8, 0);
    break;
    
    case 2:
    Serial.println("Blue");
    lcd_display("Blue", 8, 0);
  }
  
  Serial.print("\nDrop colour: ");
  lcd_display("Drop:", 0, 1);
  
  switch(location[1])
  {
    case 0:
    Serial.println("Red");
    lcd_display("Red", 8, 1);
    break;
    
    case 1:
    Serial.println("Green");
    lcd_display("Green", 8, 1);
    break;
    
    case 2:
    Serial.println("Blue");
    lcd_display("Blue", 8, 1);
  }
}

void colorPrint(int x){  	//prints the color of corresponding color pin
	switch(x){
	case 0: Serial.println("#RED#");break;
	case 1: Serial.println("#GREEN#");break;
	case 2: Serial.println("#BLUE#");break;	
	case -1: Serial.println("#NONE#");
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

void potAdjust()
{
  Serial.print("\n\nSet all potentiometers to minimum (press 1 to continue)");
  lcd_display("Set pots");
  lcd_display("to minimum", 0, 1);

  while(Serial.read()!='1')
  {
    
  }
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

void manualCalibrate(){
  allLow();
  while(!(Serial.read()=='1')){
  rgbCalc();
  }
}

/*

*/
