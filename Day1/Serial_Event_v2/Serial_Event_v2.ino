
String inp = "";
bool inpComp = false, hold = false;
float num[2];
char c;
int numlength[2];
 
void setup(){
	Serial.begin(9600);
}

void loop(){
	if (inpComp)
	{	
		Serial.print("LDR: ");
		Serial.println(num[0]);
		Serial.print("POT: ");
		Serial.println(num[1]);
                inpComp = false;
	}

}

void serialEvent(){
	while(Serial.available()){
		c = Serial.read();
	}

	if (hold)
	{
		if (c=='b')
		  {	
		  	num[0] = inp.toInt();
		  	inp = "";
		  }
        else if(c=='c')
		{
			num[1] = inp.toInt();
            inpComp = true;
            hold = false;
	        inp = "";
		}
		else
		  {
	 	     inp += c;
		  }
	} 
	if (c == 'a')
		hold = true;
	
}



