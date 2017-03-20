#include <Servo.h>

Servo myservo;
int pos=10,delayTime = 200;

void setup() {
  myservo.attach(6);
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  myservo.write(pos);
}

void loop()
{
 

  if(!digitalRead(7))
  {   
    
while(!digitalRead(7))
    {
      //Serial.println("Done 1");
    }
  pos=pos+5;  
    
  }
  Serial.println(pos);
  myservo.write(pos);delay(delayTime);
  
  
}
