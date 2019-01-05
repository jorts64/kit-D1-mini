const int buttonPin = D3;
const int ledPin = BUILTIN_LED;

void OTAwait();

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (digitalRead(buttonPin) == LOW){ 
    OTAwait();
    digitalWrite(ledPin, HIGH);
  }
  digitalWrite(ledPin, HIGH); 
  delay(300);
  digitalWrite(ledPin, LOW); 
  delay(300);
}
