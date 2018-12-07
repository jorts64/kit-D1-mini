int notes [36][3] =
{
{'8',B00100000,262}, // C5
{'(',B00100001,277}, // C5#
{'9',B00100010,294}, // D5
{')',B00100011,311}, // D5#
{'0',B00100100,330}, // E5
{'q',B00100101,349}, // F5
{'Q',B00100110,370}, // F5#
{'w',B00100111,392}, // G5
{'W',B00101000,415}, // G5#
{'e',B00101001,440}, // A5
{'E',B00101010,466}, // A5#
{'r',B00101011,494}, // B5
{'t',B00000000,523}, // C6
{'T',B00000001,554}, // C6#
{'y',B00000010,587}, // D6
{'Y',B00000011,622}, // D6#
{'u',B00000100,669}, // E6
{'i',B00000101,698}, // F6
{'I',B00000110,740}, // F6#
{'o',B00000111,784}, // G6
{'O',B00001000,831}, // G6#
{'p',B00001001,880}, // A6
{'P',B00001010,932}, // A6#
{'a',B00001011,988}, // B6
{'s',B00010000,1047}, // C7
{'S',B00010001,1109}, // C7#
{'d',B00010010,1175}, // D7
{'D',B00010011,1245}, // D7#
{'f',B00010100,1318}, // E7
{'g',B00010101,1396}, // F7
{'G',B00010110,1480}, // F7#
{'h',B00010111,1568}, // G7
{'H',B00011000,1661}, // G7#
{'j',B00011001,1760}, // A7
{'J',B00011010,1865}, // A7#
{'k',B00011011,1975}, // B7
};


int buzzer=D5; //Buzzer control port, default D5

String melodia1 = "oii paSdfgf dd ddsPpoP pp oipoyi ppoii paSdfgf dd ddsPpoP pp oipoyi ppp p dfgfd fdsd pp p dfgfd fsPf g s P poii paSdfgf dd ddsPpoPpp oipoyi ppp p dfgfd fdsd pp p dfgfd fsPf goii paSdfgf dd ddsPpoPpp oipoyi ppipoyi pp";

int melodia2[] = {0xEB,0xEB,0xEB,0xEC,0xEB,0xEB,0xEB,0xEC,0xEB,0xC2,0xE7,0xE9,0xAB,0xC0,0xC0,0x80,0xEB,0xEB,0xAB,0xEB,0xE9,0xE9,0xEB,0xA9,0xC2};

void playn (String melody) {
    for(int j=0; j<melody.length(); j++){
    int i;
    if ((melody.charAt(j)==' ')||(melody.charAt(j)=='|')) {
      if (melody.charAt(j)==' '){
        delay(300);        
      }
      else {
        delay(600);                
      }
    }
    else
    {
      for(i=0; notes[i][0]!=melody.charAt(j);i++);
      analogWriteFreq(notes[i][2]);
      analogWrite(buzzer, 512);
      delay(263);
      analogWrite(buzzer, 0);
      pinMode(buzzer, OUTPUT);
      digitalWrite(buzzer, LOW);
      delay(37);
    }
  }
}

void playp (int pmelody[], int n){
    for(int j=0; j<n; j++){
    int i,c,d;
    c = pmelody[j] & B00111111;
    d = 131;
    if (pmelody[j] & B01000000) d = d / 2;
    if (pmelody[j] & B10000000) d = d * 4;
    if (pmelody[j] & B11000000) d = d * 2;
    if ((c & B00001100)== B00001100) {
      delay (d);
    }
    else {
      for(i=0; notes[i][1]!=c;i++);
      analogWriteFreq(notes[i][2]);
      analogWrite(buzzer, 512);
      delay(d);
      analogWrite(buzzer, 0);
      pinMode(buzzer, OUTPUT);
      digitalWrite(buzzer, LOW);
      delay(d/7);    
    }
  }
}


void setup() {
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
}

void loop() {
  playn (melodia1);
  delay(5000);
  playp (melodia2, (sizeof(melodia2)/sizeof(int)));
  delay(5000);

}
