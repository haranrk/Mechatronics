#include <Servo.h> 

int c=A2,i, servopin = 5;
float val;
int rgb[3] = {3,5,6};
Servo myservo;

void setup(){
	pinMode(c,INPUT);
	for (i = 0; i < 3; ++i)
  	{
  		pinMode(rgb[i], OUTPUT);     
  	}
        myservo.attach(servopin);
  	Serial.begin(9600);
}

void loop(){
	val = analogRead(c);
	Serial.print(val);
        val = map(val, 0 ,1023,0,179);
        Serial.println(val);
        myservo.write(val);
        delay(15);
	analogWrite(rgb[0],val);



}
