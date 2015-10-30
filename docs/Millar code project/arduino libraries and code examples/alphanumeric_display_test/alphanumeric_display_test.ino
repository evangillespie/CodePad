
const byte SLR2016_D[] = {5, 6, 7, 8, 9, 10, 11};

#define SLR2016_A0 4
#define SLR2016_A1 3
#define SLR2016_WR 12
#define SLR2016_WR2 2

char msg[] = "       testing display  1   2   3     ;-)     ";

void setup() {

  for (byte i = 0; i < 7; i++) {
    pinMode(SLR2016_D[i], OUTPUT);
  }

  pinMode(SLR2016_A0, OUTPUT);
  pinMode(SLR2016_A1, OUTPUT);
  pinMode(SLR2016_WR, OUTPUT);
  pinMode(SLR2016_WR2, OUTPUT);

}

void loop() {

  for (byte p = 7; p <= 45; p++) {  
    
    /*the above code may need to be changed depending on the
    words you want scrolled. I've left 7 spaces in front and 
    behind the scroll. I change the 35 to one less digit than
    the total digits between the quotation marks. Otherwise,
    random characters have a tendency of showing up on the
    display */
  
    for (byte c = 0; c <= 7; c++) {
    
      digitalWrite(SLR2016_A0, bitRead(c, 0));
      digitalWrite(SLR2016_A1, bitRead(c, 1));
  
     for (byte i = 0; i < 7; i++) {
        digitalWrite(SLR2016_D[i], bitRead(msg[p-c], i));
      }
      
      if (c >= 4) {    
  digitalWrite(SLR2016_WR, LOW);
  digitalWrite(SLR2016_WR, HIGH); }
else {
  digitalWrite(SLR2016_WR2, LOW);
  digitalWrite(SLR2016_WR2, HIGH);
}
    }
  
    delay(250);
       }
}

