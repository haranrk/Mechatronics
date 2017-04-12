#include <Servo.h>

int prox=A1, pick_pin=6, gripper=7;

Servo pickservo;

void arm_rotate(int position)
{
  int delay_time=500;
  
  pickservo.attach(pick_pin);
  pickservo.write(position);
  delay(delay_time);
  pickservo.detach();
}

void pick()
{
  //sweep(angsweep-angoffset);
  int prox_thresh=1022;
  int grip_delay=5000;

  for(int angpick=0;angpick<=180;angpick+=2)
  {
    arm_rotate(angpick);

    if(analogRead(prox)>=prox_thresh)
    {
      digitalWrite(gripper, HIGH);
      delay(grip_delay);
      break;
    }
  }

  arm_rotate(0);
}

void setup()
{
  Serial.begin(9600);
  pinMode(prox, INPUT);
  pinMode(gripper, OUTPUT);
}

void loop()
{
  delay(2000);
  digitalWrite(gripper, LOW);
  delay(2000);
  pick();
}

