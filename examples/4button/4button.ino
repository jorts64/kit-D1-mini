void setup() {
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  Serial.print("D1: ");
  if (digitalRead(D1)) {
    Serial.println("HIGH");
  }
  else {
    Serial.println("LOW");    
  }
  Serial.print("D2: ");
  if (digitalRead(D2)) {
    Serial.println("HIGH");
  }
  else {
    Serial.println("LOW");    
  }
  Serial.print("D5: ");
  if (digitalRead(D5)) {
    Serial.println("HIGH");
  }
  else {
    Serial.println("LOW");    
  }
  Serial.print("D6: ");
  if (digitalRead(D6)) {
    Serial.println("HIGH");
  }
  else {
    Serial.println("LOW");    
  }
  Serial.println("--------------------");    
  delay(2000);
 }
