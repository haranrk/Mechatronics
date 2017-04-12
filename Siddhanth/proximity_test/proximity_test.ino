int prox=A1;
int gripper=7;

void setup() {
  pinMode(prox, INPUT);
  pinMode(gripper, OUTPUT);
  Serial.begin(9600);
  digitalWrite(gripper, HIGH);
}

void loop() {
  Serial.println(analogRead(prox));
  delay(500);
}
