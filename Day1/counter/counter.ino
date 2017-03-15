int pi[3] = {13,12,11}, n=0,m=0,i, pins[3]={0,0,0};
void setup(){
	Serial.begin(9600);
	for (i = 0; i < 3; ++i)
  {
  	pinMode(pi[i], OUTPUT);     
  }
}

void loop(){
	pins[0] = pins[0]>0?0:1;
	if(n>0){
		pins[1] = pins[1]>0?0:1;
		n=0;
	}
	else
	n++;
	
	if(m>2){
		pins[2] = pins[2]>0?0:1;
		m=0;
	}
	else
	m++;
	for (i = 0; i < 3; ++i)
  {
  	digitalWrite(pi[i],pins[i]);     
  }
	delay(500);

}
