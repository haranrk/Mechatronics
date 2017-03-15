int ldr=A3;
float val,thresh = 250;


void setup(){
	pinMode(A3,INPUT);
	Serial.begin(9600);
	pinMode(13, OUTPUT);
}

void loop(){
	val = analogRead(A3);
	Serial.println(val);
	if (val>thresh)
	{
		digitalWrite(13,HIGH);
	}
	else
	{
		digitalWrite(13,LOW);
	}
}
