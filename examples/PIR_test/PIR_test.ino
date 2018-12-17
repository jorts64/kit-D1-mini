const int buttonPin = D6;
const int ledPin = BUILTIN_LED;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);  // LED off
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, LOW);  // people detected, LED on
  } else {
    digitalWrite(ledPin, HIGH); // LED off
  }
}

