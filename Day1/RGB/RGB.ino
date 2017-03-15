/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int rgb[3] = {3,5,6};
int i;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (i = 0; i < 3; ++i)
  {
  	pinMode(rgb[i], OUTPUT);     
  }
  
}

// the loop routine runs over and over again forever:
void loop() {
  analogWrite(rgb[0],24);  //green
  analogWrite(rgb[1],0);   //blue
  analogWrite(rgb[2],1);   //red
}
