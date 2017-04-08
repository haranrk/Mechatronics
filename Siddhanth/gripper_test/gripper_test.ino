int gripper=7;

void setup()
{
  pinMode(gripper, OUTPUT);
}

void loop()
{
  digitalWrite(gripper, HIGH);
  delay(1000);
  digitalWrite(gripper, LOW);
  delay(1000);
}
