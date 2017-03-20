#include <Servo.h>

Servo myservo;
int pos=10,delayTime = 2000;

void setup() {
  myservo.attach(6);
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);

  myservo.write(pos);
}

void loop() {
  while((digitalRead(7)&&digitalRead(8)))
  {
    Serial.println(pos);
  }

  if(!digitalRead(7))
  { Serial.println("At 1");
    if(pos<180)
    {
      pos+=10;
    }
    
    

    while(!digitalRead(7))
    {
      Serial.println("Done 1");
    }
    myservo.write(pos);delay(delayTime);
  }

  if(!digitalRead(8))
  { Serial.print("At 2");
    if(pos>0)
    {
      pos-=10;
    }
    
    

    while(!digitalRead(8))
    {
      Serial.println("Done 2");
    }
    myservo.write(pos);delay(delayTime);
  }
}
