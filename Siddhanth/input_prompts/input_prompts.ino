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
  bool valid=false;
  char pick_col, drop_col;
  
  Serial.print("\n\n\nEnter pickup colour (r/g/b)");

  while(1)
  {
    pick_col=Serial.read();

    switch(pickcol)
    {
      case 'r':
      case 'R':
      location[0]=1;
      valid=true;
      break;
      
      case 'g':
      case 'G':
      location[0]=2;
      valid=true;
      break;
      
      case 'b':
      case 'B':
      location[0]=3;
      valid=true;
    }

    if(valid==true) break;
  }
  
  Serial.print("\n\nEnter drop colour (r/g/b)\n\n\n");
  valid=false;

  while(1)
  {
    drop_col=Serial.read();

    switch(dropcol)
    {
      case 'r':
      case 'R':
      location[1]=1;
      valid=true;
      break;
      
      case 'g':
      case 'G':
      location[1]=2;
      valid=true;
      break;
      
      case 'b':
      case 'B':
      location[1]=3;
      valid=true;
    }

    if(valid==true) break;
  }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
