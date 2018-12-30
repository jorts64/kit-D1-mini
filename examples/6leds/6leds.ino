void setup() {
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
}

void loop() {
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  delay(1000);
  digitalWrite(D2,HIGH);
  delay(1000);
  digitalWrite(D3,HIGH);
  delay(1000);
  digitalWrite(D4,HIGH);
  delay(1000);
  digitalWrite(D6,HIGH);
  delay(1000);
  digitalWrite(D7,HIGH);
  delay(1000);
  digitalWrite(D8,HIGH);
  delay(1000);
}
