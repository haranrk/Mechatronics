#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 8, 12, 13);

void lcd_display(String text, int x=0, int y=0)
{
  if((x==0)&&(y==0))
  {
    lcd.clear();
  }

  lcd.setCursor(x, y);
  lcd.print(text);
}

void calib_option()
{
  char opt;
  
  Serial.print("\n\n\nHow would you like to calibrate?");
  Serial.print("\n\n1.Manual");
  Serial.print("\n2.Auto");
  Serial.print("\n3.Skip calibration");
  Serial.print("\n\nEnter your choice");

  lcd_display("1.Manual");
  lcd_display("2.Auto", 8, 0);
  lcd_display("3.Skip", 0, 1);

  while(true)
  {
    opt=Serial.read();

    if(opt=='1')
    {
      Serial.print("\n\nManual Calibration");
      lcd_display("Manual");
      lcd_display("Calibration", 0, 1);
      
      manualCalibrate();
      break;
    }
    else if(opt=='2')
    {
      Serial.print("\n\nAuto Calibration");
      lcd_display("Auto");
      lcd_display("Calibration", 0, 1);
      
      autoCalibrate();
      break;
    }
    else if(opt=='3')
    {
      Serial.print("\n\nCalibration skipped");
      lcd_display("Calibration");
      lcd_display("skipped", 0, 1);
      
      break;
    }
  }
}

void col_option()
{
  bool valid=false;
  char pick_col, drop_col;
  
  Serial.print("\n\n\n\nEnter pickup colour (r/g/b)");
  lcd_display("Enter pickup");
  lcd_display("colour (r/g/b)", 0, 1);

  while(!valid)
  {
    pick_col=Serial.read();

    switch(pick_col)
    {
      case 'r':
      case 'R':
      lcd_display("Red");
      
      location[0]=0;
      valid=true;
      break;
      
      case 'g':
      case 'G':
      lcd_display("Green");
      
      location[0]=1;
      valid=true;
      break;
      
      case 'b':
      case 'B':
      lcd_display("Blue");
      
      location[0]=2;
      valid=true;
    }
  }

  delay(2000);
  Serial.print("\n\nEnter drop colour (r/g/b)");
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
      lcd_display("Red");
      
      location[1]=0;
      valid=true;
      break;
      
      case 'g':
      case 'G':
      lcd_display("Green");
      
      location[1]=1;
      valid=true;
      break;
      
      case 'b':
      case 'B':
      lcd_display("Blue");
      
      location[1]=2;
      valid=true;
    }
  }
}

void setup() {
  lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:

}
