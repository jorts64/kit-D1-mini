int buzzer=D5; //Buzzer control port, default D5

void setup() {
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}

void loop() {
  for (int i=0;i<5;i++){
      analogWriteFreq(988);      // 988 Hz, nota Do
      analogWrite(buzzer, 512);  // ona simètrica
      delay(700);                // 0,7 s durada
      analogWrite(buzzer, 0);    // silenci
      delay(50);                 // 0,05 s
      analogWriteFreq(587);      // 587 Hz, nota Si
      analogWrite(buzzer, 512); 
      delay(700);
      analogWrite(buzzer, 0);
      delay(50);    
  }
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);     // silenci
  delay(5000);
}
