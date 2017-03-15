String inp = "";
char c;
int val, swtchPin = 9;
bool StringComplete;

void setup(){
	Serial.begin(9600);
	pinMode(swtchPin, INPUT_PULLUP);
}

void loop(){
	val = digitalRead(swtchPin);
Serial.println(val);
}

void serialEvent(){
	while(Serial.available()){
		c = Serial.read();
	}
	inp+=c;
	if (c=='b')
	{
		StringComplete = true;
	}
}
