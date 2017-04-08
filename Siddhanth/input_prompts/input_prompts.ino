void calib_option()
{
  Serial.print("\n\n\nHow would you like to calibrate?");
  Serial.print("\n\n1.Manual");
  Serial.print("\n2.Auto");
  Serial.print("\n3.Skip calibration");
  Serial.print("\n\nEnter your choice\n\n\n");

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
  Serial.print("\n\n\nEnter pickup colour (r/g/b)");

  while(1)
  {
    pick_col=Serial.read();

    if(pick_col=='r'||pick_col=='g'||pick_col=='b')
    {
      break;
    }
  }
  
  Serial.print("\n\nEnter drop colour (r/g/b)\n\n\n");

  while(1)
  {
    drop_col=Serial.read();

    if(drop_col=='r'||drop_col=='g'||drop_col=='b')
    {
      break;
    }
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
