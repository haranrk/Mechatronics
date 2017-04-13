void potAdjust()
{
  Serial.print("\n\nSet all potentiometers to minimum (press 1 to continue)");
  lcd_display("Set pots");
  lcd_display("to minimum", 0, 1);

  while(Serial.read()!='1')
  {
    
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
