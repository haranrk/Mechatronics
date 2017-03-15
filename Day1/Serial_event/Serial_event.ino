
String inp = "";
bool inpComp = false, hold = false;
char num[6];
char c;
 
void setup(){
	Serial.begin(9600);
}

void loop(){
	if (inpComp)
	{
		Serial.print("\t" + inp);
		inpComp = 0;
        inp = "";
        for (int i = 0; i < 3; ++i)
        {
        	Serial.print(num[i]);
        }
        Serial.print("\t");
        for (int i = 0; i < 3; ++i)
        {
        	Serial.print(num[i+3]);
        }
        Serial.println(inp);
	}

}

void serialEvent(){
	while(Serial.available()){
		c = Serial.read();
	}

	if (c == 'a')
		hold = true;
	
	if (hold)
	{
		inp += c;
		if(c=='c'){
			int length;
			if(inp.length()<9){
				for (int i = 0; i < 6; ++i)
					{
						num[i]='*';Serial.print("Hi");
					}
				}
				
			else{	
				for (int i = 0; i < 3; ++i)
					{
						num[i] = inp[i+1];
					}
				for (int i = 0; i < 3; ++i)
					{
						num[i+3] = inp[i+5];
					}
				}
            inpComp = true;
            hold = false;
	        inp = "";
		}
	}
	
}


