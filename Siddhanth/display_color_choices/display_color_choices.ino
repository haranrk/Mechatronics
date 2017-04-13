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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
