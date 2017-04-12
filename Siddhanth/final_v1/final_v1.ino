#include <Servo.h>



int delay_time=500, grip_delay=1000;

Servo sweepservo, pickservo;
int sweep_pin=5, pick_pin=;
int angsweep, angpick, angoffset=90, angdrop=90;

int minval, mincol, detect_tolerance=;
bool first_check;

char opt, pick_col, drop_col;

int ldrpin=A2, ledpin[3]={9, 10, 11};
int i, input, maxcol;
int ldrval[3]={0, 0, 0}, maxval=0, ledset[3];
int calib_tolerance=0;

int gripper=, prox=;
int prox_thresh=;



void sweep(int position)
{
  sweepservo.attach(sweep_pin);
  sweepservo.write(position);
  delay(delay_time);
  sweepservo.detach();
}



void arm_rotate(int position)
{
  pickservo.attach(pick_pin);
  pickservo.write(position);
  delay(delay_time);
  pickservo.detach();
}



void zeropos()
{
  sweep(180);
}



void rgb_off()
{
  for(i=0;i<3;++i)
  {
    analogWrite(ledpin[i], 0);
  }
}



void rgb_calib_read()
{
  for(i=0;i<3;++i)
  {
    analogWrite(ledpin[i], 255);
    delay(delay_time);

    ldrval[i]=analogRead(ldrpin);
    delay(delay_time);

    analogWrite(ledpin[i], 0);
  }
}



void rgb_read()
{
  for(i=0;i<3;++i)
  {
    analogWrite(ledpin[i], ledset[i]);
    delay(delay_time);
    
    ldrval[i]=analogRead(ldrpin);
    delay(delay_time);
    
    analogWrite(ledpin[i], 0);
  }
}



void serial_display()
{
  Serial.print("\nR: ");
  Serial.print(ldrval[0]);
    
  Serial.print("\tG: ");
  Serial.print(ldrval[1]);
    
  Serial.print("\tB: ");
  Serial.print(ldrval[2]);
}



void ManualCalibrate()
{
  zeropos();
  
  rgb_off();

  Serial.print("\n\n\nEnter 'x' to escape calibration\n\n\n");    //Single quotes escape sequence?

  while((Serial.read()!='x')&&(Serial.read()!='X'))
  {
    rgb_calib_read();

    serial_display();
  }

  Serial.print("\n\n\nCalibration done!\n\n\n");

  for(i=0;i<3;++i)
  {
    ledset[i]=255;
  }
}



void var_intensity()
{
  input=255;
      
  //Serial.println("LDR\tMaxval");
      
  do
  {
    input-=2;

    analogWrite(ledpin[i], input);
    delay(delay_time);

    ldrval[i]=analogRead(ldrpin);
    delay(delay_time);

    //Serial.print(ldrval[i]);Serial.print("\t");Serial.println(maxval);
  }while(((maxval-ldrval[i])>calib_tolerance)&&(input>0));

  //Serial.print("\n\n\n\n\n");

  ledset[i]=input;
  analogWrite(ledpin[i], 0);
}



void AutoCalibrate()
{
  zeropos();
  
  rgb_off();

  rgb_calib_read();

  if(ldrval[0]>ldrval[1])
  {
    maxval=ldrval[0];
    maxcol=0;
  }
  else
  {
    maxval=ldrval[1];
    maxcol=1;
  }

  if(maxval<ldrval[2])
  {
    maxval=ldrval[2];
    maxcol=2;
  }
  
  for(i=0;i<3;++i)
  {
    if(i==maxcol)
    {
      ledset[i]=255;
    }
    else
    {
      var_intensity();
    }
  }
}



char coldetect()
{
  rgb_read();

  if(ldrval[0]<ldrval[1])
  {
    minval=ldrval[0];
    mincol=0;
  }
  else
  {
    minval=ldrval[1];
    mincol=1;
  }

  if(minval>ldrval[2])
  {
    minval=ldrval[2];
    mincol=2;
  }

  first_check=false;

  for(i=0;(i<3)&&(i!=mincol);++i)
  {
    if(((ldrval[i]-minval)<detect_tolerance))
    {
      if(first_check) return 'w';
      else first_check=true;
    }
  }

  switch(mincol)
  {
    case 0:return 'r';
    case 1:return 'g';
    case 2:return 'b';
  }
}



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



void find_col(char tocol)
{
  for(angsweep=180;angsweep>=0;--angsweep)
  {
    sweep(angsweep);

    if(coldetect()==tocol) return;
  }
  
  for(angsweep=0;angsweep<=180;++angsweep)
  {
    sweep(angsweep);

    if(coldetect()==tocol) return;
  }
}



void pick()
{
  sweep(angsweep-angoffset);

  for(angpick=0;angpick<=180;++angpick)
  {
    arm_rotate(angpick);

    if(analogRead(prox)>prox_thresh)
    {
      digitalWrite(gripper, HIGH);
      delay(grip_delay);
      break;
    }
  }

  arm_rotate(0);
}



void drop()
{
  sweep(angsweep-angoffset);
  
  arm_rotate(angdrop);
  
  digitalWrite(gripper, LOW);
  delay(grip_delay);

  arm_rotate(0);
}



void setup()
{
  pinMode(ldrpin, INPUT);
  pinMode(prox, INPUT);
  
  pinMode(ledpin[0], OUTPUT);
  pinMode(ledpin[1], OUTPUT);
  pinMode(ledpin[2], OUTPUT);
  pinMode(gripper, OUTPUT);
  
  Serial.begin(9600);
  digitalWrite(gripper, LOW);
}



void loop()
{
  calib_option();
  col_option();
  find_col(pick_col);
  pick();
  find_col(drop_col);
  drop();
}

