const int buttonPin = D3;
const int ledPin = BUILTIN_LED;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(ledPin, HIGH);  // button released, LED off
  } else {
    digitalWrite(ledPin, LOW); // button pressed, LED on
  }
}
