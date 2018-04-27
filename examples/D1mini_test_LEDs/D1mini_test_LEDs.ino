void setup() {
  pinMode(D4,OUTPUT); // RED
  pinMode(D8,OUTPUT); // GREEN
}

void loop() {
  digitalWrite(D4,HIGH);
  digitalWrite(D8,LOW);
  delay(500);
  digitalWrite(D4,LOW);
  digitalWrite(D8,HIGH);
  delay(2000);
}
