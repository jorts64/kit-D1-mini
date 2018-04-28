void setup() {
  pinMode(D5,OUTPUT);
}

void loop() {
  digitalWrite(D5,HIGH);
  delayMicroseconds(500);
  digitalWrite(D5,LOW);
  delayMicroseconds(500);
}
