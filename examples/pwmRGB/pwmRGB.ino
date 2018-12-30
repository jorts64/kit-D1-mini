void setup() {
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);
}

void loop() {
  int i,j,k;
  for (i=0;i<256;i+=10) {
    analogWrite(D6,i);
    for (j=0;j<256;j+=10){
      analogWrite(D7,j);
      for (k=0;k<256;k+=10) {
        analogWrite(D8,k);
        delay(1);
      }
    }
  }
}
