#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 8, 12, 13);

void lcd_display(String text, int x=0, int y=0)
{
  lcd.clear();
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
  Serial.print("\n\nEnter your choice\n\n\n");

  lcd_display("1.Manual");
  lcd_display("2.Auto", 0, 1);
  lcd_display("3.Skip", 8, 1);

  while(1)
  {
    opt=Serial.read();

    if(opt=='1')
    {
      ManualCalibrate();
      break;
    }
    else if(opt=='2')
    {
      AutoCalibrate();
      break;
    }
    else if(opt=='3')
    {
      break;
    }
  }
}

void col_option()
{
  bool valid=false;
  char pick_col, drop_col;
  
  Serial.print("\n\n\nEnter pickup colour (r/g/b)");
  lcd_display("Enter pickup colour (r/g/b)");

  while(1)
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

    if(valid==true) break;
  }
  
  Serial.print("\n\nEnter drop colour (r/g/b)\n\n\n");
  lcd_display("Enter drop colour (r/g/b)");
  valid=false;

  while(1)
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

    if(valid==true) break;
  }
}

void setup() {
  lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:

}
